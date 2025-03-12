#include <Servo.h>

Servo Baseservo;
Servo Jarservo;
Servo Rightservo;
Servo Leftservo;

int base = 0;
int jar = 5;
int right = 0;
int left = 0;
int count = 0, count2 = 0;

// Movement boundaries
int baseservoleftsidemove;
int baseservorigthsidemove;
int openjar;
int closejar;
int rightsideservofarwardsidepick;
int rightsideservobackwardpick;
int leftsideservoupmovepick;
int leftsideservodownmovepick;
int rightsideservofarwadsidedrop;
int rightsideservobackwarddrop;
int leftsideservoupmovedrop;
int leftsideservodownmovedrop;

void setup() {
    Baseservo.attach(7);
    Jarservo.attach(8);
    Rightservo.attach(9);
    Leftservo.attach(10);

    pinMode(A0, INPUT);
    pinMode(A1, INPUT);
    pinMode(A2, INPUT);
    pinMode(A3, INPUT);
    pinMode(2, INPUT_PULLUP);
    pinMode(3, INPUT_PULLUP);

    Baseservo.write(0);
    Jarservo.write(5);
    Rightservo.write(0);
    Leftservo.write(0);
    
    Serial.begin(9600);
}

void loop() {
    int var = digitalRead(2);
    if (var == 0) {
        delay(50);
        if (digitalRead(2) == 0) {
            count++;
            while (digitalRead(2) == 0);
        }
    }
    Serial.println(count);

    if (count < 3) {
        int BaseservoRead = analogRead(A3);
        if (BaseservoRead >= 800 && base < 180) {
            baseservoleftsidemove = ++base;
            Baseservo.write(base);
        } else if (BaseservoRead <= 300 && base > 0) {
            baseservorigthsidemove = --base;
            Baseservo.write(base);
        }

        int JarservoRead = analogRead(A1);
        if (JarservoRead >= 800 && jar < 40) {
            openjar = ++jar;
            Jarservo.write(jar);
        } else if (JarservoRead <= 300 && jar > 5) {
            closejar = --jar;
            Jarservo.write(jar);
        }
    }
}

void baseservomotor1() {
    for (int b = baseservorigthsidemove; b <= baseservoleftsidemove; b++) {
        Baseservo.write(b);
        delay(10);
    }
}

void baseseroback1() {
    for (int b = baseservoleftsidemove; b >= baseservorigthsidemove; b--) {
        Baseservo.write(b);
        delay(10);
    }
}

void jarservomotoropen() {
    for (int j = 5; j <= 40; j++) {
        Jarservo.write(j);
        delay(10);
    }
}

void jarservomotoclose() {
    for (int j = 40; j >= 5; j--) {
        Jarservo.write(j);
        delay(10);
    }
}
