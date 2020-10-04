//Viral Science www.youtube.com/c/viralscience  www.viralsciencecreativity.com
//Blynk Home Automation with Physical Button and ON OFF State Feedback
//Scan the QR Code to get the app with pre-installed settings

#define BLYNK_PRINT Serial            
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>



BlynkTimer timer;

void checkPhysicalButton();

int relay1State = LOW;
int pushButton1State = HIGH;

int relay2State = LOW;
int pushButton2State = HIGH;



#define AUTH "6re3J-SG0d-FpkfkDvQ28Aoctsu4OeGp"  // You should get Auth Token in the Blynk App.  
#define WIFI_SSID "Hung"                   //Enter Wifi Name
#define WIFI_PASS "Yennhi2301@"                   //Enter wifi Password

#define SERVER "blynk-cloud.com "             // Comment-out if use Blynk hosted cloud service
#define PORT 8442

#define RELAY_PIN_1      D2
#define RELAY_PIN_2      D3  


#define PUSH_BUTTON_1    D5
#define PUSH_BUTTON_2    D6


#define VPIN_BUTTON_1    V1 
#define VPIN_BUTTON_2    V2

#define LED_1 D7
#define LED_2 D8

void LED_STT(){
 
  digitalWrite(LED_1,HIGH);
  delay(100);
  digitalWrite(LED_2,HIGH);
  delay(100);
  digitalWrite(LED_1,LOW);
  delay(100);
  digitalWrite(LED_2,LOW);
  delay(100);
}
 

#define OTA_HOSTNAME "Home_Automation"


BLYNK_CONNECTED() {

  // Request the latest state from the server

  Blynk.syncVirtual(VPIN_BUTTON_1);
  Blynk.syncVirtual(VPIN_BUTTON_2);
   

  // Alternatively, you could override server state using:
 // Blynk.virtualWrite(VPIN_BUTTON_1, relay1State);
 // Blynk.virtualWrite(VPIN_BUTTON_2, relay2State);
 // Blynk.virtualWrite(VPIN_BUTTON_3, relay3State);
 // Blynk.virtualWrite(VPIN_BUTTON_4, relay4State);

}

// When App button is pushed - switch the state

BLYNK_WRITE(VPIN_BUTTON_1) {
  relay1State = param.asInt();
  digitalWrite(RELAY_PIN_1, relay1State);
}

BLYNK_WRITE(VPIN_BUTTON_2) {
  relay2State = param.asInt();
  digitalWrite(RELAY_PIN_2, relay2State);
}


void checkPhysicalButton()
{
  if (digitalRead(PUSH_BUTTON_1) == LOW) {
    // pushButton1State is used to avoid sequential toggles
    if (pushButton1State != LOW) {

      // Toggle Relay state
      relay1State = !relay1State;
      digitalWrite(RELAY_PIN_1, relay1State);

      // Update Button Widget
      Blynk.virtualWrite(VPIN_BUTTON_1, relay1State);
    }
    pushButton1State = LOW;
  } else {
    pushButton1State = HIGH;
  }

  if (digitalRead(PUSH_BUTTON_2) == LOW) {
    // pushButton2State is used to avoid sequential toggles
    if (pushButton2State != LOW) {

      // Toggle Relay state
      relay2State = !relay2State;
      digitalWrite(RELAY_PIN_2, relay2State);

      // Update Button Widget
      Blynk.virtualWrite(VPIN_BUTTON_2, relay2State);
    }
    pushButton2State = LOW;
  } else {
    pushButton2State = HIGH;
  }

}

void setup()
{

  Serial.begin(115200);
  Blynk.begin(AUTH, WIFI_SSID, WIFI_PASS,"blynk-cloud.com", 8442);
  
  pinMode(LED_1, OUTPUT);
  pinMode(RELAY_PIN_1, OUTPUT);
  pinMode(PUSH_BUTTON_1, INPUT_PULLUP);
  digitalWrite(RELAY_PIN_1, relay1State);

  pinMode(LED_2, OUTPUT);
  pinMode(RELAY_PIN_2, OUTPUT);
  pinMode(PUSH_BUTTON_2, INPUT_PULLUP);
  digitalWrite(RELAY_PIN_2, relay2State);
  for(int i=0;i<30;i++){
  LED_STT();
  }


  

  // Setup a function to be called every 100 ms
  timer.setInterval(500L, checkPhysicalButton);

}

void loop()

{
  if (WiFi.status() == WL_CONNECTED){
  digitalWrite(LED_1,HIGH);
  
  digitalWrite(LED_2,HIGH);
  Blynk.run();
}
  timer.run();
  if (WiFi.status() != WL_CONNECTED){
    digitalWrite(LED_1,HIGH);
  
  digitalWrite(LED_2,LOW);
if (digitalRead(PUSH_BUTTON_1) == LOW) {
    // pushButton1State is used to avoid sequential toggles
    if (pushButton1State != LOW) {

      // Toggle Relay state
      relay1State = !relay1State;
      digitalWrite(RELAY_PIN_1, relay1State);

      // Update Button Widget
     
    }
    pushButton1State = LOW;
  } else {
    pushButton1State = HIGH;
  }

  if (digitalRead(PUSH_BUTTON_2) == LOW) {
    // pushButton2State is used to avoid sequential toggles
    if (pushButton2State != LOW) {

      // Toggle Relay state
      relay2State = !relay2State;
      digitalWrite(RELAY_PIN_2, relay2State);

      // Update Button Widget
      
    }
    pushButton2State = LOW;
  } else {
    pushButton2State = HIGH;
  }
 
}
}
