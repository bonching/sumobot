#include "POP32.h"


/* ============= Configurations ================= */
int EDGE_LEFT_THRESHOLD = 900;
int EDGE_RIGHT_THRESHOLD = 900;
int FRONT_THRESHOLD = 500;
int RIGHT_THRESHOLD = 500; // For right object sensor
int LEFT_THRESHOLD = 500; // For left object sensor
int BACK_THRESHOLD = 1000; // For back object sensor

int PIN_BOTTOM_LEFT_SENSOR = 0;
int PIN_BOTTOM_RIGHT_SENSOR = 1;
int PIN_FRONT_SENSOR = 2;
int PIN_FRONT_LEFT_SENSOR = 6;
int PIN_FRONT_RIGHT_SENSOR = 4;
int PIN_BACK_SENSOR = 3;

int ATTACK_SPEED = 100;
int ATTACK_DELAY = 100;

int BACKOFF_SPEED = 100;
int BACKOFF_DELAY = 400;
int BACKOFF_SPIN_SPEED = 100;
int BACKOFF_SPIN_DELAY = 500;

int TURNAROUND_SPIN_SPEED = 100;
int TURNAROUND_SPIN_DELAY = 500;

int SEARCH_SPEED = 100;
int SEARCH_SPIN_SPEED = 80;
int SEARCH_SPIN_DELAY = 10;
int SEARCH_FORWARD_MAX_COUNT = 15; // search forward without turning left/right
int TOGGLE_DIRECTION_COUNT = 3; // change search direction after n count
/* ============= Configurations ================= */


/* ============= Constants ================= */
int LEFT = 0;
int RIGHT = 1;
String ACTION_SEARCH = "SEARCH      ";
String ACTION_SEARCH_LEFT = "SEARCH LEFT ";
String ACTION_SEARCH_RIGHT = "SEARCH RIGHT";
String ACTION_ATTACK = "ATTACK      ";
String ACTION_BACKOFF = "BACKOFF     ";
/* ============= Constants ================= */


/* ============= Default Values ================= */
int direction = LEFT;
int switchDirectionCount = 0;
int searchForwardCounter = 0;
String action = ""; // SEARCH/ATTACK/BACKOFF/SEARCH_LEFT/SEARCH_RIGHT
unsigned int data = 0; // stores the controller response
/* ============= Default Values ================= */


void setup() {
    oled.textSize(1);
    delay(10);
}


void loop() {
    // test();

    if (analog(PIN_BOTTOM_LEFT_SENSOR) > EDGE_LEFT_THRESHOLD) {
        // edge is detected on the left, backoff and u-turn to the right
        backoff(RIGHT);
        direction = RIGHT;
    } else if (analog(PIN_BOTTOM_RIGHT_SENSOR) > EDGE_RIGHT_THRESHOLD) {
        // edge is detected on the right, backoff and u-turn to the left
        backoff(LEFT);
        direction = LEFT;
    } else if(analog(PIN_FRONT_SENSOR) > FRONT_THRESHOLD
               && analog(PIN_FRONT_SENSOR) > analog(PIN_FRONT_LEFT_SENSOR)
               && analog(PIN_FRONT_SENSOR) > analog(PIN_FRONT_RIGHT_SENSOR)) {
        attack();
    }  else if(analog(PIN_FRONT_LEFT_SENSOR) > LEFT_THRESHOLD) {
        attack_left();
    } else if(analog(PIN_FRONT_RIGHT_SENSOR) > RIGHT_THRESHOLD) {
        attack_right();
    }  else if(analog(PIN_BACK_SENSOR) > BACK_THRESHOLD) {
        SR(TURNAROUND_SPIN_SPEED);
        delay(TURNAROUND_SPIN_DELAY);
    } else {
        searchForwardCounter++;
        search(direction);
    }

    printSensorReadings();
}

void attack() {
    action = ACTION_ATTACK;
    FD(ATTACK_SPEED);
    delay(ATTACK_DELAY);
}

void attack_left() {
    action = ACTION_SEARCH_LEFT;
    SL(SEARCH_SPIN_SPEED);
    delay(SEARCH_SPIN_DELAY);
}

void attack_right() {
    action = ACTION_SEARCH_RIGHT;
    SR(SEARCH_SPIN_SPEED);
    delay(SEARCH_SPIN_DELAY);
}

void search(int searchDirection) {
    if (searchForwardCounter <= SEARCH_FORWARD_MAX_COUNT) {
        FD(SEARCH_SPEED);
        return;
    } else {
        searchForwardCounter = 0;
    }

    action = ACTION_SEARCH;
    if (searchDirection == LEFT) {
        SL(SEARCH_SPIN_SPEED);
    } else {
        SR(SEARCH_SPIN_SPEED);
    }
    delay(SEARCH_SPIN_DELAY);

    switchDirectionCount++;
    if (switchDirectionCount == TOGGLE_DIRECTION_COUNT) {
        direction ^= 1; // toggle search direction
        switchDirectionCount = 0;
    }
}

void backoff(int direction) {
    action = ACTION_BACKOFF;
    BK(BACKOFF_SPEED);
    delay(BACKOFF_DELAY);

    if (direction == LEFT) {
        SL(BACKOFF_SPIN_SPEED);
    } else {
        SR(BACKOFF_SPIN_SPEED);
    }
    delay(BACKOFF_SPIN_DELAY);

    AO();
    delay(50);
}

void printSensorReadings() {
    oled.text(0, 0, "%d ", analog(0)); // left line sensor
    oled.text(1, 0, "%d ", analog(1)); // right line sensor
    oled.text(2, 0, "%d ", analog(2)); // front object sensor
    oled.text(3, 0, "%d ", analog(4)); // right object sensor
    oled.text(4, 0, "%d ", analog(6)); // left object sensor
    oled.text(5, 0, "%d ", analog(3)); // back object sensor
    oled.text(6, 0, action.c_str());
    oled.text(7, 0, direction == 0 ? "LEFT " : "RIGHT");
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