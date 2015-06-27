#include "Legs.h"

/*

During the physical construction of the robot I mounted the legs in a way that causes some motors to be in a different orientation than others
Because of this there are two types of legs (Odd and Even). The OddLeg and EvenLeg class contain all the same functions however some of the values are inverted
to compensate for the motors

*/

//setting pi as a constant. Trigonometry is required for the inverse kinematics calculations and is returned in radians. The motors can only accept degrees so
//all values are converted to degrees using 180/pi
const float pi = 3.14159265359;
  
//constructor  
EvenLeg::EvenLeg(Servo Coxa, Servo Femur, Servo Tibia, float tibia, float coxa, float femur, float zoffset, float deflength)
{
  //capitalization means the variable is a Servo
  _Tibia = Tibia;
  _Coxa = Coxa;
  _Femur = Femur;
  
  //lowercase means the variable is a measurement of a leg segment
  _tibia = tibia;
  _coxa = coxa;
  _femur = femur;
  
  //height of the coxa from the ground
  _zoffset = zoffset;
  
  //length of the entire leg from topview
  _deflength = deflength;
  
  //"X" see black notebook
  _stride = 10;
  
}

//finds the topview length(L1) of the projected angle
float EvenLeg::getBigLength(float tempydis){
   
 // float _biglength = _deflength/(cos(_theta1));
  float _biglength = sqrt((pow(tempydis,2))+(pow(_deflength,2)));

  return _biglength;
}

//creates the length from coxa/femur joint(L) to tip of tibia
float EvenLeg::getLength(float tempydis){
  
  _biglength = getBigLength(tempydis);
  
  _length = sqrt(( _zoffset*_zoffset)+ ((_biglength - _coxa )*(_biglength - _coxa )));
   
  return _length;
}

//finds coxa roation 
//ydistance is how far you want to move(AKA stride) 
//deflength the topview length of the whole leg(L1)
float EvenLeg::getTheta1(float stridedis){  
  
  _biglength = getBigLength(stridedis);

  _theta1=  asin(stridedis*(sin(45)/_biglength)) *(180/pi);
  
  return _theta1;
}

//finds femur rotation 
//zoffset is how high the coxa turnpoint is from the ground
//length is L
//tibia and femur are the lengths of the tibia and femur leg segments  
float EvenLeg::getTheta2 (float tempydis){
  
  _length = getLength(tempydis);
    
   int part1 = acos(_zoffset/_length)*(180/pi); //see black notebook for diagram
   
   int part2 = acos(((_femur*_femur) + (_length*_length) - (_tibia*_tibia))/(2*(_femur)*(_length)))*(180/pi);
   int _theta2 = (part1 + part2);
   

   return _theta2;
}

//function used to calibrate motors
void EvenLeg::test(){
  
  _Femur.write(0);
  _Tibia.write(0);
    
}

//finds tibia rotation
float EvenLeg::getTheta3 (float tempydis){
  
  _length = getLength(tempydis);
  
  _theta3 = acos((pow(_tibia,2)+pow(_femur,2)-pow(_length,2))/(2*_tibia*_femur))*(180/pi);
  
  return 180-_theta3;
}
 
//brings all motors to start position(calibrated for even/odd leg)  
void EvenLeg::reset(){
  
  _Coxa.write(90);
  _Femur.write(180-60);
  _Tibia.write(180-100);
}

//using all the functions above to solve inverse kinematic angles at a certain length
void EvenLeg::drag(float ydis){
  
  //assigning new angles (calibratged for even/odd legs)
  int newCoxa = getTheta1(ydis);
  int newFemur = 180-getTheta2(ydis);
  int newTibia = getTheta3(ydis);  
  
  //troubleshooting, prints the new angles to serial window
  Serial.println("");
  Serial.println("ydis");
  Serial.println(ydis);
  Serial.println("coxa");
  Serial.println(newCoxa);
  Serial.println("femur");
  Serial.println(newFemur);
  Serial.println("tibia");
  Serial.println(newTibia);
   
  //writes new angles
  _Coxa.write(newCoxa+90);
  _Femur.write(newFemur);
  _Tibia.write(180-newTibia);
  
}

//Will move one leg along a stride length
//because its a for loop while this is going on nothing else can happen
//
void EvenLeg::push(){
  
  //stride length
  float ydis = 10;
  
  for(;ydis > 0; ydis-=0.5){
   drag(ydis);
   delay(1);
  }
   //planting leg in ground
  _Femur.write(110); 
  
}

//same thing as push() but in the opposite direction
void EvenLeg::pull(){
  
  float ydis = 0;
  
  for(;ydis < 10; ydis+=0.5){
   
   drag(ydis);
   delay(1);
  }
  _Femur.write(110);  
}

//will move the Femur motor to ground level
void EvenLeg::plant(){
  _Femur.write(110);
  delay(50);
}

