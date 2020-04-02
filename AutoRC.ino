#define PIXEL_PIN    10    // Digital IO pin connected to the NeoPixels.
#include <Adafruit_NeoPixel.h>
#define PIXEL_COUNT 6
int motor1Pin1 = 7; // pin 2 on L293D IC
int motor1Pin2 = 8; // pin 7 on L293D IC
int enable1Pin = 6; // pin 1 on L293D IC
int motor2Pin1 = 3; // pin 10 on L293D IC
int motor2Pin2 = 9; // pin 15 on L293D IC
int enable2Pin = 11; // pin 9 on L293D IC
int ledPin1 = 5;
int state;
int flag=0;        //makes sure that the serial only prints once the state
int stateStop=0;
const int speed = 100;

Adafruit_NeoPixel strip = Adafruit_NeoPixel(PIXEL_COUNT, PIXEL_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
    strip.begin();
    strip.show(); 
    // sets the pins as outputs:
    pinMode(ledPin1, OUTPUT);
    pinMode(motor1Pin1, OUTPUT);
    pinMode(motor1Pin2, OUTPUT);
    pinMode(enable1Pin, OUTPUT);
    pinMode(motor2Pin1, OUTPUT);
    pinMode(motor2Pin2, OUTPUT);
    pinMode(enable2Pin, OUTPUT);
    // sets enable1Pin and enable2Pin high so that motor can turn on:
    digitalWrite(enable1Pin, HIGH);
    digitalWrite(enable2Pin, HIGH);
    // initialize serial communication at 9600 bits per second:
    Serial.begin(9600);
}

void loop() {
    //if some date is sent, reads it and saves in state
    if(Serial.available() > 0){     
      state = Serial.read();   
      flag=0;
    }   
    // if the state is 'F' the DC motor will go forward
    if (state == 'F') {
        digitalWrite(motor1Pin1, speed);
        digitalWrite(motor1Pin2, LOW); 
        
        if(flag == 0){
          Serial.println("Go Forward!");
          flag=1;
        }
    }
    
    // if the state is 'R' the motor will turn left
    else if (state == 'R') {
        digitalWrite(motor1Pin1, HIGH); 
        digitalWrite(motor1Pin2, LOW); 
        digitalWrite(motor2Pin1, LOW);
        digitalWrite(motor2Pin2, LOW);
        if(flag == 0){
          Serial.println("Turn LEFT");
          flag=1;
        }
        delay(1500);
        state=3;
        stateStop=1;
    }
    // if the state is 'S' the motor will Stop
    else if (state == 'S' || stateStop == 1) {
        digitalWrite(motor1Pin1, LOW); 
        digitalWrite(motor1Pin2, LOW); 
        digitalWrite(motor2Pin1, LOW);
        digitalWrite(motor2Pin2, LOW);
        if(flag == 0){
          Serial.println("STOP!");
          flag=1;
        }
        stateStop=0;
    }
    // if the state is 'L' the motor will turn right
    else if (state == 'L') {
        digitalWrite(motor1Pin1, LOW); 
        digitalWrite(motor1Pin2, LOW); 
        digitalWrite(motor2Pin1, LOW);
        digitalWrite(motor2Pin2, HIGH);
        if(flag == 0){
          Serial.println("Turn RIGHT");
          flag=1;
        }
        delay(1500);
        state=3;
        stateStop=1;
    }
    // if the state is 'B' the motor will Reverse
    else if (state == 'B') {
        digitalWrite(motor1Pin1, LOW); 
        digitalWrite(motor1Pin2, HIGH);
        
        if(flag == 0){
          Serial.println("Reverse!");
          flag=1;
        }
    }

    else if (state == 'E') {
        digitalWrite(ledPin1, HIGH); 
    }

    else if (state == 'A') {
        digitalWrite(ledPin1, LOW); 
    }


    else if (state == 'l') {
      uint16_t i, j;
        for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
    }
    strip.show();
    delay(9);
     }
   }

   else if (state == 'M') {
      for(int i=0;i< strip.numPixels();i++){

    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
    strip.setPixelColor(i, strip.Color(0,150,0)); // Moderately bright green color.

    strip.show(); // This sends the updated pixel color to the hardware.

    delay(10); // Delay for a period of time (in milliseconds).

      }
    }

    else if (state == 'Z') {
      for(int i=0;i< strip.numPixels();i++){

    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
    strip.setPixelColor(i, strip.Color(0,0,255)); // Moderately bright green color.

    strip.show(); // This sends the updated pixel color to the hardware.

    delay(10); // Delay for a period of time (in milliseconds).

      }
    }
    
}

uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}
