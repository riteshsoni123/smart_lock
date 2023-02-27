#include <ESP8266WiFi.h>

const char* ssid = "RedmiRks";   //enter your wi-fi name

const char* password = "11111111";    //enter the wifi password

unsigned char status_door=0;

WiFiServer server(80);

void setup() {
  Serial.begin(9600);  
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
  server.begin();
  Serial.println(WiFi.localIP());
}

void loop() {
  WiFiClient client = server.available();
  if (!client) {
    return;
  }

  while (! client.available()){
    delay (1);
  }

  String req = client.readStringUntil('\r');
  client.flush();
  if (req.indexOf("/dooroff") != -1)  {
    status_door=0;
    Serial.write("door-off#");
  }

  else if(req.indexOf("/dooron") != -1){
    status_door=1;
    Serial.println("door-on#");
  }

  client.println("HTTP/1.1 200 OK");

  client.println("Content-Type: text/html");

  client.println("Connection: close");

  client.println("");


  client.println("<!DOCTYPE HTML>");

  client.println("<HTML>");

  client.println("<H1> DOOR CONTROL </H1>");

  client.println("<br />");
 

  client.println("<a href=\"/dooron\"\"> <button style='FONT-SIZE: 40px; color: green; HEIGHT: 200px; align: center; WIDTH: 200px; 126px; Z-INDEX: 0; TOP: 200px;'> DOOR OPEN </button> </a>");

  client.println("<a href=\"/dooroff\"\"> <button style='FONT-SIZE: 40px; color: red; HEIGHT: 200px; align: center; HEIGHT: 200px; WIDTH: 300px; 126px; Z-INDEX: 0; TOP: 200px;'> DOOR CLOSE </button> </a>");

  client.println("</html>");
  delay(1);
}