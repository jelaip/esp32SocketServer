#include <WiFi.h>
#include <WebSocketClient.h>

#define blue 12
#define green 13

const char* ssid     = "";
const char* password = "";
char path[] = "/";
char host[] = "";
const char* ip = "";
const int port = 5000;
WebSocketClient webSocketClient;
WiFiClient client;

int i = 0;

void ConnectSocket(){
    digitalWrite(blue, LOW);
    while (!client.connected()) {
        if (client.connect(ip, port)) {
        Serial.println("Connected");
            webSocketClient.path = path;
            webSocketClient.host = host;
            while(!webSocketClient.handshake(client)) {
                Serial.println("Handshake failed.");
                continue;
            }
            Serial.println("Handshake successful");
            digitalWrite(blue, HIGH);
        }
        else Serial.println("try to Connect");
        delay(1000);
    }
}


void setup() {
  Serial.begin(9600);
  pinMode(blue, OUTPUT);
  pinMode(green, OUTPUT);
  digitalWrite(blue, LOW);
  digitalWrite(green, LOW);
  delay(10);

  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  delay(5000);
  ConnectSocket();
  

}


void loop() {
  String data;

  if (client.connected()) {
    
    webSocketClient.getData(data);
    if (data.length() > 0) {
      Serial.print("Received data: ");
      Serial.println(data);
    }
   
    data = "data";
    
    digitalWrite(green, HIGH);
    webSocketClient.sendData(String(i));
    digitalWrite(green, LOW);
    i++;
  } 
  else {
    Serial.println("Client disconnected.");
    ConnectSocket();
  }
  
  
  // wait to fully let the client disconnect
  delay(3000);
  
}
