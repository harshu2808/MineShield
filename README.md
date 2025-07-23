# Embedded IoT Safety Systems 🚨☀️📍

This repository contains two IoT-based embedded system projects developed to address real-world challenges in safety and monitoring using microcontrollers, sensors, and web technologies.

---

## 🔐 Project 1: **MineShield – Smart Mining Safety System**

### 🛠 Components Used
- MQ-2, MQ-135, MQ-9 Gas Sensors  
- Ultrasonic Sensors  
- Buzzer/Alarm (for audio alerts)  
- Microcontroller (e.g., NodeMCU or Arduino-based)  
- Web Server Interface (ESP8266-based)

### 🔍 Description
MineShield is a real-time underground mining safety system that:
- Detects poisonous gases using multiple gas sensors  
- Uses ultrasonic sensors for obstacle avoidance in low-visibility areas  
- Provides immediate local audio alerts  
- Supports remote monitoring via a web server for gas levels and hazard detection  
- Designed to proactively minimize hazards in underground environments

---

## ☀️ Project 2: **Solar-Powered IoT Device for Geo-Tagging CSR Assets**

### 🛠 Components Used
- ESP8266 NodeMCU (WiFi-enabled microcontroller)  
- GPS Module (NEO-6M)  
- MPU6050 (Accelerometer + Gyroscope)  
- SoftwareSerial & TinyGPS++ (Arduino libraries)  
- ESP8266WiFi, HTTPClient, ESP8266WebServer Libraries  
- ArduinoJson, Adafruit Sensor Libraries  
- PHP & MySQL for backend  
- HTML & CSS for dashboard UI

### 🔍 Description
A solar-powered IoT device designed for:
- Real-time geo-location and motion tracking  
- Displaying sensor and metadata through a browser-accessible dashboard  
- Fetching asset metadata via HTTP GET from a PHP-MySQL backend  
- Ideal for CSR use cases involving location-aware asset monitoring and reporting

---

## 📷 Screenshots & Diagrams
Coming soon...

---

## 🚀 How to Run (For Developers)
1. Flash the respective code to NodeMCU via Arduino IDE.
2. Update WiFi credentials and server endpoints in the code.
3. Use PHP & MySQL files to set up backend (for Project 2).
4. Power the device (solar or external) and access the dashboard via IP.

---

## 📂 Folder Structure
- `/MineShield/` - Code and schematics for the mining safety system  
- `/GeoTag-IoT/` - Code, backend, and UI files for the solar-powered geo-tagging system  

---

## 👨‍💻 Author
**Sukesh Reddy**  
Final Year Electronics & Communication Engineering  
Passionate about IoT, Embedded Systems, and Real-world Problem Solving  

---

## 📫 Contact
For collaboration, questions, or demo requests:  
📧 lyricsofsongs96@gmail.com  

---

## 🔗 License
This project is open-source under the MIT License.

