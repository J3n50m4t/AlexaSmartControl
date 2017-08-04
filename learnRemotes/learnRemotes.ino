  /*
    Example for Intertechno outlets
    https://github.com/sui77/rc-switch/

    This script just repeats sending commands.
    Use it to learn the Remotecode. Upload it to your Arduino and plug in the socket.
    To delete a remote uncomment the mySwitch.switchOff and comment the mySwitch.switchOn instead.
    Do it for each socket

  */
  #include <RCSwitch.h>
  RCSwitch mySwitch = RCSwitch();

  void setup() {
    Serial.begin(9600);
    // Transmitter is connected to Pin #0  
    mySwitch.enableTransmit(0);
    // Optional set pulse length.
    // mySwitch.setPulseLength(320);
    
  }

  void loop() {

  Serial.print("Switched on\n");
    
    // The first parameter represents the familycode (a, b, c, ... f)
    // The second parameter represents the group number
    // The third parameter represents the device number
    // 
    // In this example it's family 'b', group #3, device #2 


    // Switch on:

    //mySwitch.switchOn('a', 1, 1);
    //mySwitch.switchOn('a', 1, 2);
    //mySwitch.switchOn('a', 1, 3);
    
    
    // Switch off:

    //mySwitch.switchOff('a', 1, 1);
    //mySwitch.switchOff('a', 1, 2);
    //mySwitch.switchOff('a', 1, 3);
    
    // Wait a 0.3 seconds
    delay(300);
  }
