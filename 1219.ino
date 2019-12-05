#define FASTLED_USE_PROGMEM 1
#include <FastLED.h>
#include <RotaryEncoder.h>
#include "Timer.h"
#include "ClickButton.h"


Timer t;

#define LED_PIN     20
#define NUM_LEDS    300
#define BRIGHTNESS  96
#define LED_TYPE    WS2811
#define COLOR_ORDER RGB
#define UPDATES_PER_SECOND 100

CRGBArray<NUM_LEDS> leds;

CRGBSet  l0 (leds(  0 , 31 ));
CRGBSet l1 (leds(  32  , 61  ));
CRGBSet l2 (leds(  62  , 110  ));
CRGBSet l3 (leds(  111  , 147  ));
CRGBSet l4 (leds(  148  , 199  ));
CRGBSet l5 (leds(  200  , 223  ));
CRGBSet l6 (leds(  224  , 247  ));
CRGBSet l7 (leds(  248  , 265  ));
CRGBSet l8 (leds(   266 , 279  ));
CRGBSet l9 (leds(  280  , 286  ));
CRGBSet l10  (leds(  287 , 291 ));
CRGBSet l11  (leds(  292 , 294 ));


// Random starting colors
CRGB cola = CRGB(0,0,0);
CRGB colb = CRGB(0,0,0);
CRGB colc = CRGB(0,0,0);
CRGB cold = CRGB(0,0,0);

CHSV hola = CHSV(0,0,0);
CHSV holb = CHSV(0,0,0);
CHSV holc = CHSV(0,0,0);
CHSV holda = CHSV(0,0,0);

DEFINE_GRADIENT_PALETTE( bee1 ) {
  0,     233,  116,  2,   
64,   228,  230,  226,   
128,   253 , 193,  29,   
192,   202 , 62 , 11, 
255 ,  255, 213, 121
}; 



CRGBPalette16 activePal = bee1;








// Defaults
int trainr = 128;
int traing = 128;
int trainb = 128;
int dr = 0;
int dg = 0;
int db  = 0;







// Chaos Arrays

int rchaos1[302];
int gchaos1[302];
int bchaos1[302];
int rchaos2[302];
int gchaos2[302];
int bchaos2[302];






unsigned long time_now = 0;
unsigned long time_now2 = 0;


// mode control

int mode = 6;

int modecount = 7;

bool modeentry = false;



//              Flags and Toggles

bool cdran = false;

bool hdran = false;

bool trainran = false;

bool pdran = false;

bool rbpmflag = false;
bool gbpmflag = false;
bool bbpmflag = false;




// Click Toggles

bool click5n1 = false;







//        Useful Values

// fraction of blend/etc
int f = 0;

// led being addressed
int i = 0;

// Speed
int period = 1000;

// Brightness
int bright = 128;


// Mins and Maxs

int tintr = 0;
int tintg = 0;
int tintb = 0;
int changer = 0;
int changeg = 0;
int changeb = 0;

bool tintrue = false;
bool tintgue = false;
bool tintbue = false;





// Multipliers

int m1 = 5;
int m2 = 5;
int m3 = 5;
int m4 = 5;
int m5 = 5;
int mB = 10;

// BPMS

int abpm = 10;
int rbpm = 3;
int gbpm = 4;
int bbpm = 5;






// Rotary Encoders
RotaryEncoder encoder1(14, 15);
RotaryEncoder encoder2(10, 9);
RotaryEncoder encoder3(7, 8);
RotaryEncoder encoder4(5, 4);
RotaryEncoder encoder5(1, 2);

static int pos1 = 0;
static int pos2 = 0;
static int pos3 = 0;
static int pos4 = 0;
static int pos5 = 0;


// Clickers
ClickButton button1(16, LOW, CLICKBTN_PULLUP);
ClickButton button2(11, LOW, CLICKBTN_PULLUP);
ClickButton button3(6, LOW, CLICKBTN_PULLUP);
ClickButton button4(3, LOW, CLICKBTN_PULLUP);
ClickButton button5(0, LOW, CLICKBTN_PULLUP);

int clickState1 = 0;
int clickState2 = 0;
int clickState3 = 0;
int clickState4 = 0;
int clickState5 = 0;

int click1;
int click2;
int click3;
int click4;
int click5;




