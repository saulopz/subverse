#include "Enjin.h"

Enjin::Enjin()
{
	cout << "Init Enjin...";
	Uint32 flags = SDL_DOUBLEBUF | SDL_SWSURFACE; // | SDL_FULLSCREEN;
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		cerr << "[FAIL]: SDL start: " << SDL_GetError() << endl;
		return;
	}
	atexit(SDL_Quit);
	screen = SDL_SetVideoMode(800, 600, 32, flags);
	if (screen == NULL)
	{
		cerr << "[FAIL] Video mode settings: " << SDL_GetError() << endl;
		SDL_Quit();
		return;
	}
	SDL_WM_SetCaption("", NULL);
	cout << "[OK]" << endl;

	cout << "Init Mixer...";
	soundVolume = 128;
	musicVolume = 128;

	int audio_rate = 22050;
	Uint16 audio_format = AUDIO_S16;
	int audio_channels = 2;
	int audio_buffers = 4096;

	SDL_Init(SDL_INIT_AUDIO);
	if (Mix_OpenAudio(audio_rate, audio_format, audio_channels, audio_buffers))
	{
		cerr << "[FAIL] Unable to open audio..." << endl;
		SDL_Quit();
		return;
	}
	cout << " [OK]" << endl;

	cout << "Init ttf...";
	if (TTF_Init() == -1)
	{
		cout << "[FAIL] Unable to start SDL_ttf: " << TTF_GetError() << endl;
	}
	else
	{
		cout << " [OK]" << endl;
	}

	cout << "Init Joystick...";
	if (SDL_Init(SDL_INIT_JOYSTICK) < 0)
	{
		cout << "[FAIL] unable to init SDL: " << SDL_GetError() << endl;
	}
	else
	{
		cout << " [OK]" << endl;
	}
	int numJoy = SDL_NumJoysticks();
	if (numJoy > 0)
	{
		cout << "Joysticks: " << numJoy << endl;
		for (int i = 0; i < numJoy; i++)
		{
			vector<bool> aux;
			for (int j = 0; j < JOY_MAX_EVENTS; j++)
			{
				aux.push_back(false);
			}
			joyMap.push_back(aux);
		}
	}
	else
	{
		cout << "Joystick not found..." << endl;
	}
	return;
}

void Enjin::setFullScreen(bool full)
{
	Uint32 flags = SDL_DOUBLEBUF | SDL_SWSURFACE;
	if (full)
	{
		flags = SDL_DOUBLEBUF | SDL_SWSURFACE | SDL_FULLSCREEN;
	}
	screen = SDL_SetVideoMode(screen->w, screen->h, 32, flags);
	if (screen == NULL)
	{
		cout << "[FAIL] Video mode settings: " << SDL_GetError() << endl;
		SDL_Quit();
		return;
	}
}

void Enjin::set(string t, uint w, uint h)
{
	Uint32 flags = SDL_DOUBLEBUF | SDL_SWSURFACE;
	screen = SDL_SetVideoMode(w, h, 32, flags);
	if (screen == NULL)
	{
		cout << "[FAIL] Video mode settings: " << SDL_GetError() << endl;
		SDL_Quit();
		return;
	}
	SDL_WM_SetCaption(t.c_str(), NULL);
}

void Enjin::delay(int d)
{
	SDL_Delay(d);
}

void Enjin::drawScreen()
{
	SDL_Flip(screen);
}

SDL_Surface *Enjin::createImage(int w, int h)
{
	return SDL_CreateRGBSurface(SDL_SWSURFACE, w, h, 32, 0, 0, 0, 0);
}

SDL_Surface *Enjin::loadImage(string fileName)
{
	cout << "Loading image " << fileName << "...";
	SDL_Surface *image = IMG_Load(fileName.c_str());
	if (image == NULL)
	{
		cerr << "[FAIL] " << IMG_GetError() << endl;
		return NULL;
	}
	if (SDL_SetColorKey(image, SDL_SRCCOLORKEY | SDL_RLEACCEL, SDL_MapRGB(image->format, COLORKEY)) == -1)
	{
		cerr << "[FAIL] " << SDL_GetError() << endl;
		return NULL;
	}
	cout << " [OK]" << endl;
	return image;
}

