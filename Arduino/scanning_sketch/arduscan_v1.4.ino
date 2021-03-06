#include <i2cmaster.h>
#include <Servo.h> 
//#define HER delay(100)
Servo lrservo, udservo;
short pos, vos;
const int UDCENTRE = 51;
const int LRCENTRE = 70;
int with;
int height;
int stepd;
void setup() {
  udservo.attach(9); 
  lrservo.attach(10);
  Serial.begin(9600); 
  i2c_init(); //Initialise the i2c bus
  PORTC = (1 << PORTC4) | (1 << PORTC5);//enable pullups
  udservo.write(UDCENTRE); // середина, которую сами уж посчитаете
  lrservo.write(LRCENTRE); // середина, которую сами уж посчитаете
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
  
  for(pos = minud+1; pos <= maxud; pos +=stepd)
    { //вверх-вниз 
       
        udservo.write(pos);
        lrservo.write(maxlr);
        delay(900); 
        
        for(vos = maxlr; vos >= minlr+1; vos -= stepd)
        { //влево-вправо
          
             lrservo.write(vos);
             delay(200);
             print_temp();
        }
 
    }
    
  udservo.write(51); // середина, которую сами уж посчитаете
  lrservo.write(70); // середина, которую сами уж посчитаете
  }
  }

void print_temp(){
    long celcius1 = get_temp();
    long celcius2 = get_temp();
    float celcius = (celcius1 + celcius2)/2.0;
    Serial.println(round(celcius)); 
}

int get_temp(){
    int dev = 0x5A<<1;
    int data_low = 0;
    int data_high = 0;
    int pec = 0;
    i2c_start_wait(dev+I2C_WRITE);
    i2c_write(0x07); // read
    i2c_rep_start(dev+I2C_READ);
    data_low = i2c_readAck(); //Read 1 byte and then send ack
    data_high = i2c_readAck(); //Read 1 byte and then send ack
    pec = i2c_readNak();
    i2c_stop();
    double tempFactor = 0.02; // 0.02 degrees per LSB (measurement resolution of the MLX90614)
    double tempData = 0x0000; // zero out the data
    int frac; // data past the decimal point
    // This masks off the error bit of the high byte, then moves it left 8 bits and adds the low byte.
    tempData = (double)(((data_high & 0x007F) << 8) + data_low);
    tempData = (tempData * tempFactor)-0.01;
    float rawtemp = tempData - 273.15;
    long celcius = round(rawtemp*100); 
    return(celcius);
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
    
 

