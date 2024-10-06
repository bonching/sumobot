#include<POP32.h> //library

void setup() {
    // put your setup code here, to run once: global run once
    SW_OK_press();// on
    oled.text(5, 5, "Al");
    oled.show();
}

void loop() {
    glcd(2, 0
    "FORWARD 50%  ");
    FD(50);
    delay(1000);
    AO();
    sw_OK_press();
    glcd(2, 0, "BACKWARD 50% ");
    BK(50);
    delay(1000);
    AO();
    sw_OK_press();
    glcd(2, 0, "SPIN LEFT 50% ");
    SL(50);
    delay(1000);
    AO();
    sw_OK_press();
    glcd(2, 0, "SPIN RIGHT 50%");
    SR(50);
    delay(1000);
    AO();
    sw_OK_press();
    glcd(2, 0, "TURN LEFT 50% ");
    TL(50);
    delay(1000);
    A0();
    sw_OK_press();
    glcd(2, 0, "TURN RIGHT 50%");
    TR(50);
    delay(1000);
    AO();
    sw_OK_press();

}