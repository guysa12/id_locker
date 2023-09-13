#include <Servo.h>
#include <SPI.h>
#include <MFRC522.h>
#define RST_PIN 9 // Configurable, see typical pin layout above
#define SS_PIN 10 // Configurable, see typical pin layout above
Servo myservo;
//The card ID to which we will grant access
byte knownCard[] = {0x90, 0x68, 0xBE, 0x11};
MFRC522 mfrc522(SS_PIN, RST_PIN);

void setup() {
  myservo.attach(3);
  // put your setup code here, to run once:
  Serial.begin(9600); // Initialize serial communications with the PC
  while (!Serial); // Do nothing if no serial port is opened (added for Arduinos based on ATMEGA32U4)
  SPI.begin(); // Init SPI bus
  mfrc522.PCD_Init(); // Init MFRC522
  delay(4); // Optional delay. Some board do need more time after init to be ready, see Readme
  mfrc522.PCD_DumpVersionToSerial(); // Show details of PCD - MFRC522 Card Reader details
  Serial.println(F("Scan PICC to see UID, SAK, type, and data blocks..."));
}

void loop() {
//  myservo.write(0);
//  delay(1000);
//  myservo.write(90);
//  delay(1000);
//  myservo.write(180);
//  delay(1000);
  // check if a card is near the reader
  if ( ! mfrc522.PICC_IsNewCardPresent()) {
  return;
  }
  // read the card ID
  if ( ! mfrc522.PICC_ReadCardSerial()) {
  return;
  }
  // check if the card has access
  if(compareUID(mfrc522.uid.uidByte, knownCard, mfrc522.uid.size)) {
    Serial.println("Access granted!");
    myservo.write(0);
    delay(1000);
    myservo.write(90);
    delay(1000);
    myservo.write(180);
    delay(1000);
  } else {
    Serial.println("Access Denied!!");
  }
}
//a helper function to compare cards' id
bool compareUID(byte* uid1, byte* uid2, byte size) {
for (byte i=0; i < size; i++){
if (uid1[i] != uid2[i]) {
return false; // card does not match our card
}
}
return true; //it is our card
}
