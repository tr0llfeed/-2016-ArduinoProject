#include <VirtualWire.h>
#include <dht.h>
dht DHT;
#define DHT11_PIN 5

void setup()
{
    vw_set_ptt_inverted(true);  // Required by the RF module
    vw_setup(2000);            // bps connection speed
    vw_set_tx_pin(3);         // Arduino pin to connect the receiver data pin
   
}
 
void loop()
{

   sendM(humidity());
   
}

void sendM(char x){
   const char *msg = "h"+x;
   vw_send((uint8_t *)msg, strlen(msg));

   vw_wait_tx();        // We wait to finish sending the message
   delay(200);         // We wait to send the message again              
  
}

char humidity(){
    int chk = DHT.read11(DHT11_PIN);
  float a = DHT.humidity;
  a = Serial.print(DHT.humidity, 1);
  return a;
}
int temperature(){
    int chk = DHT.read11(DHT11_PIN);
  float b = DHT.temperature;
  return b;
}
