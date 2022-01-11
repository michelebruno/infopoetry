#include <ArduinoHttpClient.h>

#include <SPI.h>

#include <WiFiNINA.h>

#include "credentials.h"
 
int status = WL_IDLE_STATUS;     // the WiFi radio's status

WiFiClient wifi;

WebSocketClient client = WebSocketClient(wifi, "https://michelebruno.herokuapp.com", 80);


void setup() {
  //Initialize serial and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }


    // NOTE: SOME PRINTERS NEED 9600 BAUD instead of 19200, check test page.
  Serial1.begin(9600);  // Initialize SoftwareSerial
  //Serial1.begin(19200); // Use this instead if using hardware serial

  while (!Serial1) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  Serial1.println("Funziono!");

  Serial.println("Ho stampato");

  // check for the WiFi module:
  if (WiFi.status() == WL_NO_MODULE) {
    Serial.println("Communication with WiFi module failed!");
    // don't continue
    while (true);
  }

  String fv = WiFi.firmwareVersion();
  if (fv < WIFI_FIRMWARE_LATEST_VERSION) {
    Serial.println("Please upgrade the firmware");
  }

  // attempt to connect to WiFi network:
  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to WPA SSID: ");
    Serial.print(ssid);
    Serial.println(pass);

    // Connect to WPA/WPA2 network:
    status = WiFi.begin(ssid, pass);

    // wait 10 seconds for connection:
    delay(10000);
  }

  // you're connected now, so print out the data:
  Serial.print("You're connected to the network");
  // printCurrentNet();
  // printWifiData();


}

void loop() {
  // check the network connection once every 10 seconds:
  delay(10000);

  // printCurrentNet();

    /*
      // check if a message is available to be received
      int messageSize = client.parseMessage();

      if (messageSize > 0) {
        Serial.println("Received a message:");
        Serial.println(client.readString());
      }*/

}

void printWifiData() {
  // print your board's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);
  Serial.println(ip);

  // print your MAC address:
  byte mac[6];
  WiFi.macAddress(mac);
  Serial.print("MAC address: ");
  printMacAddress(mac);
}

void printCurrentNet() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print the MAC address of the router you're attached to:
  byte bssid[6];
  WiFi.BSSID(bssid);
  Serial.print("BSSID: ");
  printMacAddress(bssid);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.println(rssi);

  // print the encryption type:
  byte encryption = WiFi.encryptionType();
  Serial.print("Encryption Type:");
  Serial.println(encryption, HEX);
  Serial.println();
}

void printMacAddress(byte mac[]) {
  for (int i = 5; i >= 0; i--) {
    if (mac[i] < 16) {
      Serial.print("0");
    }
    Serial.print(mac[i], HEX);
    if (i > 0) {
      Serial.print(":");
    }
  }
  Serial.println();
}
