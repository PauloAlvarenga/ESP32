/*********************************************************************
This is an example for our Monochrome OLEDs based on SSD1306 drivers

  Pick one up today in the adafruit shop!
  ------> http://www.adafruit.com/category/63_98

This example is for a 128x64 size display using SPI to communicate
4 or 5 pins are required to interface

Adafruit invests time and resources providing this open source code, 
please support Adafruit and open-source hardware by purchasing 
products from Adafruit!

Written by Limor Fried/Ladyada  for Adafruit Industries.  
BSD license, check license.txt for more information
All text above, and the splash screen must be included in any redistribution
*********************************************************************/


#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <dht.h>

// ========================================================================================================
// --- Definições e Objetos ---
#define OLED_MOSI   23
#define OLED_CLK   18
#define OLED_DC    16
#define OLED_CS    17
#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);
dht   my_dht;                           //objeto para o DHT11


/* Uncomment this block to use hardware SPI
#define OLED_DC     16
#define OLED_CS     17
#define OLED_RESET  4
Adafruit_SSD1306 display(OLED_DC, OLED_RESET, OLED_CS);
*/

#if (SSD1306_LCDHEIGHT != 64)
//#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif

// ===============================================================================
// --- Mapeamento de Hardware ---
#define    dht_pin    22   //pino de sinal do dht11 
// ========================================================================================================
// --- Protótipo das Funções ---
void disp_temp(); //mostrar a temperatura em Graus Celsius
void disp_umid(); //mostrar a umidade relativa do ar


// ========================================================================================================
// --- Variáveis Globais ---
int    temperatura = 0x00,   //armazena a temperatura
       umidade     = 0x00,   //armazena a umidade
       counter     = 0x00;   //contador auxiliar





void setup()   {                
  Serial.begin(115200);
      pinMode(2, OUTPUT);  //saída digital 2 (LED onboard)
  // by default, we'll generate the high voltage from the 3.3v line internally! (neat!)
  display.begin(SSD1306_SWITCHCAPVCC);
  // init done
  
  // Show image buffer on the display hardware.
  // Since the buffer is intialized with an Adafruit splashscreen
  // internally, this will display the splashscreen.
  display.display();
  delay(200);

}

void loop() {

  int sensorValue = analogRead(34);
  float voltage = sensorValue * (3.16 / 4096.0);

     my_dht.read11(dht_pin);

   temperatura = my_dht.temperature;
   umidade     = my_dht.humidity;


    
 display.setTextSize(4);
  display.setTextColor(WHITE);
  display.setCursor(0,00);
  display.clearDisplay();
  display.print(voltage);
  display.print("V");
  display.display();
  delay(2000);


  display.clearDisplay();
  display.setTextSize(4);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.print(temperatura);
  display.print(" C");
  display.display();
  delay(2000);

  display.clearDisplay();
  display.setTextSize(4);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.print(umidade);
  display.print(" %");
  display.display();
  delay(2000);




   
  Serial.println(voltage);
  Serial.println(sensorValue);
 
   Serial.print(temperatura);
   Serial.print(" ");
   Serial.println(umidade);

}