void Enjin::drawImage(SDL_Surface *srcimg, SDL_Surface *dstimg, int x, int y,
					  int alpha = 255)
{
	blitImage(srcimg, 0, 0, srcimg->w, srcimg->h, dstimg, x, y, alpha);
}

void Enjin::blitImage(SDL_Surface *srcimg, int sx, int sy, int sw, int sh,
					  SDL_Surface *dstimg, int dx, int dy, int alpha = 255)
{
	if ((srcimg == NULL) || (alpha == 0))
	{
		return; //If theres no image, or its 100% transparent.
	}
	SDL_Rect src, dst;
	src.x = sx;
	src.y = sy;
	src.w = sw;
	src.h = sh;
	dst.x = dx;
	dst.y = dy;
	dst.w = src.w;
	dst.h = src.h;
	if (alpha != 255)
	{
		SDL_SetAlpha(srcimg, SDL_SRCALPHA, alpha);
	}
	SDL_BlitSurface(srcimg, &src, dstimg, &dst);
}

SDL_Surface *Enjin::getSprite(string nome)
{
	spriteNameIterator = spriteName.find(nome);
	if (spriteNameIterator != spriteName.end())
	{
		spriteIterator = spriteMap.find(spriteNameIterator->second);
		if (spriteIterator != spriteMap.end())
		{
			return spriteMap.find(spriteNameIterator->second)->second;
		}
	}
	return NULL;
}

bool Enjin::loadSprite(string caminhofisico, string nome)
{
	if (spriteMap.find(caminhofisico) == spriteMap.end() && spriteName.find(nome) == spriteName.end())
	{
		spriteMap[caminhofisico] = loadImage(caminhofisico);
		spriteName[nome] = caminhofisico;
		return true;
	}
	return false;
}

void Enjin::setPixel(SDL_Surface *image, int x, int y, SDL_Color color)
{
	Uint32 col = SDL_MapRGB(image->format, color.r, color.g, color.b);
	char *pos = (char *)image->pixels;
	pos += image->pitch * y;
	pos += image->format->BytesPerPixel * x;
	memcpy(pos, &col, image->format->BytesPerPixel);
}

SDL_Color Enjin::getPixel(SDL_Surface *image, int x, int y)
{
	SDL_Color color;
	Uint32 col = 0;
	char *pos = (char *)image->pixels;
	pos += image->pitch * y;
	pos += image->format->BytesPerPixel * x;
	memcpy(&col, pos, image->format->BytesPerPixel);
	SDL_GetRGB(col, image->format, &color.r, &color.g, &color.b);
	return color;
}

SDL_Color Enjin::color(int r, int g, int b)
{
	SDL_Color c;
	c.r = r;
	c.g = g;
	c.b = b;
	return c;
}

bool Enjin::isColor(SDL_Color c, int r, int g, int b)
{
	if ((c.r == r) && (c.g == g) && (c.b == b))
	{
		return true;
	}
	return false;
}

void Enjin::stopMusic()
{
	if (Mix_PlayingMusic() == 1)
	{
		Mix_HaltMusic();
	}
}

void Enjin::setMusicVolume(int volume)
{
	if (volume > 128)
	{
		volume = 128;
	}
	if (volume < 0)
	{
		volume = 0;
	}
	Mix_VolumeMusic(volume);
	musicVolume = volume;
}

void Enjin::setSoundVolume(int volume)
{
	if (volume > 128)
	{
		volume = 128;
	}
	if (volume < 0)
	{
		volume = 0;
	}
	Mix_Volume(-1, volume);
	soundVolume = volume;
}

int Enjin::getMusicVolume()
{
	return musicVolume;
}

int Enjin::getSoundVolume()
{
	return soundVolume;
}

Mix_Music *Enjin::loadMusic(string fileName)
{
	cout << "Loading music " << fileName << "...";
	Mix_Music *musicData = Mix_LoadMUS(fileName.c_str());
	if (musicData == NULL)
	{
		cout << "[FAIL] Failed to load music " << fileName << endl;
		return NULL;
	}
	cout << "[OK]" << endl;
	return musicData;
}

