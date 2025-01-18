#include <WiFi.h>
#include "time.h"
#include <EEPROM.h>
#define IN1_1 12
#define IN2_1 14
#define IN3_1 27
#define IN4_1 26

#define IN5_1 33
#define IN6_1 32
#define IN7_1 35
#define IN8_1 34
const char* daysOfWeek[] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
const int motorSteps[4][4] = {
{HIGH, LOW, LOW, HIGH},
{HIGH, HIGH, LOW, LOW},
{LOW, HIGH, HIGH, LOW},
{LOW, LOW, HIGH, HIGH}
};
float focusTime[] = {4.0, 3.75, 3.5, 3.25, 3.0, 2.75, 2.5, 2.25, 2.0, 1.75, 1.5, 1.25, 1.0, 0.75, 0.50, 0.25};
static int storedDay = 1;
static int todaysDay = 1;
static int hourMin = 0; 


void setup() {                                                                                                  //-> SETUP
  Serial.begin(9600);
  // WiFi.begin("GNXS-9A22A1", "Dangerwifi");
  // int wifiCounter = 0;
  // while (WiFi.status() != WL_CONNECTED) {
  //   delay(10000);
  //   Serial.print(".");
  //   wifiCounter++;
  //   if (wifiCounter > 20) {
  //     Serial.println("Failed to connect to WiFi.");
  //     return; 
  //   }
  // }
  // configTime(19800, 0, "pool.ntp.org");
  // Serial.println("Waiting for NTP time...");
  // struct tm timeInfo;
  // while (!getLocalTime(&timeInfo)) {
  //   Serial.print(".");
  //   delay(1000);
  // }

  //  int storedDay = EEPROM.read(0);
  //  if (storedDay >= 0 && storedDay <= 6) {
  //   Serial.print("Day already stored in EEPROM: ");
  //   Serial.println(daysOfWeek[storedDay]);  // Print the stored day name
  //  } else {
  //   int today = timeInfo.tm_wday;  // Get the current day from NTP (0 = Sunday, 6 = Saturday)
  //   EEPROM.write(0, today);  // Store the new day
  //   EEPROM.commit();         // Commit the changes
  //   Serial.print("Stored new day in EEPROM: ");
  //   Serial.println(daysOfWeek[today]);  // Print the current day name
  // }
  // EEPROM.begin(512);
  // EEPROM.write(0, today);
  // EEPROM.commit(); 

  // pinMode(IN1_1, OUTPUT);
  // pinMode(IN2_1, OUTPUT);
  // pinMode(IN3_1, OUTPUT);
  // pinMode(IN4_1, OUTPUT);
  pinMode(IN5_1, OUTPUT);
  pinMode(IN6_1, OUTPUT);
  pinMode(IN7_1, OUTPUT);
  pinMode(IN8_1, OUTPUT);
  rotate2(350,4);
  // hourMin = timeInfo.tm_hour*100+timeInfo.tm_min;
  // int time = timeInfo.tm_hour*100+timeInfo.tm_min;
  // EEPROM.begin(512);
  // EEPROM.write(1, (time >> 8) & 0xFF);  // Store the high byte (most significant byte)
  // EEPROM.write(2, time & 0xFF);
  // EEPROM.commit(); 
}

void loop() {                                                                                             //-> loop
  static unsigned long lastMillis = millis();
  static struct tm timeInfo;
  // if (millis() - lastMillis >= 10000) {
  //   // if (getLocalTime(&timeInfo)) {
  //     // int storedDay = EEPROM.read(0); // Read the stored day(actual) ->3
  //     // int todaysDay = 1;//->6
  //     // static int todaysDay = 4;
  //     // todaysDay = (todaysDay + 1) % 7; 
  //     // int todaysDay = timeInfo.tm_wday;
  //     int day_diff = (todaysDay - storedDay + 7) % 7;
  //     float rotateDeg = ((360.0 / 7.0) * day_diff);
  //     Serial.print("Stored->");
  //     Serial.println(daysOfWeek[storedDay]);
  //     Serial.print("Today->");
  //     Serial.println(daysOfWeek[todaysDay]);
  //     // Serial.print("rotate by ->");
  //     // Serial.println(rotateDeg);
  //     rotate(rotateDeg,todaysDay);
  //   // }
  //   lastMillis = millis();
  // }
  if (millis() - lastMillis >= 5000) {
    // int timeFromEEPROM = (EEPROM.read(1) << 8) | EEPROM.read(2);
    timeFn();
  }
  delay(5000);
}













