#include <Servo.h> 
#include "functions.h"
//Servo Motors PINS 3/5/6/9
#define SER_A_PIN 3
#define SER_B_PIN 5
#define SER_C_PIN 6
#define SER_D_PIN 9
//LED PINS 12/13
#define LED_WORKING 13
#define LED_STANDBY 12
#define INIT_ANGLE 90 //Defualt Angle 90 degree
int potpin = 0;  // Potentiometer input PIN 0
int SensVal[4]; // Servo Arrays for Store  Analog Value
int ist[4] ; // Servo Position After Mapping Analog Value 
int arrayStep=0;
int joint0[180];
int top = 179;
int recordButtonPin = 11;
int playButtonPin = 2;
int ste=0;
Servo servo_A,servo_B,servo_C,servo_D;
String readString;

void setup()
{
  pinMode(recordButtonPin, INPUT);
  pinMode(recordButtonPin, HIGH);
  pinMode(playButtonPin, INPUT);
  pinMode(LED_STANDBY, OUTPUT);
  pinMode(LED_WORKING, OUTPUT);
  servo_A.attach(SER_A_PIN); 
  servo_B.attach(SER_B_PIN); 
  servo_C.attach(SER_C_PIN);
  servo_D.attach(SER_D_PIN); 
  init_servo();
  Serial.begin(9600);
}
void loop()
{
    readpot();
    free_mode();
    while (digitalRead(recordButtonPin)==true)
        {
            working();
            readpot();
            free_mode();
            if(arrayStep<top)
                {
                    record();
                }
            arrayStep+=1;
            delay(100);
        }
    while (digitalRead(playButtonPin)==true)
         {
             working();
             if(ste<top)
                 {
                     play();
                     ste+=1;
                     delay(25);
                 }
             else ste=0;
         }



}
void working()
{
    Serial.println("Working ");
    digitalWrite(LED_WORKING, HIGH);
    digitalWrite(LED_STANDBY, LOW);
  
}
void init_servo()
{
    working();
    servo_A.write(INIT_ANGLE); 
    servo_B.write(INIT_ANGLE);
    servo_C.write(INIT_ANGLE); 
    servo_D.write(INIT_ANGLE);
    delay(2000);
    standby();
  
}


void standby()
{
    digitalWrite(LED_WORKING, LOW);
    digitalWrite(LED_STANDBY, HIGH);
   
}

void readpot()
{
    SensVal[0] = analogRead(potpin); 
    ist[0]  = map(SensVal[0], 0, 1023, 0, 180);     
}
void record()
{
    Serial.print("Recording: ");
    joint0[arrayStep] = ist[0];
    Serial.print("record arrayStep: ");
    Serial.println(arrayStep);
 
}

void play()
{
    servo_A.write( joint0[ste]);
}

void free_mode()
{
    servo_A.write(ist[0] );
}