Mix_Chunk *Enjin::loadSound(string fileName)
{
	cout << "Loadding sound " << fileName;
	Mix_Chunk *sound =
		Mix_LoadWAV_RW(SDL_RWFromFile(fileName.c_str(), "rb"), 1);
	if (sound == NULL)
	{
		cerr << "[FAIL] Failed to load sound " << fileName << endl;
		return NULL;
	}
	cout << " [OK]" << endl;
	return sound;
}

void Enjin::playMusic(Mix_Music *music, int repeats)
{
	if (music == NULL)
	{
		return;
	}
	stopMusic();
	Mix_PlayMusic(music, repeats);
}

void Enjin::playSound(Mix_Chunk *sound, uint repeats)
{
	if (sound == NULL)
	{
		return;
	}
	if (Mix_PlayChannel(-1, sound, repeats) == -1)
	{
		cout << "Sound: Failed to play sound " << Mix_GetError() << endl;
	}
}

TTF_Font *Enjin::loadFont(string fileName, int size)
{
	cout << "Text: Loadding font " << fileName;
	TTF_Font *font;
	font = TTF_OpenFont(fileName.c_str(), size);
	if (font == NULL)
	{
		cerr << "[FAIL] Unable to load font: " << fileName << " "
			 << TTF_GetError() << endl;
		return NULL;
	}
	cout << " [OK]" << endl;
	return font;
}

void Enjin::drawText(string text, SDL_Surface *dstimg, TTF_Font *font, int x,
					 int y, SDL_Color *fg, SDL_Color *bg)
{
	SDL_Color tmpFontColor = {0, 0, 0, 255};
	SDL_Color tmpFontBgColor = {255, 0, 255, 255};
	SDL_Surface *textImage = NULL;
	if (fg != NULL)
	{
		tmpFontColor.r = fg->r;
		tmpFontColor.g = fg->g;
		tmpFontColor.b = fg->b;
	}
	if (bg != NULL)
	{
		tmpFontBgColor.r = bg->r;
		tmpFontBgColor.g = bg->g;
		tmpFontBgColor.b = bg->b;
		textImage = TTF_RenderText_Shaded(font, text.c_str(), tmpFontColor, tmpFontBgColor);
	}
	if (textImage == NULL)
	{
		textImage = TTF_RenderText_Blended(font, text.c_str(), tmpFontColor);
	}
	drawImage(textImage, dstimg, x, y, 255);
	SDL_FreeSurface(textImage);
}

