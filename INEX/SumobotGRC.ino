#include "POP32.h"


int EDGE_L_THRESHOLD = 900;
int EDGE_R_THRESHOLD = 900;
int FRONT_THRESHOLD = 300;

int LEFT = 0;
int RIGHT = 1;
int direction = LEFT;

unsigned int data = 0; // stores the controller response


void setup() {
    oled.textSize(1);

    delay(1000);
}

void test() {
    FD(50);
    delay(5000);

    BK(50);
    delay(5000);


    TL(50);
    delay(5000);

    TR(50);
    delay(5000);


    SL(50);
    delay(5000);

    SR(50);
    delay(5000);


    search(LEFT);
    delay(5000);

    search(RIGHT);
    delay(5000);


    backoff(LEFT);
    delay(1000);

    backoff(RIGHT);
    delay(1000);
}

void lineTest() {
    oled.text(0, 0, "%d ", analog(0));
    oled.text(1, 0, "%d ", analog(1));
    oled.text(2, 0, "%d ", analog(2));
    oled.display();
}


void loop() {
    // test();
    // lineTest();

    if (analog(0) > EDGE_L_THRESHOLD) {
        // edge is detected on the left, backoff and u-turn to the right
        backoff(RIGHT);
        direction ^= 1;
    } else if (analog(1) > EDGE_R_THRESHOLD) {
        // edge is detected on the right, backoff and u-turn to the left
        backoff(LEFT);
        direction ^= 1;
    } else if(analog(2) > FRONT_THRESHOLD) {
        FD(100); // attack
    } else {
        search(direction);
    }
}

void search(int direction) {
    if (direction == LEFT) {
        SL(50);
    } else {
        SR(50);
    }
}

void backoff(int direction) {
    BK(80);
    delay(300);

    if (direction == LEFT) {
        SL(60);
    } else {
        SR(60);
    }
    delay(600);

    AO();
    delay(50);
}