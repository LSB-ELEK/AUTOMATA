//**************************************************************//
//  Name    : Control de Automata mediante Web                  //
//  Authors : Julen Barrio, Eneko Baltanas, Ander Beracoechea   //
//  Date    : 03 March 2021                                     //
//  Version : 2.0                                               //
//  Notes   : Configura tu red Wifi en las lineas siguientes    //
//**************************************************************//

// Load Wi-Fi library
#include <ESP8266WiFi.h>

// pines GIO
#define D0 16
#define D1 5
#define D2 4
#define D3 0
#define D4 2
#define D5 14
#define D6 12
#define D7 13
#define D8 15

// Contraseña WIFI
//const char* ssid     = "cursoarduino2";   //SSID
//const char* password = "cursoarduino2";   //PASSWORD
const char* ssid     = "IoT";             //SSID
const char* password = "Gt,N%2$R";        //PASSWORD


// Puerto
WiFiServer server(80);

/*    //Desactivar IP ESTATICA
        // Ip estatica
        IPAddress local_IP(172, 160, 0, 180);
        // Set your Gateway IP address
        IPAddress gateway(172, 160, 0, 1);
        
        IPAddress subnet(255, 255, 254, 0);
*/

// Guardar la peticion del PHP
String header;

// Variables de estado

String output0State = "off";
String output1State = "off";
String output2State = "off";
String output4State = "off";
String output3State = "off";
String output5State = "off";
String output6State = "off";
String output7State = "off";
String output8State = "off";

// Asignamos salidas 

const int output0 = D0;
const int output1 = D1;
const int output2 = D2;
const int output3 = D3;
const int output4 = D4;
const int output5 = D5;
const int output6 = D6;
const int output7 = D7;
const int output8 = D8;


// Millis
unsigned long currentTime = millis();

unsigned long previousTime = 0; 

const long timeoutTime = 2000;

void setup() {
  Serial.begin(9600);
  pinMode(output0, OUTPUT);
  pinMode(output1, OUTPUT);
  pinMode(output2, OUTPUT);
  pinMode(output4, OUTPUT);
  pinMode(output3, OUTPUT);
  pinMode(output5, OUTPUT);
  pinMode(output6, OUTPUT);
  pinMode(output7, OUTPUT);
  pinMode(output8, OUTPUT);

  // Salidas a LOW

  digitalWrite(output0, LOW);
  digitalWrite(output1, LOW);
  digitalWrite(output2, LOW);
  digitalWrite(output3, LOW);
  digitalWrite(output4, LOW);
  digitalWrite(output5, LOW);
  digitalWrite(output6, LOW);
  digitalWrite(output7, LOW);
  digitalWrite(output8, LOW);
/*  
        //Configure Static IP
        if (!WiFi.config(local_IP, gateway, subnet)) {
        Serial.println("STA Failed to configure");
        }
*/
  // Conectarse al wifi
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  // Imprimir IP
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  server.begin();
}

