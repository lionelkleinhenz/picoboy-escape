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
#define KEY_CENTER 0



// penalty represents a time in seconds
int miss_trys, penalty, code, puzzle;
uint64_t game_start;
int xPos=1;
int yPos=1;
char currentlydisplayedpieceofanswer[] = {'*','*','*','*'};
char lockuptable[] = {'1','2','3','4','5','6','7','8','9','q','0','e'};
int cursorPos;
int currentdigit=0;
int r = 1;


void setup() {
	// put your setup code here, to run once:+ 120000

	pinMode(LEDG, OUTPUT);
	pinMode(LEDY, OUTPUT);
	pinMode(LEDR, OUTPUT);
	pinMode(KEY_RIGHT, INPUT_PULLUP);
	pinMode(KEY_DOWN, INPUT_PULLUP);
	pinMode(KEY_LEFT, INPUT_PULLUP);
	pinMode(KEY_UP, INPUT_PULLUP);
	pinMode(KEY_CENTER, INPUT_PULLUP);

	digitalWrite(LEDR, LOW);
	digitalWrite(LEDY, LOW);
	digitalWrite(LEDG, LOW);

	miss_trys = 0;
	penalty = 0;
	code = 0;
	puzzle = 0;
	cursorPos = 0;
	game_start = time_us_64();
	drawsetup();

	// informationscreen(1);
	// penaltyscreen(30 * 1000000);

	
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




void posUpdate() {

	if (digitalRead(KEY_LEFT) == LOW) {
		if ((cursorPos / 3) > 0) {
			drawCursor();
			cursorPos -= 3;
			drawCursor();
		}
	}
	if (digitalRead(KEY_RIGHT) == LOW) {
		if ((cursorPos / 3) < 3) {
			drawCursor();
			cursorPos += 3;
			drawCursor();
		}
	}
	if (digitalRead(KEY_DOWN) == LOW) {
		if ((cursorPos % 3) > 0) {
			drawCursor();
			cursorPos -= 1;
			drawCursor();
		}
	}
	if (digitalRead(KEY_UP) == LOW) {
		if ((cursorPos % 3) < 2) {
			drawCursor();
			cursorPos += 1;
			drawCursor();
		}
	}
	if (digitalRead(KEY_CENTER) == LOW) {

		if (lockuptable[cursorPos]=='q'){
			currentdigit--;
			currentlydisplayedpieceofanswer[currentdigit] = '*';
			displayactivenumber();
		}
		else if(lockuptable[cursorPos]=='e'){
			verify();
			currentdigit = 0;
    	currentlydisplayedpieceofanswer[0] = '*';
   	  currentlydisplayedpieceofanswer[1] = '*';
   	  currentlydisplayedpieceofanswer[2] = '*';
   	  currentlydisplayedpieceofanswer[3] = '*';
			displayactivenumber();
			r++;
		}
		else {
			currentlydisplayedpieceofanswer[currentdigit] = lockuptable[cursorPos];
			displayactivenumber();
			currentdigit++;
			if(currentdigit > 4){
				currentdigit = 4;
			}
		}
	}

	// updateCursor();
	// delay(200);
}
void verify(){

}

char recalc(){
	int c = cursorPos + 1;


	char m = c + '0';
	return cursorPos;


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
	drawCursor();
}

void drawCursor(){
	u8g2.setDrawColor(2);
	u8g2.drawBox(1+cursorPos % 3*22, 63+cursorPos / 3*16, 18, 12);
	u8g2.setDrawColor(1);
	u8g2.sendBuffer();  
}


void drawtime(){
	u8g2.setFont(u8g2_font_helvR08_tr);
	u8g2.setDrawColor(0);
	u8g2.drawBox(36,0,28,15);
	u8g2.setDrawColor(1);
	readable(3600000000 - time_elapsed(game_start));
	u8g2.sendBuffer(); 
}


void displaycurrentpuzzle(){
	u8g2.setFont(u8g2_font_helvR08_tr);
	u8g2.setDrawColor(0);
	u8g2.drawBox(0,3,20,12);
	u8g2.setDrawColor(1);  
	char t[3];
  t[0] = 'R';
  t[1] = '0' + r;
  t[2] = '\0';
  u8g2.drawStr(0,15, t);
	u8g2.sendBuffer(); 
}

void displayactivenumber(){
	
	u8g2.setDrawColor(0);
	u8g2.drawBox(0,22,64,30);
	u8g2.setFont(u8g2_font_logisoso24_tf);
	u8g2.setDrawColor(1);
	u8g2.drawStr(2,50,currentlydisplayedpieceofanswer);
	u8g2.sendBuffer(); 
}


uint64_t time_elapsed(uint64_t start) {
	uint64_t end = time_us_64();
	uint64_t time_played = end - start;
	return time_played;
}

void readable(uint64_t val) {
	if (val > 3600000000) {
		gameoverscreen();
	}
	uint64_t seconds = val / 1000000;
	uint64_t seconds_mod = seconds % 60;
	uint64_t minutes = seconds / 60;
	// Serial.println(minutes);
	// Serial.println(seconds);
	// Serial.println(val);
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
	char temp[10]; // it works; don't EVER question it 
	temp[0] = final[0];
	temp[1] = final[1];
	temp[2] = final[2];
	temp[3] = final[3];
	temp[4] = final[4];
	Serial.println(temp); // DO NOT REMOVE
	// Serial.println(final);
	
  u8g2.drawStr(36, 15, final);
}

void gameoverscreen() {

}

void penaltyscreen(uint64_t penalty) {
	u8g2.clearBuffer();
	u8g2.sendBuffer();
	uint64_t penalty_start = time_us_64();
	uint64_t time = time_elapsed(penalty_start);
	uint64_t time_remaining = (penalty - time) / 1000000;
	char rem_penalty_sec[3];
	rem_penalty_sec[0] = '3';
	rem_penalty_sec[1] = '0';
	rem_penalty_sec[2] = 's';
	u8g2.setFont(u8g2_font_helvR08_tr);
	u8g2.drawStr(5, 40, "Verbleibende");
	u8g2.drawStr(10, 50, "Zeitstrafe:");
	u8g2.setDrawColor(0);
	u8g2.drawBox(0, 56, 64, 40);
	u8g2.setFont(u8g2_font_logisoso24_tf);
	u8g2.setDrawColor(1);
	u8g2.drawStr(10 ,80, rem_penalty_sec);
	u8g2.sendBuffer();
	while (time < penalty) {
		time = time_elapsed(penalty_start);
		time_remaining = (penalty - time) / 1000000;
		if (time_remaining > penalty / 1000000) {
			break;
		}
		// Serial.println(time_remaining);
		char rem[2];
		sprintf(rem, "%llu", time_remaining);
			if (rem[1] == NULL) {
				rem_penalty_sec[0] = '0';
				rem_penalty_sec[1] = rem[0];
			} else {
				rem_penalty_sec[0] = rem[0];
				rem_penalty_sec[1] = rem[1];
			}
		u8g2.setDrawColor(0);
		u8g2.drawBox(0, 56, 64, 40);
		u8g2.setDrawColor(1);
		u8g2.drawStr(10, 80, rem_penalty_sec);
		u8g2.sendBuffer();
		delay(200);
	}
	u8g2.clearBuffer();
	u8g2.setFont(u8g2_font_helvR08_tr);
	u8g2.sendBuffer();
	drawsetup();
	displayactivenumber();
	
}

void informationscreen(int room) {
	char rooms[5][5] = {"207", "LIFT", "305", "402", "112"};
	u8g2.clearBuffer();
	u8g2.sendBuffer();
	u8g2.drawStr(2, 50, "Neuer Raum:");
	u8g2.setFont(u8g2_font_logisoso16_tf);
	u8g2.drawStr(16 ,70, rooms[room]);
	u8g2.setFont(u8g2_font_helvR08_tr);
	u8g2.drawButtonUTF8(32, 90, U8G2_BTN_HCENTER|U8G2_BTN_BW1, 16,  1,  1, "Weiter!");
	u8g2.setDrawColor(2);
	u8g2.drawBox(15, 81, 33, 12);
	u8g2.setDrawColor(1);
	u8g2.sendBuffer(); 
	u8g2.sendBuffer();
	while (true) {
		if (digitalRead(KEY_CENTER) == LOW) {
			break;
		}
	}
	u8g2.sendBuffer();
	u8g2.clearBuffer();
	u8g2.sendBuffer();
	drawsetup();
	displayactivenumber();
}

