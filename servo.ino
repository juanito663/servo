#include <FirebaseESP32.h>
#include <WiFi.h>
#include "DHT.h"

#define FIREBASE_HOST "garaje-8fc81-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "5FIejTqUi1qAP9jvVuVROEqn02UcqS8j0zYA0qb2"
#define WIFI_SSID "Olivares"
#define WIFI_PASSWORD "208270508-88457067"

FirebaseData firebaseData;
String path = "/Test";
 // luz
void setup() {
  
  Serial.begin(9600);
  pinMode(2,OUTPUT);
  pinMode(27,OUTPUT);
  
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("[Wi-Fi]...Connecting");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);

  //Firewall that allows only GET and POST requests
  //Firebase.enableClassicRequest(firebaseData, true);
}

void loop() {
  Firebase.getInt(firebaseData, path + "/LED");
  Serial.println("Data= " + String(firebaseData.intData()));
  delay(200);
  if(firebaseData.intData()==1)
  {
    digitalWrite(2,HIGH);
    digitalWrite(27,HIGH);
  }
  else{
    digitalWrite(2,LOW);
    digitalWrite(27,LOW);
  }
 // Firebase.end(firebaseData);
}     
// ventilador 

#include <FirebaseESP32.h>
#include <WiFi.h>
#include "DHT.h"


#define FIREBASE_HOST "garaje-8fc81-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "5FIejTqUi1qAP9jvVuVROEqn02UcqS8j0zYA0qb2"
#define WIFI_SSID "Olivares"
#define WIFI_PASSWORD "208270508-88457067"
FirebaseData firebaseData;
String path = "/Test";
#include <FirebaseESP32.h>
#include <WiFi.h>
#include "DHT.h"

#define DHTPIN 14    

#define DHTTYPE DHT11   
DHT dht(DHTPIN, DHTTYPE);

FirebaseData firebaseData;
FirebaseJson json;

void setup() {

 Serial.begin(115200);
  dht.begin();
   WiFi.begin (WIFI_SSID, WIFI_PASSWORD);
   Serial.print("Connecting...");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
  Serial.println();
  Firebase.begin(FIREBASE_HOST,FIREBASE_Authorization_key);
  
}

void loop() {
 
  float hum = dht.readHumidity();
  float temp = dht.readTemperature();  
  
   if (isnan(hum) || isnan(temp)  ){
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  Serial.print("Temperature: ");
  Serial.print(temp);
  Serial.print("°C");
  Serial.print(" Humidity: ");
  Serial.print(hum);
  Serial.print("%");
  Serial.println();

  Firebase.setFloat(firebaseData, "/ESP32_APP/TEMPERATURE", temp);
  Firebase.setFloat(firebaseData, "/ESP32_APP/HUMIDITY", hum);
   delay(200);
}
//puerta 
#include <WiFi.h>

#include

#include <NTPClient.h>

#include <WiFiUdp.h>

#define FIREBASE_HOST "YOUR_FIRABSE_HOST"

#define FIREBASE_AUTH "YOUR_FIREBASE_AUTH"

#define WIFI_SSID "YOUR_WIFI_SID"

#define WIFI_PASSWORD "YOUR_WIFI_PASSWORD"

// Define NTP Client to get time

WiFiUDP ntpUDP;

NTPClient timeClient(ntpUDP);

// Variables to save date and time

String formattedDate;

String dayStamp;

String timeStamp;

//Define FirebaseESP32 data object

FirebaseData firebaseData;

FirebaseJson json;

String path = "/esp32";

String user = "jazmin";

String sensor = "prueba";

int valuePrueba = 12;

void setup()

{

  Serial.begin(115200);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  Serial.print("Connecting to Wi-Fi");

  while (WiFi.status() != WL_CONNECTED)

  {

    Serial.print(".");

    delay(300);

  }

  Serial.println();

  Serial.print("Connected with IP: ");

  Serial.println(WiFi.localIP());

  Serial.println();

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);

  Firebase.reconnectWiFi(true);

 //Size and its write timeout e.g. tiny (1s), small (10s), medium (30s) and large (60s).

  Firebase.setwriteSizeLimit(firebaseData, "tiny");

}

void loop()

{

    while(!timeClient.update()) {

      timeClient.forceUpdate();

    }

    formattedDate = timeClient.getFormattedDate();

    json.clear().add("Value", valuePrueba);

    json.add("Date", formattedDate);

    if (Firebase.pushJSON(firebaseData, path + "/" + user + "/" + sensor, json))

    {

      Serial.println("PASSED");

      Serial.println("PATH: " + firebaseData.dataPath());

      Serial.print("PUSH NAME: ");

      Serial.println(firebaseData.pushName());

      Serial.println("ETag: " + firebaseData.ETag());

      Serial.println("------------------------------------");

      Serial.println();

    }

    else

    {

      Serial.println("FAILED");

      Serial.println("REASON: " + firebaseData.errorReason());

      Serial.println("------------------------------------");

      Serial.println();

    }

 

    delay(1000);

}

