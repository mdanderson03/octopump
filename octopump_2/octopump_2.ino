#include <A4988.h>
#include <BasicStepperDriver.h>
#include <DRV8825.h>
#include <DRV8834.h>
#include <DRV8880.h>
#include <MultiDriver.h>
#include <SyncDriver.h>


#define dc1_pwm 5
#define dc2_pwm 10
#define dc3_pwm 11
#define dc4_pwm 3
#define dc4_1 4
#define dc4_2 2
#define STEP 12
#define DIR 9
#define MOTOR_STEPS 200
#define MICROSTEPS 1
#define SLEEP 13


int user_input;
int input_seq[3] = {0, 0, 0};
int i = 0;
int motor = 0;
int mot_speed_char1 = 0;
int mot_speed_char2 = 0;
int step_mot_delay = 0;
long start_time = 0;



void setup() {
  // put your setup code here, to run once:

pinMode(dc1_pwm, OUTPUT);
pinMode(dc2_pwm, OUTPUT);
pinMode(dc3_pwm, OUTPUT);
pinMode(dc4_pwm, OUTPUT);
pinMode(dc4_1, OUTPUT);
pinMode(dc4_2, OUTPUT);

digitalWrite(dc4_1, LOW);
digitalWrite(dc4_2, HIGH);

TCCR1B = TCCR1B & B11111000 | B00000101; // for PWM frequency of 30.64 Hz for pin 10
TCCR0B = TCCR0B & B11111000 | B00000101; // for PWM frequency of 61.04 Hz for pins 5
TCCR2B = TCCR2B & B11111000 | B00000111; // for PWM frequency of 30.64 Hz for pin 3 and 11

Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:


  if (Serial.available()>0){
    i = 0;
    while (i <= 2){
   user_input= Serial.read();
   if (user_input != -1){
   input_seq[i] = user_input - 48;
   i++;
   }
    } 
    motor = input_seq[0];
    mot_speed_char1 = input_seq[1];
    mot_speed_char2 = input_seq[2];  
  }

if (motor == 5){
  step_mot_delay = (float)((10 * (mot_speed_char1) + 1 * (mot_speed_char2))/10);

}

if (motor != 0){
  mot_run(motor, mot_speed_char1, mot_speed_char2);
  motor = 0;
  mot_speed_char1 = 0;
  mot_speed_char2 = 0;
  Serial.println(0);
}

//digitalWrite(13, HIGH);
digitalWrite(12, HIGH);
delay(step_mot_delay);
digitalWrite(12, LOW);



//end of loop!
}


//Functions are below


//places correct syringe under push rod
void mot_run(int motor, int mot_speed_char1, int mot_speed_char2){
 
  int dig_speed = (int)((0.1 * (mot_speed_char1) + 0.01 * (mot_speed_char2))* 255);
  Serial.println(dig_speed);

  if(motor == 4){
    analogWrite(dc1_pwm, dig_speed);
  }
  if(motor == 1){
    analogWrite(dc2_pwm, dig_speed);
  }
  if(motor == 3){
    analogWrite(dc3_pwm, dig_speed);
  }
  if(motor == 2){
    analogWrite(dc4_pwm, dig_speed);
  }
  if(motor == 5){  // Doesn't turn on permanately. Turns motor on at fixed speed for 30 minutes. 
    if(dig_speed == 0){
      digitalWrite(13, LOW);
    }
    if(dig_speed > 0){
      digitalWrite(13, HIGH);
    }
  }  
}