//same thing as drag but the leg will be lifted off the ground because Femur and Tibia are receiving padding
void EvenLeg::swing(float ydis){
  int newCoxa = getTheta1(ydis);
  int newFemur = 180-getTheta2(ydis);
  int newTibia = getTheta3(ydis);  
  
  Serial.println("");
  Serial.println("ydis");
  Serial.println(ydis);
  Serial.println("coxa");
  Serial.println(newCoxa);
  Serial.println("femur");
  Serial.println(newFemur);
  Serial.println("tibia");
  Serial.println(newTibia);
  
  _Coxa.write(newCoxa+90);
  _Femur.write(newFemur+5);
  _Tibia.write(180-newTibia+5);
    
  
}



//comments below are all old

OddLeg::OddLeg(Servo Coxa, Servo Femur, Servo Tibia, float tibia, float coxa, float femur, float zoffset, float deflength)
{
  _Tibia = Tibia;
  _Coxa = Coxa;
  _Femur = Femur;
  
  _tibia = tibia;
  _coxa = coxa;
  _femur = femur;
  _zoffset = zoffset;
  _deflength = deflength;
  
  _stride = 10;
  
}
//finds the topview length(L1) of the projected angle
float OddLeg::getBigLength(float tempydis){
  
  
 // float _biglength = _deflength/(cos(_theta1));
  float _biglength = sqrt((pow(tempydis,2))+(pow(_deflength,2)));

  return _biglength;
}


//creates the length from coxa/femur joint(L) to tip of tibia
float OddLeg::getLength(float tempydis){
  
  _biglength = getBigLength(tempydis);
  
  _length = sqrt(( _zoffset*_zoffset)+ ((_biglength - _coxa )*(_biglength - _coxa )));
   
  return _length;
}

//finds coxa roation ydistance is how far you want to move, deflength the topview length of the whole leg(L1)
float OddLeg::getTheta1(float stridedis){  
  
  _biglength = getBigLength(stridedis);

  _theta1=  asin(stridedis*(sin(45)/_biglength)) *(180/pi);
  
  return _theta1;
}

//finds femur rotation zoffset is how high the coxa turnpoint is from the ground, length is L, ...
//...tibia and femur are the lengths of the tibia and femur   
float OddLeg::getTheta2 (float tempydis){
  
  _length = getLength(tempydis);
    
   int part1 = acos(_zoffset/_length)*(180/pi);
   
   int part2 = acos(((_femur*_femur) + (_length*_length) - (_tibia*_tibia))/(2*(_femur)*(_length)))*(180/pi);
   int _theta2 = (part1 + part2);
   

   return _theta2;
}

void OddLeg::test(){
  
  _Femur.write(0);
  _Tibia.write(0);
    
}

//finds tibia rotation, length is L tibia and femur are lengths of the tibia and femur
float OddLeg::getTheta3 (float tempydis){
  
  _length = getLength(tempydis);
  
   _theta3 = acos((pow(_tibia,2)+pow(_femur,2)-pow(_length,2))/(2*_tibia*_femur))*(180/pi);
  
  return 180-_theta3;
}

  
void OddLeg::reset(){
  
  _Coxa.write(90);
  _Femur.write(60);
  _Tibia.write(100);
}

void OddLeg::drag(float ydis){
  
  float newCoxa = getTheta1(ydis);
  float newFemur = getTheta2(ydis);
  float newTibia = getTheta3(ydis);  
  
  Serial.println("");
  Serial.println("ydis");
  Serial.println(ydis);
  Serial.println("coxa");
  Serial.println(newCoxa);
  Serial.println("femur");
  Serial.println(newFemur);
  Serial.println("tibia");
  Serial.println(newTibia);
  
  _Coxa.write(newCoxa+45);
  _Femur.write(newFemur);
  _Tibia.write(newTibia);
  
}

void OddLeg::push(){
  
  float ydis = 10;
  Serial.println("push");
  for(;ydis > 0; ydis-=0.5){
   Serial.println("push2");
   drag(ydis);
   delay(1);
  _Femur.write(70);
  }
  
  
}

void OddLeg::pull(){
  
  float ydis = 0;
  Serial.println("push");
  for(;ydis < 10; ydis+=0.5){
   Serial.println("push2");
   drag(ydis);
   delay(1);
  _Femur.write(70);
  }
  
  
}

void OddLeg::plant(){
  _Femur.write(70);
  delay(50);
}

void OddLeg::swing(float ydis){
  
  float newCoxa = getTheta1(ydis);
  float newFemur = getTheta2(ydis);
  float newTibia = getTheta3(ydis);  
  
  Serial.println("");
  Serial.println("ydis");
  Serial.println(ydis);
  Serial.println("coxa");
  Serial.println(newCoxa);
  Serial.println("femur");
  Serial.println(newFemur);
  Serial.println("tibia");
  Serial.println(newTibia);
  
  _Coxa.write(newCoxa+45);
  _Femur.write(newFemur);
  _Tibia.write(newTibia);
  
}  
  

