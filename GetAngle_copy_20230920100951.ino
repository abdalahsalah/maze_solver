/***************************************************************************/
/******************         3LA ALLAH                  *********************/
/******************         YARAB TEMSHI               *********************/
/***************************************************************************/
#include <MPU6050_tockn.h>
#include <Wire.h>


MPU6050 mpu6050(Wire);

#define IN1 5
#define IN2 6
#define IN3 9
#define IN4 10
#define Speed_motor 200
// Define pins for IR sensors

#define IRR         4  
#define IRL         8
#define IRF         11

unsigned long startTime = 0;
bool isDelayed = false;




char dir='F';

void setup() {
    // Initialize pins for motor driver control
    pinMode(IN1, OUTPUT);
    pinMode(IN2, OUTPUT);
    pinMode(IN3, OUTPUT);
    pinMode(IN4, OUTPUT);


    pinMode(IRL, INPUT);
    pinMode(IRF, INPUT);
    pinMode(IRR, INPUT);
    // pinMode(INT_PINR, INPUT);
    // pinMode(INT_PINL, INPUT);
    // attachInterrupt(digitalPinToInterrupt(INT_PINL), ineruuptL, FALLING);
    Wire.begin();
    mpu6050.begin();
    mpu6050.calcGyroOffsets(-3.90,-0.40,0.21);
    delay(2000);

}

void loop() {

/***************************************************************************/
/******************         READ IR SENSOR             *********************/
/***************************************************************************/

    bool IR_L = digitalRead(IRL);
    bool IR_F = digitalRead(IRF);
    bool IR_R = digitalRead(IRR);
/***************************************************************************/

    dir = checkDir(IR_L, IR_F, IR_R);



     switch (dir) {
        case 'T':
            Return();
            Stop();
            delay(200);

            break;

        case 'R':
            delay(250);
            turnRight();
            // Stop();
            Forward();
            delay(200);
            Stop();
            delay(100);
            break;

        case 'L':
            // delay(100);
            turnLeft();
            // Stop();
            Forward();
            delay(200);
            Stop();
            delay(100);
            break;

        case 'F':
            Forward();
            break;

        case 'B':
            Back();
            break;
             
    }
}


/***************************************************************************/
/******************         CHECK DIRECTIONS           *********************/
/***************************************************************************/



char checkDir(bool IR_L, bool IR_F, bool IR_R)
{
  if (!IR_L && !IR_R && !IR_F)
        {
           return 'T';
        
        }
  else if ((!IR_L && !IR_R && IR_F) || (!IR_L && IR_R && IR_F))
  {
    // Check if the delay is already in progress
      return 'F';
  }
  else if ((IR_L && !IR_R && IR_F)||(IR_L && !IR_R && !IR_F)) 
        {
                  return 'L';
        
        } 
  else if ((!IR_L && IR_R && !IR_F)) 
        {
                  return 'R';
        
        } 
        
                  return 'F';

}

/***************************************************************************/
/******************         FUNCTION MOTORS            *********************/
/***************************************************************************/

void Back() {
    analogWrite(IN1, 0);
    analogWrite(IN2, Speed_motor);
    analogWrite(IN3, 0);
    analogWrite(IN4, Speed_motor-5);
}
void Forward() {
    analogWrite(IN1, Speed_motor);
    analogWrite(IN2, 0);
    analogWrite(IN3, Speed_motor-5);
    analogWrite(IN4, 0);
}

void Stop() {
    analogWrite(IN1, 0);
    analogWrite(IN2, 0);
    analogWrite(IN3, 0);
    analogWrite(IN4, 0);
} 

void turnLeft() {
  float Old_Angle = mpu6050.getAngleZ();
  while(1){
    mpu6050.update();
    float New_Angle = mpu6050.getAngleZ();
    analogWrite(IN1, 0);
    analogWrite(IN2, Speed_motor);
    analogWrite(IN3, Speed_motor);
    analogWrite(IN4, 0);
        if(abs(New_Angle - Old_Angle) >= 135.00) break;
  }
}



void turnRight() {
  float Old_Angle = mpu6050.getAngleZ();
  while(1){
    mpu6050.update();
    float New_Angle = mpu6050.getAngleZ();
    analogWrite(IN1, Speed_motor);
    analogWrite(IN2, 0);
    analogWrite(IN3, 0);
    analogWrite(IN4, Speed_motor);
        if(abs(New_Angle - Old_Angle) >= 135.00) break;


}
}

void Return() {
  float Old_Angle = mpu6050.getAngleZ();
  while(1){
  mpu6050.update();
    float New_Angle = mpu6050.getAngleZ();
    analogWrite(IN1, 0);
    analogWrite(IN2, Speed_motor);
    analogWrite(IN3, Speed_motor);
    analogWrite(IN4, 0);
        if(abs(New_Angle - Old_Angle) >= 280.00) break;
  }
}


/***************************************************************************/
/******************              THE END               *********************/
/***************************************************************************/

