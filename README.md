# Smart-Industrial-Safety-Monitoring-System-
Smart IoT-based Industrial Safety Monitoring System using ESP32 for real-time monitoring of vibration, fire, temperature, noise, current, and liquid leakage with automatic machine protection and cloud connectivity.
## 📌 Overview
The **Smart Industrial Safety Monitoring System** is an IoT-based project designed to improve industrial safety and machine protection.  
The system continuously monitors industrial conditions such as:

- Machine vibration
- Fire detection
- Noise level
- Current consumption
- Temperature monitoring
- Liquid leakage detection

If any abnormal condition is detected, the system automatically:
- Activates buzzer alerts
- Displays warning indications
- Disconnects machine power using relay protection

The project uses an **ESP32 microcontroller** for real-time monitoring and cloud connectivity.

---

# 🎯 Objectives

- Prevent industrial accidents
- Protect industrial machines
- Monitor industrial parameters in real time
- Provide automatic emergency protection
- Enable IoT-based remote monitoring

---

# 🛠 Components Used

| Component | Purpose |
|---|---|
| ESP32 | Main microcontroller |
| SW-420 Vibration Sensor | Detect machine vibration |
| Flame Sensor | Fire detection |
| KY-037 Sound Sensor | Noise monitoring |
| ACS712 Current Sensor | Current monitoring |
| DS18B20 | Temperature sensing |
| Liquid Leakage Sensor | Leakage detection |
| Relay Module | Machine power control |
| Buzzer | Emergency alert |
| LEDs | Status indication |
| LCD Display | Live sensor display |

---

# ⚙️ Working Principle

1. Sensors continuously send data to the ESP32.
2. ESP32 processes the sensor readings in real time.
3. If any parameter exceeds the safety threshold:
   - Relay disconnects machine power
   - Buzzer alert activates
   - Warning indication is displayed
4. Sensor data can also be monitored remotely through IoT platforms.

---

# 🌐 Features

✅ Real-time industrial monitoring  
✅ Automatic machine protection  
✅ Fire detection system  
✅ Over-current protection  
✅ Noise and vibration monitoring  
✅ Liquid leakage detection  
✅ IoT cloud monitoring  
✅ Emergency alert system  
✅ LCD live display  

---

# 🔌 Pin Configuration

| Device | ESP32 Pin |
|---|---|
| SW-420 | GPIO 14 |
| Flame Sensor | GPIO 13 |
| KY-037 | GPIO 34 |
| ACS712 | GPIO 35 |
| DS18B20 | GPIO 4 |
| Relay Module | GPIO 26 |
| Buzzer | GPIO 27 |
| LCD SDA | GPIO 21 |
| LCD SCL | GPIO 22 |

> Pins can be modified according to the circuit design.

---

# ☁️ IoT Integration

## Firebase
Used for:
- Real-time database
- Cloud monitoring
- Data logging

## Blynk
Used for:
- Mobile dashboard
- Remote monitoring
- Live alerts

---

# 🚨 Safety Logic

| Condition | Action |
|---|---|
| Excess Current | Relay OFF |
| Fire Detected | Alarm + Relay OFF |
| High Vibration | Warning Alert |
| High Noise | Notification |
| Liquid Leakage | Emergency Alert |
| High Temperature | Safety Warning |

---

# 💻 Software Used

- Arduino IDE
- Firebase Realtime Database
- Blynk IoT Platform

---

# 📚 Libraries Used

```cpp
#include <WiFi.h>
#include <FirebaseESP32.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <OneWire.h>
#include <DallasTemperature.h>
```

---

# 🚀 Future Improvements

- AI-based predictive maintenance
- SMS and email alerts
- Mobile application
- Industrial automation integration
- Advanced analytics dashboard

---

# 👨‍💻 Team Members

- Maaz Khanapuri
- Umarfarooq Desai
- Ashrit
- Manuja

---

# 🏆 Achievement

🏅 Achieved **3rd Prize** in an industrial project competition for innovation in industrial safety and IoT monitoring.

---

# 📄 Conclusion

The **Smart Industrial Safety Monitoring System** provides a reliable, low-cost, and efficient solution for industrial monitoring and machine protection.  
The system improves workplace safety by detecting abnormal conditions and taking immediate protective actions automatically.

---
