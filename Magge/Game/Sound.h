#pragma once
#include <SDL_mixer.h>
#include "SDL.h"
#include "String"


class Sound
{
	Mix_Chunk* sound = NULL;
	Mix_Music* music = NULL;
	bool isMusic;

public:
	
	Sound(std::string path, bool isMusic)
	{

		this->isMusic = isMusic;
		SDL_Init(SDL_INIT_AUDIO);
		SDL_Init(SDL_INIT_VIDEO);

		

		if (isMusic)
			music = Mix_LoadMUS(path.c_str());
		else
			sound = Mix_LoadWAV(path.c_str());

		if (sound == NULL && music == NULL)
		{
			printf("Failed to load sound effect! SDL_mixer Error: %s\n", Mix_GetError());
		}
	}
	~Sound()
	{
		Mix_FreeChunk(sound);
		sound = NULL;
	}

	void Play()
	{
		if (isMusic)
			Mix_PlayMusic(music, -1);
		else
			Mix_PlayChannel(-1, sound, 0);

	}

};