void setup() {

    FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( UncorrectedTemperature );
  FastLED.setBrightness(  BRIGHTNESS );


random16_set_seed(analogRead(A13));

// Fill chaos arrays
for (int i = 0; i < 302; i++) {
  rchaos1[i] = random8();
  gchaos1[i] = random8();
  bchaos1[i] = random8();
  rchaos2[i] = random8();
  gchaos2[i] = random8();
  bchaos2[i] = random8();
}

cola = CRGB(random8(),random8(),random8());
colb = CRGB(random8(),random8(),random8());
colc = CRGB(random8(),random8(),random8());
cold = CRGB(random8(),random8(),random8());

hola = CHSV(random8(),random8(),random8());
holb = CHSV(random8(),random8(),random8());
holc = CHSV(random8(),random8(),random8());
holda = CHSV(random8(),random8(),random8());







t.every(10, showleds, (void*)0);


}

void loop() {
  // put your main code here, to run repeatedly:
  t.update();

  modemaker();




  
  if (mode == 0) colordrops();
  if (mode == 1) holordrops();
  if (mode == 2) randomdancer();
  if (mode == 3) layergradient();
  if (mode == 4) noiseygradient();
  if (mode == 5) train();
  if (mode == 6) palettedrop();

}

// Color Drops  Color Drops  Color Drops  Color Drops  Color Drops  Color Drops  Color Drops
void colordrops(){
trainran = false;
hdran = false;
pdran = false;


  
if (cdran == false) {
  for (int i = 0; i < 300; i++) {
    leds[i] = CRGB(random8(),random8(),random8());
  }
  cdran = true;
}

speeds();

if(millis() > time_now + period){
    time_now = millis();
    i = random16(300);

// Stalls
stalls();


// Color Adds/Subtracts
if (pos2 > 0) changeg = qadd8 (pos2 * m2, random8());
if (pos3 > 0) changeg = qadd8 (pos3 * m3, random8());
if (pos4 > 0) changeb = qadd8 (pos4 * m4, random8());
if (pos2 < 0) changer = qsub8 (abs(pos2 * m2), random8());
if (pos3 < 0) changeg = qsub8 (abs(pos3 * m3), random8());
if (pos4 < 0) changeb = qsub8 (abs(pos4 * m4), random8());
if (pos2 == 0) changer = random8();
if (pos3 == 0) changeg = random8();
if (pos4 == 0) changeb = random8();

    
    cola = CRGB(changer, changeg, changeb);
    }
if (millis() > time_now2 + (period/255)) {
  leds[i] = blend(leds[i], cola, f);
time_now2 = millis();
  f++;
}
if (f == 255) f = 0;

}

// Holordrops Holordrops Holordrops Holordrops Holordrops Holordrops Holordrops Holordrops 
void holordrops(){
trainran = false;
cdran = false;
pdran = false;


  
if (hdran == false) {
  for (int i = 0; i < 300; i++) {
    leds[i] = CHSV(random8(),random8(),random8());
  }
  hdran = true;
}
speeds();

if(millis() > time_now + period){
    time_now = millis();
    i = random16(300);

// Stalls
void stalls();


// Color Adds/Subtracts
if (pos2 > 0) changeg = qadd8 (pos2 * m2, random8());
if (pos3 > 0) changeg = qadd8 (pos3 * m3, random8());
if (pos4 > 0) changeb = qadd8 (pos4 * m4, random8());
if (pos2 < 0) changer = qsub8 (abs(pos2 * m2), random8());
if (pos3 < 0) changeg = qsub8 (abs(pos3 * m3), random8());
if (pos4 < 0) changeb = qsub8 (abs(pos4 * m4), random8());
if (pos2 == 0) changer = random8();
if (pos3 == 0) changeg = random8();
if (pos4 == 0) changeb = random8();

    
    hola = CHSV(changer, changeg, changeb);
    }
if (millis() > time_now2 + (period/255)) {
  leds[i] = blend(leds[i], hola, f);
time_now2 = millis();
  f++;
}
if (f == 255) f = 0;

}



