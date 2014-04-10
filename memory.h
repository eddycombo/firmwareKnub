#include "Arduino.h"
#define saveTime 10

#define maxNameLength 8
#define IDLength 6
#define paramLength 3
#define modOnLength 1
#define stateLength 1
#define numLoopLength 1
#define numKnubbies 8

#define presetSize 126
#define modIndx maxNameLength+paramLength
#define stateIndx maxNameLength+paramLength+modOnLength
#define loopIndx maxNameLength+paramLength+modOnLength+stateLength

#define eepromAddr1 0x50

struct aKnub{
  char name[maxNameLength];
  byte params[3];
  byte modOn;
  byte state;
  byte numLoop;
};

typedef struct aKnub aKnub;

struct aKnubPreset{
  
  char name[maxNameLength];
  byte ID[6];
  
  aKnub knubbies[numKnubbies];
};
typedef struct aKnubPreset aKnubPreset;





void writeByte( int deviceaddress, unsigned int eeaddress, byte data ) {
    
    Wire.beginTransmission(deviceaddress);
    Wire.write((int)(eeaddress >> 8)); // MSB
    Wire.write((int)(eeaddress & 0xFF)); // LSB
    Wire.write(data);
    
    Wire.endTransmission();
    delay(5);
  }

  
byte readByte( int deviceaddress, unsigned int eeaddress ) {
   
    Wire.beginTransmission(deviceaddress);
    Wire.write((int)(eeaddress >> 8)); // MSB
    Wire.write((int)(eeaddress & 0xFF)); // LSB
    Wire.endTransmission();

    Wire.requestFrom(deviceaddress,1);
    if (Wire.available());
     return Wire.read();
  
  }


  void writeKnubPresetName( int deviceaddress, unsigned int eeaddresspage, aKnubPreset *kpreset ) {
    
    /*
    Wire.beginTransmission(deviceaddress);
    Wire.write((int)(eeaddresspage >> 8)); // MSB
    Wire.write((int)(eeaddresspage & 0xFF)); // LSB
    
    for ( byte c = 0; c < maxNameLength; c++){
      Wire.write(kpreset->name[c]);
      delay(5);
    }
    Wire.endTransmission();
    */

    for(uint16_t i = 0; i<maxNameLength; i++){

      writeByte(deviceaddress, eeaddresspage+i, kpreset->name[i]);

    }

  }
  

  void writeKnubPresetID(int deviceaddress, unsigned int eeaddresspage, aKnubPreset *kpreset){

    Wire.beginTransmission(deviceaddress);
    Wire.write((int)eeaddresspage >> 8);
    Wire.write((int)(eeaddresspage & 0xFF)); // LSB
    
    
    for (byte c = 0; c < IDLength; c++){
      Wire.write(kpreset->ID[c]);
      delay(5);
    }
    
    Wire.endTransmission();
  }

  void writeKnubbieName(int deviceaddress, unsigned int eeaddresspage, aKnubPreset *kpreset, uint8_t knubbieIndx){
    /*
    Wire.beginTransmission(deviceaddress);
    Wire.write((int)eeaddresspage >> 8);
     Wire.write((int)(eeaddresspage & 0xFF)); // LSB
    
    for (byte c = 0; c < maxNameLength; c++){
    
      Wire.write(kpreset->knubbies[knubbieIndx].name[c]);
      delay(5);
    }
    Wire.endTransmission();
    */

    for(uint16_t i =0 ; i<maxNameLength;i++){

      writeByte(deviceaddress, eeaddresspage+i, kpreset->knubbies[knubbieIndx].name[i]);



    }

  }
  
 void writeKnubbieParams(int deviceaddress, unsigned int eeaddresspage, aKnubPreset *kpreset, uint8_t knubbieIndx){

    Wire.beginTransmission(deviceaddress);
    Wire.write((int)eeaddresspage >> 8);
    Wire.write((int)(eeaddresspage & 0xFF)); // LSB
    
    
    for ( byte c = 0; c < paramLength; c++){
      Wire.write(kpreset->knubbies[knubbieIndx].params[c]);
      delay(5);
    }
    Wire.endTransmission();
  }

void writeKnubbiemodOn(int deviceaddress, unsigned int eeaddresspage, aKnubPreset *kpreset, uint8_t knubbieIndx){

    Wire.beginTransmission(deviceaddress);
    Wire.write((int)eeaddresspage >> 8);
    Wire.write((int)(eeaddresspage & 0xFF)); // LSB
    
    
    for ( byte c = 0; c < modOnLength; c++){
      Wire.write(kpreset->knubbies[knubbieIndx].modOn);
      delay(5);
      }
      Wire.endTransmission();
  }

