#include <Arduino.h>
#define MAX_LEVEL 5

int actual_led = 0;
int level = 0;
int wait[MAX_LEVEL] = {500, 300, 150, 90, 50};
volatile int win = 0;
int back = 0;

void stop();
void reset();
void spreadIn();
void spreadOut();

void setup() {
  Serial.begin(9600);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
  pinMode(2, INPUT);

  attachInterrupt(digitalPinToInterrupt(2), stop, HIGH);
}

void loop() {
  if (win == 1) {
    Serial.println("Hai vinto");
    delay(400);
    digitalWrite(8, HIGH);
    delay(400);
    digitalWrite(8, LOW);
    delay(400);
    digitalWrite(8, HIGH);
    delay(400);
    digitalWrite(8, LOW);
    reset();
    level++;
    if (level >= MAX_LEVEL) {
      level = 0;
      spreadOut();
      spreadIn();
      delay(700);
    }
  } else if (win == -1) {
    Serial.println("Hai perso");
    digitalWrite(3, HIGH);
    digitalWrite(13, HIGH);
    delay(400);
    digitalWrite(3, LOW);
    digitalWrite(13, LOW);
    delay(400);
    digitalWrite(3, HIGH);
    digitalWrite(13, HIGH);
    delay(400);
    digitalWrite(3, LOW);
    digitalWrite(13, LOW);
    delay(400);
    reset();
    level = 0;
  } else {
    if (back) {
      digitalWrite(actual_led + 3, HIGH);
      delay(wait[level]);
      digitalWrite(actual_led + 3, LOW);
      actual_led--;
      if (actual_led <= 0) {
        back = 0;
      }
    } else {
      digitalWrite(actual_led + 3, HIGH);
      delay(wait[level]);
      digitalWrite(actual_led + 3, LOW);
      actual_led++;
      if (actual_led >= 11) {
        actual_led -= 2;
        back = 1;
      }
    }
  }
}

void stop() {
  Serial.println(actual_led);
  if (actual_led == 5) {
    win = 1;
  } else {
    win = -1;
  }
}

void reset() {
  win = 0;
  actual_led = 0;
  back = 0;
}

void spreadIn() {
  digitalWrite(3, HIGH);
  digitalWrite(4, HIGH);
  digitalWrite(5, HIGH);
  digitalWrite(13, HIGH);
  digitalWrite(12, HIGH);
  digitalWrite(11, HIGH);
  delay(400);
  digitalWrite(3, LOW);
  digitalWrite(4, LOW);
  digitalWrite(5, LOW);
  digitalWrite(13, LOW);
  digitalWrite(12, LOW);
  digitalWrite(11, LOW);

  digitalWrite(6, HIGH);
  digitalWrite(7, HIGH);
  digitalWrite(10, HIGH);
  digitalWrite(9, HIGH);
  delay(400);
  digitalWrite(6, LOW);
  digitalWrite(7, LOW);
  digitalWrite(10, LOW);
  digitalWrite(9, LOW);

  digitalWrite(8, HIGH);
  delay(400);
  digitalWrite(8, LOW);
}

void spreadOut() {
  digitalWrite(8, HIGH);
  delay(400);
  digitalWrite(8, LOW);

  digitalWrite(6, HIGH);
  digitalWrite(7, HIGH);
  digitalWrite(10, HIGH);
  digitalWrite(9, HIGH);
  delay(400);
  digitalWrite(6, LOW);
  digitalWrite(7, LOW);
  digitalWrite(10, LOW);
  digitalWrite(9, LOW);

  digitalWrite(3, HIGH);
  digitalWrite(4, HIGH);
  digitalWrite(5, HIGH);
  digitalWrite(13, HIGH);
  digitalWrite(12, HIGH);
  digitalWrite(11, HIGH);
  delay(400);
  digitalWrite(3, LOW);
  digitalWrite(4, LOW);
  digitalWrite(5, LOW);
  digitalWrite(13, LOW);
  digitalWrite(12, LOW);
  digitalWrite(11, LOW);
}
