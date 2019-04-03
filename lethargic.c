#include "simpletools.h"                      
#include "servo.h"


enum LethargicState{START, STRD1, STRD2, TRD};

enum LethargicState lethargicState = START;

int irSense;
int soundSense;

time_t initial_t;
time_t current_t;
int condition_l = 0;

int lethargic(void){
  freqout(10, 1, 38000);
  freqout(14, 1, 38000);
  irSense = input(11);
  high(0);
  switch(lethargicState){
    
    case START:
      servo_speed(12, -50);
      servo_speed(13, 50);
      if (condition_l == 0){
        initial_t = time(NULL);
        condition_l = 1;
      } else {
        current_t = time(NULL); 
        if (((double) (current_t) - (double) (initial_t)) > 2){
          condition_l = 0;
          lethargicState = STRD1;
        }          
      }          
      break;
    
      case STRD1:
      servo_speed(12, -20);
      servo_speed(13, 20);
      
      if (condition_l == 0){
        initial_t = time(NULL);
        condition_l = 1;
      } else {
        current_t = time(NULL);
        if (((double) (current_t) - (double) (initial_t)) > 2){
          condition_l = 0;
          lethargicState = STRD2;
        }          
      }   
      
      if (irSense != 1){
        high(27);
        pause(500);
        low(27);
        lethargicState = START;
      } 
      if (soundSense == 1){
        high(27);
        pause(500);
        low(27);
		   lethargicState = START;
		 }  
      break;
      
    case STRD2:
      servo_speed(12, -10);
      servo_speed(13, 10);
      
      if (condition_l == 0){
        initial_t = time(NULL);
        condition_l = 1;
      } else {
        current_t = time(NULL);
        if (((double) (current_t) - (double) (initial_t)) > 2){
          condition_l = 0;
          lethargicState = TRD;
        }          
      }   
      
      if (irSense != 1){
        high(27);
        pause(500);
        low(27);
        lethargicState = START;
      } 
      if (soundSense == 1){
        high(27);
        pause(500);
        low(27);
		   lethargicState = START;
		 }  
      break;
      
    case TRD:          
      servo_speed(12, 0);
      servo_speed(13, 0);

      if (irSense != 1){
        high(27);
        pause(500);
        low(27);
        lethargicState = START;
      } 
      if (soundSense == 1){
        high(27);
        pause(500);
        low(27);
		   lethargicState = START;
		 }  
      break;
      
    default:
      lethargicState = START;
      break;
  }    
  return 0;
}