void writeKnubbieModState(int deviceaddress, unsigned int eeaddresspage, aKnubPreset *kpreset, uint8_t knubbieIndx){

    Wire.beginTransmission(deviceaddress);
    Wire.write((int)eeaddresspage >> 8);
    Wire.write((int)(eeaddresspage & 0xFF)); // LSB
    
    
    for (byte  c = 0; c < stateLength; c++){
      Wire.write(kpreset->knubbies[knubbieIndx].state);
      delay(5);
    }
    Wire.endTransmission();
  }

void writeKnubbieNumLoop(int deviceaddress, unsigned int eeaddresspage, aKnubPreset *kpreset, uint8_t knubbieIndx){

    Wire.beginTransmission(deviceaddress);
    Wire.write((int)eeaddresspage >> 8);
    Wire.write((int)(eeaddresspage & 0xFF)); // LSB
    
    
    for (byte c = 0; c < numLoopLength; c++){
      Wire.write(kpreset->knubbies[knubbieIndx].numLoop);
      delay(5);
    }
    Wire.endTransmission();
  }


void readKnubPresetName( int deviceaddress, unsigned int eeaddress, aKnubPreset *kpreset) {
    
    Wire.beginTransmission(deviceaddress);
    Wire.write((int)(eeaddress >> 8)); // MSB
    Wire.write((int)(eeaddress & 0xFF)); // LSB
    Wire.endTransmission();
    
    Wire.requestFrom(deviceaddress,maxNameLength);
    
    for (byte c = 0; c < maxNameLength; c++ )
      if (Wire.available()) kpreset->name[c] = Wire.read();
}

void readKnubPresetID( int deviceaddress, unsigned int eeaddress, aKnubPreset *kpreset) {
    
    Wire.beginTransmission(deviceaddress);
    Wire.write((int)(eeaddress >> 8)); // MSB
    Wire.write((int)(eeaddress & 0xFF)); // LSB
    Wire.endTransmission();
    
    Wire.requestFrom(deviceaddress,IDLength);
    
    for(byte c = 0; c<IDLength; c++){
      if (Wire.available()) kpreset->ID[c] = Wire.read();
    }
}

void readKnubbieName( int deviceaddress, unsigned int eeaddress, aKnubPreset *kpreset, uint8_t knubbieIndx) {
    
    Wire.beginTransmission(deviceaddress);
    Wire.write((int)(eeaddress >> 8)); // MSB
    Wire.write((int)(eeaddress & 0xFF)); // LSB
    Wire.endTransmission();
    
    Wire.requestFrom(deviceaddress,maxNameLength);
    
    for (byte c = 0; c < 8; c++ ){
      
        if (Wire.available()){ 
          
          //Serial.println((char)rData);
          kpreset->knubbies[knubbieIndx].name[c] = Wire.read();
      }
  }
}

void readKnubbieParams(int deviceaddress, unsigned int eeaddress, aKnubPreset *kpreset, uint8_t knubbieIndx){


  Wire.beginTransmission(deviceaddress);
    Wire.write((int)(eeaddress >> 8)); // MSB
    Wire.write((int)(eeaddress & 0xFF)); // LSB
    Wire.endTransmission();
    
    Wire.requestFrom(deviceaddress,paramLength);
    
    for ( byte c = 0; c < paramLength; c++ ){
      if (Wire.available()) kpreset->knubbies[knubbieIndx].params[c] = Wire.read();
    }
}

void readKnubbiemodOn(int deviceaddress, unsigned int eeaddress, aKnubPreset *kpreset, uint8_t knubbieIndx){


  Wire.beginTransmission(deviceaddress);
    Wire.write((int)(eeaddress >> 8)); // MSB
    Wire.write((int)(eeaddress & 0xFF)); // LSB
    Wire.endTransmission();
    
    Wire.requestFrom(deviceaddress,1);
  
      if (Wire.available()) kpreset->knubbies[knubbieIndx].modOn = Wire.read();
}
void readKnubbieModState(int deviceaddress, unsigned int eeaddress, aKnubPreset *kpreset, uint8_t knubbieIndx){


  Wire.beginTransmission(deviceaddress);
    Wire.write((int)(eeaddress >> 8)); // MSB
    Wire.write((int)(eeaddress & 0xFF)); // LSB
    Wire.endTransmission();
    
    Wire.requestFrom(deviceaddress,1);
  
      if (Wire.available()) kpreset->knubbies[knubbieIndx].state = Wire.read();
}
void readKnubbieNumLoop(int deviceaddress, unsigned int eeaddress, aKnubPreset *kpreset, uint8_t knubbieIndx){


  Wire.beginTransmission(deviceaddress);
    Wire.write((int)(eeaddress >> 8)); // MSB
    Wire.write((int)(eeaddress & 0xFF)); // LSB
    Wire.endTransmission();
    
    Wire.requestFrom(deviceaddress,1);
  
      if (Wire.available()) kpreset->knubbies[knubbieIndx].numLoop = Wire.read();
}



