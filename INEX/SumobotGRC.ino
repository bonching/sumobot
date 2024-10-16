#include "POP32.h"


int EDGE_LEFT_THRESHOLD = 900;
int EDGE_RIGHT_THRESHOLD = 900;
int FRONT_THRESHOLD = 250;

int ATTACK_SPEED = 100;
int BACKOFF_SPEED = 80;
int BACKOFF_SPIN_SPEED = 60;
int SEARCH_SPIN_SPEED = 50;

int LEFT = 0;
int RIGHT = 1;


int direction = LEFT;
unsigned int data = 0; // stores the controller response


void setup() {
    oled.textSize(1);
    delay(1000);
}


void loop() {
    // test();
    printSensorReadings();

    if (analog(0) > EDGE_LEFT_THRESHOLD) {
        // edge is detected on the left, backoff and u-turn to the right
        backoff(RIGHT);
        direction ^= 1;
    } else if (analog(1) > EDGE_RIGHT_THRESHOLD) {
        // edge is detected on the right, backoff and u-turn to the left
        backoff(LEFT);
        direction ^= 1;
    } else if(analog(2) > FRONT_THRESHOLD) {
        attack();
    } else {
        search(direction);
    }
}

void attack() {
    FD(ATTACK_SPEED);
}

void search(int direction) {
    if (direction == LEFT) {
        SL(SEARCH_SPIN_SPEED);
    } else {
        SR(SEARCH_SPIN_SPEED);
    }
}

void backoff(int direction) {
    BK(BACKOFF_SPEED);
    delay(300);

    if (direction == LEFT) {
        SL(BACKOFF_SPIN_SPEED);
    } else {
        SR(BACKOFF_SPIN_SPEED);
    }
    delay(600);

    AO();
    delay(50);
}

void printSensorReadings() {
    oled.text(0, 0, "%d ", analog(0)); // left line sensor
    oled.text(1, 0, "%d ", analog(1)); // right line sensor
    oled.text(2, 0, "%d ", analog(2)); // front object sensor
    oled.display();
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
