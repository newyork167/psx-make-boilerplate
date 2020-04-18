#include "main.h"

int main() {
	initialize();
    setupDamageSplash();

	while(1) {
		update();
		clearDisplay();
        damageSplash();
		draw();
		display();
	}
}

void setupDamageSplash() {
    damageSplashBox.attribute = 0xD;
    damageSplashBox.x = 0;
    damageSplashBox.y = 0;
    damageSplashBox.h = SCREEN_HEIGHT;
    damageSplashBox.w = SCREEN_WIDTH;
    damageSplashBox.r = 255;
    damageSplashBox.g = 0;
    damageSplashBox.b = 0;
}

void damageSplash() {
    damageColorR -= 10;
    damageSplashBox.r = damageColorR;
}

void initialize() {
	initializeScreen();
	initializePad();
	setBackgroundColor(createColor(0, 0, 0));
	ps1 = createImage(img_ps1);
	crash = createImage(img_crash);
	crash = moveImage(crash, (SCREEN_WIDTH - crash.sprite.w) / 2, (SCREEN_HEIGHT - crash.sprite.h) / 2);
	inCurrentCollision = false;

	// Copy audio files to SPUv
	audioInit();
    audioTransferVagToSPU(&hpup, hpup_size, SPU_0CH);
    audioTransferVagToSPU(&crate, crate_size, SPU_1CH);
}

void playAudio() {
    audioPlay(SPU_0CH);
    audioPlay(SPU_1CH);
}

void checkCrashHit(Image crash) {
	BOOL betweenX = (crash.sprite.x >= ps1.sprite.x) && (crash.sprite.x <= ps1.sprite.x + ps1.sprite.w);
	BOOL betweenY = (crash.sprite.y >= ps1.sprite.y) && (crash.sprite.y <= ps1.sprite.y + ps1.sprite.h);

	if (betweenX && betweenY) {
		// TODO: Play sound
		if (!inCurrentCollision) {
			playAudio();
			printf("Hit the Playstation!\n");
			inCurrentCollision = true;
		}
	} else {
		inCurrentCollision = false;
	}
}

void handleInput() {
	if(padCheck(Pad1Circle)) {
		speed = 2;
	} else {
		speed = 4;
	}

	if(padCheck(Pad1Up)) {
		y -= speed;
		crash = moveImage(crash, x, y);
		checkForCollision = true;
	}

	if(padCheck(Pad1Down)) {
		y += speed;
		crash = moveImage(crash, x, y);
		checkForCollision = true;
	}

	if(padCheck(Pad1Left)) {
		x -= speed;
		crash = moveImage(crash, x, y);
		checkForCollision = true;
	}

	if(padCheck(Pad1Right)) {
		x += speed;
		crash = moveImage(crash, x, y);
		checkForCollision = true;
	}

	if(padCheck(Pad1Start)) {
		initialize();
	}

	if (checkForCollision) {
		checkCrashHit(crash);
	}
}

void update() {
	padUpdate();
	handleInput();

	x = crash.sprite.x;
	y = crash.sprite.y;
}

void draw() {
	drawImage(crash);
	drawImage(ps1);
}
