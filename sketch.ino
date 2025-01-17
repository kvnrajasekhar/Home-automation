#define BLYNK_TEMPLATE_ID "TMPLTiPE10Xt" 
#define BLYNK_DEVICE_NAME "Class Room" 
#define BLYNK_AUTH_TOKEN 
"FxGXLYwznRVovFThefpk93MU7_ZT9ZP" 
// Your WiFi credentials. 
// Set password to "" for open networks. 
char ssid[] = "wifi_username"; 
char pass[] = "paswword@12345"; 
bool fetch_blynk_state = true; 
//#define BLYNK_PRINT Serial 
#include <ESP8266WiFi.h> 
#include <BlynkSimpleEsp8266.h> 
// define the GPIO connected with Relays and switches 
#define RelayPin1 5  //D1 
#define RelayPin2 4  //D2 
#define RelayPin3 14 //D5 
#define RelayPin4 12 //D6 
#define SwitchPin1 10  //SD3 
#define SwitchPin2 D3   //D3  
#define SwitchPin3 13  //D7 
#define SwitchPin4 3   //RX 
#define wifiLed   16   //D0 
//Change the virtual pins according the rooms 
#define VPIN_BUTTON_1    V5 
#define VPIN_BUTTON_2    V6 
#define VPIN_BUTTON_3    V7  
#define VPIN_BUTTON_4    V8 
// Relay State 
bool toggleState_1 = LOW;  
bool toggleState_2 = LOW 
bool toggleState_3 = LOW;  
bool toggleState_4 = LOW 
// Switch State 
bool SwitchState_1 = LOW; 
bool SwitchState_2 = LOW; 
bool SwitchState_3 = LOW; 
bool SwitchState_4 = LOW; 
int wifiFlag = 0; 
char auth[] = BLYNK_AUTH_TOKEN; 
BlynkTimer timer; 
// When App button is pushed - switch the state 
BLYNK_WRITE(VPIN_BUTTON_1) { 
toggleState_1 = param.asInt(); 
digitalWrite(RelayPin1, !toggleState_1); 
} 
BLYNK_WRITE(VPIN_BUTTON_2) { 
toggleState_2 = param.asInt(); 
digitalWrite(RelayPin2, !toggleState_2); 
} 
BLYNK_WRITE(VPIN_BUTTON_3) { 
toggleState_3 = param.asInt(); 
digitalWrite(RelayPin3, !toggleState_3); 
} 
BLYNK_WRITE(VPIN_BUTTON_4) { 
toggleState_4 = param.asInt(); 
digitalWrite(RelayPin4, !toggleState_4); 
} 
void checkBlynkStatus() { // called every 3 seconds by SimpleTimer 
bool isconnected = Blynk.connected(); 
if (isconnected == false) { 
wifiFlag = 1; 
Serial.println("Blynk Not Connected"); 
digitalWrite(wifiLed, HIGH); 
} 
if (isconnected == true) { 
wifiFlag = 0; 
if (!fetch_blynk_state){ 
Blynk.virtualWrite(VPIN_BUTTON_1, toggleState_1); 
Blynk.virtualWrite(VPIN_BUTTON_2, toggleState_2); 
Blynk.virtualWrite(VPIN_BUTTON_3, toggleState_3); 
Blynk.virtualWrite(VPIN_BUTTON_4, toggleState_4); 
} 
digitalWrite(wifiLed, LOW); 
Serial.println("Blynk Connected"); 
} 
} 
BLYNK_CONNECTED() { 
// Request the latest state from the server 
if (fetch_blynk_state){ 
Blynk.syncVirtual(VPIN_BUTTON_1); 
Blynk.syncVirtual(VPIN_BUTTON_2); 
Blynk.syncVirtual(VPIN_BUTTON_3); 
Blynk.syncVirtual(VPIN_BUTTON_4); 
} 
} 
void manual_control() 
{ 
if (digitalRead(SwitchPin1) == LOW && SwitchState_1 == LOW) { 
digitalWrite(RelayPin1, LOW); 
toggleState_1 = 1; 
SwitchState_1 = HIGH; 
Blynk.virtualWrite(VPIN_BUTTON_1, toggleState_1); 
Serial.println("Switch-1 on"); 
} 
if (digitalRead(SwitchPin1) == HIGH && SwitchState_1 == HIGH) { 
digitalWrite(RelayPin1, HIGH); 
toggleState_1 = 0; 
SwitchState_1 = LOW; 
Blynk.virtualWrite(VPIN_BUTTON_1, toggleState_1); 
Serial.println("Switch-1 off"); 
} 
if (digitalRead(SwitchPin2) == LOW && SwitchState_2 == LOW) { 
digitalWrite(RelayPin2, LOW); 
toggleState_2 = 1; 
SwitchState_2 = HIGH; 
Blynk.virtualWrite(VPIN_BUTTON_2, toggleState_2); 
Serial.println("Switch-2 on"); 
} 
if (digitalRead(SwitchPin2) == HIGH && SwitchState_2 == HIGH) { 
digitalWrite(RelayPin2, HIGH); 
toggleState_2 = 0; 
SwitchState_2 = LOW; 
Blynk.virtualWrite(VPIN_BUTTON_2, toggleState_2); 
Serial.println("Switch-2 off"); 
} 
if (digitalRead(SwitchPin3) == LOW && SwitchState_3 == LOW) { 
digitalWrite(RelayPin3, LOW); 
toggleState_3 = 1; 
SwitchState_3 = HIGH; 
Blynk.virtualWrite(VPIN_BUTTON_3, toggleState_3); 
Serial.println("Switch-3 on"); 
} 
if (digitalRead(SwitchPin3) == HIGH && SwitchState_3 == HIGH) { 
digitalWrite(RelayPin3, HIGH); 
toggleState_3 = 0; 
SwitchState_3 = LOW; 
Blynk.virtualWrite(VPIN_BUTTON_3, toggleState_3); 
Serial.println("Switch-3 off"); 
} 
if (digitalRead(SwitchPin4) == LOW && SwitchState_4 == LOW) { 
digitalWrite(RelayPin4, LOW); 
toggleState_4 = 1; 
SwitchState_4 = HIGH; 
Blynk.virtualWrite(VPIN_BUTTON_4, toggleState_4); 
Serial.println("Switch-4 on"); 
} 
if (digitalRead(SwitchPin4) == HIGH && SwitchState_4 == HIGH) { 
digitalWrite(RelayPin4, HIGH); 
toggleState_4 = 0; 
SwitchState_4 = LOW; 
Blynk.virtualWrite(VPIN_BUTTON_4, toggleState_4); 
Serial.println("Switch-4 off"); 
} 
}   
void setup() 
{ 
Serial.begin(9600); 
pinMode(RelayPin1, OUTPUT); 
pinMode(RelayPin2, OUTPUT); 
pinMode(RelayPin3, OUTPUT); 
pinMode(RelayPin4, OUTPUT); 
pinMode(wifiLed, OUTPUT); 
pinMode(SwitchPin1, INPUT_PULLUP); 
pinMode(SwitchPin2, INPUT_PULLUP); 
pinMode(SwitchPin3, INPUT_PULLUP); 
pinMode(SwitchPin4, INPUT_PULLUP); 
//During Starting all Relays should TURN OFF 
digitalWrite(RelayPin1, !toggleState_1); 
digitalWrite(RelayPin2, !toggleState_2); 
digitalWrite(RelayPin3, !toggleState_3); 
digitalWrite(RelayPin4, !toggleState_4); 
digitalWrite(wifiLed, HIGH); 
//Blynk.begin(auth, ssid, pass); 
WiFi.begin(ssid, pass); 
timer.setInterval(2000L, checkBlynkStatus); // check if Blynk server 
is connected every 2 seconds 
Blynk.config(auth); 
delay(1000); 
if (!fetch_blynk_state){ 
Blynk.virtualWrite(VPIN_BUTTON_1, toggleState_1); 
Blynk.virtualWrite(VPIN_BUTTON_2, toggleState_2); 
Blynk.virtualWrite(VPIN_BUTTON_3, toggleState_3); 
Blynk.virtualWrite(VPIN_BUTTON_4, toggleState_4); 
} 
} 
void loop() 
{  
manual_control(); 
Blynk.run(); 
timer.run(); 
} 
