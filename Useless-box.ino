#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
#include <Servo.h>
#include <LiquidCrystal.h> 

#define DHTPIN 6     // what pin we're connected to
#define DHTTYPE DHT22   // DHT22
Servo fingerServo;
Servo doorServo;
int switchPin = 9;
const int trigPin = 10;
const int echoPin = 11;
const int rs = 12, en = 13, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
int pos = 0;
int selectedMove = 0;
int sensorMove = 0;
long duration;
int distance;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  // put your setup code here, to run once:
  lcd.begin(16, 2);
  pinMode(A0, INPUT);
  pinMode(switchPin, INPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  fingerServo.attach(7);
  doorServo.attach(8);
  doorServo.write(90);
  fingerServo.write(180);
  dht.begin();
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  lcd.noDisplay();
  distance = getDistance();
  

  if (digitalRead(switchPin) == HIGH) {
    if (selectedMove > 9) { 
    selectedMove = 0; 
    } //when all moves are played, repeat the moves from beginning 
    
    if (selectedMove == 0) { 
    simpleClose(); 
    }
    else if (selectedMove == 1) { 
    simpleClose(); 
    }   
    else if (selectedMove == 2) { 
    simpleClose2(); 
    }
    else if (selectedMove == 3) { 
    crazydoor(); 
    }
    else if (selectedMove == 4) { 
    slow(); 
    }
    else if (selectedMove == 5) { 
    serious(); 
    }
    else if (selectedMove == 6) { 
    trollClose(); 
    }
    else if (selectedMove == 7) { 
    simpleClose(); 
    }
    else if (selectedMove == 8) { 
    matrix(); 
    }
    else if (selectedMove == 9) { 
    sneak(); 
    }
     
   selectedMove += 1;  
  }
  
  distance = getDistance();
  if (distance <= 10) {
    if (sensorMove > 2){
    sensorMove = 0;
    }

    if (sensorMove == 0) {
    simpleDoorOpen();
    }

    if (sensorMove == 1) {
    slowDoorOpen();  
    }

    if (sensorMove == 2) {
    superFastOpen();
    }

    sensorMove += 1;
  }
  
}

// Moves

  // basic move 
  void simpleClose() 
  {    
  //Moving door
  for(pos = 90; pos < 155; pos += 3)   
  {           
    displayTemp();
    doorServo.write(pos);              
    delay(15);                       
  }
  
  //Moving hand
  for(pos = 180; pos > 180-129; pos -= 4)  
  {                                   
    fingerServo.write(pos);               
    delay(15);                       
  }  
  
  //hiding hand
  for(pos = 180-129; pos<=180; pos+=4)      
  {                                
    fingerServo.write(pos);               
    delay(15);                        
  } 
    
  //hiding door
  for(pos = 155; pos>=90; pos-=3)     
  {             
    displayTemp();                     
    doorServo.write(pos);              
    delay(15);                      
  } 
  } 
    
  // open and wait, then move finger and wait, then switch of and hide  
  void simpleClose2()
  {
//Moving door
  for(pos = 90; pos < 155; pos += 3)   
  {              
    displayTemp();                     
    doorServo.write(pos);              
    delay(15);                       
  }
  delay(800); 
  //Moving hand
  for(pos = 180; pos > 180- 100; pos -= 4)  
  {                                   
    fingerServo.write(pos);               
    delay(15);                       
  }
  delay(1000); 
  for(pos = 180-100; pos > 180-129; pos -= 4)  
  {                                   
    fingerServo.write(pos);               
    delay(15);                       
  }    
  
  //hiding hand
  for(pos = 180-129; pos<=180; pos+=5)      
  {                                
    fingerServo.write(pos);               
    delay(15);                        
  } 
    
  //hiding door
  for(pos = 155; pos>=90; pos-=3)     
  {       
    displayTemp();                           
    doorServo.write(pos);              
    delay(15);                    
  } 
    
  }

  //open door then close it many times, wait, then quickly reopen, switch off and hide.

  void crazydoor()
{
  
  //Moving door
  for(pos = 90; pos < 125; pos += 3)   
  {            
    displayTemp();                         
    doorServo.write(pos);              
    delay(15);                       
  }

  //hiding door
  for(pos = 125; pos>=90; pos-=5)     
  {                
    displayTemp();                  
    doorServo.write(pos);              
    delay(15);                      
  } 
  //Moving door
  for(pos = 90; pos < 110; pos += 3)   
  {           
    displayTemp();                          
    doorServo.write(pos);              
    delay(15);                       
  }

  //hiding door
  for(pos = 110; pos>=90; pos-=15)     
  {      
    displayTemp();                            
    doorServo.write(pos);              
    delay(15);                      
  } 
  delay(700);
  //Moving door
  for(pos = 90; pos < 125; pos += 3)   
  {                  
    displayTemp();                   
    doorServo.write(pos);              
    delay(15);                       
  }
  delay(700);
  //hiding door
  for(pos = 125; pos>=90; pos-=5)     
  {  
    displayTemp();                                
    doorServo.write(pos);              
    delay(15);                      
  } 

//Moving door
  for(pos = 90; pos < 155; pos += 8)   
  {    
    displayTemp();                                 
    doorServo.write(pos);              
    delay(15);                       
  }
  
  //Moving hand
  for(pos = 180; pos > 180-129; pos -= 3)  
  {                                   
    fingerServo.write(pos);               
    delay(15);                       
  }  
  
  //hiding hand
  for(pos = 180-129; pos<=180; pos+=3)      
  {                                
    fingerServo.write(pos);               
    delay(15);                        
  } 
    
  //hiding door
  for(pos = 155; pos>=90; pos-=15)     
  {    
    displayTemp();                              
    doorServo.write(pos);              
    delay(15);                      
  }    
  
}   


