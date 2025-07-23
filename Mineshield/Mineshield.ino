#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ArduinoJson.h>

const char* ssid = "project";
const char* password = "00000000";

ESP8266WebServer server(80);
String formattedData = "No data received";
String serialBuffer = "";

void setup() {
  Serial.begin(9600);
  WiFi.begin(ssid, password);

  Serial.print("Connecting to WiFi...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("\nConnected to WiFi");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  server.on("/", []() {
    String html = "<!DOCTYPE html><html lang='en'><head>";
    html += "<meta charset='UTF-8'>";
    html += "<meta name='viewport' content='width=device-width, initial-scale=1'>";
    html += "<title>Mine Exploration Data</title>";
    html += "<link rel='stylesheet' href='https://cdnjs.cloudflare.com/ajax/libs/font-awesome/6.0.0/css/all.min.css'>";

    html += "<style>";
    html += "body { font-family: 'Arial', sans-serif; text-align: center; background: #121212; color: #fff; margin: 0; padding: 20px; }";
    html += "#container { max-width: 500px; width: 90%; margin: auto; padding: 20px; background: rgba(255, 255, 255, 0.1); border-radius: 15px; box-shadow: 0 0 15px rgba(0, 255, 255, 0.5); }";
    html += "h1 { color: #0ff; text-shadow: 0px 0px 10px #0ff; font-size: 24px; }";
    html += "#data-container { background: #222; padding: 15px; border-radius: 10px; font-size: 18px; text-align: left; display: inline-block; width: 90%; }";
    html += "#alert { display: none; padding: 12px; background: red; color: white; border-radius: 8px; font-size: 18px; font-weight: bold; box-shadow: 0 0 15px red; margin-top: 10px; animation: blink 1s infinite alternate; }";
    html += "@keyframes blink { 0% { opacity: 1; } 100% { opacity: 0.5; } }";
    html += "</style></head><body>";
    
    html += "<div id='container'>";
    html += "<h1><i class='fas fa-mountain'></i> Mine Exploration Data</h1>";
    html += "<div id='alert'>⚠ DANGER! Risk Detected! ⚠</div>";
    html += "<div id='data-container'>" + formattedData + "</div>";
    html += "<script>";
    html += "setInterval(updateData, 2000); function updateData() { var xhr = new XMLHttpRequest(); xhr.onreadystatechange = function() { if (xhr.readyState == 4 && xhr.status == 200) { document.getElementById('data-container').innerHTML = xhr.responseText; let alertBox = document.getElementById('alert'); let co = parseInt(xhr.responseText.match(/CO: (\\d+)/)[1]); let smoke = parseInt(xhr.responseText.match(/Smoke: (\\d+)/)[1]); let airQuality = parseInt(xhr.responseText.match(/Air Quality: (\\d+)/)[1]); let dist1 = parseInt(xhr.responseText.match(/Dist1: (\\d+)/)[1]); let dist2 = parseInt(xhr.responseText.match(/Dist2: (\\d+)/)[1]); let dist3 = parseInt(xhr.responseText.match(/Dist3: (\\d+)/)[1]); if (co > 170 || smoke > 550 || airQuality > 570 || dist1 < 100 || dist2 < 100 || dist3 < 100) { alertBox.style.display = 'block'; var audio = new Audio('https://www.soundjay.com/button/beep-07.wav'); audio.play(); } else { alertBox.style.display = 'none'; } } }; xhr.open('GET', '/data', true); xhr.send(); }";
    html += "</script></body></html>";
    server.send(200, "text/html", html);
  });

  server.on("/data", []() {
    server.send(200, "text/plain", formattedData);
  });
  
  server.begin();
  Serial.println("Web server started.");
}

void loop() {
  server.handleClient();
  while (Serial.available()) {
    char c = Serial.read();
    if (c == '\n') {
      processSerialData(serialBuffer);
      serialBuffer = "";
    } else {
      serialBuffer += c;
    }
  }
}

void processSerialData(String jsonData) {
  jsonData.trim();
  StaticJsonDocument<200> doc;
  DeserializationError error = deserializeJson(doc, jsonData);
  if (!error) {
    formattedData = "";
    formattedData += "Smoke: " + String(doc["smoke"].as<int>()) + " ppm<br>";
    formattedData += "CO: " + String(doc["co"].as<int>()) + " ppm<br>";
    formattedData += "Air Quality: " + String(doc["airQuality"].as<int>()) + " ppm<br>";
    formattedData += "Dist1: " + String(doc["dist1"].as<int>()) + " cm<br>";
    formattedData += "Dist2: " + String(doc["dist2"].as<int>()) + " cm<br>";
    formattedData += "Dist3: " + String(doc["dist3"].as<int>()) + " cm";
    Serial.println("Updated Data: " + formattedData);
  } else {
    Serial.println("JSON Parsing Failed: " + jsonData);
  }
}