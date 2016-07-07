/*
 * This program is made for deocding PWM duty ratio.
 * Copyright (c) 2016 Tiryoh <tiryoh@gmail.com>
 *
 * This software is released under the MIT License.
 * http://opensource.org/licenses/mit-license.php
 */

//define period (ms)
volatile unsigned long period = 20;
//define Max duty ratio (percent)
#define DutyMax 9.0
//define Min. duty ratio (percent)
#define DutyMin 6.0

//pin definition
int rcv1 = 7; //1st ch
int rcv2 = 8; //2nd ch
int outPin1_1 = 5;
int outPin1_2 = 6;
int outPin2_1 = 9;
int outPin2_2 = 10;

//variable definition
volatile unsigned long duration1 = 0, duration2 = 0;
int speedVal1 = 0, speedVal2 = 0, timer = 0;

void setup()
{
  Serial.begin(9600);
  pinMode(rcv1, INPUT);
  pinMode(rcv2, INPUT);
  pinMode(outPin1_1, OUTPUT);
  pinMode(outPin1_2, OUTPUT);
  pinMode(outPin2_1, OUTPUT);
  pinMode(outPin2_2, OUTPUT);
  Serial.println("START");
}

void loop()
{
  duration1 = pulseIn(rcv1, HIGH, period * 3000UL);
  speedVal1 = map(duration1, period * 10 * DutyMin, period * 10 * DutyMax, 255, -255);
  duration2 = pulseIn(rcv2, HIGH, period * 3000UL);
  speedVal2 = map(duration2, period * 10 * DutyMin, period * 10 * DutyMax, 255, -255);
  speedVal1 = constrain(speedVal1, -250, 250);
  speedVal2 = constrain(speedVal2, -250, 250);
  if (duration1 > period * 150 )speedVal1 = 0;
  if (duration2 > period * 150 )speedVal2 = 0;
  //  Serial.print("timer:,");
  //  Serial.print(timer);
  //  Serial.print(",");
  Serial.print("rcv1:");
  Serial.print(speedVal1);
  Serial.print(",rcv2:");
  Serial.println(speedVal2);
  //  if((speedVal1>-20&&speedVal1<20&&(speedVal2<-20||speedVal2>20))||((speedVal1<-20||speedVal1>20)&&speedVal2>-20&&speedVal2<20)){
  //    timer=0;
  //  }
  //  if((speedVal1>40||speedVal2>40||speedVal1<-40||speedVal2<-40)&&timer<=500){
  //    timer++;
  if ((speedVal2 >= 30 ||  speedVal2 <= -30) && (speedVal1 >= 30 ||  speedVal1 <= -30))
  {
    if (speedVal1 < 260 && speedVal1 > 100)
    {
      analogWrite(outPin1_1, 255);
      digitalWrite(outPin1_2, LOW);
    }
    else if (speedVal1 < 260 && speedVal1 > 40)
    {
      analogWrite(outPin1_1, 80);
      digitalWrite(outPin1_2, LOW);
    }
    else if (speedVal1 > -260 && speedVal1 < -100)
    {
      digitalWrite(outPin1_1, LOW);
      analogWrite(outPin1_2, 255);
    }
    else if (speedVal1 > -260 && speedVal1 < -40)
    {
      digitalWrite(outPin1_1, LOW);
      analogWrite(outPin1_2, 80);
    }
    else
    {
      digitalWrite(outPin1_1, LOW);
      digitalWrite(outPin1_2, LOW);
    }
    
    if (speedVal2 < 260 &&  speedVal2 > 100)
    {
      Serial.println("lmax");
      analogWrite(outPin2_1, 255);
      digitalWrite(outPin2_2, LOW);
    }
    else if (speedVal2 < 260 && speedVal2 > 40)
    {
      Serial.println("lmin");
      analogWrite(outPin2_1, 80);
      digitalWrite(outPin2_2, LOW);
    }
    else if (speedVal2 > -260 && speedVal2 < -100)
    {
      digitalWrite(outPin2_1, LOW);
      analogWrite(outPin2_2, 255);
    }
    else if (speedVal2 > -260 && speedVal2 < -40)
    {
      digitalWrite(outPin2_1, LOW);
      analogWrite(outPin2_2, 80);
    }
    else
    {
      digitalWrite(outPin2_1, LOW);
      digitalWrite(outPin2_2, LOW);
    }
  }
  else if (speedVal2 < 30 &&  speedVal2 > -30)
  {
  if (speedVal1 < 260 && speedVal1 > 100)
    {
      analogWrite(outPin1_1, 255);
      digitalWrite(outPin1_2, LOW);
      analogWrite(outPin2_1, 35);
      digitalWrite(outPin2_2, LOW);
    }
    else if (speedVal1 < 260 && speedVal1 > 40)
    {
      analogWrite(outPin1_1, 255);
      digitalWrite(outPin1_2, LOW);
      analogWrite(outPin2_1, 35);
      digitalWrite(outPin2_2, LOW);
    }
    else if (speedVal1 > -260 && speedVal1 < -100)
    {
      digitalWrite(outPin1_1, LOW);
      analogWrite(outPin1_2, 255);
      digitalWrite(outPin2_1, LOW);
      analogWrite(outPin2_2, 35);
    }
    else if (speedVal1 > -260 && speedVal1 < -40)
    {
      digitalWrite(outPin1_1, LOW);
      analogWrite(outPin1_2, 255);
      digitalWrite(outPin2_1, LOW);
      analogWrite(outPin2_2, 35);
    }
    else
    {
      digitalWrite(outPin1_1, LOW);
      digitalWrite(outPin1_2, LOW);
      digitalWrite(outPin2_1, LOW);
      digitalWrite(outPin2_2, LOW);
    }
  }
  else if (speedVal1 < 30 &&  speedVal1 > -30)
  {
  if (speedVal2 < 260 &&  speedVal2 > 100)
    {
      Serial.println("lmax");
      analogWrite(outPin1_1, 35);
      digitalWrite(outPin1_2, LOW);
      analogWrite(outPin2_1, 255);
      digitalWrite(outPin2_2, LOW);
    }
    else if (speedVal2 < 260 && speedVal2 > 40)
    {
      Serial.println("lmin");
      analogWrite(outPin1_1, 35);
      digitalWrite(outPin1_2, LOW);
      analogWrite(outPin2_1, 255);
      digitalWrite(outPin2_2, LOW);
    }
    else if (speedVal2 > -260 && speedVal2 < -100)
    {
      digitalWrite(outPin1_1, LOW);
      analogWrite(outPin1_2, 35);
      digitalWrite(outPin2_1, LOW);
      analogWrite(outPin2_2, 255);
    }
    else if (speedVal2 > -260 && speedVal2 < -40)
    {
      digitalWrite(outPin1_1, LOW);
      analogWrite(outPin1_2, 35);
      digitalWrite(outPin2_1, LOW);
      analogWrite(outPin2_2, 255);
    }
    else
    {
      digitalWrite(outPin1_1, LOW);
      digitalWrite(outPin1_2, LOW);
      digitalWrite(outPin2_1, LOW);
      digitalWrite(outPin2_2, LOW);
    }
  }

  delayMicroseconds(period * 2000);
}
//  }else if(timer>500){
//    digitalWrite(outPin1_1, LOW);
//    digitalWrite(outPin1_2, LOW);
//    digitalWrite(outPin2_1, LOW);
//    digitalWrite(outPin2_2, LOW);
//    delay(1);
//    Serial.println("STOP");
//    timer=0;
//  }else{
//    timer=0;
//    digitalWrite(outPin1_1, LOW);
//    digitalWrite(outPin1_2, LOW);
//    digitalWrite(outPin2_1, LOW);
//    digitalWrite(outPin2_2, LOW);
//  }
//}

