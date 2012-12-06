/*
  PiWi.h - Library for Wireless Communication with the Raspberry PI
  It used 433.92Mhz Emitter or Receiver.
  Created by Sarrailh Remi
  Released into the public domain.
*/

#include "Arduino.h"
#include "Piwi.h"

//Class Initialization
Piwi::Piwi(int receiver)
{
pinMode(receiver, INPUT);

_receiver = receiver;
int character = 666;               //Value of information received
int num_chars = 0;                 //Position of the information message
int ok = 0;                        //Don't verify next statement.
int digital_pin_selected;          //Digital pin selected
int state_selected;                //State selected (0 or 1)
int synchro = 0;                   //syncho verified if the 
int num_mes = 0;                   //Number of message received
String message;                    //The message

}

void Piwi::listen()
{
character = 666;
//Recording 24 times the digital value of the DATA pin before showing it
  for(int code = 1; code <= 8; code++)
  {
    //This delay is the same as on the Rpi code for synchronisation purpose
    //Without this delay, message will not be correctly transmit.
    delay(1);
    message = message + digitalRead(_receiver);
  }
  if ((message == "11111111") && (synchro == 0))
  { 
    num_mes++;
    synchro = 1;
  }
  if ((message == "11111111") && (synchro == 1))
  {
    num_mes++;
  }
  if ((message != "11111111" && (synchro == 1)))
  {
    if (num_mes > 10)
    {
    character = (num_mes/10-1);  
    num_mes = 0;
    synchro = 0;   
    }
    else
    {
    num_mes = 0;
    synchro = 0;
    }
  }
  //Clean the message 
  message = "";


//Using Character-------------------
  //If character not empty
  if (character != 666)
  {  
	
    //Take number of PIN
    if (num_chars == 0)
    {
      digital_pin_selected = character;
      num_chars = 1;
      ok = 1;
	  //Serial.print("PIN:");
	  //Serial.println(digital_pin_selected);
    }
    
    //Take State of Pin
    if (num_chars == 1 && ok == 0)
    {
      //Verify if state is coherent.
      if (character == 0 || character == 1)
      {
        state_selected = character;
        ok = 2;
		//Serial.print("STATE:");
		//Serial.println(state_selected);
      }
      
      //If state incoherent then discarded message
      if (character > 1)
      {
        ok = 0;
      }
      num_chars = 0;
      
    }   
    if (ok == 2)
    {
	  
	  if (digital_pin_selected != _receiver)
	  {
	  digitalWrite(digital_pin_selected,state_selected);
	  //Serial.println("OK");
	  }
    }
    
   ok = 0;
   
  }
}
