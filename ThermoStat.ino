#include <DHT.h>
#include <LinkedList.h>
#define BLYNK_PRINT Serial
#include "Time.h"
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#define INTERVAL_MESSAGE1 5000
#define DHTTYPE DHT11 




char auth[] = "YOUR BLYNK TOKEN HERE";


// Set password to "" for open networks.
char ssid[] = "YOUR Network name HERE";
char pass[] = "Your Password";
BlynkTimer timer;
WidgetLCD lcd(V1);
long endTimeInSecs;
long startTimeInSecs;
long daySeconds;
long weekSeconds;
long thursdaySeconds = 86400;
long fridaySeconds = 86400 + 86400;
long saturdaySeconds = 86400 + 86400 + 86400;
long sundaySeconds = 86400 + 86400 + 86400 + 86400;
long mondaySeconds = 86400 + 86400 + 86400 + 86400 + 86400;
long tuesdaySeconds = 86400 + 86400 + 86400 + 86400 + 86400 + 86400;
long wednesdaySeconds = 86400 + 86400 + 86400 + 86400 + 86400 + 86400+ 86400;

const int acRELAY_PIN = 4;
const int heatRELAY_PIN = 5;

const int  DHTPin = 12;
//3volt
DHT dht(DHTPin, DHTTYPE);

int Temperature;
int Humidity;

 
unsigned long time_1 = 0;
unsigned long time_2 = 0;
unsigned long time_3 = 0;
unsigned long time_4 = 0;
int count = 0;
int key = 0;
int hold = 0;
int monSize,tueSize,wedSize,thurSize,friSize,satSize,sunSize;
int stepValue;

volatile int acORheatValue = 5;

LinkedList<long> monStart = LinkedList<long>();
LinkedList<long> monStop = LinkedList<long>();
LinkedList<long> tueStart = LinkedList<long>();
LinkedList<long> tueStop = LinkedList<long>();
LinkedList<long> wedStart = LinkedList<long>();
LinkedList<long> wedStop = LinkedList<long>();
LinkedList<long> thurStart = LinkedList<long>();
LinkedList<long> thurStop = LinkedList<long>();
LinkedList<long> friStart = LinkedList<long>();
LinkedList<long> friStop = LinkedList<long>();
LinkedList<long> satStart = LinkedList<long>();
LinkedList<long> satStop = LinkedList<long>();
LinkedList<long> sunStart = LinkedList<long>();
LinkedList<long> sunStop = LinkedList<long>();

//ui io

void requestTime() {
  Blynk.sendInternal("rtc", "sync");
}

BLYNK_WRITE(InternalPinRTC) {
  long t = param.asLong();
  daySeconds = t % 86400;
  weekSeconds = t % 604800;

}


BLYNK_WRITE(V4) { // step
  stepValue = (param.asFloat()); // set the global step value
  
}



  BLYNK_WRITE(V3){
  
    if (param.asInt()) {
        //HIGH
        //switch selected heat
        Serial.print( " heat   hght " );
        acORheatValue = 1;
    } else {
       //LOW
        Serial.print( "ac   low " );
        acORheatValue = 0;
    }
}




//schedule clear function
BLYNK_WRITE(V2){
monStart.clear();
monStop.clear();
tueStart.clear();
tueStop.clear();
wedStart.clear();
wedStop.clear();
thurStart.clear();
thurStop.clear();
friStart.clear();
friStop.clear();
satStart.clear();
satStop.clear();
sunStart.clear();
sunStop.clear();
  
}


BLYNK_WRITE(V0) {
  startTimeInSecs = param[0].asLong();
  endTimeInSecs = param[1].asLong();
  TimeInputParam t(param);
  for (int i = 1; i <= 7; i++) {
    if (t.isWeekdaySelected(i)) {




         switch (i) {

   case 1:
   {
    monStart.add(startTimeInSecs);
    monStop.add(endTimeInSecs);
    monSize = monStart.size();
    
    Serial.print( " Monday start " );
  
   }
    break;
  case 2:
  {
    tueStart.add(startTimeInSecs);
    tueStop.add(endTimeInSecs);
    tueSize = tueStart.size();
    
    Serial.print( " Tues start ");
    
    break;
  }
  case 3:
  {
    wedStart.add(startTimeInSecs);
    wedStop.add(endTimeInSecs);
    wedSize = wedStart.size();
    
    Serial.print( " wed start ");
    break;
  }
  case 4:
  {
    thurStart.add(startTimeInSecs);
    thurStop.add(endTimeInSecs);
    thurSize = thurStart.size();
    
    Serial.print( " thur start " );
    break;
  }
    case 5:
    {
    friStart.add(startTimeInSecs);
    friStop.add(endTimeInSecs);
    friSize = friStart.size();
    
    Serial.print( " fri start " );
    break;
    }
  case 6:
  {
    satStart.add(startTimeInSecs);
    satStop.add(endTimeInSecs);
    satSize = satStart.size();
    
    Serial.print( " sat start " );
    break;
  }
  case 7:
  {
  
    sunStart.add(startTimeInSecs);
    sunStop.add(endTimeInSecs);
    sunSize = sunStart.size();
    
   Serial.print( " sun start ");
    break;
  }
  

}
    }
  }

  
  







      
    }
  





 

