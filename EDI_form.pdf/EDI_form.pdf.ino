#include <LiquidCrystal.h> #Header file
#include <LiquidCrystal.h>
LiquidCrystal lcd(A5, A4, A3, A2, A1, A0);//Pin connection
#include "DHT.h"// 

char str[100]; //to ave 100 char
int i=0; // var
DHT dht; // sensor 
#define mo 3 // motor conection 3 no
#define rly1 12 // connection 12
#define rly2 13 // conection 13
#define led 11 // conection 11 
#include <SoftwareSerial.h>  // micro and gsm seriaal connection
#define DEBUG true // define debug var

int temp1=0,i1=0; // var def
int temp=0;

byte degree_symbol[8] = 
              {
                0b00111,
                0b00101,
                0b00111,
                0b00000,
                0b00000,
                0b00000,
                0b00000,
                0b00000
              }; // Temp symbol showing

volatile unsigned long duration=0; // var def
//unsigned char i[5];
unsigned int j[40];
unsigned char value=0;
unsigned answer=0;
int z=0;
int b=1;
int s1=0;
void setup() 
{
 dht.setup(2);// Tem and hum sensor setup
  pinMode(mo, INPUT); // moister sensor input
   pinMode(rly1, OUTPUT); // fan output
    pinMode(rly2, OUTPUT); // motor output
     pinMode(led, OUTPUT);
lcd.begin(16, 2); // LCd star comand
Serial.begin(9600); // speed of serial communication, bodrate 
        // Setting the baudrate at 9600
     // Set the baudrate according to you esp's baudrate. your esp's baudrate might be different from mine
  // Setting the echoPin as Input pin
 // delay(5000);

attachInterrupt(0, increment, RISING); // increment use for doing another task by micro
lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("WELCOME TO GREEN");
  lcd.setCursor(0,1);
 dht.setup(2);
  lcd.print("HOUSE MONITORING");
   delay(1000);

Serial.println("AT"); //GSM module cmd
delay(4000);
Serial.println("AT+CNMI=2,2,0,0,0");
  delay(2000);
  Serial.println("AT+CMGF=1");
  delay(1500);
 lcd.clear();
  
}
void loop() // continiously running condn 
{
delay(dht.getMinimumSamplingPeriod());  /* Delay of amount equal to sampling period */  
  float humidity = dht.getHumidity();     /* Get humidity value */
  float temperature = dht.getTemperature(); //Temp value save
lcd.clear(); 
 lcd.print("Temp = "); //temp value print
 lcd.setCursor(0,1); //
 lcd.print("Humidity = ");
 //lcd.createChar(1, degree_symbol);
 lcd.setCursor(9,0);
 lcd.write(1);
 lcd.print("C");
 lcd.setCursor(13,1);
 lcd.print("%");
lcd.setCursor(7,0);
lcd.print(temperature, 1);
lcd.setCursor(11,1);
lcd.print(humidity, 1);
delay(20);
{

if(temperature>40)
{

 lcd.clear(); 
  lcd.print("HIGH TEMP LEVEL");
   delay(100);
lcd.clear(); 
  lcd.print("TURNING ON DEVICE");
   delay(100);
 digitalWrite(led,HIGH); // LED on
  
}
if (temp==1)
{
temp=0;
lcd.clear();
lcd.print("SMS MOTOR ON");
digitalWrite(rly2,HIGH);
delay(1000);
}
if (temp1==1 && s1==1)
{
temp1=0;
s1=0;
lcd.clear();
lcd.print("SMS MOTOR OFF");
digitalWrite(rly2,LOW);
delay(1000);
}

if(temperature<40)
{
 digitalWrite(led,LOW);
}
if(humidity<65)
{
 digitalWrite(rly1,LOW);
  
}
if(humidity>65)
{

 lcd.clear(); 
  lcd.print("HIGH HUMI LEVEL");
   delay(100);
lcd.clear(); 
  lcd.print("FAN IS ON");
   delay(100);
   digitalWrite(rly1,HIGH);
}
if (digitalRead(mo)==0)
{
  temp1=1;

}
else
{
lcd.clear(); 
  lcd.print("LOW WATER CONTENT");
   delay(100);
lcd.clear(); 
  lcd.print("PUMP IS ON");
   delay(100);
   digitalWrite(rly2,HIGH);
SendMessage();
temp1=0;
delay(2000);
 digitalWrite(rly2,LOW);

}
}}

void increment() {
  while(Serial.available())
  {
    char ch=(char)Serial.read();
    str[i++]=ch;
    if(ch == '*')
    {
      temp=1;
      lcd.clear();
      lcd.print("Message Received"); 
      s1=0;
      delay(1000);
    }
 if(ch == '#')
    {
      s1=1;
      lcd.clear();
      lcd.print("Message Received");
      delay(1000);
    }

  }}
void SendMessage()
{ Serial.println("AT");    //Sets the GSM Module in Text Mode
  delay(1000);  
  Serial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(1000);  // Delay of 1000 milli seconds or 1 second
  Serial.println("AT+CMGS=\"+917721853465\"\r"); // Replace x with mobile number
  delay(1000);
  Serial.println("LOW WATER DETECTED TURNING MOTOR ON.....");// The SMS text you want to send
  delay(100);
  Serial.println((char)26);
  
  lcd.setCursor(0,0);
  lcd.print("MESSAGE SENT");
  
   //lcd.print(n);
 //delay(2500);
 delay(1000);
 lcd.clear();// ASCII code of CTRL+Z
 // delay(1000);
}
