
#include <ArduinoRS485.h>

#define LEDpinA 13 //PB5
#define LEDpinB 12 //PB4
#define LEDpinC 11 //PB3
#define LEDpinD 10 //PB2
boolean LEDpinA_state;
boolean LEDpinB_state;
boolean LEDpinC_state;
boolean LEDpinD_state;
int key = 0;
int temp;

void setup() {
  Serial.begin(9600);
  while (!Serial);

  RS485.begin(9600);

  // enable reception, can be disabled with: RS485.noReceive();
  RS485.receive();

  DDRB |= 0B00111100;  //port PB5,4,3,2 output
//  pinMode(LEDpinA, OUTPUT);
//  pinMode(LEDpinB, OUTPUT);
//  pinMode(LEDpinC, OUTPUT);
//  pinMode(LEDpinD, OUTPUT);
}

void loop() {
  if (RS485.available()) {
    key = RS485.read();
    Serial.write(key);
  }
  if (key == 'A'){
    PORTB = PORTB ^B00100000;  // Remember LED state, lit or unlit.
  }
  else if (key == 'B'){
    PORTB = PORTB ^B00010000;  // Remember LED state, lit or unlit.
  }
  else if (key == 'C'){
    PORTB = PORTB ^B00001000;  // Remember LED state, lit or unlit.
  }
  else if (key == 'D'){
    PORTB = PORTB ^B00000100;  // Remember LED state, lit or unlit.
  }
  else if (key == '#'){
    int count = 1;
    temp = PORTB;
    while (count<=5){
      PORTB = 0B00111100;
      delay(175);
      PORTB = PORTB ^ 0B00111100;
      delay(75);
      count++;
    }
    PORTB = temp;
  }        
  else if (key == '*'){
    int count = 1;
    temp = PORTB;
    while (count<=5){
      PORTB = 0B00100000;
      delay(50);
      PORTB = PORTB >>1;
      delay(50);
      PORTB = PORTB >>1;
      delay(50);
      PORTB = PORTB >>1;
      delay(50);
      PORTB = 0x00;
      delay(50);
      count++;
    }
    PORTB = temp;
  }
  Serial.write(key);
}