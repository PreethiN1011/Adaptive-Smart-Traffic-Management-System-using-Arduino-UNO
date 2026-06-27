// ---------------- LED Pins ----------------
const int RED = 8;
const int YELLOW = 9;
const int GREEN = 10;

// ---------------- Button ----------------
const int BUTTON = 2;

// ---------------- Buzzer ----------------
const int BUZZER = 3;

// ---------------- Ultrasonic ----------------
const int TRIG = 6;
const int ECHO = 7;

// ---------------- 74HC595 ----------------
const int dataPin = 11;
const int clockPin = 12;
const int latchPin = 13;

// -------- 7-Segment Digits (Common Anode) --------
byte digits[10] = {
B11000000, //0
B11111001, //1
B10100100, //2
B10110000, //3
B10011001, //4
B10010010, //5
B10000010, //6
B11111000, //7
B10000000, //8
B10010000  //9
};

// ---------------- Functions ----------------

float getDistance()
{
digitalWrite(TRIG, LOW);
delayMicroseconds(2);

digitalWrite(TRIG, HIGH);
delayMicroseconds(10);

digitalWrite(TRIG, LOW);

long duration = pulseIn(ECHO, HIGH);

return duration \* 0.034 / 2.0;
}

void displayDigit(int num)
{
digitalWrite(latchPin, LOW);
shiftOut(dataPin, clockPin, MSBFIRST, digits[num]);
digitalWrite(latchPin, HIGH);
}

void countdown()
{
for(int i = 5; i >= 1; i--)
{
displayDigit(i);

```
tone(BUZZER,1000,100);

delay(1000);
```

}

displayDigit(0);
}

void pedestrianCross()
{
digitalWrite(GREEN, LOW);

digitalWrite(YELLOW, HIGH);
delay(2000);

digitalWrite(YELLOW, LOW);

digitalWrite(RED, HIGH);

countdown();

delay(1000);

digitalWrite(RED, LOW);
}

void setup()
{
pinMode(RED, OUTPUT);
pinMode(YELLOW, OUTPUT);
pinMode(GREEN, OUTPUT);

pinMode(BUTTON, INPUT\_PULLUP);

pinMode(TRIG, OUTPUT);
pinMode(ECHO, INPUT);

pinMode(BUZZER, OUTPUT);

pinMode(dataPin, OUTPUT);
pinMode(clockPin, OUTPUT);
pinMode(latchPin, OUTPUT);

Serial.begin(9600);
}

void loop()
{
float distance = getDistance();

Serial.print("Distance: ");
Serial.print(distance);
Serial.println(" cm");

int greenTime;

if(distance < 20)
greenTime = 10000;   //10 seconds
else
greenTime = 5000;    //5 seconds

// GREEN
digitalWrite(GREEN, HIGH);
digitalWrite(YELLOW, LOW);
digitalWrite(RED, LOW);

for(int i = 0; i < greenTime / 100; i++)
{
if(digitalRead(BUTTON) == LOW)
{
pedestrianCross();
return;
}

```
delay(100);
```

}

// YELLOW
digitalWrite(GREEN, LOW);
digitalWrite(YELLOW, HIGH);
delay(2000);

// RED
digitalWrite(YELLOW, LOW);
digitalWrite(RED, HIGH);

countdown();

delay(1000);

digitalWrite(RED, LOW);
} is it right bro???????????????????????
