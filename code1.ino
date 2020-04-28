//YWROBOT

//Compatible with the Arduino IDE 1.0

//Library version:1.1

#include <Wire.h> 

#include <LiquidCrystal_I2C.h>

#include "RunningAverage.h"


RunningAverage myRA(10);
LiquidCrystal_I2C lcd(0x3F,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display
const int Potentiometer_pin = A1;

// Variables will change:

int vol = 0;   // counter for the number of button presses
int lastVol = -1;
int samples = 0;

byte LT[8] = 

{



  B00111,

  B01111,

  B11111,

  B11111,

  B11111,

  B11111,

  B11111,

  B11111

};

byte UB[8] =

{

  B11111,

  B11111,

  B11111,

  B00000,

  B00000,

  B00000,

  B00000,

  B00000

};

byte RT[8] =

{



  B11100,

  B11110,

  B11111,

  B11111,

  B11111,

  B11111,

  B11111,

  B11111

};

byte LL[8] =

{



  B11111,

  B11111,

  B11111,

  B11111,

  B11111,

  B11111,

  B01111,

  B00111

};

byte LB[8] =

{

  B00000,

  B00000,

  B00000,

  B00000,

  B00000,

  B11111,

  B11111,

  B11111

};

byte LR[8] =

{



  B11111,

  B11111,

  B11111,

  B11111,

  B11111,

  B11111,

  B11110,

  B11100

};

byte MB[8] =

{

  B11111,

  B11111,

  B11111,

  B00000,

  B00000,

  B00000,

  B11111,

  B11111

};

byte block[8] =

{

  B11111,

  B11111,

  B11111,

  B11111,

  B11111,

  B11111,

  B11111,

  B11111

};



void setup()

{

  

  Serial.begin(9600);

  lcd.init();                      // initialize the lcd 



  lcd.createChar(0,LT);

  lcd.createChar(1,UB);

  lcd.createChar(2,RT);

  lcd.createChar(3,LL);

  lcd.createChar(4,LB);

  lcd.createChar(5,LR);

  lcd.createChar(6,MB);

  lcd.createChar(7,block);

  

  // Print a message to the LCD.

  lcd.backlight();

   

  lcd.clear();



  displayNumber();

   

}



void printNumber(int val){

  

     int col=5;     

     

     if( val >= 10){

       printDigits(val/10,col);     

       printDigits(val%10,col+4);

     }

     else{

       printDigits(val,col);

     }

}



void loop()

{

   vol = analogRead(Potentiometer_pin);            // reads the value of the potentiometer (value between 0 and 1023)

   vol = map(vol, 0, 1023, 0, 30); 



    myRA.addValue(vol );

    samples++; 

      



   if (samples == 300)

  {

    vol = myRA.getAverage();

    if( lastVol != vol ){      

      Serial.println( vol );

       lastVol = vol;

       displayNumber();

       delay(300);

    }

    samples = 0;

    myRA.clear();

    

  }



  



  

}

void displayNumber(){

    

    lcd.clear();

    lcd.setCursor(0,0);

    lcd.print("Vol:"); 

    printNumber( vol );

    

}

void custom0(int x){ 



  lcd.setCursor(x,0); 

  lcd.write(0);  

  lcd.write(1);  

  lcd.write(2);

  lcd.setCursor(x, 1); 

  lcd.write(3);  

  lcd.write(4);  

  lcd.write(5);

}



void custom1(int x){

  lcd.setCursor(x,0);

  lcd.write(1);

  lcd.write(2);

  lcd.print(" ");

  lcd.setCursor(x,1);

  lcd.write(4);

  lcd.write(7);

  lcd.write(4);

}



void custom2(int x){

  lcd.setCursor(x,0);

  lcd.write(6);

  lcd.write(6);

  lcd.write(2);

  lcd.setCursor(x, 1);

  lcd.write(3);

  lcd.write(4);

  lcd.write(4);

}



void custom3(int x){

  lcd.setCursor(x,0);

  lcd.write(6);

  lcd.write(6);

  lcd.write(2);

  lcd.setCursor(x, 1);

  lcd.write(4);

  lcd.write(4);

  lcd.write(5); 

}



void custom4(int x){

  lcd.setCursor(x,0);

  lcd.write(3);

  lcd.write(4);

  lcd.write(7);

  lcd.setCursor(x, 1);

  lcd.print(" ");

  lcd.print(" ");

  lcd.write(7);

}



void custom5(int x){

  lcd.setCursor(x,0);

  lcd.write(3);

  lcd.write(6);

  lcd.write(6);

  lcd.setCursor(x, 1);

  lcd.write(4);

  lcd.write(4);

  lcd.write(5);

}



void custom6(int x){

  lcd.setCursor(x,0);

  lcd.write(0);

  lcd.write(6);

  lcd.write(6);

  lcd.setCursor(x, 1);

  lcd.write(3);

  lcd.write(4);

  lcd.write(5);

}



void custom7(int x){

  lcd.setCursor(x,0);

  lcd.write(1);

  lcd.write(1);

  lcd.write(2);

  lcd.setCursor(x, 1);

  lcd.print(" ");

  lcd.print(" ");

  lcd.write(7);

}



void custom8(int x){

  lcd.setCursor(x,0);

  lcd.write(0);

  lcd.write(6);

  lcd.write(2);

  lcd.setCursor(x, 1);

  lcd.write(3);

  lcd.write(4);

  lcd.write(5);

}



void custom9(int x){

  

  lcd.setCursor(x,0);

  lcd.write(0);

  lcd.write(6);

  lcd.write(2);

  lcd.setCursor(x, 1);

  lcd.print(" ");

  lcd.print(" ");

  lcd.write(7);



}

void printDigits(int digits, int x){

  // utility function for digital clock display: prints preceding colon and leading 0



  switch (digits) {

  case 0:  

    custom0(x);

    break;

  case 1:  

    custom1(x);

    break;

  case 2:  

    custom2(x);

    break;

  case 3:  

    custom3(x);

    break;

  case 4:  

    custom4(x);

    break;

  case 5:  

    custom5(x);

    break;

  case 6:  

    custom6(x);

    break;

  case 7:  

    custom7(x);

    break;

  case 8:  

    custom8(x);

    break;

  case 9:  

    custom9(x);

    break;



  }



}



--------------------------------------------------------------------------------------------------------------------------



Arduino Potentiometer Software Filter



RunningAverage.h



#ifndef RunningAverage_h

#define RunningAverage_h

//

//    FILE: RunningAverage.h

//  AUTHOR: Rob dot Tillaart at gmail dot com

// PURPOSE: RunningAverage library for Arduino

//     URL: http://arduino.cc/playground/Main/RunningAverage

// HISTORY: See RunningAverage.cpp

//

// Released to the public domain

//



// backwards compatibility

// clr() clear()

// add(x) addValue(x)

// avg() getAverage()



#define RUNNINGAVERAGE_LIB_VERSION "0.2.04"



#include "Arduino.h"



class RunningAverage

{

public:

    RunningAverage(void);

    RunningAverage(int);

    ~RunningAverage();



    void clear();

    void addValue(float);

    void fillValue(float, int);



    float getAverage();



    float getElement(uint8_t idx);

    uint8_t getSize() { return _size; }

    uint8_t getCount() { return _cnt; }



protected:

    uint8_t _size;

    uint8_t _cnt;

    uint8_t _idx;

    float   _sum;

    float * _ar;

};



#endif

// END OF FILE



--------------------------------------------------------------------------------------------------------------------------

RunningAverage.cpp



#include "RunningAverage.h"

#include <stdlib.h>



RunningAverage::RunningAverage(int n)

{

    _size = n;

    _ar = (float*) malloc(_size * sizeof(float));

    if (_ar == NULL) _size = 0;

    clear();

}



RunningAverage::~RunningAverage()

{

    if (_ar != NULL) free(_ar);

}



// resets all counters

void RunningAverage::clear()

{

    _cnt = 0;

    _idx = 0;

    _sum = 0.0;

    for (int i = 0; i< _size; i++) _ar[i] = 0.0;  // needed to keep addValue simple

}



// adds a new value to the data-set

void RunningAverage::addValue(float f)

{

    if (_ar == NULL) return;

    _sum -= _ar[_idx];

    _ar[_idx] = f;

    _sum += _ar[_idx];

    _idx++;

    if (_idx == _size) _idx = 0;  // faster than %

    if (_cnt < _size) _cnt++;

}



// returns the average of the data-set added sofar

float RunningAverage::getAverage()

{

    if (_cnt == 0) return NAN;

    return _sum / _cnt;

}



// returns the value of an element if exist, 0 otherwise

float RunningAverage::getElement(uint8_t idx)

{

    if (idx >=_cnt ) return NAN;

    return _ar[idx];

}



// fill the average with a value

// the param number determines how often value is added (weight)

// number should preferably be between 1 and size

void RunningAverage::fillValue(float value, int number)

{

    clear();

    for (int i = 0; i < number; i++)

    {

        addValue(value);

    }

}
