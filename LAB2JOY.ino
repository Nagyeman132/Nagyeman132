//Nathan AYeman and Brandon K.
//


#include <basicMPU6050.h>
basicMPU6050 <> mpu;

bool centerX = false;
bool centerY = false;
bool JoyU = false;
bool JoyD = false;
bool JoyR = false;
bool JoyL  = false;

int xPJ = 0;
int YPJ = 1;
int position = 0;
String beep = "";

unsigned long prevTime  = 0;
unsigned long currentTime;

int PB= 3;

void setup() {
  // put your setup code here, to run once:
  mpu.setup();              // MPU library intiialization 
  mpu.setBias();           
  Serial.begin(9600);
 
  pinMode(PB, OUTPUT);      //
}

void loop() {
  // put your main code here, to run repeatedly:
//
  if(Serial.available() > 0){
    beep = Serial.readString();
  }
 
  currentTime = millis();
 
  if (beep == "E"){             //buzzer loop
    prevTime = currentTime +  2000;     
  }
 
 
  if((currentTime  < prevTime)){
    for(int i = 0;  i<10; i++){
    if((i%2)==0){
    digitalWrite(PB, HIGH);
//    Serial.println(currentTime  - prevTime);
    } 
    else{
      delay(5);
      digitalWrite(PB, LOW);
    }
   }
    beep  = "boop";
  }
  else {
    digitalWrite(PB, LOW);
  }
 
  double X = mpu.gx();   //x-axis 
  double Y = mpu.gy();   //y-axis 
  double Z = mpu.gz();   //z-axis 
 
  if((X >= -.1) & (X<=.1)){   //if X axis is centered, reset 
    centerX = true;
    position = 0;
  }
  if((Y >= -.1) & (Y<=.1)){ //if Y axis is centered, reset  
    centerY = true;
    position = 0;
  }
  
   if( ((analogRead(xPJ)) > 950) & !(JoyR)){  // Going Right on the Joystick 
    JoyR = true;
    JoyL = false;
    JoyU = false;
    JoyD = false;
    Serial.println("Right");
  }
  
  else if( (analogRead(xPJ)) < 50 & !(JoyL)){  //Going Left on the Joystick
    JoyL = true;
    JoyR = false;
    JoyU = false;
    JoyD = false;
    Serial.println("Left");
  }
  
  else if( (analogRead(YPJ)) > 950 &  !(JoyU)){ //Going up the Joystick
    JoyU = true;
    JoyD = false;
    JoyL = false;
    JoyR = false;
    Serial.println("Up");
  }
  
  else if( (analogRead(YPJ)) < 50 & !(JoyD)){   //Going down on the Joystick
    JoyD = true;
    JoyU = false;
    Serial.println("Down");
  }
 
  if(((X  < -1.5)  & centerX)|((position == 1)&(X  < -.5))){ //right for gryo 
    centerX = false;
    Serial.println("Down");
    position = 1;
  }

  if(((X  > 1.5)  & centerX)|((position == 2)&(X  > .5))){ //Up for Gyro 
    centerX = false;
    Serial.println("Up");
    position = 2;
  }

  if(((Y  < -1.5)  & centerY)|((position == 3)&(Y  < -.5))){  //Left for gryo 
    centerY = false;
    Serial.println("Left");
    position  = 3;
  }

  if(((Y  > 1.5)  & centerY)|((position == 4)&(Y  > .5))){ // Right on the gryo
    centerY = false;
    Serial.println("Right");
    position = 4;
  }  

//  Serial.println(String(analogRead(xPJ)) + " " + String(analogRead(YPJ)));
  delay(100); //delay for program
}
