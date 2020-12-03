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
int del = 2000;
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.
int x = 0;
char *arr[] = {"00 00 00 00"};
int arrlen = 1;
int t;
String cardid;

// Variables for webserver
String password = "CHANGEME";
ESP8266WebServer server(80);

// Variables and Functions for IFTTT
String sifttt = "maker.ifttt.com";
String resource = "Token";

void handleRoot() {
  String s = page; //Read HTML contents
  server.send(200, "text/html", s);
}
void sendcid(String cardid) {
    if (cardid != "" && x == 0) {
      String jsonObject = String("{\"value1\":\"") + cardid + "\"" + "," + String("\"value2\":\"") + "Location" + "\"}";
      //sifttt
      Serial.print("Sending: "+jsonObject);

      Serial.print("Connecting to "); 
      Serial.print(sifttt);
      
      // Connect to wifi
      WiFiClient client;
      int retries = 20;
      while(!!!client.connect(sifttt, 80) && (retries-- > 0)) {
        Serial.print(".");
      }
      Serial.println(" ");
      if(!!!client.connected()) {Serial.println("Failed to connect...");}
      
      Serial.print("Request resource: "); 
      Serial.println(resource);
            
      client.println(String("POST ") + resource + " HTTP/1.1");
      client.println(String("Host: ") + sifttt); 
      client.println("Connection: close\r\nContent-Type: application/json");
      client.print("Content-Length: ");
      client.println(jsonObject.length());
      client.println();
      client.println(jsonObject);
      while(client.available()){Serial.write(client.read());}
      Serial.println("closing connection.\n");
      client.stop();
      cardid = "";
    }
    Serial.println("Not sending empty.");
  }

// Variables for relay
int doorpin = 16;

void opendoor(int t) {
    if (t == 0) {
      Serial.println("Access granted. From card.");
      sendcid(cardid);
      digitalWrite(doorpin, LOW);
      delay(3000);
      digitalWrite(doorpin, HIGH);
    } 
    if (t == 1) {
      Serial.println("Access granted. From wifi.");
      sendcid("WiFi");
      digitalWrite(doorpin, LOW);
      delay(3000);
      digitalWrite(doorpin, HIGH);
    }
  }

void handleDoor() {
  String t_pass = server.arg("passw");
  Serial.println("Button was clicked on website.");
  Serial.println("Password Sent: "+t_pass);
  if(password == t_pass){
    opendoor(1);
  }
}

void setup() {
  Serial.begin(9600);   // Initiate a serial communication
  SPI.begin();      // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522
  Serial.println("Ready to read cards!");
  Serial.println("");
  // DOOR PIN Setup
  pinMode(doorpin, OUTPUT);
  digitalWrite(doorpin, HIGH);

  // Wifi connect /  Server start
  const char* ssid = "SSID";
  const char* password = "SSID-PASSWORD";
  WiFi.begin(ssid, password);
  IPAddress staticIP(192, 168, 1, 196); // Static IP Address
  IPAddress gateway(192, 168, 1, 10); // Gateway (usually its your main router in the building)
  IPAddress subnet(255, 255, 255, 0); // Do some searching on how to get this 
  IPAddress dns(1, 1, 1, 1); // Not really needed unless you're requesting info from external sites
  // Connect to self to host server
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  //If connection successful show IP address in serial monitor
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());  //IP address assigned to your ESP
  server.on("/", handleRoot);      //Which routine to handle at root location
  server.on("/", handleRoot);      //Which routine to handle at root location. This is display page
  server.on("/openDoor", handleDoor);
  server.begin();                  //Start server
  Serial.println("HTTP server started! Scanning for cards now!");
  IPAddress local_IP(192, 168, 1, 42);
}

void loop() {
  server.handleClient();//Check if webpage is requested
  // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent()) {
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) {
    return;
  }
  //Show UID on serial monitor

  Serial.print("UID tag :");
  String content= "";
  for (byte i = 0; i < mfrc522.uid.size; i++) {
    Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
    Serial.print(mfrc522.uid.uidByte[i], HEX);
    content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
    content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  Serial.print("Message : ");
  content.toUpperCase();
  cardid = content.substring(1);
  for (int i=0; i<arrlen; i++) {
    if (String(arr[i]) == cardid) {
     //change here the UID of the card/cards that you want to give access    
      Serial.println("Authorized access");
      opendoor(0);
      Serial.println();
      return;
    }
  }   
  Serial.println(" Access denied");
  sendcid(cardid);
  delay(del);
  del = del*2; // Exponential wait time to mitigate brute force attacks
}
