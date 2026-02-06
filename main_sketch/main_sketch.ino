#include <U8g2lib.h>
#include <SPI.h>
#include <sstream>




U8G2_SH1106_128X64_NONAME_F_4W_HW_SPI u8g2(U8G2_R3, 10, 8, 9);



#define LEDR 5  
#define LEDY 6       
#define LEDG 7  
#define SPEAKER 15
#define KEY_RIGHT 2
#define KEY_DOWN 3
#define KEY_LEFT 4
#define KEY_UP 1



// penalty represents a time in seconds
int miss_trys, penalty, code, puzzle;
uint64_t start;
int xPos=1;
int yPos=1;
int currentlydisplayedpieceofanswer[] = {-1,-1,-1,-1};

int numtable[4][3] = {
	{1, 2, 3},  
	{4, 5, 6},
	{7, 8, 9},
	{10, 0, 11}
};
int cursorPos;


void setup() {
	// put your setup code here, to run once:+ 120000

	pinMode(LEDG, OUTPUT);
	pinMode(LEDY, OUTPUT);
	pinMode(LEDR, OUTPUT);
	pinMode(KEY_RIGHT, INPUT_PULLUP);
	pinMode(KEY_DOWN, INPUT_PULLUP);
	pinMode(KEY_LEFT, INPUT_PULLUP);
	pinMode(KEY_UP, INPUT_PULLUP);

	digitalWrite(LEDR, LOW);
	digitalWrite(LEDY, LOW);
	digitalWrite(LEDG, LOW);

	miss_trys = 0;
	penalty = 0;
	code = 0;
	puzzle = 0;
	cursorPos = 0;
	start = time_us_64();
	drawsetup();

	
	
	
}

void loop() {

	/*
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
	*/
	// updateCursor();
	posUpdate();
	// updateCursor();
	delay(200);
	drawtime();
	displayactivenumber();
	displaycurrentpuzzle();
}

