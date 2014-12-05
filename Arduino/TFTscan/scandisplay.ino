#include <Adafruit_GFX.h> 
#include <SWTFT.h> 
#include <TouchScreen.h>

// AND DEFINES WILL BE HERE 
#define MINPRESSURE 10
#define MAXPRESSURE 1000


#define	BLACK   0x0000
#define	BLUE    0x001F
#define	RED     0xF800
#define	GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF

#define YP A1  // must be an analog pin, use "An" notation!
#define XM A2  // must be an analog pin, use "An" notation!
#define YM 7   // can be a digital pin
#define XP 6   // can be a digital pin

//разрешение дисплея
#define TS_MINX 150 
#define TS_MINY 120
#define TS_MAXX 920
#define TS_MAXY 940


TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);
SWTFT tft;
long T, Tmid, delta,
Tmax=72,
Tmin=19;
short x1,y1,a;

void setup(){
tft.reset();
uint16_t identifier = tft.readID();
tft.begin(identifier);
tft.fillScreen(BLACK);
Tmid = Tmax-Tmin;
delta = Tmid/5;
tft.setRotation(1);
// ЗАГРУЗОЧНЫЙ ЭКРАН
  tft.setCursor(0, 0); 
  tft.setTextColor(RED);  tft.setTextSize(6);
  tft.println("");
  tft.println("  OSIRS");
  tft.setTextColor(GREEN);  tft.setTextSize(2);
  tft.println("");
  tft.println("");
  tft.println("");
  tft.println("");
  tft.println("       v0.1");
  delay(1000);
tft.fillScreen(BLACK);
randomSeed(analogRead(0));
}

void loop(){
  TSPoint p = ts.getPoint(); 
  pinMode(XM, OUTPUT);
  pinMode(YP, OUTPUT);
  p.x = tft.width()-(map(p.x, TS_MINX, TS_MAXX, tft.width(), 0));
  p.y = tft.height()-(map(p.y, TS_MINY, TS_MAXY, tft.height(), 0));
  delay(20);
  // главное меню
      tft.drawRect(1,1,242,239, WHITE); // общий кввадрат
      tft.fillRect(258,170, 50, 50, WHITE); 
      tft.setCursor(265, 20);
      tft.setTextColor(GREEN);  tft.setTextSize(1);
      tft.println("COLOUR");
      tft.drawRect(258, 170, 50, 50, BLUE);
      tft.fillRect(258,100, 50, 50, WHITE);
      tft.setCursor(265, 90);
      tft.setTextColor(GREEN);  tft.setTextSize(1);
      tft.println("B/W"); 
      tft.drawRect(258, 100, 50, 50, BLUE);
      tft.fillRect(258,30, 50, 50, WHITE);
      tft.drawRect(258, 30, 50, 50, BLUE);
      tft.setCursor(265, 160);
      tft.setTextColor(GREEN);  tft.setTextSize(1);
      tft.println("SAVE"); 
 //  ЦВЕТНОЙ  РЕЖИМ
if ((p.x>230)&&(p.y>190)&&(p.y<220) ){
    // фигачим меню
      tft.drawRect(1,1,242,239, WHITE);
      tft.fillRect(2,3,240,236, 0x0005);
      tft.fillRect(258,170, 50, 50, WHITE); 
      tft.drawRect(258, 170, 50, 50, BLUE);
      tft.fillRect(258,100, 50, 50, WHITE); 
      tft.drawRect(258, 100, 50, 50, BLUE);
      tft.fillRect(258,30, 50, 50, RED);
      tft.drawRect(258, 30, 50, 50, BLUE);
   Colour();
   done();
 }
   
 //ЧЕРНО-БЕЛЫЙ режим
if ((p.x<156)&&(p.x>100)&&(p.y>190)&&(p.y<220) ){
      tft.drawRect(1,1,242,239, WHITE);
      tft.fillRect(2,3,240,236, 0x0005);
      tft.fillRect(258,170, 50, 50, WHITE); 
      tft.drawRect(258, 170, 50, 50, BLUE);
      tft.fillRect(258,100, 50, 50, RED); 
      tft.drawRect(258, 100, 50, 50, BLUE);
      tft.fillRect(258,30, 50, 50, WHITE);
      tft.drawRect(258, 30, 50, 50, BLUE);
      Black();
      done();
 } 
// СОХРАНЕНИЕ
if ((p.x<90)&&(p.x>30)&&(p.y>190)&&(p.y<220)){
     tft.drawRect(1,1,242,239, WHITE);
     tft.fillRect(258,170, 50, 50, RED); 
     tft.drawRect(258, 170, 50, 50, BLUE);
     tft.fillRect(258,100, 50, 50, WHITE); 
     tft.drawRect(258, 100, 50, 50, BLUE);
     tft.fillRect(258,30, 50, 50, WHITE);
     tft.drawRect(258, 30, 50, 50, BLUE);
     SAVE();
 }

if ((p.x<10)&&(p.y<10)){
  tft.fillRect(2,3,240,236, 0x0005);
  randome();
  tft.setCursor(20, 60);
  tft.setTextColor(RED);  tft.setTextSize(6);
  tft.println("PRIVET");
  tft.println("  EPTA");
 }
}
//__________________________________________________________
//ФУНКЦИИ
int Colour(){
 for ( y1 = 2; y1<239; y1+=3) { 
   tft.setCursor(280, 230);
   tft.setTextColor(GREEN);  tft.setTextSize(1);
   tft.fillRect(260,230, 50, 50, BLACK);
   tft.print(100*y1/236);
   tft.println("%");
   T = 16;
   for (x1 = 2; x1<240; x1+=3){
     if (T<Tmin) { 
       for (int i=0; i<3; i++){ 
        for( int k=0; k<3;k++){
          tft.drawPixel(x1+k, y1+i, tft.color565(255, 0, 255));
     }}}
     if ((Tmin<=T)&&(T<=Tmin+delta)) { 
        for (int i=0; i<3; i++){ 
         for( int k=0; k<3;k++){
          tft.drawPixel(x1+k, y1+i, tft.color565(((Tmin+delta-T)*255/delta), 0, 255)); //0 - теплее
     }}}
     if ((Tmin+delta<T)&&(T<=Tmin+2*delta)){ 
        for (int i=0; i<3; i++){ 
         for( int k=0; k<3;k++){
          tft.drawPixel(x1+k, y1+i, tft.color565(0, 255-((Tmin+delta+delta-T)*255)/delta, 255));//255-тепло
     }}}
     if (((Tmin+2*delta)<T)&&(T<=Tmin+3*delta)){ 
       for (int i=0; i<3; i++){ 
         for( int k=0; k<3;k++){
           tft.drawPixel(x1+k, y1+i, tft.color565(0, 255, (Tmin+3*delta-T)*255/delta));
     }}}// 0 - теплее
     if ((Tmin+3*delta<T)&&(T<=Tmin+4*delta)){  
       for (int i=0; i<3; i++){ 
        for( int k=0; k<3;k++){
         tft.drawPixel(x1+k, y1+i, tft.color565((255-(Tmin+4*delta-T)*255/delta), 255, 0));
     }}} //255 - теплее
     if ((Tmin+4*delta<T)&&(T<=Tmin+5*delta)){  
      for (int i=0; i<3; i++){ 
       for( int k=0; k<3;k++){
        tft.drawPixel(x1+k, y1+i, tft.color565(255,(Tmin+5*delta-T)*255/delta , 0));
     }}} // 0 -теплее
     if (Tmin+5*delta<T){  
       for (int i=0; i<3; i++){ 
         for( int k=0; k<3;k++){
           tft.drawPixel(x1+k, y1+i, tft.color565(255, 0, 0)); 
     }}}
     T++;
  }  
 }
}

