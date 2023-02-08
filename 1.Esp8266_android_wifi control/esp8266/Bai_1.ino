
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

#define GPIO  2
ESP8266WebServer server(80);
//////////////////////////////////////////////////////////
const char *ssid = "Robo-MT";    
const char *pass = "dmt@123abc";

void setup() 
{
  Serial.begin(9600);     // Khai báo Serial port
  pinMode(GPIO,  OUTPUT); // Khai báo chân xuất tín hiệu
  ////////////
  WiFi.begin(ssid, pass); // Kết nối wifi 
  while (WiFi.status() != WL_CONNECTED){ delay(500); Serial.print("."); } // Kiểm tra kết nối
  Serial.println("");
  Serial.println(WiFi.localIP()); // Xuất địa chỉ IP
  ////////////  
  server.on("/", TrangIndex); // khai báo hàm nhận phương thức GET
  server.begin();             // run server   
}
//////////////////////////////////////////////////////////
void loop() 
{
   server.handleClient(); // Lắng nghe request gởi lên server 
   delay(1000);
}
//////////////////////////////////////////////////////////
void TrangIndex() 
{
  if (server.hasArg("den"))
  { 
    String sTT = server.arg("den") ;
    if (sTT == "0"){ digitalWrite(GPIO, HIGH); } // Tắt đèn led
    if (sTT == "1"){ digitalWrite(GPIO, LOW);  } // Bật đèn led
  }
  server.send(200, "text/html", "");
}
//////////////////////////////////////////////////////////
