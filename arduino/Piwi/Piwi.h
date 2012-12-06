/*
  PiWi.h - Library for Wireless Communication with the Raspberry PI
  It used 433.92Mhz Emitter or Receiver.
  Created by Sarrailh Remi
  Released into the public domain.
*/

#ifndef PiWi_h
#define PiWi_h

#include "Arduino.h"

class Piwi
{
  public:
    Piwi(int receiver);
    void listen();
  private:
	int _receiver;
	int character;                 //Value of information received
	int num_chars;                 //Position of the information message
	int ok;                        //Don't verify next statement.
	int digital_pin_selected;      //Digital pin selected
	int state_selected;            //State selected (0 or 1)
	int synchro;                   //syncho verified if the 
	int num_mes;                   //Number of message received
	String message;                //The message
};


#endif