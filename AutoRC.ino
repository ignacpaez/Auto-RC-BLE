#define PIXEL_PIN    10    // pin conectado a la tira NeoPixels.
#include <Adafruit_NeoPixel.h>
#define PIXEL_COUNT 6  //leds rgb
int motor1Pin1 = 7; // pin 7 en L293D
int motor1Pin2 = 8; // pin 8 en L293D 
int enable1Pin = 6; // pin 6 en L293D 
int motor2Pin1 = 3; // pin 3 en L293D 
int motor2Pin2 = 9; // pin 9 en L293D 
int enable2Pin = 11; // pin 11 en L293D 
int ledPin1 = 5;
int state;
int flag=0;        //estado nivel 0
int stateStop=0;
const int speed = 100;

Adafruit_NeoPixel strip = Adafruit_NeoPixel(PIXEL_COUNT, PIXEL_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
    strip.begin();
    strip.show(); 
    // setear puertos de salida
    pinMode(ledPin1, OUTPUT);
    pinMode(motor1Pin1, OUTPUT);
    pinMode(motor1Pin2, OUTPUT);
    pinMode(enable1Pin, OUTPUT);
    pinMode(motor2Pin1, OUTPUT);
    pinMode(motor2Pin2, OUTPUT);
    pinMode(enable2Pin, OUTPUT);
    // setear puertos a encendido
    digitalWrite(enable1Pin, HIGH);
    digitalWrite(enable2Pin, HIGH);
    // puerto para iniciar
    Serial.begin(9600);
}

void loop() {
    //estado para las acciones de receptor
    if(Serial.available() > 0){     
      state = Serial.read();   
      flag=0;
    }   
    // F para retroceder
    if (state == 'F') {
        digitalWrite(motor1Pin1, speed);
        digitalWrite(motor1Pin2, LOW); 
        
        if(flag == 0){
          Serial.println("Go Forward!");
          flag=1;
        }
    }
    
    // R para izquierda
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
    // S para detener
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
    // L para derecha
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
    // B para reversa
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
        for(j=0; j<256*5; j++) { // 5 ciclos para los colores en cascada
    for(i=0; i< strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
    }
    strip.show();
    delay(9);
     }
   }

   else if (state == 'M') {
      for(int i=0;i< strip.numPixels();i++){
          
    strip.setPixelColor(i, strip.Color(0,150,0)); 
    strip.show(); 
    delay(10); 
      }
    }

    else if (state == 'Z') {
      for(int i=0;i< strip.numPixels();i++){

    strip.setPixelColor(i, strip.Color(0,0,255));
    strip.show(); 
    delay(10);
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
