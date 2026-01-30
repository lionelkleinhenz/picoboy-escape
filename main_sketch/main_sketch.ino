#include <U8g2lib.h>
#include <SPI.h>




U8G2_SH1106_128X64_NONAME_F_4W_HW_SPI u8g2(U8G2_R0, 10, 8, 9);



#define LEDR 5  
#define LEDY 6       
#define LEDG 7  
#define SPEAKER 15

int miss_trys, cur_time, code, puzzle;

void setup() {
  // put your setup code here, to run once:+ 120000

  pinMode(LEDG, OUTPUT);
  pinMode(LEDY, OUTPUT);
  pinMode(LEDR, OUTPUT);

  digitalWrite(LEDR, LOW);
  digitalWrite(LEDY, LOW);
  digitalWrite(LEDG, LOW);

  miss_trys = 0;
  cur_time = 0;
  code = 0;
  puzzle = 0;



  u8g2.begin();    
  u8g2.clearBuffer();  

  u8g2.sendBuffer();   
}

void loop() {
  if (!enter(code)) {
    miss_trys++;
    miss_trys = miss_trys % 4;
    update_leds();
  } else {
    puzzle++;
  } if (miss_trys == 3) {
    tone(SPEAKER, 2000, 40);
  }
  
  delay(500);
  // put your main code here, to run repeatedly:

}


void update_leds() {
  switch (miss_trys) {
    case 0:
      penalty();
      digitalWrite(LEDR, LOW);
      digitalWrite(LEDY, LOW);
      digitalWrite(LEDG, LOW);
      break;
    case 1:
      digitalWrite(LEDG, HIGH);
      break;
    case 2:
      digitalWrite(LEDY, HIGH);
      break;
    case 3: 
      digitalWrite(LEDR, HIGH);
  }
}

void penalty() {
  int penalty = 120000;
  cur_time += penalty;
}

bool enter(int code) {
  int solutions[7] = {234, 573, 827, 983, 073, 937, 897}; 
  return code == solutions[puzzle];
}