#include <U8g2lib.h>
#include <SPI.h>




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
	// u8g2.drawLine(76, 0, 76, 63);

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




uint64_t completion_time() {
	uint64_t end = time_us_64();
	return end - start;
}