// Layer Gradient Layer Gradient Layer Gradient Layer Gradient Layer Gradient Layer Gradient Layer Gradient 
void layergradient() {
  trainran = false;
hdran = false;
cdran = false;
pdran = false;

speeds();
// Check time, increment fade
if(millis() > time_now + period){
    time_now = millis();
    f++;
}



 l0 = blend(blend(cola, colc, f), blend(colb, cold, f), 0);
 l1 = blend(blend(cola, colc, f), blend(colb, cold, f), 15);
 l2 = blend(blend(cola, colc, f), blend(colb, cold, f), 31);
 l3 = blend(blend(cola, colc, f), blend(colb, cold, f), 47);
 l4 = blend(blend(cola, colc, f), blend(colb, cold, f), 63);
 l5 = blend(blend(cola, colc, f), blend(colb, cold, f), 79);
 l6 = blend(blend(cola, colc, f), blend(colb, cold, f), 95);
 l7 = blend(blend(cola, colc, f), blend(colb, cold, f), 111);
 l8 = blend(blend(cola, colc, f), blend(colb, cold, f), 127);
 l9 = blend(blend(cola, colc, f), blend(colb, cold, f), 143);
 l10 = blend(blend(cola, colc, f), blend(colb, cold, f), 159);
 l11 = blend(blend(cola, colc, f), blend(colb, cold, f), 175);
leds[295] = blend(blend(cola, colc, f), blend(colb, cold, f), 191);
leds[296] = blend(blend(cola, colc, f), blend(colb, cold, f), 207);
leds[297] = blend(blend(cola, colc, f), blend(colb, cold, f), 223); 
leds[298] = blend(blend(cola, colc, f), blend(colb, cold, f), 239);
leds[299] = blend(blend(cola, colc, f), blend(colb, cold, f), 255);



 
 t.update(); 

 // Swap target color
if (f == 255) { 
  f = 0;
cola = colc;
colb = cold;
colc = CRGB(random8(),random8(),random8());
cold = CRGB(random8(),random8(),random8());
}

}

// Noisey Gradient  Noisey Gradient  Noisey Gradient  Noisey Gradient  Noisey Gradient  Noisey Gradient  
void noiseygradient() {

trainran = false;
hdran = false;
cdran = false;

speeds();
// Check time, increment fade
if(millis() > time_now + period){
    time_now = millis();
    f++;
}



 l0 = blend(blend(cola, colc, f), blend(colb, cold, f), 0);
 l1 = blend(blend(cola, colc, f), blend(colb, cold, f), 15);
 l2 = blend(blend(cola, colc, f), blend(colb, cold, f), 31);
 l3 = blend(blend(cola, colc, f), blend(colb, cold, f), 47);
 l4 = blend(blend(cola, colc, f), blend(colb, cold, f), 63);
 l5 = blend(blend(cola, colc, f), blend(colb, cold, f), 79);
 l6 = blend(blend(cola, colc, f), blend(colb, cold, f), 95);
 l7 = blend(blend(cola, colc, f), blend(colb, cold, f), 111);
 l8 = blend(blend(cola, colc, f), blend(colb, cold, f), 127);
 l9 = blend(blend(cola, colc, f), blend(colb, cold, f), 143);
 l10 = blend(blend(cola, colc, f), blend(colb, cold, f), 159);
 l11 = blend(blend(cola, colc, f), blend(colb, cold, f), 175);
leds[295] = blend(blend(cola, colc, f), blend(colb, cold, f), 191);
leds[296] = blend(blend(cola, colc, f), blend(colb, cold, f), 207);
leds[297] = blend(blend(cola, colc, f), blend(colb, cold, f), 223); 
leds[298] = blend(blend(cola, colc, f), blend(colb, cold, f), 239);
leds[299] = blend(blend(cola, colc, f), blend(colb, cold, f), 255);

for (int i = 0; i < 300; i++) {
  leds[i] = blend(leds[i], 
  blend(CRGB(rchaos1[i], gchaos1[i], bchaos1[i]), CRGB(rchaos2[i], gchaos2[i], bchaos2[i]), f),
  64);
}
 
 t.update(); 

 // Swap target color
if (f == 255) { 
  f = 0;
cola = colc;
colb = cold;
colc = CRGB(random8(),random8(),random8());
cold = CRGB(random8(),random8(),random8());
for (int i = 0; i < 300; i++) {
  t.update();
  rchaos1[i] = rchaos2[i];
  rchaos2[i] = random8();
  gchaos1[i] = gchaos2[i];
  gchaos2[i] = random8();
  bchaos1[i] = bchaos2[i];
  bchaos2[i] = random8();
}


}

}

// Random Dancer  Random Dancer  Random Dancer  Random Dancer  Random Dancer  Random Dancer  Random Dancer  


