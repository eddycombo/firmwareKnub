#include "Arduino.h"

//OSC------------------------------------
  byte myMac[] = {0x00, 0xAA, 0xBB, 0xCC, 0xDE, 0x02};

  byte myIp[]  = { 192, 168, 0, 8 };
  uint16_t  myPort  = 10000;

  Z_OSCServer server;
  Z_OSCMessage *rcvMes;

char *subAddress[3]={"/k", "/pl", "/ps"};

void knubDoOsc(){

  if(server.available()){
  
    rcvMes = server.getMessage();
   
   //deals with pots messages
    if(!strcmp(rcvMes->getZ_OSCAddress(), subAddress[0])){
        
      byte wichPot = rcvMes->getInteger32(0);
      byte potVal =  rcvMes->getInteger32(1);   
      
      turnKnub(wichPot, potVal);     
    }
    
    if(!strcmp(rcvMes->getZ_OSCAddress(), subAddress[1])){
        

          byte readAdr = rcvMes->getInteger32(0);
          //loac presets
          loadFlag = true;
  
          readKnubPreset(eepromAddr1, readAdr, &currentPreset);
          
          updateKnubs(&currentPreset);
       
          loadFlag = false;
          //isEdited = false;
          
          #ifdef DEBUG_LOAD_PRESET
            Serial.println(readAdr);
            debugKnubPreset(&currentPreset);
          #endif
          clearLoopsOut();
          
          // fill up loopsOut array
            
            for(uint8_t i = 0; i<numKnubbies; i++){

              fillLoopsOut(currentPreset.knubbies[i].numLoop, currentPreset.knubbies[i].state);
            } 
            
            // check loops state and update
            
            for(uint8_t i = 0; i<4; i++){

                if(checkLoopsOut(i) == true){
                    
                    switchLoop(i, 1);
                    
                }else{

                    switchLoop(i, 0);
                }
            } 
            time2ChangePage = true;
        }

      if(!strcmp(rcvMes->getZ_OSCAddress(), subAddress[1])){


          //save current preset
          writeKnubPreset(eepromAddr1, readAdr, &currentPreset);
          delay(saveTime*5);
        }
    }
}
