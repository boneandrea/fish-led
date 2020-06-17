/*
  NanoはWifiないから時間取れないのか...
 */

#include <MsTimer2.h>
#define RELAY 12
#define HEARTBEAT 13
#define HOUR 3600L // L重要
#define CORRECT_PER_DAY 21L // 60*60*24 との誤差sec (結構長期測定した)


void tick(int t) {
  digitalWrite(HEARTBEAT, HIGH);
  delay(t);
  digitalWrite(HEARTBEAT, LOW);

}

// 23時に起動すると、すぐ点灯　−　5分後に消灯、 6時に点灯となります
// 7時に起動すると、すぐ点灯　−　22:30に消灯、 6:30に点灯となります
// int やらlong やらの勉強になったわ

#define SLEEP_HOUR 14
#define SLEEP_START 11


void on() {
  digitalWrite(RELAY, HIGH);
}
void off() {
  digitalWrite(RELAY, LOW);
}

void fire() {

  static long a = 0;

  if (HOUR * SLEEP_START <= a && a < HOUR * (SLEEP_START + SLEEP_HOUR)) {
    tick(200);
    on();
  } else {
    off();
  }

  a++;

  a = a % ( HOUR * 24 + CORRECT_PER_DAY ); //　誤差補正
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