void readKnubPreset(int deviceaddress, unsigned int eeaddress, aKnubPreset *kpreset){
  
    ///first we read the preset's name and ID
    
    // so name
    readKnubPresetName(deviceaddress, eeaddress, kpreset); 
    //delay(5);
    //then ID
    readKnubPresetID(deviceaddress, eeaddress + maxNameLength, kpreset);
    //delay(5);
    //so now eeaddress is maxNameLength + IDLength
     unsigned int addrPtr = eeaddress + maxNameLength + IDLength;
   

     //readKnubbieName(deviceaddress, addrPtr, kpreset, 0);

   
   for(int i = 0; i<numKnubbies; i++){
     
     ///move addrPtr to start of knubbie
     addrPtr = addrPtr*(i+1);
     
     
     readKnubbieName(deviceaddress,addrPtr , kpreset, i);
     
     //delay(5);
     readKnubbieParams(deviceaddress, addrPtr+maxNameLength, kpreset, i);
     //delay(5);  
     readKnubbiemodOn(deviceaddress, addrPtr+modIndx, kpreset, i);
     //delay(5);
     readKnubbieModState(deviceaddress, addrPtr+stateIndx, kpreset, i);
     //delay(5);
     readKnubbieNumLoop(deviceaddress, addrPtr+loopIndx, kpreset, i);
     //delay(5);    
    
   
   }
   
   
}

void writeKnubPreset(int deviceaddress, unsigned int eeaddress, aKnubPreset *kpreset){
  
    // so name
    writeKnubPresetName(deviceaddress, eeaddress, kpreset); 
    delay(saveTime);
    //then ID
    writeKnubPresetID(deviceaddress, eeaddress + maxNameLength, kpreset);
    delay(saveTime);
    //so now eeaddress is maxNameLength + IDLength
    unsigned int addrPtr = eeaddress + maxNameLength + IDLength;
    
    
    //writeKnubbieName(deviceaddress, addrPtr, kpreset, 0);
    //delay(saveTime);

   
   for(int i = 0; i<numKnubbies; i++){
     
     ///move addrPtr to start of knubbie
     addrPtr = addrPtr*(i+1);
     
     //delay(saveTime);
     writeKnubbieName(deviceaddress,addrPtr , kpreset, i);
     
     delay(saveTime);
     
     writeKnubbieParams(deviceaddress, addrPtr+maxNameLength, kpreset, i);
     delay(saveTime);  
     writeKnubbiemodOn(deviceaddress, addrPtr+maxNameLength+paramLength, kpreset, i);
     delay(saveTime);
     writeKnubbieModState(deviceaddress, addrPtr+maxNameLength+paramLength+modOnLength, kpreset, i);
     delay(saveTime);
     writeKnubbieNumLoop(deviceaddress, addrPtr+maxNameLength+paramLength+modOnLength+stateLength, kpreset, i);
    delay(saveTime);
   }
   
   
   
}
//single read/write functions

 byte i2c_eeprom_read_byte( int deviceaddress, unsigned int eeaddress ) {
    
    Wire.beginTransmission(deviceaddress);
    Wire.write((int)(eeaddress >> 8)); // MSB
    Wire.write((int)(eeaddress & 0xFF)); // LSB
    Wire.endTransmission();
    
    Wire.requestFrom(deviceaddress,1);
    if (Wire.available());
    return Wire.read();
  }

   void i2c_eeprom_write_byte( int deviceaddress, unsigned int eeaddress, byte data ) {
    
    Wire.beginTransmission(deviceaddress);
    Wire.write((int)(eeaddress >> 8)); // MSB
    Wire.write((int)(eeaddress & 0xFF)); // LSB
    Wire.write(data);
    Wire.endTransmission();
  }


