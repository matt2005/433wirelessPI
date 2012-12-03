/*
  433.92Mhz Recepter on Pin 2
  Led1 on Pin 7
  Led2 on Pin 10
*/

int remotereceiver = 2;
int led1 = 7;
int led2 = 10;
String message;

//Setting things up
void setup() {
  
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  
  // Remote Receiver are on Input mode / Leds on Ouput
  pinMode(remotereceiver, INPUT);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
}


void loop() {
  
//This delay scrolls the message so if the message was received too early it correctly synchronize
delay(20);

  //Recording 24 times the digital of the DATA pins before showing it
  for(int code = 1; code <=24 ; code++)
  {
    //This delay is the same as on the Rpi code for synchronisation purpose.
    delay(10);
    message = message + digitalRead(remotereceiver);
  }
  
//Leds ON message 
  if (message == "111111111010101011111111")
  {
   Serial.println("And Rpi said let's there be light!");
   digitalWrite(led1,HIGH);
   digitalWrite(led2,HIGH);
  }

//Leds Off message 
   if (message == "111111111101011111111111")
  {
   Serial.println("And Rpi send everything to darkness!");
   digitalWrite(led1,LOW);
   digitalWrite(led2,LOW);
  } 

//Show message and reset it
   Serial.println(message);
   message = "";

}




