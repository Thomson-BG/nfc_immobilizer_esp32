# 🛠️ ESP32 NFC Car Immobilizer — Installation & Wiring Guide

Welcome to the step-by-step guide to building, wiring, and installing the ESP32 NFC Car Immobilizer! 🏗️

---

## 📝 What You’ll Need

### Hardware
- **ESP32 Dev Board** (e.g., DevKitC, WROOM, or similar)
- **PN532 NFC Module** (I2C version)
- **Relay Module** (5V or 12V, depending on your car’s needs)
- **NFC Keychain/Card** (13.56MHz, e.g., MIFARE Classic, NTAG)
- **Red LED** + resistor (220–470 Ω)
- **Green LED** + resistor (220–470 Ω)
- **Breadboard & Jumper Wires** or PCB
- **Power Source** (e.g., USB, or car 12V to 5V step-down converter)

### Tools
- Soldering iron (for permanent install)
- Screwdrivers, pliers, wire strippers/cutters
- Multimeter (recommended)

---

## ⚡ Wiring Diagram

### ESP32 Pinout

| Function          | ESP32 Pin | Module/Device    |
|-------------------|-----------|------------------|
| Relay Signal      | GPIO 8    | Relay IN         |
| Red LED           | GPIO 6    | Anode (resistor) |
| Green LED         | GPIO 7    | Anode (resistor) |
| PN532 SDA         | GPIO 21   | PN532 SDA        |
| PN532 SCL         | GPIO 22   | PN532 SCL        |
| 3.3V / 5V         | 3V3 / 5V  | PN532 VCC        |
| GND               | GND       | All GNDs         |

**Note:** Adjust pin numbers in the code if you connect differently!

---

### 🖇️ Step-by-Step Wiring

1. **Relay Module**
   - Connect **IN** to ESP32 GPIO 8
   - **VCC** to 5V (from ESP32 or external supply)
   - **GND** to GND

2. **Red LED**
   - **Anode (+)** through resistor to ESP32 GPIO 6
   - **Cathode (-)** to GND

3. **Green LED**
   - **Anode (+)** through resistor to ESP32 GPIO 7
   - **Cathode (-)** to GND

4. **PN532 NFC Reader (I2C)**
   - **SDA** to ESP32 GPIO 21
   - **SCL** to ESP32 GPIO 22
   - **VCC** to 3.3V or 5V (check your PN532 version!)
   - **GND** to ESP32 GND

5. **Powering the ESP32**
   - For breadboard testing: use USB.
   - For car install: use a 12V-to-5V step-down converter ("buck converter") to supply stable 5V to ESP32 VIN and relay module.

---

## 🛠️ Software Setup

1. **Install Arduino IDE**
2. **Install ESP32 Board Support** via Boards Manager
3. **Install Libraries:**
   - `Adafruit PN532` (for NFC)
4. **Download the code**: [src/nfc_immobilizer_esp32.ino](src/nfc_immobilizer_esp32.ino)
5. **Upload code** to your ESP32

---

## 🔑 Registering Your NFC Keychain

1. Open the Serial Monitor at 9600 baud.
2. Scan your NFC tag/keychain.
3. Note the UID displayed in Serial Monitor.
4. Edit the `allowedUID` array in the code to match your tag’s UID.
5. Upload the code again.

---

## 🚗 Vehicle Installation

1. **Locate your vehicle’s ignition or fuel pump relay circuit.** (Consult service manual.)
2. **Wire your relay module** to interrupt the starter/ignition/fuel pump circuit.
   - **Caution:** If unsure, get professional help. Incorrect wiring can damage your car.
3. **Mount the ESP32 and PN532** securely under the dashboard or other protected location.
4. **Mount the NFC reader** where you can easily scan your keychain (but not visible to outsiders).
5. **Connect power** and ensure all is secure and insulated.

---

## 🧪 Testing

- With the immobilizer active, your car will not start.
- Scan your registered NFC keychain: green LED lights up, relay activates, and you can start the car.
- Scan an unauthorized tag: red LED flashes rapidly.

---

## 🛡️ Safety & Tips

- Always disconnect car battery before wiring.
- Use heatshrink and proper insulation on all connections.
- Secure all modules to prevent rattling or disconnection.
- Test thoroughly before relying on the system.

---

Happy building and stay secure! 🔒🛠️
