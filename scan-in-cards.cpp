/*
// USED FOR SCANNING IN NEW CARD AND COPYING/PASTING THEM INTO MAIN.CPP
#include <SPI.h>
#include <MFRC522.h>
#include <SoftwareSerial.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include "index.h" //html page
 
// Variables for card reader:
#define SS_PIN 15
#define RST_PIN 0
int del = 3000;
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.
int x = 1;
char *arr[] = {};
int arrlen = 100;
int t;
String cardid;

void setup() {
  Serial.begin(9600);   // Initiate a serial communication
  SPI.begin();      // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522
  Serial.println("Ready to read cards!");
  Serial.println("");
}

void loop() {
  // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent()) {
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) {
    return;
  }
  //Show UID on serial monitor

  Serial.print('"');
  String content= "";
  for (byte i = 0; i < mfrc522.uid.size; i++) {
    Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
    Serial.print(mfrc522.uid.uidByte[i], HEX);
    content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
    content.concat(String(mfrc522.uid.uidByte[i], HEX));
  };
  Serial.print("[Spacer]");
  delay(500);
}
*/