void timeFn(){
  // int strHour  = hourMin/100;
  // int strMin   = hourMin%100;
  int strHour  = 1;
  int strMin   = 45;
      if (strMin >= 0 && strMin <= 15) {
        strMin = 0;
      }
      else if (strMin > 15 && strMin <= 30) {
        strMin = 25;
      }
      else if (strMin > 30 && strMin <= 45) {
        strMin = 50;
      }
      else if (strMin > 45 && strMin <= 60) {
        strMin = 45;
      }
  float strTime = strHour + (strMin/100.0);

  int currHour = 9;
  int currMin  = 0;
  if(currHour >= 8 && currHour <= 12){
    int rotateByHour = strHour - (currHour - 8); // 4 - (9 - 8) = 1
    int rotateByMin = abs(strMin - (abs(currMin - 60)));// 15 - (60) = 45
      if (rotateByMin >= 0 && rotateByMin <= 15) {
        rotateByMin = 25;
      }
      else if (rotateByMin > 15 && rotateByMin <= 30) {
        rotateByMin = 50;
      }
      else if (rotateByMin > 30 && rotateByMin <= 45) {
        rotateByMin = 75;
      }
      else if (rotateByMin > 45 && rotateByMin <= 60) {
        rotateByMin = 0;
      }
      float time = rotateByHour + (rotateByMin / 100.0);
    Serial.print(time);
    Serial.println(strTime);
    int t1 = findIndex(time);
    int t2 = findIndex(strTime);
    if(t1 == -1 || t2 == -1){
      Serial.println(t1);
      Serial.println(t2);
      Serial.println("Err in time");
      return;
    }
    Serial.println(abs(t1-t2));
    Serial.println("---------------------------------------");
    
  }else if(currHour >= 14 && currHour <= 18){
    
  }
  else if(currHour >= 20 && currHour <= 24){
    
  }
}
















void rotate(float rotateDeg,int today) {                                                                       //-> Rotate
  int stepsToRotate = round((rotateDeg / 0.17578)/4);
  stepsToRotate = stepsToRotate % 2048;   
  Serial.print("Rotating motor by ");
  Serial.print(stepsToRotate);
  Serial.println(" steps");

  Serial.print(abs(stepsToRotate));
  for (int i = 0; i < abs(stepsToRotate); i++) {
    for (int step = 0; step < 4; step++) {
      digitalWrite(IN1_1, motorSteps[step][0]);
      digitalWrite(IN2_1, motorSteps[step][1]);
      digitalWrite(IN3_1, motorSteps[step][2]);
      digitalWrite(IN4_1, motorSteps[step][3]);
      delay(10);
    }
  }
  todaysDay=random(0,7);
  storedDay = today;
    // EEPROM.write(0,today ); 
    // EEPROM.commit();
}

void rotate2(float rotateDeg, int today) {                                                                       //-> Rotate
  int stepsToRotate = round((rotateDeg / 0.17578) / 4);
  stepsToRotate = stepsToRotate % 2048;  // Ensure the number of steps is within the stepper's limits

  Serial.print("Rotating motor by ");
  Serial.print(stepsToRotate);
  Serial.println(" steps");

  Serial.print(abs(stepsToRotate));
  // Rotate counterclockwise (reverse the direction by changing step order)
  for (int i = 0; i < abs(stepsToRotate); i++) {
    for (int step = 0; step < 4; step++) {
      digitalWrite(IN5_1, motorSteps[step][0]);
      digitalWrite(IN6_1, motorSteps[step][1]);
      digitalWrite(IN7_1, motorSteps[step][2]);
      digitalWrite(IN8_1, motorSteps[step][3]);
      delay(10);
    }
  }
}


int findIndex(float target) {
  for (int i = 0; i < 16; i++) {
    if (focusTime[i] == target) {
      return i; // Return the index when found
    }
  }
  return -1; // Return -1 if the target is not found
}
