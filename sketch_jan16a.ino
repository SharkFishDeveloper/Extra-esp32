  #include <WiFi.h>
  #include "time.h"
  #include <EEPROM.h>
  struct TimeDifference {
    int hours;
    int minutes;
  };
  #define IN1_1 12
  #define IN2_1 14
  #define IN3_1 27
  #define IN4_1 26

  #define IN5_1 33
  #define IN6_1 32
  #define IN7_1 35
  #define IN8_1 34

  const char* daysOfWeek[] = { "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday" };
  const int motorSteps[4][4] = {
    { HIGH, LOW, LOW, HIGH },
    { HIGH, HIGH, LOW, LOW },
    { LOW, HIGH, HIGH, LOW },
    { LOW, LOW, HIGH, HIGH }
  };
  static int storedDay = 1;
  static int todaysDay = 1;

  void setup() {
    Serial.begin(9600);
    WiFi.begin("GNXS-9A22A1", "Dangerwifi");
    int wifiCounter = 0;
    while (WiFi.status() != WL_CONNECTED) {
      delay(10000);
      Serial.print(".");
      wifiCounter++;
      if (wifiCounter > 20) {
        Serial.println("Failed to connect to WiFi.");
        return;
      }
    }
    configTime(19800, 0, "pool.ntp.org");
    Serial.println("Waiting for NTP time...");
    struct tm timeInfo;
    while (!getLocalTime(&timeInfo)) {
      Serial.print(".");
      delay(1000);
    }

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

    // timeFn(7,15);


    // EEPROM.begin(512);
    // EEPROM.write(1, (1) & 0xFF); 
    //         int n = 0;
    // int minute = n < 0 ? 256 + n : n; 
    // EEPROM.write(2, (minute / 256) & 0xFF);  // Store the high byte of minutes in EEPROM at address 2
    // EEPROM.write(3, minute & 0xFF);
    // EEPROM.commit();

    // int storedTime = EEPROM.read(1);
    // int storedMin = EEPROM.read(2);
    // if(storedTime < -1 || storedTime > 4){
    // int positiveEquivalent = storedMin < 0 ? 256 + storedMin : storedMin;
    // EEPROM.begin(512);
    // EEPROM.write(1, (0) & 0xFF); 
    // EEPROM.write(2, positiveEquivalent && 0xFF);
    // EEPROM.commit();
    // }
  }

  void loop() {  //-> loop
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
    timeFn();
    delay(15000);
  }



  void timeFn() {
    // int timeFromEEPROM = EEPROM.read(1);
    // int storedHighByte = EEPROM.read(2);  
    // int storedLowByte = EEPROM.read(3);
    // int strMin = storedHighByte * 256 + storedLowByte;  
    // if (strMin > 127) {
    //   strMin -= 256;
    // }
    // int strHour = timeFromEEPROM;

    // struct tm timeInfo;
    // configTime(19800, 0, "pool.ntp.org");
    // while (!getLocalTime(&timeInfo)) {
    //   Serial.print(".");
    //   delay(1000);
    // }
    
    int currHour = 8;
    int currMin = 30;
    int strHour = 2;
    int strMin = 30;
    // int currHour = timeInfo.tm_hour;
    // int currMin = timeInfo.tm_min;
    
    Serial.print(currHour);
    Serial.println(currMin);
    Serial.print("=>");
    Serial.print(strHour);
    Serial.print(strMin);
    Serial.println("END");
    if (currMin >= 0 && currMin < 15) {
      currMin = 0;
    } else if (currMin >= 15 && currMin < 30) {
      currMin = 15;
    } else if (currMin >= 30 && currMin < 45) {
      currMin = 30;
    } else if (currMin >= 45 && currMin < 60) {
      currMin = 45;
    }

    int storedTimeInMinutes = strHour * 60 + strMin; 

    if (currHour >= 8 && currHour <= 12) {
      if(currHour == 12 && currMin >= 0){
        currMin = 0;
      }
      int currentTimeInMinutes = currHour * 60 + currMin;
      int _8inMinutes = 8 * 60;                                                                                                        
      int differenceInMinutes = abs(currentTimeInMinutes - _8inMinutes) - storedTimeInMinutes;  
      int intervalsOf15 = (differenceInMinutes / 15);                                           
      int day_diff = intervalsOf15 < 0 ? 20 - (abs((intervalsOf15)) % 20) : (abs((intervalsOf15)) % 20);
      float rotateDeg = (18.0 * day_diff);
      Serial.print("DAY DIFF 8 // ");
      Serial.println(day_diff);
      TimeDifference diff = calculateTimeDifference(currHour, currMin, strHour, strMin,8);
      // Serial.print(diff.hours);
      // Serial.print(":");
      // Serial.println(diff. minutes);
      rotate2(rotateDeg,diff);
          // Serial.println("====");
    } 
    else if (currHour >= 14 && currHour <= 18) {
      if(currHour == 18 && currMin >= 0){
        currMin = 0;
      }
      int currentTimeInMinutes = currHour * 60 + currMin; 
      int _2inMinutes = 14 * 60;
      int differenceInMinutes = abs(currentTimeInMinutes - _2inMinutes) - storedTimeInMinutes;  
      int intervalsOf15 = (differenceInMinutes / 15);   
      int day_diff = intervalsOf15 < 0 ? 20 - (abs((intervalsOf15)) % 20) : (abs((intervalsOf15)) % 20);
      float rotateDeg = (18.0 * day_diff);
      Serial.print("DAY DIFF 12 // ");
      Serial.println(day_diff);    
      TimeDifference diff = calculateTimeDifference(currHour, currMin, strHour, strMin,14);
      // Serial.print(diff.hours);
      // Serial.print(":");
      // Serial.println(diff. minutes);
      rotate2(rotateDeg,diff);
          // Serial.println("====");
    } 
    else if (currHour >= 20 && currHour <= 24) {
        if(currHour == 24 && currMin >= 0){
          currMin = 0;
        }
      int currentTimeInMinutes = currHour * 60 + currMin; // 1320
      int _20inMinutes = 20 * 60; // 1200
      int differenceInMinutes = abs(currentTimeInMinutes - _20inMinutes) - storedTimeInMinutes;  // 120 - 270== -150 
      int intervalsOf15 = (differenceInMinutes / 15);   
      int day_diff = intervalsOf15 < 0 ? 20 - (abs((intervalsOf15)) % 20) : (abs((intervalsOf15)) % 20);
      float rotateDeg = (18.0 * day_diff);
      Serial.print("DAY DIFF 20 // ");
      Serial.println(day_diff);   
      TimeDifference diff = calculateTimeDifference(currHour, currMin, strHour, strMin,20);
      // Serial.print(diff.hours);
      // Serial.print(":");
      // Serial.println(diff. minutes);
      rotate2(rotateDeg,diff);
          // Serial.println("====");
    }

    // Time is out of boundary
    else if(currHour >= 13 && currHour < 14){
      int remTime = currMin/15; // 30/15 = 2
      int quarter15 = calculate15MinuteIntervals(strHour,strMin);// 0:-45
      int total = (remTime +  quarter15);
      total = total > 20 ? total % 20 : total;
      Serial.println(total);

      float rotateDeg = (18.0 * total);
      TimeDifference diff = IdelTimeDifference(currMin);
      // Serial.print(diff.hours);
      // Serial.print(":");
      // Serial.println(diff. minutes);
      rotate2(rotateDeg,diff);
          // Serial.println("====");
    }
    else if(currHour >= 19 && currHour < 20){
      int remTime = currMin/15; //3
      int quarter15 = calculate15MinuteIntervals(strHour,strMin);// 2
      int total = (remTime +  quarter15);
      Serial.println(total);
       total = total > 20 ? total % 20 : total;
      float rotateDeg = (18.0 * total);
      TimeDifference diff = IdelTimeDifference(currMin);
      // Serial.print(diff.hours);
      // Serial.print(":");
      // Serial.println(diff. minutes);
      rotate2(rotateDeg,diff);
          // Serial.println("====");
    }
    else if(currHour >= 7 && currHour < 8){
      int remTime = currMin/15; //3
      int quarter15 = calculate15MinuteIntervals(strHour,strMin);// 2
      int total = (remTime +  quarter15);
       total = total > 20 ? total % 20 : total;
      Serial.println(total);
      float rotateDeg = (18.0 * total);
      TimeDifference diff = IdelTimeDifference(currMin);
      // Serial.print(diff.hours);
      // Serial.print(":");
      // Serial.println(diff. minutes);
      rotate2(rotateDeg,diff);
          // Serial.println("====");
    }
  }











  void rotate(float rotateDeg, int today) { 
    int stepsToRotate = round((rotateDeg / 0.17578) / 4);
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
    todaysDay = random(0, 7);
    storedDay = today;
    // EEPROM.write(0,today );
    // EEPROM.commit();
  }

  void rotate2(float rotateDeg, TimeDifference diff) { 
    int stepsToRotate = round((rotateDeg / 0.17578) / 4);
    stepsToRotate = stepsToRotate % 2048;
    for (int i = 0; i < abs(stepsToRotate); i++) {
      for (int step = 0; step < 4; step++) {
        digitalWrite(IN5_1, motorSteps[step][0]);
        digitalWrite(IN6_1, motorSteps[step][1]);
        digitalWrite(IN7_1, motorSteps[step][2]);
        digitalWrite(IN8_1, motorSteps[step][3]);
        delay(10);
      }
    }
    Serial.print("Diff.hours->");
    Serial.print(diff.hours);
    Serial.print("Diff.Min->");
    Serial.print(diff.minutes);
  }



  TimeDifference calculateTimeDifference(int currHour, int currMin, int strHour, int strMin,int baseHour) {
    TimeDifference diff;
  strHour = (baseHour) % 24;
  diff.hours = currHour - strHour; //8
  diff.minutes = currMin - 0;//0
  if (diff.minutes < 0) {
    diff.minutes += 60;
    diff.hours -= 1;
  }
  if (diff.hours < 0) {
    diff.hours += 24;
  }
    int min = diff.minutes < 0 ? 256 + diff.minutes : diff.minutes;
    EEPROM.begin(512);
    EEPROM.write(1, (diff.hours) & 0xFF); 
    EEPROM.write(2, (min / 256) & 0xFF);  // Store the high byte (will be 0 for values < 256)
    EEPROM.write(3, min & 0xFF); 
    EEPROM.commit();
  return diff;
  }

  TimeDifference IdelTimeDifference(int currMin) {
    TimeDifference diff;
    diff.minutes = currMin;
    diff.hours = 0;
    if (diff.minutes < 0) {
      diff.minutes += 60;
      diff.hours -= 1;
    }
    if (diff.hours < 0) {
      diff.hours += 24;  
    }
    int min = diff.minutes < 0 ? 256 + diff.minutes : diff.minutes;
    EEPROM.begin(512);
    EEPROM.write(1, (diff.hours) & 0xFF); 
    EEPROM.write(2, (min / 256) & 0xFF);  // Store the high byte (will be 0 for values < 256)
    EEPROM.write(3, min & 0xFF); 
    EEPROM.commit();
    return diff;
  }


  int calculate15MinuteIntervals(int currHour, int currMin) {
      int timeH = currHour % 12;
      int adjustedHour = 4 - timeH;
      if (adjustedHour < 0) {
          adjustedHour += 12;
      }
      int adjustedTotalMinutes = adjustedHour * 60 - (-60 - currMin);
      if (adjustedTotalMinutes < 0) {
          adjustedTotalMinutes += 12 * 60; 
      }
      return adjustedTotalMinutes / 15;
  }