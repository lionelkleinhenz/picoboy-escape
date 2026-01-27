#include <U8g2lib.h>
#include <SPI.h>




U8G2_SH1106_128X64_NONAME_F_4W_HW_SPI u8g2(U8G2_R0, 10, 8, 9);



#define LEDR 5  
#define LEDY 6       
#define LEDG 7      


void setup() {
  // put your setup code here, to run once:

  pinMode(LEDG, OUTPUT);
  pinMode(LEDY, OUTPUT);
  pinMode(LEDR, OUTPUT);

  digitalWrite(LEDR, LOW);
  digitalWrite(LEDY, LOW);
  digitalWrite(LEDG, LOW);

  digitalWrite(LEDR, HIGH);
  digitalWrite(LEDY, HIGH);  
  digitalWrite(LEDG, HIGH);





  u8g2.begin();    
  u8g2.clearBuffer();  

  u8g2.sendBuffer();   
}

void loop() {
  // put your main code here, to run repeatedly:

}
