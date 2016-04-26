#include <Servo.h>

#define gate  A5
#define sensor A1

Servo myservo[2];  
     
#define upperClosed 0
#define lowerClosed 180

#define upperOpen 180
#define upperWipe 90

#define lowerOpen 0
#define lowerWipe 90

int irLevel = 0;

void setup() {

  //Serial.begin(9600);

  pinMode(gate, 1);
  
  myservo[0].attach(3);
  myservo[1].attach(4); 


  myservo[0].write(upperClosed);  
  myservo[1].write(lowerClosed);

  delay(1000);

  irLevel = analogRead(sensor);

}

void loop() {

  if (analogRead(sensor) > (irLevel + 100)) {

    while (analogRead(sensor) > (irLevel + 50)) { //Wait for hand to move
      delay(1000);      
    }

    delay(1000);
    cleaner();
    delay(2000);
    
    irLevel = analogRead(sensor);       //Check new level
    
  }

}


void cleaner() {

  digitalWrite(gate, 1);

  delay(100);

  myservo[0].write(upperOpen);  
  myservo[1].write(lowerWipe);

  int x = 0;
  int xx = 0;

  for (x = 0 ; x < 10 ; x++) {

    for (xx = 90 ; xx > 0 ; xx--) {

      delay(40);
      myservo[0].write(90 + xx);  
      myservo[1].write(xx);
      
    }
    
    for (xx = 0 ; xx < 90 ; xx++) {

      delay(40);
      myservo[0].write(90 + xx);  
      myservo[1].write(xx);
      
    }   
    
  }
  
  delay(1000);
  
  myservo[0].write(upperClosed);  
  myservo[1].write(lowerClosed);

  delay(2000);

  digitalWrite(gate, 0);
  
}

