#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 20, 4); // I2C address 0x27, 20 column and 4 rows
#include <SoftwareSerial.h>
SoftwareSerial mySerial(3, 2);
const int trigPin = 9;
const int echoPin = 10;
const int level4 = 8;
const int level3 = 11;
const int level2 = 12;
const int level1 = 13;


unsigned char sentSMS1 = 0;
unsigned char sentSMS2 = 0;
unsigned char sentSMS3 = 0;
unsigned char sentSMS4 = 0;

// defines variables
long duration;
int distance;
int safetyDistance;
 
void setup() {
lcd.init();               // initialize the lcd
lcd.backlight();
lcd.clear();              // config echo pin to input mode
pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
pinMode(echoPin, INPUT); // Sets the echoPin as an Input
pinMode(level4, OUTPUT);
pinMode(level3, OUTPUT);
pinMode(level2, OUTPUT);
pinMode(level1, OUTPUT);
//Serial.begin(9600); // Starts the serial communication
}
 
void loop() {
// Clears the trigPin
digitalWrite(trigPin, LOW);
delayMicroseconds(2);
 
// Sets the trigPin on HIGH state for 10 micro seconds
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);
 
// Reads the echoPin, returns the sound wave travel time in microseconds
duration = pulseIn(echoPin, HIGH);
 
// Calculating the distance
distance= duration*0.034/2;
 
safetyDistance = distance;
// Prints the distance on the LCD
lcd.setCursor(0, 0);
lcd.print("WaterLvl: ");
lcd.print(distance);
lcd.print("cm");

if (distance <= 5 )
{
  digitalWrite(level4, LOW);
      if (sentSMS1 == 0) {
      sendMsg4();
      delay(500); 
      sentSMS1 = 1;
    }
}
else
{
  digitalWrite(level4, HIGH);
  sentSMS1 = 0;
}

if (distance <=10 )
{
  digitalWrite(level3, LOW);
     if (sentSMS2 == 0){
     sendMsg3();
     delay(500);
     sentSMS2 = 1;
   }
}
else
{
  digitalWrite(level3, HIGH);
   sentSMS2 = 0;

}

if (distance <=15)
{
  digitalWrite(level2, LOW);
  if(sentSMS3 == 0) {
    sendMsg2();
    delay(500);
    sentSMS3 = 1;
  }
}
else
{
  digitalWrite(level2, HIGH);
  sentSMS3 = 0;

}
if (distance <=25 )
{
  digitalWrite(level1, LOW);
    if (sentSMS4 == 0){
      sendMsg1();
      delay(500);
      sentSMS4 = 1;
      }
}
else
{
  digitalWrite(level1, HIGH);
  sentSMS4 = 0;
}
 


delay(500);
}

void sendMsg1(){
 Serial.begin(9600);
  
 
  mySerial.begin(9600);

  Serial.println("Initializing..."); 
  delay(1000);

  mySerial.println("AT");
  updateSerial();

  mySerial.println("AT+CMGF=1"); 
  updateSerial();
  mySerial.println("AT+CMGS=\"+xxxxxxxxxxxxxxxx\""); // enter your phone number here (prefix country code)
  updateSerial();
  mySerial.print("The flood rises at level 1!"); // enter your message here
  updateSerial();
  mySerial.write(26);
}

void sendMsg2(){
 Serial.begin(9600);
  
 
  mySerial.begin(9600);

  Serial.println("Initializing..."); 
  delay(1000);

  mySerial.println("AT");
  updateSerial();

  mySerial.println("AT+CMGF=1"); 
  updateSerial();
  mySerial.println("AT+CMGS=\"+xxxxxxxxxxxxxxxx\""); // enter your phone number here (prefix country code)
  updateSerial();
  mySerial.print("The flood rises at level 2!"); // enter your message here
  updateSerial();
  mySerial.write(26);
}

void sendMsg3(){
 Serial.begin(9600);
  
 
  mySerial.begin(9600);

  Serial.println("Initializing..."); 
  delay(1000);

  mySerial.println("AT");
  updateSerial();

  mySerial.println("AT+CMGF=1"); 
  updateSerial();
  mySerial.println("AT+CMGS=\"+xxxxxxxxxxxx\""); // enter your phone number here (prefix country code)
  updateSerial();
  mySerial.print("The flood rises at level 3! Caution!"); // enter your message here
  updateSerial();
  mySerial.write(26);
}

void sendMsg4(){
 Serial.begin(9600);
  
 
  mySerial.begin(9600);

  Serial.println("Initializing..."); 
  delay(1000);

  mySerial.println("AT");
  updateSerial();

  mySerial.println("AT+CMGF=1"); 
  updateSerial();
  mySerial.println("AT+CMGS=\"+xxxxxxxxxx\""); // enter your phone number here (prefix country code)
  updateSerial();
  mySerial.print("The flood rises at level 4! Critical!"); // enter your message here
  updateSerial();
  mySerial.write(26);
}
void updateSerial()
{
  delay(500);
  while (Serial.available()) 
  {
    mySerial.write(Serial.read());//Forward what Serial received to Software Serial Port
  }
  while(mySerial.available()) 
  {
    Serial.write(mySerial.read());//Forward what Software Serial received to Serial Port
  }
}