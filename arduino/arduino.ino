#include <ArduinoHttpClient.h>

#include <SPI.h>

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>
#include <WiFiNINA.h>
#include <ArduinoHttpClient.h>

#include "credentials.h"

int status = WL_IDLE_STATUS;     // the WiFi radio's status
int count= 0;

WiFiClient wifi;

WebSocketClient client = WebSocketClient(wifi, "michelebruno.herokuapp.com/infopoetry", 80);

Adafruit_SH1107 display = Adafruit_SH1107(64, 128, &Wire);

#include "drawqrcode.h"
#include "wifidebug.h"

// https://github.com/arduino-libraries/ArduinoHttpClient/issues/95

void setup() {

  Serial.begin(9600);

    //Initialize serial and wait for port to open:
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  Serial.println("128x64 OLED FeatherWing test");

  display.begin(0x3C, true); // Address 0x3C default

  Serial.println("OLED begun");

  // Show image buffer on the display hardware.
  // Since the buffer is intialized with an Adafruit splashscreen
  // internally, this will display the splashscreen.
  // display.display();
  display.clearDisplay();



  const char *lines[4] = { "Scan to", "Join", "Lumifera", "WiFi" };

  drawQrCode("https://michelebruno.herokuapp.com", lines);


    // NOTE: SOME PRINTERS NEED 9600 BAUD instead of 19200, check test page.
  Serial1.begin(9600);  // Initialize SoftwareSerial
  //Serial1.begin(19200); // Use this instead if using hardware serial

  while (!Serial1) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  delay(5000);
  Serial1.write("Funziono!");

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
    // delay(10000);

    if (status != WL_CONNECTED) {
        
      Serial.print("Attempting to connect to WPA SSID: ");
      Serial.print("eduroam ");
      Serial.println(pass);
  
      // Connect to WPA/WPA2 network:
      status = WiFi.beginEnterprise("eduroam",  "10696137@polimi.it", "QTv9RraTz8JKkr");
  
      // wait 10 seconds for connection:
      delay(10000);

   
    }

    
  }

  // you're connected now, so print out the data:
  Serial.print("You're connected to the network");
  printCurrentNet();
  printWifiData();


}

void loop() {
  Serial.println("starting WebSocket client");
  client.begin();

  while (client.connected()) {
    Serial.print("Sending hello ");
    Serial.println(count);

    // send a hello #
    client.beginMessage(TYPE_TEXT);
    client.print("hello ");
    client.print(count);
    client.endMessage();

    // increment count for next message
    count++;

    // check if a message is available to be received
    int messageSize = client.parseMessage();

    if (messageSize > 0) {
      Serial.println("Received a message:");
      Serial.println(client.readString());
    }

    // wait 5 seconds
    delay(5000);
  }

  Serial.println("disconnected");
}
