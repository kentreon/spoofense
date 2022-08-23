
#include <SoftwareSerial.h>

const unsigned long BAUD_RATE = 9600;

// The bluetooth tx and rx pins must be supported by software serial.
// Visit https://www.arduino.cc/en/Reference/SoftwareSerial for unsupported pins.
// Bluetooth TX -> Arduino D8
const int BLUETOOTH_TX = 4;
// Bluetooth RX -> Arduino D7
const int BLUETOOTH_RX = 7;

const int READ_TIME = 500;
long lastShock = 0;
int strength = 0;

SoftwareSerial bt(BLUETOOTH_TX, BLUETOOTH_RX);

void setup() {
  // Baud rate must be same for bluetooth and serial.
  // It helps to prevent interference.
  bt.begin(BAUD_RATE);
  Serial.begin(BAUD_RATE);
  Serial.println("Setup Complete");
  pinMode(3, OUTPUT);
  pinMode(5, OUTPUT);
}

void loop() {
  // while incoming signal is available.
  if (bt.available()) {
    String input = "";
    unsigned long readStart = millis();
    while (bt.available() || millis() - readStart < 15) {
      if (bt.available()) {
        char inbuff = (char)bt.read();
        input += inbuff;
      }
    }
    respond(input);
  }
  shock();
}
void respond(String input) {
  String output = "";
  if (input.indexOf("Vibrate") >= 0) {
    String amount = input;
    int pin = 3;
    if (input.indexOf("Vibrate2") >= 0)pin = 5;
    String buff = "";
    buff += amount[9];
    if (amount[10] != ';')buff += amount[10];
    int amountn = buff.toInt();
    if (amountn != 0) {
      if (pin == 3) {
        amountn *= 5;

        amountn += 45;
      }
      else {
        strength = amountn;
        amountn = 0;
      }
    } else {
      strength = amountn;
    }
    analogWrite(pin, amountn);
    output = "OK;";
  }
  else if (input.indexOf("DeviceType") >= 0)output = "P:10:0082059AD3BD;";
  else if (input.indexOf("Battery") >= 0)output = "100;";
  else if (input.indexOf("PowerOff") >= 0)output = "OK;";
  else if (input.indexOf("Status:1") >= 0)output = "2;";
  bt.print(output);
}
void shock() {
  int dlay = (20 - strength) * 20 + 250;
  if (millis() - lastShock > dlay && strength > 0) {
    lastShock =  millis();
    analogWrite(5, 7+(int)((float)strength/5.5));
    delay(25);
    analogWrite(5, 0);
  }
}
