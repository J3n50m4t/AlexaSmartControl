void setupRC(){
    mySwitch.enableTransmit(rc433_connected_pin);
}

void callcase48(){
    mySwitch.switchOn('a', 1, 1); 
    client.publish("fromarduino", "0"); 
    Serial.println("Antwort gesendet 0"); 
}
void callcase49(){
    mySwitch.switchOff('a', 1, 1); 
    client.publish("fromarduino", "1");     
    Serial.println("Antwort gesendet 1"); 
}


void callcase50(){
    mySwitch.switchOn('a', 1, 2); 
    client.publish("fromarduino", "2");     
    Serial.println("Antwort gesendet 2"); 
}
void callcase51(){
    mySwitch.switchOff('a', 1, 2); 
    client.publish("fromarduino", "3");     
    Serial.println("Antwort gesendet 3"); 
}

void callcase52(){
    mySwitch.switchOn('a', 1, 3); 
     client.publish("fromarduino", "4"); 
    Serial.println("Antwort gesendet 4");
}
void callcase53(){
    mySwitch.switchOff('a', 1, 3); 
    client.publish("fromarduino", "5");
    Serial.println("Antwort gesendet 5"); 
}
