#ifndef FUNCTIONS_H
#define FUNCTIONS_H
/*Servo Motors PINS 3/5/6/9*/
#define SER_A_PIN 3
#define SER_B_PIN 5
#define SER_C_PIN 6
#define SER_D_PIN 9
/*LED PINS 12/13*/
#define LED_WORKING 13
#define LED_STANDBY 12
/*Buttons PINS 2/11*/
#define RECORD_BUTT 11
#define PLAY_BUTT 2
#define INIT_ANGLE 90 /*Defualt Angle 90 degree*/
extern void init_servo();
extern void working();
extern void readpot();
extern void free_mode();
extern void standby();
extern void record();
extern void play();
#endif
