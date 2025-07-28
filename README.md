# nfc_immobilizer_esp32
Uses an ESP32 microcontroller with an NFC module to act as a vehicle immobilizer, only allowing the vehicle to start once an authorized NFC tag is scanned. 

# 🚗 ESP32 NFC Car Immobilizer

Welcome to the **ESP32 NFC Car Immobilizer** project! This open-source solution lets you secure your vehicle with an NFC keychain or card. Only a recognized NFC tag can disable the immobilizer and allow your car to start. The system provides clear LED status indicators and is easy to build and use.

---

## ✨ Features

- 🔒 **Immobilizer**: Prevents unauthorized vehicle starting
- 🪪 **NFC Authentication**: Only registered NFC keychains/cards unlock
- 🟢 **Clear Status LEDs**: Red and green LEDs indicate system status
- ⏱️ **Timed Unlock**: Valid NFC unlocks for 20 seconds
- 🚨 **Intruder Alert**: Rapid LED flashing for unrecognized tags
- ⚡ **Open Hardware & Code**: Easily customizable for your needs

---

## 🧰 Hardware Required

- **ESP32 dev board**
- **PN532 NFC Reader** (I2C)
- **Relay Module** (suitable for your car's ignition/fuel pump circuit)
- **NFC Keychain or Card** (13.56MHz, MIFARE Classic or NTAG preferred)
- **Red and Green LEDs** with resistors (220–470Ω)
- **Jumper Wires & Breadboard** or PCB
- **Power Supply** (car 12V to 5V converter, or USB for testing)

---

## 📂 Repository Structure

```
/
├── src/
│   └── nfc_immobilizer_esp32.ino      # Main Arduino/ESP32 code
├── HOWTO.md                           # Step-by-step installation & wiring guide
├── OPERATORS_MANUAL.md                # In-depth usage and troubleshooting manual
└── README.md                          # Project overview, features, and requirements
```

---

## 🚦 Quick Start

1. **Connect all hardware** as described in [HOWTO.md](HOWTO.md)
2. **Upload the code** in [src/nfc_immobilizer_esp32.ino](src/nfc_immobilizer_esp32.ino) to your ESP32
3. **Scan your NFC keychain** and use the Serial Monitor to obtain its UID
4. **Update the code** with your NFC tag's UID and re-upload
5. **Install the system** in your vehicle (refer to HOWTO and OPERATORS_MANUAL)
6. **Drive securely!** 🚙

---

## 📖 Documentation

- [🛠️ HOWTO: Installation & Wiring Guide](HOWTO.md)
- [📗 Operators Manual & Usage](OPERATORS_MANUAL.md)

---

## 🙏 Contributing

Pull requests are welcome! Please see [CONTRIBUTING.md](CONTRIBUTING.md) (if present) for details.

---

## ⚠️ Disclaimer

- This project is for educational purposes. Installation in a real vehicle is at your own risk.
- Always follow automotive safety and electrical best practices.
