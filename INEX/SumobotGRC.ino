#include<POP32.h> //library
void setup() {
  // put your setup code here, to run once: global run once
SW_OK_press();// on
oled.text(5,5, "Al");
oled.show();
}

void loop() {// local area
  // put your main code here, to run repeatedly:
//movement forward, backward, left, right, spin L, spin R, 
motor(1,50); //FD(100) ay 4 motors small ay 2 motors
delay (500); //1000=1 sec  duration of movement
motor(34,50); delay(100);
}