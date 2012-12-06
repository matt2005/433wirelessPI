#/bin/bash

if [ $# -ne 2 ]
then
	echo "Arduino Wireless Communicator by Sarrailh Remi"
	echo "Public Domain"
	echo "----------------------------------------------"
	echo "Usage: `basename $0` digital_pin state"
	echo "Example: `basename $0` 5 0"
	echo "----------------------------------------------"
else
./arduino_wireless $1
./arduino_wireless $2
fi