bool Enjin::updateEvents()
{
	SDL_Event event;
	vector<int> keys;
	mouseButtonUp = 0;
	mouseButtonDown = 0;

	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			return true;
			break;
		case SDL_KEYDOWN:
			keyMap[event.key.keysym.sym] = 'd';
			keys.push_back(event.key.keysym.sym);
			break;
		case SDL_KEYUP:
			keyMap[event.key.keysym.sym] = 'u';
			keys.push_back(event.key.keysym.sym);
			break;
		case SDL_MOUSEMOTION:
			mouseX = event.motion.x;
			mouseY = event.motion.y;
			break;
		case SDL_MOUSEBUTTONUP:
			mouseButtonUp = event.button.button;
			break;
		case SDL_MOUSEBUTTONDOWN:
			mouseButtonDown = event.button.button;
			break;
		case SDL_JOYAXISMOTION:
			//cout << "SDL_JOYAXISMOTION " << event.jaxis.value << endl;
			break;
		case SDL_JOYBALLMOTION:
			//cout << "SDL_JOYBALLMOTION " << endl;
			break;
		case SDL_JOYHATMOTION:
			//cout << "SDL_JOYHATMOTION " << event.jhat.hat << " " << event.jhat.value << endl;
			break;
		case SDL_JOYBUTTONDOWN:
			//cout << "SDL_JOYBUTTONDOWN " << event.jbutton.button << endl;
			break;
		default:
			break;
		}
	}
	//check to see if any keys haven't been released but were press
	// ie being held
	for (map<int, char>::iterator itr = keyMap.begin(); itr != keyMap.end(); itr++)
	{
		//put no status flag
		if (itr->second == 'u')
		{
			bool keyFound = false;
			for (uint i = 0; i < keys.size(); i++)
			{
				if (keys[i] == itr->first)
				{
					keyFound = true;
					break;
				}
			}
			if (!keyFound)
			{
				itr->second = 'n';
			}
		}
		else if (itr->second == 'd')
		{
			bool keyFound = false;
			for (uint i = 0; i < keys.size(); i++)
			{
				if (keys[i] == itr->first)
				{
					keyFound = true;
					break;
				}
			}
			if (!keyFound)
			{
				itr->second = 'h';
			}
		}
	}
	for (int i = 0; i < SDL_NumJoysticks(); i++)
	{
		SDL_Joystick *joy = SDL_JoystickOpen(i);

		for (int j = 0; j < JOY_MAX_BUTTONS; j++)
		{
			joyMap[i][j] = SDL_JoystickGetButton(joy, j);
		}
		// Comparamos com 16 em vez de zero para contornar desvios de calibragem
		joyMap[i][JOY_UP] = (SDL_JoystickGetAxis(joy, 1) < -16);
		joyMap[i][JOY_DOWN] = (SDL_JoystickGetAxis(joy, 1) > 16);
		joyMap[i][JOY_LEFT] = (SDL_JoystickGetAxis(joy, 0) < -16);
		joyMap[i][JOY_RIGHT] = (SDL_JoystickGetAxis(joy, 0) > 16);
	}
	return false;
}

bool Enjin::isKeyHeld(int key)
{
	if (keyMap[key] == 'h')
	{
		return true;
	}
	return false;
}

bool Enjin::isKeyDown(int key)
{
	if (keyMap[key] == 'd')
	{
		return true;
	}
	return false;
}

bool Enjin::isKeyUp(int key)
{
	if (keyMap[key] == 'u')
	{
		return true;
	}
	return false;
}

bool Enjin::isMouseDown()
{
	if (mouseButtonDown != 0)
	{
		return true;
	}
	return false;
}

bool Enjin::isMouseUp()
{
	if (mouseButtonUp != 0)
	{
		return true;
	}
	return false;
}

int Enjin::getMouseButton()
{
	int aux = mouseButtonDown;
	if (mouseButtonDown == 0)
	{
		aux = mouseButtonUp;
	}
	return aux;
}

int Enjin::getMouseX()
{
	return mouseX;
}

int Enjin::getMouseY()
{
	return mouseY;
}

bool Enjin::isJoystickUp(int joy)
{
	if (joy < SDL_NumJoysticks())
	{
		return joyMap[joy][JOY_UP];
	}
	return false;
}

bool Enjin::isJoystickDown(int joy)
{
	if (joy < SDL_NumJoysticks())
	{
		return joyMap[joy][JOY_DOWN];
	}
	return false;
}

bool Enjin::isJoystickLeft(int joy)
{
	if (joy < SDL_NumJoysticks())
	{
		return joyMap[joy][JOY_LEFT];
	}
	return false;
}

bool Enjin::isJoystickRight(int joy)
{
	if (joy < SDL_NumJoysticks())
	{
		return joyMap[joy][JOY_RIGHT];
	}
	return false;
}

bool Enjin::isJoystickButtonPressed(int joy, int button)
{
	if (joy < SDL_NumJoysticks())
	{
		if (button < JOY_MAX_EVENTS)
		{
			return joyMap[joy][button];
		}
		return false;
	}
	return false;
}

Enjin::~Enjin()
{
	cout << "Finalizing Enjin...";
	for (spriteIterator = spriteMap.begin(); spriteIterator != spriteMap.end(); spriteIterator++)
	{
		SDL_FreeSurface(spriteIterator->second);
		delete spriteIterator->second;
	}
	spriteMap.clear();
	spriteName.clear();
	stopMusic();
	Mix_CloseAudio();
	SDL_Quit();
	cout << " [OK]" << endl;
}