void loop(){
  WiFiClient client = server.available();   // Esperar a clientes

  if (client) {                             // Si hay un cliente
    Serial.println("New Client.");          // imprimimos en el serial
    String currentLine = "";                // String para guardar datos del cliente
    currentTime = millis();
    previousTime = currentTime;
    while (client.connected() && currentTime - previousTime <= timeoutTime) { // Loop mientras este un cliente conectado
      currentTime = millis();         
      if (client.available()) {             // Cuando hay un cliente
        char c = client.read();             // leemos la informacion del cliente
        Serial.write(c);                    // y la imprimimos en el serial
        header += c;
        if (c == '\n') {                    // cuando es un enter
          // Cuando la siguiente linea al enter es otro enter significa 
          // que el cliente http a salido
          if (currentLine.length() == 0) {
            
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();
            
            // turns the GPIOs on and off
           if (header.indexOf("GET /1/on") >= 0) {            //RECOGER INPUT PULSA 1
              Serial.println("PC on");
              output0State = "on";
              digitalWrite(output0, HIGH);
            } else if (header.indexOf("GET /1/off") >= 0) {
              Serial.println("PC off");
              output0State = "off";
              digitalWrite(output0, LOW);
          }else if (header.indexOf("GET /2/on") >= 0) {       // RECOGER INPUT PULSA 2
              Serial.println("PANTALLA ON");
              output1State = "on";
              digitalWrite(output1, HIGH);
              } else if (header.indexOf("GET /2/off") >= 0) {
              Serial.println("PANTALLA off");
              output1State = "off";
              digitalWrite(output1, LOW);
          }else if (header.indexOf("GET /3/on") >= 0) {       // RECOGER INPUT PULSA 3
              Serial.println("COMPRESOR ON");
              output2State = "on";
              digitalWrite(output2, HIGH);
              } else if (header.indexOf("GET /3/off") >= 0) {
              Serial.println("COMPRESOR off");
              output2State = "off";
              digitalWrite(output2, LOW);
          }else if (header.indexOf("GET /5/on") >= 0) {       // RECOGER INPUT PULSA 4
              Serial.println("FUENTE 24Von");
              output4State = "on";
              digitalWrite(output4, HIGH);
              } else if (header.indexOf("GET /5/off") >= 0) {
              Serial.println("FUENTE 24Voff");
              output4State = "off";
              digitalWrite(output4, LOW);
          } else if (header.indexOf("GET /4/on") >= 0) {      // RECOGER INPUT PULSA 5
              Serial.println("AUTOMATA on");
              output3State = "on";
              digitalWrite(output3, HIGH);
            } else if (header.indexOf("GET /4/off") >= 0) {
              Serial.println("AUTOMATA off");
              output3State = "off";
              digitalWrite(output3, LOW);
          }else if (header.indexOf("GET /6/on") >= 0) {      // RECOGER INPUT PULSA 6
              Serial.println("ARGIA on");
              output5State = "on";
              digitalWrite(output5, HIGH);
            } else if (header.indexOf("GET /6/off") >= 0) {
              Serial.println("ARGIA off");
              output5State = "off";
              digitalWrite(output5, LOW);
          }else if (header.indexOf("GET /7/on") >= 0) {      // RECOGER INPUT PULSA 7
              Serial.println("HAIZEA on");
              output6State = "on";
              digitalWrite(output6, HIGH);
            } else if (header.indexOf("GET /7/off") >= 0) {
              Serial.println("HAIZEA off");
              output6State = "off";
              digitalWrite(output6, LOW);
          }else if (header.indexOf("GET /8/") >= 0) {      // RECOGER INPUT PULSA 8-9
              Serial.println("AUTO on");
              output7State = "on";
              digitalWrite(output7, HIGH);
              //digitalWrite(output8, LOW);
              delay(500);
              digitalWrite(output7, LOW);
            } else if (header.indexOf("GET /9/") >= 0) {
              Serial.println("AUTO off");
              output7State = "off";
              digitalWrite(output8, HIGH);
              //digitalWrite(output7, LOW);
              delay(500);
              digitalWrite(output8, LOW);
            }
            
            // Caracteristicas HTML
            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            client.println("<link rel=\"icon\" href=\"data:,\">");
            // CSS
            client.println("<style>html { font-family: JetBrains Mono; display: inline-block; margin: 0px auto; text-align: center;}");
            client.println(".button { background-color: #195B6A; border: none; color: white; padding: 16px 40px;");
            client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
            client.println(".button2 {background-color: #77878A;}</style></head>");
            
            // Header
            client.println("<img src=http://www.lasalleberrozpe.eus/web/sites/default/files/laSalleBerrozpeLogo.png aling=left width=100 height=52");
            client.println("<body><h1>WEB CONTROL AUTOMATA</h1>");
            // Botones ON/OFF
            client.println("<p>PC - Estado " + output0State + "</p>");
            // If the output0State is off, it displays the ON button       
            if (output0State=="off") {
              client.println("<p><a href=\"/1/on\"><button class=\"button\">ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/1/off\"><button class=\"button button2\">OFF</button></a></p>");
            }
            client.println("</body></html>");
            
            // Display current state, and ON/OFF buttons for PANTALLA  
            client.println("<p>PANTALLA - Estado " + output1State + "</p>");
            // If the output1State is off, it displays the ON button       
            if (output1State=="off") {
              client.println("<p><a href=\"/2/on\"><button class=\"button\">ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/2/off\"><button class=\"button button2\">OFF</button></a></p>");
            }
            client.println("</body></html>");
                        
            // Display current state, and ON/OFF buttons for COMPRESOR 
            client.println("<p>COMPRESOR - Estado " + output2State + "</p>");
            // If the output2State is off, it displays the ON button       
            if (output2State=="off") {
              client.println("<p><a href=\"/3/on\"><button class=\"button\">ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/3/off\"><button class=\"button button2\">OFF</button></a></p>");
            }
            client.println("</body></html>");
            
            // Display current state, and ON/OFF buttons for AUTOMATA  
            client.println("<p>AUTOMATA - Estado " + output3State + "</p>");
            // If the output3State is off, it displays the ON button       
            if (output3State=="off") {
              client.println("<p><a href=\"/4/on\"><button class=\"button\">ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/4/off\"><button class=\"button button2\">OFF</button></a></p>");
            }
            client.println("</body></html>");

            // Display current state, and ON/OFF buttons for FUENTE 24V 
            client.println("<p>FUENTE 24V- Estado " + output4State + "</p>");
            // If the output4State is off, it displays the ON button       
            if (output4State=="off") {
              client.println("<p><a href=\"/5/on\"><button class=\"button\">ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/5/off\"><button class=\"button button2\">OFF</button></a></p>");
            } 
            client.println("</body></html>");
            
            // Display current state, and ON/OFF buttons for ARGIA
            client.println("<p>ARGIA- Estado " + output5State + "</p>");
            // If the output5State is off, it displays the ON button       
            if (output5State=="off") {
              client.println("<p><a href=\"/6/on\"><button class=\"button\">ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/6/off\"><button class=\"button button2\">OFF</button></a></p>");
            } 
            client.println("</body></html>");
            
            // Display current state, and ON/OFF buttons for HAIZEA
            client.println("<p>HAIZEA- Estado " + output6State + "</p>");
            // If the output6State is off, it displays the ON button       
            if (output6State=="off") {
              client.println("<p><a href=\"/7/on\"><button class=\"button\">ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/7/off\"><button class=\"button button2\">OFF</button></a></p>");
            } 
            client.println("</body></html>");

            // Display current state, and ON/OFF buttons for AUTOs
            client.println("<p>AUTO - Estado " + output7State + "</p>");
              client.println("<p><a href=\"/8/\"><button class=\"button\">ON</button></a>");
              client.println("<a href=\"/9/\"><button class=\"button button2\">OFF</button></a></p>");
            client.println("</body></html>");
            client.println("<p align=right><big><br>Julen Barrio<br>Eneko Baltanas<br>Ander Beracoechea");
             

            // El http responde con una linea en blanco
            client.println();
            // Rompe el loop
            break;
          } else { // Cuando tenemos una nueva linea la sustituimos por la anterior
            currentLine = "";
          }
        } else if (c != '\r') {  // Si tiene mas que un caracter
          currentLine += c;      // lo añadimos a currentline
        }
      }
    }
    // Limpiamos la variable header
    header = "";
    // Y cerramos la conexion
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
  }
}
