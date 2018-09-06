#include <IRremote.h>

int RECV_PIN = 3;
int stat;
IRrecv irrecv(RECV_PIN);
int redPin = 8; 
int bluePin = 6; 
int greenPin = 7 ;
decode_results results;

void setup()
{
  Serial.begin(9600);
  irrecv.enableIRIn(); // Start the receiver
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
 pinMode(2, OUTPUT);


  stat = 0;
}

void loop() {
digitalWrite(2,HIGH);
  if (irrecv.decode(&results)) {

    if(results.value == 0xFF906F){

      stat=0;
    }

    if(stat == 0){
        switch(results.value){
      case 0xFF30CF: //1 - ая клавиша (ручной ввод)
        stat = 1;
        break;
      case 0xFF18E7://2 - ая клавиша (Цвета)
        stat = 2;
        break;
      case 0xFF7A85://3 - ая клавиша (Переливание)
        stat = 3;
        break;
      }
    } 

    if(stat==2){
      switch(results.value){
      case 0xFF906F: //EQ - выход    
        clr();
        stat=0;

        break;

      case 0xFF6897://0 - ая клавиша 
        clr();

        break;

      case 0xFF30CF: //1 - ая клавиша
        clr();
        digitalWrite(redPin,HIGH);
        break;

      case 0xFF18E7://2 - ая клавиша 
        clr();
        digitalWrite(greenPin,HIGH);
        break;

      case 0xFF7A85://3 - ая клавиша 
        clr();
        digitalWrite(bluePin,HIGH);
        break;

      case 0xFF10EF://4 - ая клавиша 
        clr();
        analogWrite(redPin, 0);  //Бирюзовый
        analogWrite(greenPin, 255);
        analogWrite(bluePin, 255);
        break;

      case 0xFF38C7://5 - ая клавиша 
        clr();
        analogWrite(redPin, 255  );  // желтый
        analogWrite(greenPin, 255    );
        analogWrite(bluePin,1);

        break;



      }
    }


    Serial.println(stat); 
    Serial.println(results.value, HEX); 
    irrecv.resume(); // Receive the next value
  }





}//end

void clr(){
  analogWrite(redPin, 1);  // белый
  analogWrite(greenPin, 1);
  analogWrite(bluePin, 1);
}
