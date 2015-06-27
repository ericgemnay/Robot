
#include <Servo.h>
#include <Arduino.h>
#ifndef Legs_H
#define Legs_H
  
class EvenLeg
{
  public:
    EvenLeg(Servo Tibia, Servo Coxa, Servo Femur, float tibia, float coxa, float femur, float zoffset, float deflength);
    void push();
    void pull();
    void reset();
    void test();
    void plant();
    void swing(float ydis);
    
    float getBigLength(float tempydis);
    float getLength(float tempydis);
    float getTheta1(float stridedis);
    float getTheta2(float tempydis);
    float getTheta3(float tempydis);
    
    void drag(float ydis);
   
  private:
    float _tibia;
    float _coxa;
    float _femur;
    float _zoffset;
    float _deflength;
    float _biglength;
    float _length;
    int _theta1;
    int _theta2;
    int _theta3;
  

    
    float stridedis;
    float ydis;
    float tempydis;
    
 
    Servo _Tibia;
    Servo _Coxa;
    Servo _Femur;
 
    int _stride;
 
};

class OddLeg
{
  public:
    OddLeg(Servo Tibia, Servo Coxa, Servo Femur, float tibia, float coxa, float femur, float zoffset, float deflength);
    void push();
    void pull();
    void reset();
    void test();
    void swing(float ydis);    
    void plant();

    float getBigLength(float tempydis);
    float getLength(float tempydis);
    float getTheta1(float stridedis);
    float getTheta2(float tempydis);
    float getTheta3(float tempydis);
    
    Servo _Tibia;
    Servo _Coxa;
    Servo _Femur;    
    
    void drag(float ydis);
    
  private:
    float _tibia;
    float _coxa;
    float _femur;
    float _zoffset;
    float _deflength;
    float _biglength;
    float _length;
    int _theta1;
    int _theta2;
    int _theta3;
  

    
    float stridedis;
    float ydis;
    float tempydis;
    
 

 
    int _stride;
 
};
#endif

