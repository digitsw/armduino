#include <Servo.h> 
#include "common.h"

uint16_t potpin = 0;  /* Potentiometer input PIN 0*/
uint16_t val[4]; /* Servo array to store the analog values */
uint16_t map_val[4] ; /* Servo array to store the position after mapping the analog value */
uint16_t step=1; /* Array's "change steps" to store it in array steps */
uint16_t sero_pos[180]; /* An array  Store the steps for a one servo*/ 
uint16_t step_max = 179; /* Max steps */
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
    init_servo(); /* set & write all servo angles to INIT_ANGLE*/
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
            /* Check if the position changed sero_pos[step-1]!=map_val[0] */
            if(sero_pos[step-1]!=map_val[0] && step<step_max )
                {
                    Serial.println( map_val[0]);
                    Serial.println(   sero_pos[step-1] );
                    record();
                    step+=1;
                }
            
            delay(100);
        }
    while (digitalRead(PLAY_BUTT)==true)
                {
                    working();
                    if(ste<step)
                        {
                            play();
                            ste+=1;
                            delay(35);
                        }
            else ste=0;
        }
}

/* working() 
 * a function to turn on/turn off the "LED working"
 *  when Servo changes angle */  
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
    val[0] = analogRead(potpin); 
    map_val[0]  = map(val[0], 0, 1023, 0, 180);     
}

void record()
{
    Serial.print("Recording: ");
    sero_pos[step] = map_val[0];
    Serial.print("record step: ");
    Serial.println(step);
 
}

void play()
{
    Serial.print("Playing: ");
    servo_A.write( sero_pos[ste]);
    Serial.print(sero_pos[ste]);
}

void free_mode()
{
    servo_A.write(map_val[0]);
}