//open door,move finger very slowly forward and back to hiding very slowly, then quickly close door
void slow()
{

  //Moving door
  for(pos = 90; pos < 155; pos += 1)   
  {      
    displayTemp();                               
    doorServo.write(pos);              
    delay(30);                       
  }
  
  //Moving hand
  for(pos = 180; pos > 180-129; pos -= 1)  
  {                                   
    fingerServo.write(pos);               
    delay(30);                       
  }  
  
  //hiding hand
  for(pos = 180-129; pos<=180; pos+=1)      
  {                                
    fingerServo.write(pos);               
    delay(30);                        
  } 
    
  //hiding door
  for(pos = 155; pos>=125; pos-=1)     
  {      
    displayTemp();                            
    doorServo.write(pos);              
    delay(30);                      
  }
  delay(100);
  for(pos = 125; pos>=90; pos-=4)     
  {   
    displayTemp();                               
    doorServo.write(pos);              
    delay(15);                      
  }     
  

}

//serious

void serious() {

  //Moving door
  for(pos = 90; pos < 155; pos += 3)   
  {      
    displayTemp();                               
    doorServo.write(pos);              
    delay(15);                       
  }
    
  //Moving hand
  for(pos = 180; pos > 180-70; pos -= 1)  
  {                                   
    fingerServo.write(pos);               
    delay(15);                       
  }
  delay(800);
  
  
  //hiding door
  for(pos = 155; pos>=130; pos-=3)     
  {   
    displayTemp();                               
    doorServo.write(pos);              
    delay(15); 
  }
  
  //hiding door
  for(pos = 130; pos < 155; pos+=3)     
  {    
    displayTemp();                              
    doorServo.write(pos);              
    delay(15); 
  } 
    //hiding door
  for(pos = 155; pos>=130; pos-=3)     
  {                                
    displayTemp();  
    doorServo.write(pos);              
    delay(15); 
  }   
  //hiding door
  for(pos = 130; pos < 155; pos+=3)     
  {    
    displayTemp();                              
    doorServo.write(pos);              
    delay(15); 
  } 
    
  fingerServo.write(180-40);
  delay(1000);
    
  //Moving hand
  for(pos = 180-40; pos > 180-129; pos -= 4)  
  {                                   
    fingerServo.write(pos);               
    delay(15);                       
  } 
  
  //hiding hand
  for(pos = 180-129; pos<=180; pos+=4)      
  {                                
    fingerServo.write(pos);               
    delay(15);                        
  } 
  
  //Hiding door
  for(pos = 120; pos>=90; pos -= 1)   
  {     
    displayTemp();                                
    doorServo.write(pos);              
    delay(15);                       
  }
  
  
    
} 

void trollClose(){
//Moving door
  for(pos = 90; pos < 155; pos += 3)   
  {       
    displayTemp();                              
    doorServo.write(pos);              
    delay(15);                       
  }
  
  //Moving hand
  for(pos = 180; pos > 180-127; pos -= 4)  
  {                                   
    fingerServo.write(pos);               
    delay(15);                       
  }
  //hiding door
  for(pos = 155; pos>=130; pos-=3)     
  {  
    displayTemp();                                
    doorServo.write(pos);              
    delay(15);                      
  }   
  delay(2000);
  
  for(pos = 130; pos < 155; pos += 3)   
  {         
    displayTemp();                            
    doorServo.write(pos);              
    delay(15);                       
  }
  
  for(pos = 155; pos>=140; pos-=3)     
  {     
    displayTemp();                             
    doorServo.write(pos);              
    delay(15);
  }
  for(pos = 140; pos < 155; pos += 3)   
  {                
    displayTemp();                     
    doorServo.write(pos);              
    delay(15);                       
  }
  delay(500);
  //hiding hand
  for(pos = 180-127; pos<=180; pos+=4)      
  {                                
    fingerServo.write(pos);               
    delay(15);                        
  } 
    
  //hiding door
  for(pos = 155; pos>=90; pos-=3)     
  {       
    displayTemp();                           
    doorServo.write(pos);              
    delay(15);                      
  } 

}
  