void randomdancer() {

trainran = false;
hdran = false;
cdran = false;

speeds();



if(millis() > time_now + period){
    time_now = millis();
    f++;
}


for (int i = 0; i < 300; i++) {
  leds[i] = blend(CRGB(rchaos1[i], gchaos1[i], bchaos1[i]), CRGB(rchaos2[i], gchaos2[i], bchaos2[i]), f);
}

if (f == 255) { 
  f = 0;
for (int i = 0; i < 300; i++) {
  t.update();
  rchaos1[i] = rchaos2[i];
  rchaos2[i] = random8();
  gchaos1[i] = gchaos2[i];
  gchaos2[i] = random8();
  bchaos1[i] = bchaos2[i];
  bchaos2[i] = random8();
}

}
}




// Train  Train  Train  Train  Train  Train  Train  Train  Train  Train  Train  Train  Train  

void train() {

hdran = false;
cdran = false;


speeds();

if(millis() > time_now + period){
    time_now = millis();
    f++;
}


for (int i = 0; i < 300; i++) {
  leds[i] = blend(CRGB(rchaos1[(i+2)], gchaos1[(i+2)], bchaos1[(i+2)]), CRGB(rchaos1[(i+1)], gchaos1[(i+1)], bchaos1[(i+1)]), ease8InOutQuad(f));
}

if (f == 255) { 
  f = 0;
rchaos1[0] = random8();
gchaos1[0] = random8();
bchaos1[0] = random8();
for (int i = 301; i > 0; i--) {
  rchaos1[i] = rchaos1[(i - 1)];
  gchaos1[i] = gchaos1[(i - 1)];
  bchaos1[i] = bchaos1[(i - 1)];
}
}


}


// Palette Drops    Palette Drops    Palette Drops    Palette Drops    Palette Drops    Palette Drops    Palette Drops    Palette Drops    Palette Drops   

void palettedrop() {

hdran = false;
cdran = false;


  
if (pdran == false) {

for (i = 0; i < 300; i++) {
leds[i] = ColorFromPalette( activePal, random8()); // normal palette access
}
  pdran = true;
}

speeds();
// Stalls
stalls();

if(millis() > time_now + period){
    time_now = millis();
    i = random16(300);
    leds[i] = ColorFromPalette( activePal, random8());

}


}





 
// Utility Loops  Utility Loops  Utility Loops  Utility Loops  Utility Loops  

void modemaker() {
  
    if (click5 == 3) {
    if (modeentry == false) {
    encoder1.setPosition(0);
    encoder2.setPosition(0);
    encoder3.setPosition(0);
    encoder4.setPosition(0);
    encoder5.setPosition(mode);
    modeentry = true;
    trainran = false;
    
    click1 = 0;
    click2 = 0;
    click3 = 0;
    click4 = 0;
    }
    mode = abs(pos5) % modecount;
    if (modeentry == true && pos1 !=0) {
      click5 = 0;
      modeentry = false;
    }
    if (modeentry == true && pos2 !=0) {
      click5 = 0;
      modeentry = false;
    }
    if (modeentry == true && pos3 !=0) {
      click5 = 0;
      modeentry = false;
    }
    if (modeentry == true && pos4 !=0) {
      click5 = 0;
      modeentry = false;
    }
   }

}








void speeds() {
  t.update();
  if (pos1 != 0) {
  period = period + (pos1 * m1); 
  encoder1.setPosition(0);
}
if (period < 10) period = 10;
if (period > 10000) period = 10000;
}

void showleds(void *context)
{
  buttons();
  encoders();
  FastLED.show();
}

void encoders() {

  encoder1.tick();
  encoder2.tick();
  encoder3.tick();
  encoder4.tick();
  encoder5.tick();
  
  pos1 = encoder1.getPosition();
  pos2 = encoder2.getPosition();
  pos3 = encoder3.getPosition();
  pos4 = encoder4.getPosition();
  pos5 = encoder5.getPosition();
  
}

void stalls() {
if (pos2 > 255) encoder2.setPosition(255);
if (pos2 < -255) encoder2.setPosition(-255);
if (pos3 > 255) encoder3.setPosition(255);
if (pos3 < -255) encoder3.setPosition(-255);
if (pos4 > 255) encoder4.setPosition(255);
if (pos4 < -255) encoder4.setPosition(-255);
}

void buttons() {

button1.Update();
button2.Update();
button3.Update();
button4.Update();
button5.Update();

if (button1.clicks != 0) click1 = button1.clicks;
if (button2.clicks != 0) click2 = button2.clicks;
if (button3.clicks != 0) click3 = button3.clicks;
if (button4.clicks != 0) click4 = button4.clicks;
if (button5.clicks != 0) click5 = button5.clicks;
  
}
