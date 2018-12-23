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
//Buttons PINS 2/11
#define RECORD_BUTT 11
#define PLAY_BUTT 2
#define INIT_ANGLE 90 //Defualt Angle 90 degree
uint16_t potpin = 0;  // Potentiometer input PIN 0
uint16_t SensVal[4]; // Servo Arrays for Store  Analog Value
uint16_t ist[4] ; // Servo to store position  after Mapping Analog Value 
uint16_t arrayStep=1; // Array change steps to store it in array steps 
uint16_t joint0[180]; // Array for Store steps for one servo 
uint16_t top = 179; // max steps
uint16_t ste=0;
Servo servo_A,servo_B,servo_C,servo_D;

void setup()
{
    pinMode(RECORD_BUTT, INPUT);
    pinMode(RECORD_BUTT, HIGH);
    pinMode(PLAY_BUTT, INPUT);
    pinMode(LED_STANDBY, OUTPUT);
    pinMode(LED_WORKING, OUTPUT);
    servo_A.attach(SER_A_PIN); 
    servo_B.attach(SER_B_PIN); 
    servo_C.attach(SER_C_PIN);
    servo_D.attach(SER_D_PIN); 
    init_servo(); // set & write all servo angle to INIT_ANGLE
    Serial.begin(9600);
}
void loop()
{
    // readpot(); 
    // free_mode();
    while (digitalRead(RECORD_BUTT)==true)
        {
            working();
            readpot();
            free_mode();
            // Check if Position changed joint0[arrayStep-1]!=ist[0]
            if(joint0[arrayStep-1]!=ist[0] && arrayStep<top )
                {
                    Serial.println( ist[0]);
                    Serial.println(   joint0[arrayStep-1] );
                    record();
                    arrayStep+=1;
                }
            
            delay(100);

        }
    while (digitalRead(PLAY_BUTT)==true)
                {
                    working();
                    if(ste<arrayStep)
                        {
                            play();
                            ste+=1;
                            delay(35);
                        }
            else ste=0;
        }



}
/* working() 
   funtion for turn on LED working
   when Servo  change angle */  
void working()
{
    Serial.println("Working nee ");
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
    Serial.print("Playing: ");
    servo_A.write( joint0[ste]);
    Serial.print(joint0[ste]);
}

void free_mode()
{
    servo_A.write(ist[0]);
}

