 #include <Arduino.h>
 #include"MPU6050Functions.h"
// 5 6 7 8
// Define pins for DC motors and motor driver
#define IN1 3
#define IN2 5
#define IN3 6
#define IN4 9
// Define pins for ultrasonic sensors
//3 5 6 9 10 11

#define IRSR 2
#define IRSL 4
#define IRSF 11

int dir = 4;

void setup() {
    // Initialize pins for motor driver control
    pinMode(IN1, OUTPUT);
    pinMode(IN2, OUTPUT);
    pinMode(IN3, OUTPUT);
    pinMode(IN4, OUTPUT);

    // Initialize pins for ultrasonic sensors
    pinMode(IRSR, INPUT);
    pinMode(IRSL, INPUT);
    pinMode(IRSF, INPUT);
    delay(1000);

}

void loop() {

    dir = check_dir(digitalRead(IRSL), digitalRead(IRSF), digitalRead(IRSR)); // Swap left and right sensor values
    delay(100);
    switch (dir) 
    {
          case 1:
              Forward();
              break;
          case 2:
              turnRight();
              delay(500);
              break;
          case 3:
              turnLeft();
              break;
          case 4:
             Return();
              delay(1000);
              break;

    }
}

// Function to measure distance using the ultrasonic sensor
int check_dir(bool IRL, bool IRF, bool IRR) { // Swap IRL and IRR
    if ((IRL == false) && (IRR == false) && (IRF ==true)||((IRL == false) && (IRR == true) && (IRF=true ))||((IRL == true) && (IRR == true) && (IRF=true ))) 
    {
      //forward
        return 1;
    } 
         else if (( (IRL == false) && (IRR == true) && (IRF=false )))
    {
      //right
        return 2;
    } 
     else if (((IRL == true) && (IRR == true) && (IRF=false ))||((IRL == true) && (IRR == false) && (IRF ==false))||((IRL == true) && (IRR == false) && (IRF ==true))) 
    {
      //left
        return  3;
    }
    

   
    else if ((IRL == false) && (IRR == false) && (IRF ==false))
    {
        return 4;
    }
 
}
void Forward() {
    analogWrite(IN1, 150);
    analogWrite(IN2, 0);
    analogWrite(IN3, 160);
    analogWrite(IN4, 0);
}

void turnLeft() {
    analogWrite(IN1, 150);
    analogWrite(IN2, 0);
    analogWrite(IN3, 0);
    analogWrite(IN4, 160);
}

void turnRight() {
    analogWrite(IN1, 0);
    analogWrite(IN2, 150);
    analogWrite(IN3, 160);
    analogWrite(IN4, 0);
}

void Return() {
    analogWrite(IN1, 0);
    analogWrite(IN2, 150);
    analogWrite(IN3, 0);
    analogWrite(IN4, 160);
    
}

void Stop() {
    analogWrite(IN1, 0);
    analogWrite(IN2, 0);
    analogWrite(IN3, 0);
    analogWrite(IN4, 0);
}
