
//including libraries
#include <Servo.h>
#include "Legs.h"


//makes the objects for servos
Servo Coxa1; 
Servo Femur1;
Servo Tibia1;
Servo Coxa2; 
Servo Femur2; //alt
Servo Tibia2; //alt
Servo Coxa3; 
Servo Femur3;
Servo Tibia3;
Servo Coxa4; 
Servo Femur4; //alt
Servo Tibia4; //alt

//starting angles
/*
int startingposCoxa = 90;
int startingposTibia = 110;
int startingposFemur = 70;
*/
int startingposCoxa = 90;
int startingposTibia = 110;
int startingposFemur = 70;

int startingposCoxaalt = 180-startingposCoxa;
int startingposTibiaalt = 180-startingposTibia;
int startingposFemuralt = 180-startingposFemur;


//Making an object for each leg
//(Servo Tibia, Servo Coxa, Servo Femur, float tibia, float coxa, float femur, float zoffset, float deflength)
OddLeg FrontLeft = OddLeg(Coxa1, Femur1, Tibia1, 5.468, 6.557, 7.681, 8.2, 8.2);
EvenLeg FrontRight = EvenLeg(Coxa2, Femur2, Tibia2, 5.468, 6.557, 7.681, 8, 8.2);
OddLeg BackRight = OddLeg(Coxa3, Femur3, Tibia3, 5.468, 6.557, 7.681, 8, 8.2);
EvenLeg BackLeft = EvenLeg(Coxa4, Femur4, Tibia4, 5.468, 6.557, 7.681, 8, 8.2);


void setup(){
  //only needed for troubleshooting, starting a serial connection
  //between the board and the computer
  Serial.begin(9600);
     
  //Assings servo objects to pins
  Coxa1.attach(2);
  Femur1.attach(3);
  Tibia1.attach(4);
  Coxa2.attach(7);
  Femur2.attach(6);
  Tibia2.attach(5);  
  Coxa3.attach(10);
  Femur3.attach(8);
  Tibia3.attach(9);  
  Coxa4.attach(13);
  Femur4.attach(12);
  Tibia4.attach(11);
  
  //Sets the servos to starting positions
  Coxa1.write(startingposCoxaalt);
  Femur1.write(startingposFemur);
  Tibia1.write(startingposTibia);
  Coxa2.write(startingposCoxa);
  Femur2.write(startingposFemuralt);
  Tibia2.write(startingposTibiaalt);
  Coxa3.write(startingposCoxaalt);
  Femur3.write(startingposFemur);
  Tibia3.write(startingposTibia);
  Coxa4.write(startingposCoxa);
  Femur4.write(startingposFemuralt);
  Tibia4.write(startingposTibiaalt);

}

//function that makes the stable tripod for gait
//and causes them to drift backwards
//exception is which leg is not in the tripod
//stride is how far they drift back (use 10 for now)
void drift(int exception, int stride){
 
  //the original stride, the variable is changed by the loop
  int ostride = stride;
  
  //the number you enter is the leg that moves forward
  switch (exception){
    case 1:{
       //ostride-stride causes the leg to go in the opposite direction.
       //Some even legs need to be inverted because of how they were built mechanically
       for (;stride > 0; stride -= 0.5){
         FrontLeft.swing(stride); //taking a step
         FrontRight.drag(ostride-stride);
         BackRight.drag(stride);
         BackLeft.drag(stride);
       }
       //plant causes the leg to go to a low z-level (hopefully makes it touch the ground)
       FrontLeft.plant();
           
    break;    
    }  
    case 2:{
      
       //calls the drag function with a different stride distance everytime in a for loop
       //drag function calculates the angles of the three motors on each leg depending on a stride length
       //swing does the same thing but in the other direction
       //look in Legs.cpp foir more info
       for (;stride > 0; stride -= 0.5){
         FrontLeft.drag(ostride-stride);
         FrontRight.swing(stride); //taking a step
         BackRight.drag(stride);
         BackLeft.drag(stride);
        }
     FrontRight.plant();   
    
    break; 
    } 
    case 3:{
       for (;stride > 0; stride -= 0.5){
         FrontLeft.drag(ostride-stride);
         FrontRight.drag(ostride-stride);
         BackRight.swing(ostride-stride); //taking a step
         BackLeft.drag(stride);
        } 
     BackRight.plant();   
    
    break; 
    } 
    case 4:{
        for (;stride > 0; stride -= 0.5){
         FrontLeft.drag(ostride-stride);
         FrontRight.drag(ostride-stride);
         BackRight.drag(stride);
         BackLeft.swing(ostride-stride); //taking a step
        }
     BackLeft.plant();
       
    
    break;
    }  
  }
}

//puts all the motors in their starting positions
void reset(){
 FrontLeft.reset(); 
 FrontRight.reset(); 
 BackLeft.reset(); 
 BackRight.reset(); 
 delay(500); 
}

void loop(){
  
  drift(1, 10);
  delay(1000);
  reset();
  drift(2, 10);
  delay(1000);
  reset();
  drift(3, 10);
  delay(1000);  
  reset();
  drift(4, 10);
  delay(1000);  
  reset();
  delay(10000);

}
