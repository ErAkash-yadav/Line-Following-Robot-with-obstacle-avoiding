# 🤖 Line-Following-Robot

Arduino आधारित **Line Following Robot** (IR sensors + HC-SR04 ultrasonic + Servo + Adafruit Motor Shield V1)  
यह रीपो GitHub पर upload करने के लिए तैयार है — code, schematic और images सभी included हैं।

---

## 🧩 फाइल स्ट्रक्चर
```
Line-Following-Robot/
│
├── Arduino_Code/
│     └── line_following.ino
│
├── Circuit_Diagram/
│     └── schematic.png
│
├── Images/
│     └── robot_photo.jpg
│
└── README.md
```

---

## ⚙️ Hardware Connections (Code के अनुसार)
- **IR Sensors**:
  - IR1 → A0
  - IR2 → A1
  - IR3 → A2
  - IR4 → A3
  - IR5 → A4
- **Ultrasonic (HC-SR04)**:
  - Trig → A5
  - Echo → D10
- **Servo**:
  - Signal → D9
  - Vcc → 5V (or servo supply)  
  - GND → GND
- **Motors**:
  - Right motor → M1 terminal on Adafruit Motor Shield V1
  - Left motor → M2 terminal on Adafruit Motor Shield V1
- **Motor Shield**: Mount on Arduino Uno headers. Supply motor power (Vin) according to your motors (e.g., 6V–9V).
- **Grounds**: Common GND between Arduino, motor power supply, servo, sensors, and ultrasonic.

---

## 🧾 Software / Libraries
- AFMotor (Adafruit Motor Shield v1) — install via Library Manager  
- Servo.h (built-in)

---

## ⚠️ Tips & Calibration
- IR modules output can be `LOW` for line detected (0) or `HIGH` depending on module; यदि logic उल्टा हो तो code में `0/1` चेक adjust करो।
- Ultrasonic range in code uses cm; check wiring and sensor timeout if unreliable.
- Adjust motor speeds in functions (forward(), left(), right()) for smooth turning.

---

## 📸 Images
Robot photo included in `Images/robot_photo.jpg`.

---

## 📝 License
Open-source — use, modify और improve करो।  
Contributions welcome.