void matrix()
{

//Moving door
  for(pos = 90; pos < 155; pos += 3)   
  {  
    displayTemp();                                   
    doorServo.write(pos);              
    delay(15);                       
  }
  
  //Moving hand
  for(pos = 180; pos > 180-80; pos -= 4)  
  {                                   
    fingerServo.write(pos);               
    delay(15);                       
  }
  
  for(pos = 180-80; pos > 180-129; pos -= 1)  
  {                                   
    fingerServo.write(pos);               
    delay(30);                       
  }  
  delay(300);
  
  for(pos = 180-129; pos<=180; pos+=4)      
  {                                
    fingerServo.write(pos);               
    delay(10);                        
  } 
    
  //hiding door
  for(pos = 155; pos>=90; pos-=3)     
  {   
    displayTemp();                               
    doorServo.write(pos);              
    delay(15);                      
  } 

}

void sneak() 
{    
  //Moving door
  for(pos = 90; pos < 130; pos += 1)   
  {    
    displayTemp();                                 
    doorServo.write(pos);              
    delay(30);                       
  }
  delay(2000);
  
  //Moving hand
  for(pos = 180; pos > 180-40; pos -= 1)  
  {                                   
    fingerServo.write(pos);               
    delay(30);                       
  }  
      
  delay(500);
  //Moving door
  for(pos = 130; pos < 155; pos += 4)   
  {              
    displayTemp();                     
    doorServo.write(pos);              
    delay(15);                       
  }
  delay(100);
  
  for(pos = 180-40; pos > 180-90; pos -= 4)  
  {                                   
    fingerServo.write(pos);               
    delay(15);                       
  }  
  delay(500);
  //hiding hand
  for(pos = 180-90; pos<=180-70; pos+=4)      
  {                                
    fingerServo.write(pos);               
    delay(15);                        
  }
  delay(100);
  for(pos = 180-70; pos > 180-90; pos -= 4)  
  {                                   
    fingerServo.write(pos);               
    delay(15);                       
  }
  delay(100);
  for(pos = 180-90; pos<=180-70; pos+=4)      
  {                                
    fingerServo.write(pos);               
    delay(15);                        
  }
  delay(100);
      
  for(pos = 180-70; pos > 180-129; pos -= 4)  
  {                                   
    fingerServo.write(pos);               
    delay(15);                       
  }
  
  for(pos = 180-129; pos<=180; pos+=4)      
  {                                
    fingerServo.write(pos);               
    delay(15);                        
  }    
  //hiding door
  for(pos = 155; pos>=90; pos-=3)     
  {     
    displayTemp();                             
    doorServo.write(pos);              
    delay(15);                      
  } 
} 
   
void displayTemp(){
  float t = dht.readTemperature();
  float h = dht.readHumidity();
  if (doorServo.read() > 120){
    lcd.clear();
    lcd.print(t);
    lcd.print(" Celsius");
    lcd.setCursor(0, 2);
    lcd.print(h);
    lcd.print("% Humid");
    lcd.display();
  }
}

float getDistance(){
  digitalWrite(trigPin, LOW);
  delay(2);
  digitalWrite(trigPin, HIGH);
  delay(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;
  return distance;
  
}

void simpleDoorOpen(){
  //Moving door
  for(pos = 90; pos < 130; pos += 3)   
  {                                   
    doorServo.write(pos);  
    displayTemp();
    delay(15);   
  }
  
  //hiding door
  for(pos = 130; pos>=90; pos-=3)     
  {                                
    doorServo.write(pos);     
    displayTemp();         
    delay(15);                      
  } 
}

void slowDoorOpen(){
  //Moving door
  for(pos = 90; pos <130; pos += 1)
  {
    doorServo.write(pos);
    displayTemp();
    delay(40);
  }

  //Hiding door
  for(pos = 130; pos>=90; pos-=1)
  {
    doorServo.write(pos);
    displayTemp();
    delay(40);
  }
}

void superFastOpen(){
  //Moving door 
  for(pos = 90; pos <130; pos +=8)
  {
    doorServo.write(pos);
    displayTemp();
  }
  //Hiding door
  for(pos = 130; pos>=90; pos-=8)
  {
    doorServo.write(pos);
    displayTemp();
  }
}
