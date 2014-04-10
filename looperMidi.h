#include "Arduino.h"
/*
FOR TESTING USE SOFTSERIAL BUT FINAL VERSION USES MAIN SERIAL OUT
*/
#define CC2Looper 191

byte loopsOut[4];

SoftwareSerial looperSerial(11, 4);

byte switchSysEx[8] = {240, 0, 0, 7, 1, 8, 16, 247};

byte switchLoops[8] = {80, 81, 82, 83};
byte loopStates[2] = {0, 127};


void sendSwitchSysEx(){


	for(uint8_t i = 0; i<8;i++){
		
		looperSerial.write(switchSysEx[i]);
	}
}

void switchLoop( byte loopNum, byte state){

	looperSerial.write(CC2Looper);
	looperSerial.write(switchLoops[loopNum]);
	looperSerial.write(loopStates[state]);
}

void clearLoopsOut(){

	for(uint8_t i = 0; i<4; i++){

		loopsOut[i] = 0;
	}
}

void fillLoopsOut(byte indx, byte val){

    loopsOut[indx] += val;
}

bool checkLoopsOut(byte indx ){

  if(loopsOut[indx] != 0){

      return true;
  }else if(loopsOut[indx] == 0){

      return false;
  }
}

void checkUILeds(){


	for(uint8_t i =0; i<4;i++){

		if(checkLoopsOut(i)){
			switchUILed(i, 1);

		}else{switchUILed(i, 0);}
	}
}
void updateLoops(byte indx, byte val){

	
		if(val == 0){
				if(loopsOut[indx] >0){
					loopsOut[indx] -= 1;
			}
		}else{
			if(loopsOut[indx]<3){
				loopsOut[indx] += 1;
			}
		}
	
}

