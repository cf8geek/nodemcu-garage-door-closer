#include <ESP8266WiFi.h>

const char* ssid = "AAA";
const char* password = "AAA";
const char* path = "AAA";
const char* host = "maker.ifttt.com";
const char* url = "http://maker.ifttt.com/trigger/AAA/with/key/AAA";

void setup() {
/*start*/
  Serial.begin(115200);
  delay(10);

  // We start by connecting to a WiFi network

  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
/*stop*/
  // We start by connecting to a WiFi network
  WiFi.begin(ssid, password);
/*start*/
  while (WiFi.status() != WL_CONNECTED) {
    delay(750);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
/*stop*/
}
int value = 0;
void loop() {
  // initial delay; equal to 2 hours in milliseconds.
  delay(7200000);
  // delay(120000); // two minute delay for test purposes!
  
  // tries to trigger, waits some milliseconds, tries again, repeats.
  delay(5000);
  ++value;

/*start*/
  Serial.print("connecting to ");
  Serial.println(host);
/*stop*/
  // Use WiFiClient class to create TCP connections
  WiFiClient client;
  const int httpPort = 80;
/*start*/
if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return;
  }
/*stop*/
  // This will send the request to the server
  client.print(String("GET ") + path + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" + 
               "Connection: close\r\n\r\n");
  unsigned long timeout = millis();
  while (client.available() == 0) {
    if (millis() - timeout > 5000) {
      client.stop();
      return;
    }
  }
/*start*/
  // Read all the lines of the reply from server and print them to Serial
  while(client.available()){
    String line = client.readStringUntil('\r');
    Serial.print(line);
  }
  
  Serial.println();
  Serial.println("closing connection");
/*stop*/
  delay(300000); // 5 minutes
  //  delay(30000); // 30 seconds
}