void setup()
{
 
  // Debug console
  Serial.begin(4800);
//time = millis();
  Blynk.begin(auth, ssid, pass);
  timer.setInterval(10000L, requestTime);
  pinMode(acRELAY_PIN, OUTPUT);
  pinMode(heatRELAY_PIN, OUTPUT);
  pinMode(DHTPin, INPUT);

dht.begin();
  
digitalWrite(acRELAY_PIN, HIGH);
digitalWrite(heatRELAY_PIN, HIGH);

}
void print_time(unsigned long time_millis){
}






 void turnRelayON(){

 if(acORheatValue == 0){
  digitalWrite(heatRELAY_PIN, HIGH);
  //if(stepValue<Temperature){
  digitalWrite(acRELAY_PIN, LOW);
  
 // }
  }
  else if(acORheatValue == 1){
    digitalWrite(acRELAY_PIN, HIGH);
  //  if(stepValue>Temperature){
    digitalWrite(heatRELAY_PIN, LOW);
    
   // }
  }
 }

  void turnRelayOFF(){
    
    if(acORheatValue == 0){
    //  if(stepValue>Temperature){
  digitalWrite(acRELAY_PIN, HIGH);
    //  }
  
  }
  else if(acORheatValue == 1){
  //  if(stepValue<Temperature){
    digitalWrite(heatRELAY_PIN, HIGH);
   // }
  }
 }

