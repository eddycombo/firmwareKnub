#include "Arduino.h"
//#include "luts.h"

uint8_t redLUT[] = {3 ,  6 ,  8 ,  10 ,  11 ,  12 ,  14 ,  15 ,  16 ,  
  16 ,  17 ,  18 ,  19 ,  19 ,  20 ,  20 ,  21 ,  21 ,  22 ,  22 ,  23 ,  23 ,  
  24 ,  24 ,  24 ,  25 ,  25 ,  25 ,  26 ,  26 ,  26 ,  27 ,  27 ,  27 ,  28 ,  
  28 ,  28 ,  29 ,  29 ,  29 ,  29 ,  30 ,  30 ,  30 ,  30 ,  30 ,  31 ,  31 ,  
  31 ,  31 ,  32 ,  32 ,  32 ,  33 ,  33 ,  33 ,  33 ,  34 ,  34 ,  35 ,  35 ,  
  35 ,  35 ,  36 ,  36 ,  36 ,  36 ,  36 ,  36 ,  36 ,  37 ,  37 ,  38 ,  38 ,  
  38 ,  39 ,  39 ,  39 ,  40 ,  41 ,  41 ,  42 ,  42 ,  42 ,  43 ,  43 ,  43 ,  
  44 ,  44 ,  44 ,  45 ,  45 ,  46 ,  46 ,  46 ,  46 ,  47 ,  47 ,  47 ,  48 ,  
  48 ,  48 ,  49 ,  49 ,  49 ,  50 ,  50 ,  51 ,  51 ,  51 ,  52 ,  52 ,  53 ,  
  53 ,  54 ,  54 ,  55 ,  55 ,  55 ,  56 ,  56 ,  57 ,  57 ,  58 ,  58 ,  58 ,  
  59 ,  59 ,  59 ,  60 ,  60 ,  61 ,  61 ,  61 ,  62 ,  62 ,  62 ,  63 ,  63 ,  
  64 ,  64 ,  64 ,  65 ,  66 ,  66 ,  66 ,  67 ,  67 ,  67 ,  67 ,  68 ,  68 ,  
  68 ,  69 ,  69 ,  69 ,  70 ,  70 ,  70 ,  71 ,  71 ,  72 ,  72 ,  73 ,  73 ,  
  74 ,  74 ,  75 ,  75 ,  76 ,  76 ,  77 ,  77 ,  77 ,  78 ,  79 ,  80 ,  80 ,  
  81 ,  82 ,  83 ,  83 ,  84 ,  85 ,  85 ,  86 ,  87 ,  87 ,  88 ,  89 ,  89 ,  
  90 ,  91 ,  91 ,  92 ,  92 ,  94 ,  94 ,  95 ,  97 ,  97 ,  98 ,  100 ,  101 ,  
  102 ,  103 ,  104 ,  105 ,  106 ,  107 ,  108 ,  109 ,  111 ,  112 ,  113 ,  115 ,  
  116 ,  118 ,  120 ,  122 ,  125 ,  127 ,  128 ,  131 ,  132 ,  135 ,  137 ,  140 ,  
  145 ,  145 ,  151 ,  158 ,  165 ,  173 ,  180 ,  185 ,  190 ,  199 ,  208 ,  212 ,  
  215 ,  219 ,  225 ,  230 ,  235 ,  240 ,  244 ,  250 ,  252 ,  253 ,  254 ,  255 ,  
  255 ,  255 ,  255};

uint16_t vacMin = 0;
uint16_t vacMax = 4095;


uint8_t DACIDZ[2] = {B0001100, B0001101};

uint8_t writeCommands[4] = {B00110001, B00110010,B00110100, B00111000};

uint16_t  lowVal, highVal, prevExp;

// bool prevUp, prevDown;

void writeDac(uint8_t id, uint8_t wichDac, uint16_t value){

    Wire.beginTransmission(id);
    Wire.write(writeCommands[wichDac]);
    Wire.write(highByte(value));
    Wire.write(lowByte(value));
    Wire.endTransmission();
}

//actual turn knub func

void turnKnub(uint8_t knubNum,uint8_t knubVal){


    byte hiRead = 255 - knubVal;

    lowVal = map(redLUT[knubVal], 0, 255, vacMin, vacMax);
    highVal = map(redLUT[hiRead], 0, 255, vacMin, vacMax);
    
    switch(knubNum){
  
    case 0:
      
      writeDac(DACIDZ[0], 0, lowVal);
      writeDac(DACIDZ[0], 1, highVal);
    break;
    

    case 1:
     writeDac(DACIDZ[0], 2, lowVal);
     writeDac(DACIDZ[0], 3, highVal);
    break;
    
    case 2:
      writeDac(DACIDZ[1], 0, lowVal);
      writeDac(DACIDZ[1], 1, highVal);
    break;
    
    case 3:
      writeDac(DACIDZ[1], 2, lowVal);
     writeDac(DACIDZ[1], 3, highVal);
    break;
    }
}
 void updateKnubs(aKnubPreset * kPreset){
 
      for(uint8_t i = 0; i<4; i++){
        if(kPreset->knubbies[i].state == 1){
      
          turnKnub(i, kPreset->knubbies[i].params[0]);
        }
      }
}


void printPresetName(aKnubPreset *kPreset){

    Serial.println(kPreset->name);
}


void doExpressionPedal(unsigned int expVal){

  expVal = expVal >> 2;

    if(abs(expVal - prevExp) > 2){

      for(uint8_t i =0; i<4; i++){
        if(currentPreset.knubbies[i].modOn == 1){
          turnKnub(i, map(expVal, 0, 255, currentPreset.knubbies[i].params[0], currentPreset.knubbies[i].params[1]));
       
        }
      }

    prevExp = expVal;
  }
}

void debugKnubPreset(aKnubPreset *kPreset){

  Serial.print("PRESET NAME: ");
  Serial.println(kPreset->name);

  for(uint8_t  i = 0; i<numKnubbies;i++){

    Serial.print("KNUBBIE: ");
    Serial.println(kPreset->knubbies[i].name);
    Serial.print("VAL1: ");
    Serial.println(kPreset->knubbies[i].params[0]);
  }
}