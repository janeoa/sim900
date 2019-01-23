#include <SoftwareSerial.h>

SoftwareSerial mySerial(7, 8); // RX, TX

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  mySerial.begin(19200);
  delay(5000);
  Serial.println("ready");
  sendSMS("\"+77058400077\"", "Example");
}

char inbuff[255];
int  ibi = 0;
int  mode = 0; 
/*  0 - no
 *  1 - number
 *  2 - text
*/
                  
void loop() {
  if (mySerial.available())
    Serial.write(mySerial.read());

  if (Serial.available()){
    char c = Serial.read();  //#PN&
    mySerial.write(Serial.read());
    switch(mode){
      case 0: {
        if (c == '#') {
            c = Serial.read();
            switch(c){
              case 'P': {c = Serial.read(); if(c == '&') mode = 1; Serial.println();}break;
              case 'M': {c = Serial.read(); if(c == '&') mode = 2;}break;
              case 'E': {c = Serial.read(); if(c == '&') mode = 3;}break;
            }
        }
      }break;
      case 1: {
  //      if()
      }break;
    }
  }
}

void sendSMS(char *phone, char *text) {
  // AT command to set mySerial to SMS mode
  mySerial.print("AT+CMGF=1\r"); 
  delay(100);

  // REPLACE THE X's WITH THE RECIPIENT'S MOBILE NUMBER
  // USE INTERNATIONAL FORMAT CODE FOR MOBILE NUMBERS
  char buff[100];
  sprintf(buff, "AT + CMGS = \"%s\"", phone);
  mySerial.println(buff); 
  delay(100);
  
  // REPLACE WITH YOUR OWN SMS MESSAGE CONTENT
  mySerial.println(text); 
  delay(100);

  // End AT command with a ^Z, ASCII code 26
  mySerial.println((char)26); 
  delay(100);
  mySerial.println();
  // Give module time to send SMS
  delay(5000); 
}
