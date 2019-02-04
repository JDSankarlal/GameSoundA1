/*==============================================================================
3D Example
Copyright (c), Firelight Technologies Pty, Ltd 2004-2018.

This example shows how to basic 3D positioning of sounds.

Brent Cowan. Jan 21 2019
Josh Sankarlal Jan. 21 2019
==============================================================================*/
#pragma once
#pragma comment (lib, "FMOD/lib/fmod_vc.lib")
#include "FMOD/inc/fmod.hpp"

void FmodErrorCheck(FMOD_RESULT result);

struct Listener
{
	FMOD_VECTOR Pos = { 0.0f, 0.0f, 0.0f };
	FMOD_VECTOR Vel = { 0.0f, 0.0f, 0.0f };
	FMOD_VECTOR Forward = { 0.0f, 0.0f, 1.0f };
	FMOD_VECTOR Up = { 0.0f, 1.0f, 0.0f };
};

class SoundEngine
{
private: 
	unsigned int     version;
	void            *extradriverdata = 0;
	FMOD_RESULT      result;
	bool init = false;
public: 
	~SoundEngine();
	void Init();
	void Update();
	FMOD::System *system;
	Listener listener;
};


class Sound 
{
private:
	static FMOD_RESULT result;
	FMOD::Channel   *channel = 0; //Channel is audio being played. One sound many channels can play it. 
	bool init = false;				

public: 
	~Sound();
	bool Load(const char* fileName);

	FMOD::Channel   *Play(bool loop); //Channel is audio being played. One sound many channels can play it. 
	static void SetPosition(FMOD::Channel* thisChannel, FMOD_VECTOR newPos, FMOD_VECTOR newVec = { 0.0f,0.0f,0.0f });
	FMOD::Sound     *sound; //Sound is the file

	FMOD_VECTOR pos = { 0.0f, 0.0f, 0.0f };
	FMOD_VECTOR vel = { 0.0f, 0.0f, 0.0f };

	static SoundEngine engine;
};





















