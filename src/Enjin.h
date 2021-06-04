#ifndef ENJIN_H_
#define ENJIN_H_

#include "Globals.h"
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>

typedef SDL_Surface Image;

#define COLORKEY 255, 0, 255

class Enjin
{
private:
	int musicVolume;
	int soundVolume;
	map<int, char> keyMap;
	vector<vector<bool>> joyMap;
	int mouseX;
	int mouseY;
	int mouseButtonUp;
	int mouseButtonDown;

	map<string, SDL_Surface *> spriteMap;
	map<string, string> spriteName;
	map<string, SDL_Surface *>::iterator spriteIterator;
	map<string, string>::iterator spriteNameIterator;

public:
	SDL_Surface *screen;

	Enjin();
	~Enjin();

	// Images
	void set(string t, uint w, uint h);
	void setFullScreen(bool full);
	void drawScreen();
	void delay(int d);
	void drawImage(SDL_Surface *srcimg, SDL_Surface *dstimg, int x, int y,
				   int alpha);
	void blitImage(SDL_Surface *srcimg, int sx, int sy, int sw, int sh,
				   SDL_Surface *dstimg, int dx, int dy, int alpha);
	SDL_Surface *createImage(int w, int h);
	SDL_Surface *loadImage(string fileName);

	bool loadSprite(string caminhofisico, string nome);
	SDL_Surface *getSprite(string nome);
	void setPixel(SDL_Surface *image, int x, int y, SDL_Color color);
	SDL_Color getPixel(SDL_Surface *image, int x, int y);
	SDL_Color color(int r, int g, int b);
	bool isColor(SDL_Color c, int r, int g, int b);

	// Musics and sounds
	void stopMusic();
	void setMusicVolume(int Volume);
	void setSoundVolume(int Volume);
	int getMusicVolume();
	int getSoundVolume();
	Mix_Music *loadMusic(string fileName);
	Mix_Chunk *loadSound(string fileName);
	void playMusic(Mix_Music *music, int repeats);
	void playSound(Mix_Chunk *sound, uint repeats);

	// Fonts and text
	TTF_Font *loadFont(string fileName, int size);
	void drawText(string text, SDL_Surface *dstimg, TTF_Font *font, int x,
				  int y, SDL_Color *fg, SDL_Color *bg);

	// Events
	bool updateEvents();
	bool isKeyHeld(int key);
	bool isKeyDown(int key);
	bool isKeyUp(int key);
	bool isMouseDown();
	bool isMouseUp();
	int getMouseButton();
	int getMouseX();
	int getMouseY();

	bool isJoystickUp(int joy);
	bool isJoystickDown(int joy);
	bool isJoystickLeft(int joy);
	bool isJoystickRight(int joy);
	bool isJoystickButtonPressed(int joy, int button);
};

#endif /* ENJIN_H_ */