int Black(){
 for ( y1 = 2; y1<239; y1+=3) { 
   //счет процентов
   tft.setCursor(280, 230);
   tft.setTextColor(GREEN);  tft.setTextSize(1);
   tft.fillRect(260,230, 50, 50, BLACK);
   tft.print(100*y1/236);
   tft.println("%");
 //get_T();
   T = 16; // текущая температура ect.
   for (x1 = 2; x1<240; x1+=3){
        if (T<Tmin) { 
          for (int i=0; i<3; i++){ 
            for( int k=0; k<3;k++){
             tft.drawPixel(x1+k, y1+i, tft.color565(0, 0, 0)); }
          }}
        if ((Tmin<=T)&&(T<=Tmax)) { 
           for (int i=0; i<3; i++){ 
             for( int k=0; k<3;k++){
              tft.drawPixel(x1+k, y1+i, tft.color565(255-(Tmax-T)*255/Tmid, 255-(Tmax-T)*255/Tmid, 255-(Tmax-T)*255/Tmid));
          }}}
        if (Tmin+5*delta<T){  
           for (int i=0; i<3; i++){ 
             for( int k=0; k<3;k++){
              tft.drawPixel(x1+k, y1+i, tft.color565(255, 255, 255)); }
           }}
        T++; //закомментить, если раскомментите get_T()
   }  
 } 
}

int randome(){
for ( y1 = 2; y1<239; y1+=1) { 
 tft.setCursor(280, 230);
 tft.setTextColor(GREEN);  tft.setTextSize(1);
 tft.fillRect(260,230, 50, 50, BLACK);
 tft.print(100*y1/236);
 tft.println("%");
 for (x1 = 2; x1<242; x1+=1){
  T = random(19, 72);
  if (T<Tmin)  tft.drawPixel(x1, y1, tft.color565(255, 0, 255)); 
  if ((Tmin<=T)&&(T<=Tmin+delta)) tft.drawPixel(x1, y1, tft.color565(((Tmin+delta-T)*255/delta), 0, 255));
  if ((Tmin+delta<T)&&(T<=Tmin+2*delta)) tft.drawPixel(x1, y1, tft.color565(0, 255-((Tmin+delta+delta-T)*255)/delta, 255));
  if (((Tmin+2*delta)<T)&&(T<=Tmin+3*delta)) tft.drawPixel(x1, y1, tft.color565(0, 255, (Tmin+3*delta-T)*255/delta));
  if ((Tmin+3*delta<T)&&(T<=Tmin+4*delta)) tft.drawPixel(x1, y1, tft.color565((255-(Tmin+4*delta-T)*255/delta), 255, 0));
  if ((Tmin+4*delta<T)&&(T<=Tmin+5*delta)) tft.drawPixel(x1, y1, tft.color565(255,(Tmin+5*delta-T)*255/delta , 0));
  if (Tmin+5*delta<T) tft.drawPixel(x1, y1, tft.color565(255, 0, 0)); 
}}}

int done(){
   tft.setCursor(270, 230);
   tft.setTextColor(GREEN);  tft.setTextSize(1);
   tft.fillRect(260,230, 50, 50, BLACK);
   tft.println("done!");
}

int SAVE(){
   tft.setCursor(270, 230);
   tft.setTextColor(GREEN);  tft.setTextSize(1);
   tft.fillRect(260,230, 50, 50, BLACK);
   tft.println("saved");
   delay(100);
}


