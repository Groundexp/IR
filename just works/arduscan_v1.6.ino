#include <Servo.h>
#include <Wire.h>
#include <Adafruit_MLX90614.h>
#define UDCENTRE 51
#define LRCENTRE 70
#define LR 9 
#define UD 10
short with, height, stepd, pos, vos;
Servo lrservo, udservo;
Adafruit_MLX90614 mlx = Adafruit_MLX90614();

void setup() {
  udservo.attach(LR); 
  lrservo.attach(UD);
  Serial.begin(9600); 
  udservo.write(UDCENTRE); // середина, которую сами уж посчитаете
  lrservo.write(LRCENTRE); // середина, которую сами уж посчитаете
  mlx.begin();  
}

void loop() {
 if (Serial.available() > 0) {
  with = Serial.parseInt();
  height = Serial.parseInt();
  stepd =  Serial.parseInt();
  short maxlr = LRCENTRE+(with*stepd/2); // левая граница
  short minlr = maxlr-with*stepd; // правая граница
  short maxud = UDCENTRE+(height*stepd/2); // нижняя граница
  short minud = maxud-height*stepd; // верхняя граница 
  servotest(maxlr, minlr, maxud, minud);
  for(pos = minud+1; pos <= maxud; pos +=stepd){  //вверх-вниз 
        udservo.write(pos); 
        lrservo.write(maxlr);
        delay(900); 
        for(vos = maxlr; vos >= minlr+1; vos -= stepd){  //влево-вправо
          lrservo.write(vos);
          delay(200);
          print_temp();
        }
   }
  udservo.write(UDCENTRE); 
  lrservo.write(LRCENTRE); 
 }
}


void print_temp(){ int n;
int t1 = mlx.readObjectTempC()*100; delay(20);
int t2 = mlx.readObjectTempC()*100; delay(20);
int t3 = mlx.readObjectTempC()*100;
int values[] = {t1, t2, t3};
qsort(values, 3, sizeof(int), cmpfunc);
float midt=0;
if ((values[1]-values[0])<=100) {
  if ((values[2]-values[1])<=100) {
    Serial.println(round((values[0]+values[1]+values[2])/3.0)); }
  else { Serial.println(round((values[0]+values[1])/2.0));}
}  
else if ((values[2]-values[1])<=100){ Serial.println(round((values[1]+values[2])/2.0));}
else { Serial.println(values[1]);}
}

int cmpfunc (const void * a, const void * b){ return ( *(int*)a - *(int*)b );}

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
    
 

