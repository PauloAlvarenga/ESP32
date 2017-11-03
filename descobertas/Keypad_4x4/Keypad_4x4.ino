#include <Keypad.h>

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

void setup() {

Serial.begin(115200);

}

//If key is pressed, this key is stored in 'keypressed' variable //If key is not equal to 'NO_KEY', then this key is printed out //if count=17, then count is reset back to 0 (this means no key is pressed during the whole keypad scan process


// ========================================================================================================
// --- Loop Infinito ---  
void loop(){


// ========================================================================================================
// --- LEITURA DO KEYPAD --- 
  char key = keypad.getKey();
  
  if (key){
    Serial.println(key); //DEBUG DO KEYPAD NA SERIAL
  }

// ========================================================================================================
// --- PROGRAMAÇÃO DO DISPLAY --- 
  u8g2.firstPage();
  do {
    u8g2.setFont(u8g2_font_ncenB14_tr);
    u8g2.drawStr(0,15,"Hello World!");
    u8g2.drawStr(0,30,"Hello World!");
    u8g2.drawStr(0,45,"Hello World!");
    u8g2.drawStr(0,60,"Hello World!");
  } while ( u8g2.nextPage() );
  delay(1000);

  
}

