//file LEDfade.c
//runs on tiny13

#include <iot13v.h>
#include <macros.h>

//---------------------------
void port_init(void){
  PORTB = 0x00;
  DDRB  = 0x00;
}

//---------------------------------
//TIMER0 initialize - prescale:1
// WGM: PWM Fast
// desired value: 1Hz
// actual value: 3906.250Hz (100.0%)
void timer0_init(void){
  TCCR0B = 0x00; //stop
  OCR0A = 0xFF;
  OCR0B = 0xFF;
  TCNT0 = 0x01; //set count
  TCCR0A = 0xC3; 
  TCCR0B = 0x01; //start timer
}

//-------------------------------
void init_devices(void){
  CLI(); //disable all interrupts
  port_init();
  timer0_init();

  MCUCR = 0x00;
  TIMSK0 = 0x00; //timer interrupt sources
  GIMSK = 0x00; //interrupt sources
  SEI(); //re-enable interrupts
}

//-------------------
void delnms(int n){
//delay n ms
int x;

  while(n--){
    x=162;       //empirically determined fudge factor  1 mhz
    while(x--);
  }
}

//----------------------------------------------------
//algo:
//fade up 1.7 sec, hold 1 sec, fade dn 1.7 sec

//                        off                                        full
unsigned char pwmdat[17]={0,1,2,3,4,6,8,12,16,24,32,48,64,96,128,192,255};
unsigned char ndx;        //index into pwmdat
unsigned char dem;        //from pwmdat table
unsigned char pos;        //counts to meets demand to make led fade smoothly
unsigned char countingup; //bool state
unsigned char countingdn; //bool state
unsigned char holding;    //bool state
unsigned char upcount;    //0-170 10ms loops
unsigned char dncount;    //0-170
unsigned char holdcount;  //0-100

//-----------------
void main(void){
//main program, 10ms per pass 

  init_devices();
	countingup=1;
  while(1){               //loop forever
		if(countingup){
		  if(upcount < 170){  //count to 170 10ms at a time
		    upcount++;        //1700ms fade up 
			}else{
			  countingup=0;     //stop counting up at 170
			}	
  	  ndx=upcount/10;     //ndx is 0-17 
		}	
		holding = !countingup && !countingdn;
		if(holding){
		  if(holdcount < 100){
		    holdcount++;      //1000ms
		  }else{
			  holding=0;        //stop holding at 1000ms
				holdcount=0;   
				countingdn=1;     //start counting down
			}
		}		
		if(countingdn){
		  if(dncount < 170){
		    dncount++;        //1700ms fade dn 
			}else{
			  countingdn=0;     //stop counting down
				countingup=1;     //start counting up
			}	
  	  ndx=dncount/10;     //ndx is 0-17 
		}
		dem=pwmdat[ndx];      //get demand from table
		if(dem > pos){        //inc or dec pos to match demand
		  pos++;          
		}	
		if(dem < pos){
		  pos--;
		}	
		OCR0A=pos;            //set pwm fn of pos
		delnms(10);           //10 loops per sec
  }//while
}
//--------eof-------------
