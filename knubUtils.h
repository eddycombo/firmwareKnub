void checkEdition(bool editState){

	if(editState == false){

		editState == true;	

	}
}


void printCurrentPreset(){


	Serial.println(currentPreset.name);
 	
 	Serial.println("----------------------");
   	
   	Serial.println("KNUBBIES: ");

   	for(int i = 0; i<numKnubbies; i++){
   			Serial.println(currentPreset.knubbies[i].name);

   	}   	
 	
 	Serial.println("----------------------");
   	
   	Serial.println("KNUBBIE 1 PARAMS : ");

   	for(int i = 0; i<paramLength; i++){

   		Serial.println(currentPreset.knubbies[0].params[i]);
	}
 

	Serial.println("KNUBBIE 1 modOn: ");
	Serial.println(currentPreset.knubbies[0].modOn);
	Serial.println("KNUBBIE 1 STATE: ");
	Serial.println(currentPreset.knubbies[0].state);
	Serial.println("KNUBBIE 1 NUMLOOP: ");
	Serial.println(currentPreset.knubbies[0].numLoop);

	Serial.println("----------------------");
   	Serial.println("KNUBBIE 2 PARAMS : ");

   	for(int i = 0; i<paramLength; i++){

   		Serial.println(currentPreset.knubbies[1].params[i]);
	}
 

	Serial.println("KNUBBIE 2 modOn: ");
	Serial.println(currentPreset.knubbies[1].modOn);
	Serial.println("KNUBBIE 2 STATE: ");
	Serial.println(currentPreset.knubbies[1].state);
	Serial.println("KNUBBIE 2 NUMLOOP: ");
	Serial.println(currentPreset.knubbies[1].numLoop);

	Serial.println("----------------------");
   	Serial.println("KNUBBIE 3 PARAMS : ");

   	for(int i = 0; i<paramLength; i++){

   		Serial.println(currentPreset.knubbies[2].params[i]);
	}
 

	Serial.println("KNUBBIE 3 modOn: ");
	Serial.println(currentPreset.knubbies[2].modOn);
	Serial.println("KNUBBIE 3 STATE: ");
	Serial.println(currentPreset.knubbies[2].state);
	Serial.println("KNUBBIE 3 NUMLOOP: ");
	Serial.println(currentPreset.knubbies[2].numLoop);
}
