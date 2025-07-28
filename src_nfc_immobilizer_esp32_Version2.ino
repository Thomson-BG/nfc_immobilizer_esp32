#include <Wire.h>
#include <Adafruit_PN532.h>

// Pin definitions
#define RELAY_PIN   8
#define RED_LED     6
#define GREEN_LED   7
#define SDA_PIN     21 // ESP32 default I2C SDA
#define SCL_PIN     22 // ESP32 default I2C SCL

Adafruit_PN532 nfc(SDA_PIN, SCL_PIN);

// Allowed UID (update this with your tag's UID)
uint8_t allowedUID[4] = {0xDE, 0xAD, 0xBE, 0xEF}; // Replace with your tag's UID

// Timings
const unsigned long greenDuration = 20000; // 20 seconds (ms)
const unsigned long redBlinkInterval = 2400; // 25 times a minute = 2.4s cycle
const unsigned long redBlinkOn = 1200;      // 1.2s ON per cycle
const unsigned long rapidBlinkOn = 1000;    // 1s ON
const unsigned long rapidBlinkOff = 1000;   // 1s OFF

// State variables
unsigned long lastRedBlinkMillis = 0;
bool redLedState = false;
bool immobilizerActive = true;
unsigned long greenStartMillis = 0;
bool greenLedActive = false;
int rapidBlinks = 0;
bool rapidBlinking = false;

void setup(void) {
  Serial.begin(9600);
  pinMode(RELAY_PIN, OUTPUT);
  pinMode(RED_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);

  digitalWrite(RELAY_PIN, LOW);     // Immobilizer ON
  digitalWrite(RED_LED, LOW);       // LED off
  digitalWrite(GREEN_LED, LOW);     // LED off

  nfc.begin();
  uint32_t versiondata = nfc.getFirmwareVersion();
  if (!versiondata) {
    Serial.print("Didn't find PN53x board");
    while (1); // halt
  }
  nfc.SAMConfig();
  Serial.println("Waiting for NFC keychain...");
}

void loop(void) {
  unsigned long now = millis();

  // Handle immobilizer "active" LED blink
  if (immobilizerActive && !rapidBlinking && !greenLedActive) {
    if (redLedState) {
      if (now - lastRedBlinkMillis >= redBlinkOn) {
        digitalWrite(RED_LED, LOW);
        redLedState = false;
        lastRedBlinkMillis = now;
      }
    } else {
      if (now - lastRedBlinkMillis >= redBlinkInterval - redBlinkOn) {
        digitalWrite(RED_LED, HIGH);
        redLedState = true;
        lastRedBlinkMillis = now;
      }
    }
  }

  // Handle green LED and relay ON (immobilizer OFF)
  if (greenLedActive) {
    if (now - greenStartMillis >= greenDuration) {
      digitalWrite(GREEN_LED, LOW);
      digitalWrite(RELAY_PIN, LOW);  // Immobilizer ON
      immobilizerActive = true;
      greenLedActive = false;
      Serial.println("Immobilizer ON (timeout)");
    }
  }

  // Handle rapid red blinking
  if (rapidBlinking) {
    static bool ledState = false;
    static unsigned long lastRapidBlink = 0;
    if (now - lastRapidBlink >= (ledState ? rapidBlinkOn : rapidBlinkOff)) {
      ledState = !ledState;
      digitalWrite(RED_LED, ledState ? HIGH : LOW);
      lastRapidBlink = now;
      if (!ledState) {
        rapidBlinks++;
        if (rapidBlinks >= 5) {
          rapidBlinking = false;
          rapidBlinks = 0;
        }
      }
    }
    // Don't process NFC while blinking rapidly
    return;
  }

  // NFC reading
  boolean success;
  uint8_t uid[] = { 0, 0, 0, 0, 0, 0, 0 };  // Buffer to store the returned UID
  uint8_t uidLength;

  success = nfc.readPassiveTargetID(PN532_MIFARE_ISO14443A, uid, &uidLength);
  if (success) {
    bool match = true;
    if (uidLength == 4) {
      for (uint8_t i = 0; i < 4; i++) {
        if (uid[i] != allowedUID[i]) {
          match = false;
          break;
        }
      }
    } else {
      match = false;
    }

    if (match) {
      Serial.println("Keychain recognized: Immobilizer OFF, green LED ON");
      digitalWrite(RELAY_PIN, HIGH);     // Immobilizer OFF
      digitalWrite(GREEN_LED, HIGH);     // Green LED ON
      digitalWrite(RED_LED, LOW);        // Red LED OFF
      immobilizerActive = false;
      greenLedActive = true;
      greenStartMillis = now;
    } else {
      // Unknown card rapid blink
      Serial.print("Unknown card. UID: ");
      for (uint8_t i = 0; i < uidLength; i++) {
        Serial.print(uid[i], HEX); Serial.print(" ");
      }
      Serial.println();
      rapidBlinking = true;
      rapidBlinks = 0;
      digitalWrite(GREEN_LED, LOW);
      digitalWrite(RELAY_PIN, LOW);      // Immobilizer ON
      immobilizerActive = true;
      // Red LED blinking will be handled above
    }
    delay(1000); // Debounce to avoid double reads
  }
}