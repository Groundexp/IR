#include <Servo.h>
#include <Wire.h>
#include <Adafruit_MLX90614.h>

#define LR 9 
#define UD 10
#define UDCENTRE 51
#define LRCENTRE 70

Servo lrservo, udservo;
short pos, vos, with, height,stepd, maxlr, minlr, maxud, minud;
 
Adafruit_MLX90614 mlx = Adafruit_MLX90614();

void setup() {
  udservo.attach(LR); 
  lrservo.attach(UD);
  Serial.begin(9600); 
  udservo.write(UDCENTRE); // середина, которую сами уж посчитаете
  lrservo.write(LRCENTRE); // середина, которую сами уж посчитаете
  mlx.begin();  
}

void loop(){
 if (Serial.available() > 0) {
  with   = Serial.parseInt();
  height = Serial.parseInt();
  stepd  = Serial.parseInt();
  maxlr = LRCENTRE+(with*stepd/2); // левая граница
  minlr = maxlr-with*stepd; // правая граница
  maxud = UDCENTRE+(height*stepd/2); // нижняя граница
  minud = maxud-height*stepd; // верхняя граница 
  servotest(maxlr, minlr, maxud, minud);
  scan();
 }
}


int scan() {
  for(pos = minud+1; pos <= maxud; pos +=stepd){ //вверх-вниз 
     udservo.write(pos);
     lrservo.write(maxlr);
     delay(200); 
     for(vos = maxlr; vos >= minlr+1; vos -= stepd){ //влево-вправо
          lrservo.write(vos);
          delay(200);
          print_temp();
        }
  }
udservo.write(UDCENTRE); // середина, которую сами уж посчитаете
lrservo.write(LRCENTRE); // середина, которую сами уж посчитаете
}
  
void print_temp(){
    float celcius1 = mlx.readObjectTempC()*100;
    delay(10);
    float celcius2 = mlx.readObjectTempC()*100;
    float celcius = (celcius1 + celcius2)/2.0;
    Serial.println((round(celcius))); 
}

void servotest(int maxlr,int minlr,int maxud,int minud){
    udservo.write(UDCENTRE); //середина, которую сами уж посчитаете
    delay(800);
    lrservo.write(LRCENTRE); //середина, которую сами уж посчитаете
    delay(800);
    lrservo.write(maxlr);
    delay(800);
    udservo.write(minud);
    delay(800);
    lrservo.write(minlr);
    delay(800);
    udservo.write(maxud);
    delay(800);
    lrservo.write(maxlr);
    delay(800);
    udservo.write(UDCENTRE); //середина, которую сами уж посчитаете
    delay(800);
    lrservo.write(LRCENTRE); //середина, которую сами уж посчитаете
    delay(800);
}