void update_leds() {
	switch (miss_trys) {
		case 0:
			penalty += 120;
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

bool enter(int code) {
	int solutions[7] = {234, 573, 827, 983, 073, 937, 897}; 
	return code == solutions[puzzle];
}


void check(){
	if (digitalRead(KEY_UP) == LOW) {
		drawCursor(xPos, yPos);
		yPos = yPos - 1;
		drawCursor(xPos, yPos);
		delay(200);
	}
	if (digitalRead(KEY_DOWN) == LOW) {
		drawCursor(xPos, yPos);
		yPos = yPos + 1;
		drawCursor(xPos, yPos);
		delay(200);
	}
	if (digitalRead(KEY_LEFT) == LOW) {
		drawCursor(xPos, yPos);
		xPos = xPos - 1;
		drawCursor(xPos, yPos);
		delay(200);
	}
	if (digitalRead(KEY_RIGHT) == LOW) {
		drawCursor(xPos, yPos);
		xPos = xPos + 1;
		drawCursor(xPos, yPos);
		delay(200);
	}
}

void posUpdate() {

	if (digitalRead(KEY_LEFT) == LOW) {
		if ((cursorPos / 3) > 0) {
			updateCursor();
			cursorPos -= 3;
			updateCursor();
		}
	}
	if (digitalRead(KEY_RIGHT) == LOW) {
		if ((cursorPos / 3) < 3) {
			updateCursor();
			cursorPos += 3;
			updateCursor();
		}
	}
	if (digitalRead(KEY_DOWN) == LOW) {
		if ((cursorPos % 3) > 0) {
			updateCursor();
			cursorPos -= 1;
			updateCursor();
		}
	}
	if (digitalRead(KEY_UP) == LOW) {
		if ((cursorPos % 3) < 2) {
			updateCursor();
			cursorPos += 1;
			updateCursor();
		}
	}
	// updateCursor();
	// delay(200);
}

int lookuptable(int x, int y){
  return numtable[y][x];
}

void updateCursor() {
	u8g2.setDrawColor(2);
	int x = cursorPos % 3;
	int y = cursorPos / 3;
	u8g2.drawBox(1+x*22, 63+y*16, 18, 12);
	u8g2.setDrawColor(1);
	u8g2.sendBuffer();  
}

void drawsetup() {
	u8g2.begin();    
	u8g2.clearBuffer();  
	u8g2.drawLine(0, 16, 63, 16);

	u8g2.setFont(u8g2_font_helvR08_tr);
	u8g2.drawButtonUTF8(10, 72, U8G2_BTN_HCENTER|U8G2_BTN_BW1, 16,  1,  1, "1" );
	u8g2.drawButtonUTF8(32, 72, U8G2_BTN_HCENTER|U8G2_BTN_BW1, 16,  1,  1, "2" );
	u8g2.drawButtonUTF8(54, 72, U8G2_BTN_HCENTER|U8G2_BTN_BW1, 16,  1,  1, "3" );
	u8g2.drawButtonUTF8(10, 88, U8G2_BTN_HCENTER|U8G2_BTN_BW1, 16,  1,  1, "4" );
	u8g2.drawButtonUTF8(32, 88, U8G2_BTN_HCENTER|U8G2_BTN_BW1, 16,  1,  1, "5" );
	u8g2.drawButtonUTF8(54, 88, U8G2_BTN_HCENTER|U8G2_BTN_BW1, 16,  1,  1, "6" );
	u8g2.drawButtonUTF8(10, 104, U8G2_BTN_HCENTER|U8G2_BTN_BW1, 16,  1,  1, "7" );
	u8g2.drawButtonUTF8(32, 104, U8G2_BTN_HCENTER|U8G2_BTN_BW1, 16,  1,  1, "8" );
	u8g2.drawButtonUTF8(54, 104, U8G2_BTN_HCENTER|U8G2_BTN_BW1, 16,  1,  1, "9" );
	u8g2.drawButtonUTF8(10, 120, U8G2_BTN_HCENTER|U8G2_BTN_BW1, 16,  1,  1, "x" );
	u8g2.drawButtonUTF8(32, 120, U8G2_BTN_HCENTER|U8G2_BTN_BW1, 16,  1,  1, "0" );
	u8g2.drawButtonUTF8(54, 120, U8G2_BTN_HCENTER|U8G2_BTN_BW1, 16,  1,  1, "<=" );

	u8g2.sendBuffer();  
	updateCursor();
}

void drawCursor(int x, int y){
	u8g2.setDrawColor(2);
	u8g2.drawBox(80+x*17, 2+y*16, 13, 12);
	u8g2.setDrawColor(1);
	u8g2.sendBuffer();  
}


void drawtime(){
	u8g2.setFont(u8g2_font_helvR08_tr);
	u8g2.setDrawColor(0);
	u8g2.drawBox(36,0,28,15);
	u8g2.setDrawColor(1);
	readable(time_elapsed());
	u8g2.sendBuffer(); 
}


void displaycurrentpuzzle(){
	u8g2.setFont(u8g2_font_helvR08_tr);
	u8g2.setDrawColor(0);
	u8g2.drawBox(0,3,20,12);
	u8g2.setDrawColor(1);
	u8g2.drawStr(0,15,"R4");
	u8g2.sendBuffer(); 
}

void displayactivenumber(){
	u8g2.setFont(u8g2_font_logisoso24_tf);
	u8g2.setDrawColor(1);
	u8g2.drawStr(2,50,"0000");
	u8g2.sendBuffer(); 
}


uint64_t time_elapsed() {
	uint64_t end = time_us_64();
	return (3600000000) - (end - start) + penalty * 1000000;
}

void readable(uint64_t val) {
	uint64_t seconds = val / 1000000;
	uint64_t seconds_mod = seconds % 60;
	uint64_t minutes = seconds / 60;
	Serial.println(minutes);
	Serial.println(seconds);
	Serial.println(val);
  char final[5];
	char sec[2];
	char min[2];
	sprintf(min, "%llu", minutes);
	if (min[1] == NULL) {
		final[0] = '0';
		final[1] = min[0];
	} else {
		final[0] = min[0];
		final[1] = min[1];
	}
	// sprintf(min, "%llu", minutes);
	sprintf(sec, "%llu", seconds_mod);
	final[2] = ':';
	if (sec[1] == NULL) {
		final[3] = '0';
		final[4] = sec[0];
	} else {
		final[3] = sec[0];
		final[4] = sec[1];
	}
	char temp[10]; // it works
	temp[0] = final[0];
	temp[1] = final[1];
	temp[2] = final[2];
	temp[3] = final[3];
	temp[4] = final[4];
	Serial.println(temp);
	
	// char* concatenated = strcat(strcat(strcat(strcat(output, min_string), min_symbol), sec_string), sec_symbol);
	// Serial.begin(0);
  u8g2.drawStr(36, 15, final);
}