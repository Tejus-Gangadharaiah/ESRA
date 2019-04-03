#include "simpletools.h"                      
#include "servo.h"

#define NOTE1 6
#define NOTE2 8
#define NOTE3 1


#define C6 1046.5
#define C6S 1108.7
#define D6  1174.7
#define D6S 1244.5
#define E6 1318.5
#define F6 1396.9
#define F6S 1480.0
#define G6 1568.0
#define G6S 1661.2
#define A6 1760.0
#define A6S 1864.7
#define B6 1975.5

#define C7 2093.0
#define C7S 2217.5
#define D7  2349.3
#define D7S 2489.0
#define E7 2367.0
#define F7 2793.9
#define F7S 2960.0
#define G7 3136.0
#define G7S 3322.4
#define A7 3520.0
#define A7S 3729.3
#define B7 3951.1

#define C8 4186.0

#define WHOLE 1500
#define HALF WHOLE/2
#define QUART WHOLE/4

enum LovingState{START, LOVE};

enum LovingState lovingState = START;

int irSense;
int soundSense; 

time_t initial_t;
time_t current_t;
int counter_lo = 0;

int loving(void){
  freqout(10, 1, 38000);
  freqout(14, 1, 38000);
  irSense = input(11);

  switch(lovingState){
    case START:
      if (irSense != 1){
        servo_speed(12, -40);
        servo_speed(13, 40);
        counter_lo++;
      } 
      if (counter_lo > 2)
        lovingState = LOVE;
      break;
      
    case LOVE:          
      BridalChorus();
      lovingState = START;  
      break;
      
    default:
      lovingState = START;
      break;
  }    
  return 0;
}

void BridalChorus(){
  freqout(NOTE1, QUART, C6);
  pause(100);
  freqout(NOTE1, QUART, F6);
  pause(100);
  freqout(NOTE1, QUART/2, F6);
  pause(100);
  
  freqout(NOTE1, QUART, F6);
  pause(100);
  freqout(NOTE1, QUART*2.5, 0);
  pause(100);
  
  freqout(NOTE1, QUART, C6);
  pause(100);
  freqout(NOTE1, QUART*1.5+50, G6);
  freqout(NOTE1, QUART/2+50, E6);
  pause(100);
  
  freqout(NOTE1, QUART, F6);
  pause(100);
  freqout(NOTE1, QUART, 0);
  pause(100);
  
  freqout(NOTE1, QUART, C6);
  pause(100);
  freqout(NOTE1, QUART+50, F6);
  freqout(NOTE1, QUART/2+50, A6S);
  pause(100);
  
  freqout(NOTE1, QUART, A6S);
  pause(100);
  freqout(NOTE1, QUART/2, A6);
  pause(100);
  freqout(NOTE1, QUART/2, G6);
  pause(100);
  
  freqout(NOTE1, QUART/3+33, F6);
  freqout(NOTE1, QUART/3+33, G6);
  freqout(NOTE1, QUART/3+33, F6);
  pause(100);
  freqout(NOTE1, QUART+50, E6);
  freqout(NOTE1, QUART/2+50, F6);
  pause(100);
  
  freqout(NOTE1, QUART, G6);
  pause(100);
}  
