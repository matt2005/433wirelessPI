433wirelessPI
=============
This GITHUB contains programs to communicate with objects with 433.92Mhz Receiver with an Raspberry PI

You will need :
- An raspberry PI
- An 433.92Mhz Transmitter

That's it!

Objects you can control with this code:
-------------------------------------------
Arduino
SCS 3616-2 Power Outlet
-------------------------------------------

SCS 3616-2---------------------------------
/rpi/scs_s3616

This program put SCS3616-2 Outlet On/Off

WARNING: KEEP IN MIND THAT THESES OUTLETS CAN BE CONTROL BY ANYONE KNOWING THE CODES AND WILL NOT WORK IF 433.92Mhz is saturated.
		 NEVER USE THIS FOR CRITICAL APPLICATIONS.

Exemple of usage : ./scs_s3616 a1 1 (Put A1 Outlet On)

You have to be root to execute this program.

Every codes has been tested and can be found inside : /rpi/scs_s3816_2/ (in text and audio format)
---------------------------------------------

Arduino-------------------------------------
/arduino/piwi

Piwi Library.
You have to copy this library inside arduino/librairies.

An example for how to use this can be founded inside the library.

Functions: 
Piwi piwi(2);  //Initiate Receiver at Digital Pin 2
piwi.listen(); //Listen to Transmitter

/rpi/ardwl_cs.sh
Put Digital Pin on Arduino on/off

Example: ardwl_cs.sh 6 1 (Put Digital Pin 6 on)
--------------------------------------------
 

