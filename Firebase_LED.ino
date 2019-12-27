#include <WiFi.h>                                                // esp32 library
#include <IOXhop_FirebaseESP32.h>                                             // firebase library

#define FIREBASE_HOST "home-automation-a55b6.firebaseio.com"                         // the project name address from firebase id
#define FIREBASE_AUTH "xPQMO5z9ju5Nu0kk5hzdcKlxBILL3siOX0zsjJIp"                    // the secret key generated from firebase
#define WIFI_SSID "Amplifiers"                                          // input your home or public wifi name
#define WIFI_PASSWORD "123456789"                                    //password of wifi ssid

String fireStatus = "";                                                     // led status received from firebase
int led = 5;                                                               

void setup() {

  Serial.begin(9600);
  delay(1000);
  pinMode(5, OUTPUT);                
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);                                      //try to connect with wifi

  Serial.print("Connecting to ");

  Serial.print(WIFI_SSID);

  while (WiFi.status() != WL_CONNECTED) {

    Serial.print(".");

    delay(500);

  }

  Serial.println();

  Serial.print("Connected to ");

  Serial.println(WIFI_SSID);

  Serial.print("IP Address is : ");

  Serial.println(WiFi.localIP());                                                      //print local IP address

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);                                       // connect to firebase

  Firebase.setString("LED_STATUS", "OFF");                                          //send initial string of led status

}

void loop() {

  fireStatus = Firebase.getString("ESP8266_Test/FAN");                     // get led status input from firebase
  Serial.println(fireStatus);
if(fireStatus == "\\\"ON\\\""){ 
    Serial.println("Led Turned ON");                 

    digitalWrite(2, HIGH);                                                         // make output led ON

  }

  else if (fireStatus == "\\\"OFF\\\"") {              // compare the input of led status received from firebase

    Serial.println("Led Turned OFF");

    digitalWrite(2, LOW);                                                         // make output led OFF

  }

  else {

    Serial.println("Wrong Credential! Please send ON/OFF");

  }

}
