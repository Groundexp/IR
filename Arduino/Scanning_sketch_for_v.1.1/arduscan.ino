#include <i2cmaster.h>
#include <Servo.h> 
//#define HER delay(100)
Servo lrservo, udservo;
short pos, vos;
int with;
int height;
int stepd;
void setup() {
  udservo.attach(9); 
  lrservo.attach(10);
  Serial.begin(9600); 
  i2c_init(); //Initialise the i2c bus
  PORTC = (1 << PORTC4) | (1 << PORTC5);//enable pullups
  servotest();
	
}

void loop() {
  if (Serial.available() > 0) {
    with = Serial.parseInt();
    height = Serial.parseInt();
    stepd =  Serial.parseInt();
     short maxlr = 30+with*stepd, // левая граница
            minlr = 30, // правая граница
            maxud = 11+height*stepd, // нижняя граница
            minud = 11; // верхняя граница 
            
  for(pos = minud+1; pos <= maxud; pos +=stepd){ //вверх-вниз 
       
        udservo.write(pos);
        lrservo.write(maxlr);
        delay(900); 
        
        for(vos = maxlr; vos >= minlr+1; vos -= stepd){ //влево-вправо
          
             lrservo.write(vos);
             delay(200);
             print_temp();
       }
 
    }
    
  udservo.write(51); // середина, которую сами уж посчитаете
  lrservo.write(70); // середина, которую сами уж посчитаете

  while(1); //спокойной ночи:з
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

void servotest(){
    udservo.write(51); //середина, которую сами уж посчитаете
    delay(1000);
    lrservo.write(70); //середина, которую сами уж посчитаете
    delay(2000);
//    lrservo.write(maxlr);
//    delay(1000);
//    udservo.write(minud);
//    delay(1000);
//    lrservo.write(minlr);
//    delay(1000);
//    udservo.write(maxud);
//    delay(1000);
//    lrservo.write(maxlr);
//    delay(1000);
//    udservo.write(51); //середина, которую сами уж посчитаете
//    delay(1000);
//    lrservo.write(70); //середина, которую сами уж посчитаете
//    delay(1000);
}
    
 

