#include <Servo.h> 
#include "common.h"

uint16_t val[4]; /* Servo array to store the analog values */
uint16_t map_val[4] ; /* Servo array to store the position after mapping the analog value */
uint16_t step[4]={0,0,0,0}; /* Array's "change steps" to store it in array steps */
uint16_t sero_pos[180]; /* An array  Store the steps for a one servo*/ 
uint16_t sero_pos1[180];
uint16_t sero_pos2[180];
uint16_t sero_pos3[180];
uint16_t sero_pos4[180]; 
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
    //  init_servo(); /* set & write all servo angles to INIT_ANGLE*/
    Serial.begin(9600);
}

void loop()
{
    standby();
    while (digitalRead(RECORD_BUTT)==true)
        {
            working();
            readpot();
            free_mode();
            /* Check if the position changed sero_pos[step-1]!=map_val[0] */
            if(sero_pos[step[0]-1]!=map_val[0] && step[0]<step_max )
                {
                    Serial.println(map_val[0]);
                    Serial.println(sero_pos[step[0]-1]);
                    record(0);
                    step[0]++;
                }
            
            delay(100);
        }
    while (digitalRead(PLAY_BUTT)==true)
        {
            working();
            if(ste<step[0])
                {
                    play(0);
                    ste+=1;
                    delay(100);
                }
            else ste=0;
        }
}

/* working() 
 * a function to turn on/turn off the "LED working"
 *  when Servo changes angle */  
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
    val[0] = analogRead(POT_PIN0); 
    map_val[0]  = map(val[0], 0, 1023, 0, 180);
    val[1] = analogRead(POT_PIN1); 
    map_val[1]  = map(val[1], 0, 1023, 0, 180);
}

void record(int ser)
{
    Serial.print("Recording: ");
    sero_pos[step[ser]] = map_val[ser];
    Serial.print("record step: ");
    Serial.println(step[ser]);
 
}
void play(int ser)
{
    Serial.print("Playing: ");
    servo_A.write( sero_pos[ser]);
    Serial.print(sero_pos[ser]);
}

void free_mode()
{
    servo_A.write(map_val[0]);
    servo_B.write(map_val[1]);
}

