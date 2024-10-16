#include "POP32.h"


/* ============= Configurations ================= */
int EDGE_LEFT_THRESHOLD = 900;
int EDGE_RIGHT_THRESHOLD = 900;
int FRONT_THRESHOLD = 500;

int ATTACK_SPEED = 100;

int BACKOFF_SPEED = 80;
int BACKOFF_DELAY = 500;
int BACKOFF_SPIN_SPEED = 60;
int BACKOFF_SPIN_DELAY = 1000;

int SEARCH_SPEED = 60;
int SEARCH_TURN_SPEED = 50;
int SEARCH_TURN_DELAY = 1000;
int SEARCH_FORWARD_MAX_COUNT = 15; // search forward without turning left/right
int TOGGLE_DIRECTION_COUNT = 3; // change search direction after n count
/* ============= Configurations ================= */


/* ============= Constants ================= */
int LEFT = 0;
int RIGHT = 1;
String ACTION_SEARCH = "SEARCH ";
String ACTION_ATTACK = "ATTACK ";
String ACTION_BACKOFF = "BACKOFF";
/* ============= Constants ================= */


/* ============= Default Values ================= */
int direction = LEFT;
int switchDirectionCount = 0;
int searchForwardCounter = 0;
String action = ""; // SEARCH/ATTACK/BACKOFF
unsigned int data = 0; // stores the controller response
/* ============= Default Values ================= */


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
        direction = RIGHT;
    } else if (analog(1) > EDGE_RIGHT_THRESHOLD) {
        // edge is detected on the right, backoff and u-turn to the left
        backoff(LEFT);
        direction = LEFT;
    } else if(analog(2) > FRONT_THRESHOLD) {
        attack();
    } else {
        searchForwardCounter++;
        search(direction);
    }
}

void attack() {
    action = ACTION_ATTACK;
    FD(ATTACK_SPEED);
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
        TL(SEARCH_TURN_SPEED);
    } else {
        TR(SEARCH_TURN_SPEED);
    }
    delay(SEARCH_TURN_DELAY);

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
    oled.text(3, 0, action.c_str());
    oled.text(4, 0, direction == 0 ? "LEFT " : "RIGHT");
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
