#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

#define trigPin D6
#define echoPin D7
#define buzzer 12
 
const char* ssid = "*****";
const char* password = "*********";
int sound = 250;
 
void setup() {
  Serial.begin(115200);
  delay(10);
 
  // Connect to WiFi network
  Serial.print("\n\nConnecting to: ");
  Serial.println(ssid);
 
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("WiFi connected");
 
  // Print the IP address
  Serial.print("Wifi local IP: ");
  Serial.print(WiFi.localIP());
  Serial.println("");

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzer, OUTPUT);
}
 
void loop() {
  
  long duration, distance;
  digitalWrite(trigPin, LOW); 
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) / 29.1;
 
 if (distance >100 || distance <= 0){
    Serial.println("No object detected");
    noTone(buzzer);
  }
  else {
    Serial.print(distance);
    Serial.println(" cm Object detected");
    tone(buzzer, sound);
    sendResult(distance);
  }
  delay(500);
}

void sendResult(long distance) {
  // Check if a client has connected
  HTTPClient httpClient;
  Serial.print("[HTTP] begin...\n");
  String url = "http://192.168.43.19:8080/arduino/set-distance.php?distance=" + String(distance);
  httpClient.begin(url); //HTTP
  int httpCode = httpClient.GET();
  if(httpCode > 0) {
      // HTTP header has been send and Server response header has been handled
      Serial.printf("[HTTP] GET... code: %d\n", httpCode);
      if(httpCode == HTTP_CODE_OK) {
          String payload = httpClient.getString();
          Serial.println(payload);
      }
  } else {
      Serial.printf("[HTTP] GET... failed, error: %s\n", httpClient.errorToString(httpCode).c_str());
  }

  httpClient.end();
}

