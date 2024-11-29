#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClientSecure.h>
#include <ArduinoJson.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <AudioFileSourceHTTPStream.h>
#include <AudioFileSourceBuffer.h>
#include <AudioGeneratorMP3.h>
#include <AudioOutputI2SNoDAC.h>

const char* ssid = "your_ssid";
const char* password = "your_password";

const char* serverAddress = "https://alphaclothes.com.br/horacerta/api2.php";
const char* audioServerAddress = "https://alphaclothes.com.br/horacerta/audios/";

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org");

const long gmtOffset_sec = -3 * 3600; 

AudioGeneratorMP3 *mp3;
AudioFileSourceHTTPStream *file;
AudioFileSourceBuffer *buff;
AudioOutputI2SNoDAC *out;

void setup() {
  Serial.begin(115200);
  
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Conectando...");
  }
  Serial.println("Conectado ao WiFi");

  timeClient.begin();
  timeClient.setUpdateInterval(3600000);
  timeClient.setTimeOffset(gmtOffset_sec);
}

void playAudio(const char* filename) {
  String fullUrl = String(audioServerAddress) + filename;
  file = new AudioFileSourceHTTPStream(fullUrl.c_str());
  buff = new AudioFileSourceBuffer(file, 2048);
  out = new AudioOutputI2SNoDAC();
  mp3 = new AudioGeneratorMP3();
  
  mp3->begin(buff, out);
  
  while(mp3->isRunning()) {
    if (!mp3->loop()) mp3->stop();
  }
  
  delete file;
  delete buff;
  delete out;
  delete mp3;
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    WiFiClientSecure client;
    client.setInsecure();
    HTTPClient http;
    
    http.begin(client, serverAddress);
    int httpCode = http.GET();
    
    if (httpCode > 0) {
      String payload = http.getString();
      
      int startBracket = payload.indexOf('[');
      if (startBracket != -1) {
        payload = payload.substring(startBracket);
      }
      
      DynamicJsonDocument doc(1024);
      DeserializationError error = deserializeJson(doc, payload);
      
      if (error) {
        Serial.print(F("deserializeJson() failed: "));
        Serial.println(error.c_str());
      } else {
        timeClient.update();
        int currentHour = timeClient.getHours();
        int currentMinute = timeClient.getMinutes();
        
        Serial.print("Horário atual: ");
        Serial.print(currentHour);
        Serial.print(":");
        Serial.println(currentMinute);
        
        for (JsonObject horario : doc.as<JsonArray>()) {
          String scheduleTime = horario["horario"];
          int scheduleHour = scheduleTime.substring(0, 2).toInt();
          int scheduleMinute = scheduleTime.substring(3, 5).toInt();
          
          int timeDiff = (scheduleHour * 60 + scheduleMinute) - (currentHour * 60 + currentMinute);
          
          if (timeDiff == 10) {
            playAudio("10_minutos.mp3");
          } else if (timeDiff == 3) {
            playAudio("3_minutos.mp3");
          } else if (timeDiff == 1) {
            playAudio("1_minuto.mp3");
          } else if (timeDiff == 0) {
            playAudio("alexaLigar.mp3");
          } else if (timeDiff == -1) {
            playAudio("alexaDesligar.mp3");
          }
        }
      }
    }
    
    http.end();
  }
  
  delay(60000);
}
