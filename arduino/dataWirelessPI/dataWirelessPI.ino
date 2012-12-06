/*
  433.92Mhz Message Receiver.
  
  Receive Number : 0 to 9
  The receiver detected octet message :1111111
  In order to avoid receiving error    
  
  -----------------
  How do it works:
  15 = 0
  25 = 1
  35 = 2
  45 = 3
  55 = 4
  65 = 5
  75 = 6
  85 = 7
  95 = 8
  105 = 9
  -----------------
*/

int synchro = 0;                   //syncho verified if the 
int num_mes = 0;                   //Number of message received
int character = 666;               //Value of information received
int num_chars = 0;                 //Position of the information message
int ok = 0;                        //Don't verify next statement.

int digital_pin_selected;          //Digital pin selected
int state_selected;                //State selected (0 or 1)

String message;                    //The message


int receive_char()
{
//Recording 24 times the digital value of the DATA pin before showing it
  for(int code = 1; code <= 8; code++)
  {
    //This delay is the same as on the Rpi code for synchronisation purpose
    //Without this delay, message will not be correctly transmit.
    delay(1);
    message = message + digitalRead(receiver);
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
  return character;
}

void pi_wirelesscontrol()
{
  character = receive_char();
  
  //If character not empty
  if (character != 666)
  {  
    //Take number of PIN
    if (num_chars == 0)
    {
      digital_pin_selected = character;
      num_chars = 1;
      ok = 1;
    }
    
    //Take State of Pin
    if (num_chars == 1 && ok == 0)
    {
      //Verify if state is coherent.
      if (character == 0 || character == 1)
      {
        state_selected = character;
        ok = 2;
      }
      
      //If state incoherent then discarded message
      if (character > 1)
      {
        ok = 1;
      }
      num_chars = 0;
      
    }   
    if (ok == 2)
    {
	  if (digital_pin_selected != receiver)
	  {
	  digitalWrite(digital_pin_selected,state_selected);
	  }
    }
    
   ok = 0;
   character = 666;
  }
}

/*PIN*/
int receiver = 2;              //Data Pin of the Receiver
/*PIN*/

//Setting things up
void setup() {
  // Remote Receiver are in Input mode
  pinMode(receiver, INPUT);
}


void loop() {
  pi_wirelesscontrol();
}
