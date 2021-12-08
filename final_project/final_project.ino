#include <Adafruit_SSD1306.h>
#include <Adafruit_NeoPixel.h>
Adafruit_SSD1306 lcd(128, 64); // create display object
#define SENSOR A10
#define SIZE 500
#define PIN 25
#define OUTPIN A5
#define ringshow_noglitch() {delay(1);ring.show();delay(1);ring.show();}
Adafruit_NeoPixel ring = Adafruit_NeoPixel(16, PIN, NEO_GRB + NEO_KHZ800);
// FOR DISTANCE SENSOR
#define TRIG 5
#define ECHO 16
#define BUZZER 17

void setup() {
  // put your setup code here, to run once:
  lcd.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  lcd.clearDisplay();
  lcd.setTextColor(WHITE);
  lcd.setCursor(0, 0);
  lcd.print("waiting for data...");
  lcd.display();
  ring.begin();
  ring.setBrightness(32);
  ring.clear();
  ring.setPixelColor(0,0);
  ringshow_noglitch();
  pinMode(OUTPIN, OUTPUT);
  Serial.begin(9600);
  // ATTEMPTING THE DISTANCE SENSOR
  pinMode(TRIG, OUTPUT); // set up distance sensor pins
  pinMode(ECHO, INPUT);
  digitalWrite(TRIG, LOW);
  pinMode(BUZZER, OUTPUT); // setup buzzerz
  ledcSetup(0, 5000, 8);
  ledcAttachPin(BUZZER, 0);
}

int count = 0;
float sum = 0;
float dist = 0;
void loop() {
  // put your main code here, to run repeatedly
  lcd.clearDisplay();
//  int curr_time = millis();
  int avg = sum / count;
  if (count == 500) {
    dist = readDistance();
    if (avg > 2000) {
      if (dist > 20) {
        
        // song();
        digitalWrite(OUTPIN, HIGH);
      } else {
        
        digitalWrite(OUTPIN, LOW);
      }
    } else {
      digitalWrite(OUTPIN, HIGH);
    }
    lcd.clearDisplay();
    lcd.setCursor(0, 0);
    lcd.print("Avg: "); 
    lcd.println(avg);
    
    // DISTANCE SENSOR
    lcd.print("Water lvl:");
    lcd.println(dist);
    if (dist > 20) {
      lcd.println("REFILL WATER");
      ledcWriteTone(0, 200);
    }
    else {
      lcd.println("Water basin full :D");
      ledcWriteTone(0, 0);
    }
    lcd.display();
    count = 0;
    sum = 0; 
  } else {
    sum  += analogRead(SENSOR);
    count++;
  }
  LED(avg, dist);
}


void LED(float reading, float dist) {
  ring.clear();
  int x = ((reading - 1300) / 1600) * 256;
  for (int i = 0; i < 16 - floor(((dist - 3) / 17) * 16); i++) {
    ring.setPixelColor(i, x, 256 - x, 0);
  }
  ringshow_noglitch();
}

// read distance sensor, return centimeters
float readDistance() {
  digitalWrite(TRIG, LOW); delayMicroseconds(2);
  digitalWrite(TRIG, HIGH); delayMicroseconds(10);
  digitalWrite(TRIG, LOW);
  unsigned long timeout=micros()+26233L;
  while((digitalRead(ECHO)==LOW)&&(micros()<timeout));
  unsigned long start_time = micros();
  timeout=start_time+26233L;
  while((digitalRead(ECHO)==HIGH)&&(micros()<timeout));
  unsigned long lapse = micros() - start_time;
  return lapse*0.01716f;
}

// easter egg - smash bros. ultimate theme
void song() {
  ledcWriteTone(0,330);//E4 
  delay(310); 
  ledcWriteTone(0,370);//Gb/F#4 
  delay(310);
  ledcWriteTone(0,392);//G4 
  delay(414);  
  ledcWriteTone(0,330);//E4 
  delay(207); 
  ledcWriteTone(0,392);//G4 
  delay(207); 
  ledcWriteTone(0,587);//D5 
  delay(207); 
  ledcWriteTone(0,554);//Db/C#5 
  delay(310); 
  ledcWriteTone(0,494);//B4 
  delay(310);
  ledcWriteTone(0,554);//Db/C#5 
  delay(207); 
  ledcWriteTone(0,659);//E5 
  delay(828);
  ledcWriteTone(0,523);//C5 
  delay(310);
  ledcWriteTone(0,494);//B4 
  delay(310);
  ledcWriteTone(0,440);//A4 
  delay(414); 
  ledcWriteTone(0,392);//G4 
  delay(207); 
  ledcWriteTone(0,440);//A4 
  delay(207); 
  ledcWriteTone(0,494);//B4 
  delay(207);
  ledcWriteTone(0,440);//A4 
  delay(310); 
  ledcWriteTone(0,392);//G4 
  delay(310); 
  ledcWriteTone(0,440);//A4 
  delay(207); 
  ledcWriteTone(0,370);//Gb/F#4 
  delay(310);
  ledcWriteTone(0,440);//A4 
  delay(310); 
  ledcWriteTone(0,587);//D5 
  delay(207); 
  ledcWriteTone(0,659);//E5 
  delay(3312); 
  
  //First Line
  
  ledcWriteTone(0,392);//G4 
  delay(414); 
  ledcWriteTone(0,440);//A4 
  delay(414); 
  ledcWriteTone(0,370);//Gb/F#4 
  delay(621); 
  ledcWriteTone(0,330);//E4 
  delay(103); 
  ledcWriteTone(0,370);//Gb/F#4 
  delay(103);
  ledcWriteTone(0,392);//G4 
  delay(310);
  ledcWriteTone(0,440);//A4 
  delay(310); 
  ledcWriteTone(0,494);//B4 
  delay(207); 
  ledcWriteTone(0,440);//A4 
  delay(828); 
  ledcWriteTone(0,392);//G4 
  delay(414); 
  ledcWriteTone(0,440);//A4 
  delay(414); 
  ledcWriteTone(0,370);//Gb/F#4 
  delay(310);
  ledcWriteTone(0,330);//E4 
  delay(310); 
  ledcWriteTone(0,294);//D4 
  delay(207); 
  ledcWriteTone(0,330);//E4 
  delay(1656); 
  ledcWriteTone(0,392);//G4 
  delay(414); 
  ledcWriteTone(0,440);//A4 
  delay(414); 
  ledcWriteTone(0,370);//Gb/F#4 
  delay(621); 
  ledcWriteTone(0,330);//E4 
  delay(103); 
  ledcWriteTone(0,370);//Gb/F#4 
  delay(103);
  ledcWriteTone(0,392);//G4 
  delay(310);
  ledcWriteTone(0,440);//A4 
  delay(310); 
  ledcWriteTone(0,494);//B4 
  delay(207); 
  ledcWriteTone(0,440);//A4 
  delay(310); 
  ledcWriteTone(0,370);//Gb/F#4 
  delay(310); 
  ledcWriteTone(0,294);//D4 
  delay(207); 
  ledcWriteTone(0,330);//E4 
  delay(828); 
  ledcWriteTone(0,330);//E4 
  delay(310); 
  ledcWriteTone(0,370);//Gb/F#4 
  delay(310); 
  ledcWriteTone(0,392);//G4 
  delay(207);
  ledcWriteTone(0,440);//A4 
  delay(828); 
  ledcWriteTone(0,494);//B4 
  delay(828);
}
