/*
 * TESTE MONSTRO
 * 
 */
//============================================================================================
//===BIBLIOTECAS===  
 #include <Keypad.h> // KEYPAD 4X4
 #include <Arduino.h>
 #include <SPI.h> //Protocolo de comunicação do display OLED  
 #include <U8g2lib.h> //Biblioteca para display monocromatico.
 #include <dht.h> // Sensor de umidade
  
//============================================================================================ 
//===MAPEAMENTO DE HARDWARE===

U8G2_SSD1306_128X64_NONAME_1_4W_SW_SPI u8g2(U8G2_R2, /* clock=*/ 18, /* data=*/ 23, /* cs=*/ 17, /* dc=*/ 16, /* reset=*/ 4); 

/* ===DEFINIÇÃO DAS PORTAS DO DISPLAY OLED===
CLOCK = SCL = Porta SPI fixa definida em cada processador.
DATA = SDA = MOSI = Porta SPI fixa definida em cada processador.
CS = CHIP SELECT = Pode ser qualquer I/O digital disponível.
DC = DATA COMAND = Pode ser qualquer I/O digital disponível.
RES = RESET = Pode ser qualquer I/O digital disponível, mas de preferencia para a I/O 4 no caso da ESP32
/*

/*
The first argument of the constructor assignes the basic layout for the display:

Layout              Description
U8G2_R0        No rotation, landscape
U8G2_R1        90 degree clockwise rotation
U8G2_R2        180 degree clockwise rotation
U8G2_R3        270 degree clockwise rotation
U8G2_MIRROR    No rotation, landscape, display content is mirrored (v2.6.x)
 * 
 */

//============================================================================================
//===VARIAVEIS GLOBAIS DO KEYPAD===
 
const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte rowPins[ROWS] = {26,25,33,32}; //Rows 0 to 3

byte colPins[COLS]= {27,14,12,13}; //Columns 0 to 3

//initializes an instance of the Keypad class

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

//============================================================================================
//=== DTH ===

dht   my_dht;                           //objeto para o DHT11

// --- Mapeamento de Hardware ---
#define    dht_pin    22   //pino de sinal do dht11 

// --- Protótipo das Funções ---
void disp_temp(); //mostrar a temperatura em Graus Celsius
void disp_umid(); //mostrar a umidade relativa do ar

// --- Variáveis Globais ---
int    temperatura = 0x00,   //armazena a temperatura
       umidade     = 0x00,   //armazena a umidade
       counter     = 0x00;   //contador auxiliar
              
//============================================================================================
//===CONFIGURAÇÕES INICIAIS===
 
 void setup() {
 
Serial.begin(115200); //INICIALIZAÇÃO DA PORTA SERIAL PARA DEBUG

u8g2.begin();  //INICIALIZAÇÃO DO DISPLAY

}
//If key is pressed, this key is stored in 'keypressed' variable 
//If key is not equal to 'NO_KEY', then this key is printed out 
//if count=17, then count is reset back to 0 (this means no key is pressed during the whole keypad scan process

void loop() {

//============================================================================================
//===LEITURA DO KEYPAD===
 char key = keypad.getKey();
  
  if (key){
    Serial.println(key);
  }

//============================================================================================
//===LEITURA DO VOLTIMETRO===

  int sensorValue = analogRead(34);
  float voltage = sensorValue * (3.3 / 4096.0);

//============================================================================================
//===LEITURA DO DTH===

   my_dht.read11(dht_pin);

   temperatura = my_dht.temperature;
   umidade     = my_dht.humidity;

  
//============================================================================================
//===PROGRAMAÇÃO DO DISPLAY===

  u8g2.firstPage();
  do {
    u8g2.setFont(u8g2_font_ncenB12_tr);
    
    u8g2.drawStr(0,15,"Tensao:");
    u8g2.drawStr(105,15,"V");
    u8g2.setCursor(68, 15);
    u8g2.print(voltage);

    u8g2.drawStr(0,30,"Umid:");
    u8g2.drawStr(105,30,"%");   
    u8g2.setCursor(68, 30);
    u8g2.print(umidade);

    u8g2.drawStr(0,45,"Temp:");
    u8g2.drawStr(105,45,"C");
    u8g2.setCursor(68, 45);
    u8g2.print(temperatura);
    
    u8g2.drawStr(0,60,"Hello World!");
  } while ( u8g2.nextPage() );
  delay(400);


  Serial.println(voltage);
  Serial.println(sensorValue);
 
  Serial.print(temperatura);
  Serial.println(" C");
  Serial.print(umidade);
  Serial.println(" %");

}
