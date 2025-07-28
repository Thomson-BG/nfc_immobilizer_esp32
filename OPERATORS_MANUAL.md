# 📗 ESP32 NFC Car Immobilizer — Operator’s Manual

Congratulations on installing your **ESP32 NFC Car Immobilizer**! This manual explains how to operate, maintain, and troubleshoot your new security system. 🚙🔒

---

## 🏁 System Overview

- **Immobilizer ON (Red LED flashing):** Vehicle is locked and cannot start.
- **Authorized NFC Scan (Green LED ON):** Immobilizer OFF; you have 20 seconds to start the vehicle.
- **Unauthorized NFC Scan (Red LED rapid flash):** Intrusion attempt; immobilizer remains ON.

---

## 🚦 LED Status Indicators

| LED  | State                   | Meaning                                      |
|------|-------------------------|----------------------------------------------|
| 🔴    | Slow flash (25/min)     | Immobilizer active; waiting for NFC key      |
| 🟢    | Solid ON (20 seconds)   | Authorized NFC detected; immobilizer OFF     |
| 🔴    | Rapid flash (5x, 1s)    | Unauthorized NFC scanned; access denied      |
| 🟢/🔴 | OFF                     | System unpowered or error                    |

---

## 🗝️ Using the System

### 1. **Activating Immobilizer**

- The system is active (red LED flashing) whenever power is supplied and no valid NFC tag has been scanned.

### 2. **Unlocking with Your NFC Keychain**

- Present your NFC keychain to the reader.
- The green LED will turn ON for 20 seconds.
- You now have 20 seconds to turn your vehicle’s ignition and start the engine.
- After 20 seconds, the system automatically re-locks (red LED resumes flashing).

### 3. **Unauthorized Attempt**

- If an unknown NFC tag is scanned, red LED blinks rapidly 5 times.
- The immobilizer remains ON, and the car cannot be started.

---

## 🛠️ Maintenance & Best Practices

- **Keep your NFC keychain safe**—treat it like a car key!
- **Have a backup keychain/card** programmed and stored securely in case of loss.
- **Periodically check LEDs and system operation** to ensure everything is working.
- **Don’t expose electronics to moisture**—mount all modules securely and out of sight.

---

## ⚠️ Troubleshooting

| Problem                                    | Possible Cause                               | Solution                                      |
|---------------------------------------------|----------------------------------------------|-----------------------------------------------|
| System does not power on                    | Power wiring, fuse, or ESP32 issue           | Check all power connections and fuses         |
| Red LED never flashes                       | LED wiring, code, or pin number mismatch     | Inspect wiring and ensure code matches pins   |
| NFC not detected                            | PN532 wiring, tag type, or orientation error | Check reader wiring and use supported tags    |
| Green LED doesn’t turn on with valid tag    | Wrong UID programmed, or code issue          | Double-check and reprogram allowedUID         |
| Relay not activating                        | Relay wiring, code/pin, or power issue       | Verify relay module wiring and pin config     |
| Red LED rapid flashes with valid tag        | Wrong tag, or UID not matching               | Obtain tag UID from Serial Monitor and update |

---

## 📝 Adding/Changing NFC Keychains

1. Connect ESP32 to your computer via USB.
2. Open Serial Monitor in Arduino IDE.
3. Scan your new NFC tag/keychain.
4. Note the UID shown; update the `allowedUID` array in the code.
5. Re-upload code to ESP32.

---

## 🛡️ Security Tips

- Mount the NFC reader out of direct sight to prevent tampering.
- Never leave backup tags/cards in your vehicle.
- Consider additional layers of security for high-value vehicles.

---

## 🤝 Support & Contributions

For improvements, bugs, or feature requests, open an issue or pull request on GitHub. Community contributions are welcome!

---

**Drive safe and secure!** 🚗🔒🛡️
