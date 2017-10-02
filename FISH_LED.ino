/*

*/

#include <MsTimer2.h>
#define RELAY 12
#define HEARTBEAT 13
#define HOUR 3600L // L重要
#define CORRECT_PER_DAY 70L // 誤差：70秒


void tick(int t){
  digitalWrite(HEARTBEAT,HIGH);
  delay(t);
  digitalWrite(HEARTBEAT,LOW);
  
}

// 23時に起動すると、すぐ点灯　−　5分後に消灯、 6時に点灯となります
// 7時に起動すると、すぐ点灯　−　22:30に消灯、 6:30に点灯となります
// int やらlong やらの勉強になったわ
#define SLEEP_HOUR 8
#define SLEEP_START 3


void fire(){
  
  static long a=0;

  //Serial.println(a); // 実際数みんとわからんのう
  if(HOUR*SLEEP_START <= a && a < HOUR*(SLEEP_START+SLEEP_HOUR)){
    // 消灯
    digitalWrite(RELAY,LOW);
  }else{
    tick(200);
    digitalWrite(RELAY,HIGH);
  }

  a++;
  
  a=a%(HOUR*24+CORRECT_PER_DAY);
}


void setup() {
  Serial.begin(9600);       // 通信速度は9600bps
  pinMode(RELAY, OUTPUT);
  pinMode(HEARTBEAT, OUTPUT);
        
  MsTimer2::set(1000, fire); // ここにデカイ値入れてもうまく動かないので毎秒見るようにした
  Serial.println("start");
  MsTimer2::start();

}

void loop() {
  
}
