#include<wiringPi.h>
#include<stdio.h>

#define LED0 0
#define SW   1

int main()
{
  int swValue;
  int flag;
  
  // 1. wiringPI Init
  wiringPiSetup();

  // 2. pinMode Init
  pinMode(SW,INPUT);
  pinMode(LED0,OUTPUT);
  // 3. read/write
  while(1)
 {
   swValue = digitalRead(SW);
  // if(swValue)
//	flag=~flag;
   if(swValue)
     digitalWrite(LED0,HIGH);
   else 
     digitalWrite(LED0,LOW);
   delay(100);
 }
  return 0;
}
