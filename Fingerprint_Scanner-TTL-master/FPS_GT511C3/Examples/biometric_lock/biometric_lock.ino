#include "FPS_GT511C3.h"
#include "SoftwareSerial.h"

// set up software serial pins for Arduino's w/ Atmega328P's
// FPS (TX) is connected to pin 4 (Arduino's Software RX)
// FPS (RX) is connected through a converter to pin 5 (Arduino's Software TX)
FPS_GT511C3 fps(4, 5); // (Arduino SS_RX = pin 4, Arduino SS_TX = pin 5)
int lockPin = 13;
/*If using another Arduino microcontroller, try commenting out line 51 and
uncommenting line 60 due to the limitations listed in the
library's note => https://www.arduino.cc/en/Reference/softwareSerial . Do
not forget to rewire the connection to the Arduino*/

// FPS (TX) is connected to pin 10 (Arduino's Software RX)
// FPS (RX) is connected through a converter to pin 11 (Arduino's Software TX)
//FPS_GT511C3 fps(10, 11); // (Arduino SS_RX = pin 10, Arduino SS_TX = pin 11)

void setup()
{
  Serial.begin(9600); //set up Arduino's hardware serial UART
  delay(100);
  fps.Open();         //send serial command to initialize fps
  fps.SetLED(true);   //turn on LED so fps can see fingerprint
  pinMode(lockPin, OUTPUT);
}

void lockUnlock(boolean lock){
  if(lock){
    digitalWrite(lockPin, LOW);
    delay(1000);
  }else{
    digitalWrite(lockPin, HIGH);
    delay(1000);
  }
}

void ring()
{
  digitalWrite(11,HIGH);
  delay(1000);
  digitalWrite(11,LOW);
  delay(1000); 
}

void loop()
{
  // Identify fingerprint test
  if (fps.IsPressFinger())
  {
    fps.CaptureFinger(false);
    int id = fps.Identify1_N();
    
          /*Note : GT-511C3 can hold 200 fingerprint templates. 
             GT-511C1R can hold 20 fingerprint templates.
       Make sure to change the id depending on what
       model you are using */
    if (id <200)
    {//if the fingerprint matches, provide the matching template ID
      Serial.print("Verified ID:");
      Serial.println(id);
    }
    else
    {//if unable to recognize
      Serial.println("Finger not found");
    }
  }
  else
  {
    Serial.println("Please press finger");
  }
  delay(100);
}