void loop()
{



  Blynk.run();
  timer.run();
  
  Temperature = dht.readTemperature(); 
     Serial.println("temp in celcius  :" );
  Serial.println(Temperature);
  Temperature = (Temperature * 9/5) + 32;    // Gets the values of the temperature
  Humidity = dht.readHumidity();
   Serial.println("temp  :" );
  Serial.println(Temperature);
  Serial.println("humidity");
  Serial.println(Humidity);
  
 



  if(millis() >= time_1 + INTERVAL_MESSAGE1){
        key = count % 7;
        time_1 +=INTERVAL_MESSAGE1;
        print_time(time_1);
        Serial.println(key);
        //Serial.print();
        lcd.clear();
        
       
        
        
        
        switch (key) {

  case 0:
  {

    int temp = monSize;
    int iter = 0;
    
    while(temp >= 0){
      delay(1000);
      lcd.print(0, 1,"M");
      lcd.print(3, 1,(monStart.get(iter)/60/60%24));
      lcd.print(5, 1, ":");
      lcd.print(6, 1, (monStart.get(iter)/60%60));
      lcd.print(8, 1, "to");
      lcd.print(11, 1,(monStop.get(iter)/60/60%24));
      lcd.print(13, 1, ":");
      lcd.print(14, 1, (monStop.get(iter)/60%60));

          lcd.print(0, 0, "CUR");
    lcd.print(4, 0, Temperature);
    lcd.print(6, 0, "F");
    lcd.print(7, 0, Humidity);
    lcd.print(9, 0, "%");
    lcd.print(10, 0, "SET");
    lcd.print(13, 0, stepValue);
   lcd.print(15, 0, "F");
      
      iter++;
      temp--;
      //count--;
    }
    
    break;
        }
  case 1:
  {

    int temp = tueSize;
    int iter = 0;
    
    while(temp >= 0){
      delay(1000);
            lcd.print(0, 1,"T");
      lcd.print(3, 1,(tueStart.get(iter)/60/60%24));
      lcd.print(5, 1, ":");
      lcd.print(6, 1, (tueStart.get(iter)/60%60));
      lcd.print(8, 1, "to");
      lcd.print(11, 1,(tueStop.get(iter)/60/60%24));
      lcd.print(13, 1, ":");
      lcd.print(14, 1, (tueStop.get(iter)/60%60));

          lcd.print(0, 0, "CUR");
    lcd.print(4, 0, Temperature);
    lcd.print(6, 0, "F");
    lcd.print(7, 0, Humidity);
    lcd.print(9, 0, "%");
    lcd.print(10, 0, "SET");
    lcd.print(13, 0, stepValue);
   lcd.print(15, 0, "F");
      
      iter++;
      temp--;
      //count--;
    }
    break;
        }
  case 2:
  {

        int temp = wedSize;
    int iter = 0;
    
    while(temp >= 0){
      delay(1000);
           lcd.print(0, 1,"W");
      lcd.print(3, 1,(wedStart.get(iter)/60/60%24));
      lcd.print(5, 1, ":");
      lcd.print(6, 1, (wedStart.get(iter)/60%60));
      lcd.print(8, 1, "to");
      lcd.print(11, 1,(wedStop.get(iter)/60/60%24));
      lcd.print(13, 1, ":");
      lcd.print(14, 1, (wedStop.get(iter)/60%60));
          lcd.print(0, 0, "CUR");
    lcd.print(4, 0, Temperature);
    lcd.print(6, 0, "F");
    lcd.print(7, 0, Humidity);
    lcd.print(9, 0, "%");
    lcd.print(10, 0, "SET");
    lcd.print(13, 0, stepValue);
   lcd.print(15, 0, "F");
      
      iter++;
      temp--;
      }
    break;
  
  }
  
  case 3:
  {

        int temp = thurSize;
    int iter = 0;
    
    while(temp >= 0){
      delay(1000);
           lcd.print(0, 1,"Th");
      lcd.print(3, 1,(thurStart.get(iter)/60/60%24));
      lcd.print(5, 1, ":");
      lcd.print(6, 1, (thurStart.get(iter)/60%60));
      lcd.print(8, 1, "to");
      lcd.print(11, 1,(thurStop.get(iter)/60/60%24));
      lcd.print(13, 1, ":");
      lcd.print(14, 1, (thurStop.get(iter)/60%60));

          lcd.print(0, 0, "CUR");
    lcd.print(4, 0, Temperature);
    lcd.print(6, 0, "F");
    lcd.print(7, 0, Humidity);
    lcd.print(9, 0, "%");
    lcd.print(10, 0, "SET");
    lcd.print(13, 0, stepValue);
   lcd.print(15, 0, "F");
      
      iter++;
      temp--;
       }
    break;
 
  }
    case 4:
    {

        int temp = friSize;
    int iter = 0;
    
    while(temp >= 0){
      delay(1000);
      iter++;
      temp--;
      }
    break;
    
    }
  case 5:
  {

        int temp = satSize;
    int iter = 0;
    
    while(temp >= 0){
      delay(1000);
           lcd.print(0, 1,"Sa");
      lcd.print(3, 1,(satStart.get(iter)/60/60%24));
      lcd.print(5, 1, ":");
      lcd.print(6, 1, (satStart.get(iter)/60%60));
      lcd.print(8, 1, "to");
      lcd.print(11, 1,(satStop.get(iter)/60/60%24));
      lcd.print(13, 1, ":");
      lcd.print(14, 1, (satStop.get(iter)/60%60));

          lcd.print(0, 0, "CUR");
    lcd.print(4, 0, Temperature);
    lcd.print(6, 0, "F");
    lcd.print(7, 0, Humidity);
    lcd.print(9, 0, "%");
    lcd.print(10, 0, "SET");
    lcd.print(13, 0, stepValue);
   lcd.print(15, 0, "F");

      
      iter++;
      temp--;
      }
    break;
  
  }
  case 6:
  {            
   
        int temp = sunSize;
    int iter = 0;
    
    while(temp >= 0){
      delay(1000);
           lcd.print(0, 1,"Su");
      lcd.print(3, 1,(sunStart.get(iter)/60/60%24));
      lcd.print(5, 1, ":");
      lcd.print(6, 1, (sunStart.get(iter)/60%60));
      lcd.print(8, 1, "to");
      lcd.print(11, 1,(sunStop.get(iter)/60/60%24));
      lcd.print(13, 1, ":");
      lcd.print(14, 1, (sunStop.get(iter)/60%60));

           lcd.print(0, 0, "CUR");
    lcd.print(4, 0, Temperature);
    lcd.print(6, 0, "F");
    lcd.print(7, 0, Humidity);
    lcd.print(9, 0, "%");
    lcd.print(10, 0, "SET");
    lcd.print(13, 0, stepValue);
   lcd.print(15, 0, "F");

      
      iter++;
      temp--;
       }
    break;
 

}


    
    
    
    }
    count++;
  }

    

            

   if((mondaySeconds -  86400) < weekSeconds && weekSeconds < mondaySeconds)
   {
    Serial.print( "Unit is within Monday start time----------------------------------------------------------------" );

    int temp = monSize;
    int iter = 0;
    int count = 0;
    
    while(temp >= 0){
      if(monStart.get(iter) < daySeconds && daySeconds < monStop.get(iter)){
  count++;
     }
      iter++;
      temp--;
      }

  if(count > 0){
          if(acORheatValue == 0){
      if(stepValue<Temperature){
  digitalWrite(heatRELAY_PIN, HIGH);
  digitalWrite(acRELAY_PIN, LOW);
     }else{
     digitalWrite(acRELAY_PIN, HIGH);
     digitalWrite(heatRELAY_PIN, HIGH);
     }
  
  }
  else if(acORheatValue == 1){
    if(stepValue>Temperature){
  digitalWrite(acRELAY_PIN, HIGH);
  digitalWrite(heatRELAY_PIN, LOW);
    }else{
     digitalWrite(heatRELAY_PIN, HIGH);
     digitalWrite(acRELAY_PIN, HIGH);
    }
  }
          
        }else
        {
        turnRelayOFF();
        }
  }
  
   
  
   else if((tuesdaySeconds - 86400) < weekSeconds && weekSeconds < tuesdaySeconds)
    {
    Serial.print( "Unit is within tue start time--------------------------------------------------------------------" );

    int temp = tueSize;
    int iter = 0;
    int count = 0;
    
    while(temp >= 0){
      if(tueStart.get(iter) < daySeconds && daySeconds < tueStop.get(iter)){
  count++;
     }
      iter++;
      temp--;
      }

     if(count > 0){
          if(acORheatValue == 0){
      if(stepValue<Temperature){
  digitalWrite(heatRELAY_PIN, HIGH);
  digitalWrite(acRELAY_PIN, LOW);
     }else{
     digitalWrite(acRELAY_PIN, HIGH);
     digitalWrite(heatRELAY_PIN, HIGH);
     }
  
  }
  else if(acORheatValue == 1){
    if(stepValue>Temperature){
  digitalWrite(acRELAY_PIN, HIGH);
  digitalWrite(heatRELAY_PIN, LOW);
    }else{
     digitalWrite(heatRELAY_PIN, HIGH);
     digitalWrite(acRELAY_PIN, HIGH);
    }
  }
          
        }else
        {
        turnRelayOFF();
        }
  }
  
   
   else if((wednesdaySeconds - 86400) < weekSeconds && weekSeconds < wednesdaySeconds)
   {
   // Serial.print( "Unit is within wed start time  DAY----------------------------------------------------" );

    int temp = wedSize;
    int iter = 0;
    int count = 0;
    
    while(temp >= 0){
      if(wedStart.get(iter) < daySeconds && daySeconds < wedStop.get(iter)){
      
        
        count++;
      }


      
      iter++;
      temp--;
    
  }

     
     if(count > 0){
          if(acORheatValue == 0){
      if(stepValue<Temperature){
  digitalWrite(heatRELAY_PIN, HIGH);
  digitalWrite(acRELAY_PIN, LOW);
     }else{
     digitalWrite(acRELAY_PIN, HIGH);
     digitalWrite(heatRELAY_PIN, HIGH);
     }
  
  }
  else if(acORheatValue == 1){
    if(stepValue>Temperature){
  digitalWrite(acRELAY_PIN, HIGH);
  digitalWrite(heatRELAY_PIN, LOW);
    }else{
     digitalWrite(heatRELAY_PIN, HIGH);
     digitalWrite(acRELAY_PIN, HIGH);
    }
  }
          
        }else
        {
        turnRelayOFF();
        }
  }
    else if((thursdaySeconds - 86400) < weekSeconds && weekSeconds < wednesdaySeconds + 86400)
   {
    Serial.print( "Unit is within thur start time------------------------------------------" );

    int temp = thurSize;
    int iter = 0;
    int count = 0;
    
    while(temp >= 0){
      if(thurStart.get(iter) < daySeconds && daySeconds < thurStop.get(iter)){
        count++;
      }


      
      iter++;
      temp--;
    
  }
     if(count > 0){
          if(acORheatValue == 0){
      if(stepValue<Temperature){
  digitalWrite(heatRELAY_PIN, HIGH);
  digitalWrite(acRELAY_PIN, LOW);
     }else{
     digitalWrite(acRELAY_PIN, HIGH);
     digitalWrite(heatRELAY_PIN, HIGH);
     }
  
  }
  else if(acORheatValue == 1){
    if(stepValue>Temperature){
  digitalWrite(acRELAY_PIN, HIGH);
  digitalWrite(heatRELAY_PIN, LOW);
    }else{
     digitalWrite(heatRELAY_PIN, HIGH);
     digitalWrite(acRELAY_PIN, HIGH);
    }
  }
          
        }else
        {
        turnRelayOFF();
        }
  }
    else if((fridaySeconds - 86400) < weekSeconds && weekSeconds < fridaySeconds)
    {
    Serial.print( "Unit is within fri start time---------------------------------------------------" );

    int temp = friSize;
    int iter = 0;
    int count = 0;
    
    while(temp >= 0){
      if(friStart.get(iter) < daySeconds && daySeconds < friStop.get(iter)){
        count++;
      }


      
      iter++;
      temp--;
    
  }
          
     if(count > 0){
          if(acORheatValue == 0){
      if(stepValue<Temperature){
  digitalWrite(heatRELAY_PIN, HIGH);
  digitalWrite(acRELAY_PIN, LOW);
     }else{
     digitalWrite(acRELAY_PIN, HIGH);
     digitalWrite(heatRELAY_PIN, HIGH);
     }
  
  }
  else if(acORheatValue == 1){
    if(stepValue>Temperature){
  digitalWrite(acRELAY_PIN, HIGH);
  digitalWrite(heatRELAY_PIN, LOW);
    }else{
     digitalWrite(heatRELAY_PIN, HIGH);
     digitalWrite(acRELAY_PIN, HIGH);
    }
  }
          
        }else
        {
        turnRelayOFF();
        }
  }
    else if((saturdaySeconds - 86400) < weekSeconds && weekSeconds < saturdaySeconds)
    {
    Serial.print( "Unit is within sat start time-------------------------------------------" );

    int temp = satSize;
    int iter = 0;
    int count = 0;
    
    while(temp >= 0){
      if(satStart.get(iter) < daySeconds && daySeconds < satStop.get(iter)){
        count++;
      }


      
      iter++;
      temp--;
    
  }
         
     if(count > 0){
          if(acORheatValue == 0){
      if(stepValue<Temperature){
  digitalWrite(heatRELAY_PIN, HIGH);
  digitalWrite(acRELAY_PIN, LOW);
     }else{
     digitalWrite(acRELAY_PIN, HIGH);
     digitalWrite(heatRELAY_PIN, HIGH);
     }
  
  }
  else if(acORheatValue == 1){
    if(stepValue>Temperature){
  digitalWrite(acRELAY_PIN, HIGH);
  digitalWrite(heatRELAY_PIN, LOW);
    }else{
     digitalWrite(heatRELAY_PIN, HIGH);
     digitalWrite(acRELAY_PIN, HIGH);
    }
  }
          
        }else
        {
        turnRelayOFF();
        }
  }
   else if((sundaySeconds - 86400) < weekSeconds && weekSeconds < sundaySeconds)
    {
    Serial.print( "Unit is within sun start time--------------------------------------------" );

    int temp = sunSize;
    int iter = 0;
    int count = 0;
    
    while(temp >= 0){
      if(sunStart.get(iter) < daySeconds && daySeconds < sunStop.get(iter)){
        count++;
      }


      
      iter++;
      temp--;
    
  }
           
     if(count > 0){
          if(acORheatValue == 0){
      if(stepValue<Temperature){
  digitalWrite(heatRELAY_PIN, HIGH);
  digitalWrite(acRELAY_PIN, LOW);
     }else{
     digitalWrite(acRELAY_PIN, HIGH);
     digitalWrite(heatRELAY_PIN, HIGH);
     }
  
  }
  else if(acORheatValue == 1){
    if(stepValue>Temperature){
  digitalWrite(acRELAY_PIN, HIGH);
  digitalWrite(heatRELAY_PIN, LOW);
    }else{
     digitalWrite(heatRELAY_PIN, HIGH);
     digitalWrite(acRELAY_PIN, HIGH);
    }
  }
          
        }else
        {
        turnRelayOFF();
        }
  }
 //ac and heat cant both be on at the same time
  if(digitalRead(heatRELAY_PIN) == LOW && digitalRead(acRELAY_PIN) == LOW){
  digitalWrite(heatRELAY_PIN, HIGH);
  digitalWrite(acRELAY_PIN, HIGH);

  }
  
  }
   



  
