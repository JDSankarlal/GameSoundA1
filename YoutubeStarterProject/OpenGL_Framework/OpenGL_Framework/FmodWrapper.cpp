#include "FmodWrapper.h"
#include <iostream>

using namespace std;

void FmodErrorCheck(FMOD_RESULT result)
{
	if (result != FMOD_OK)
	{
		//cout << FMOD_ErrorString(result) << endl;
		system("pause");
	}
}

SoundEngine::~SoundEngine()
{
	if (init)
	{

		result = system->close();
		FmodErrorCheck(result);
		result = system->release();
		FmodErrorCheck(result);
		init = false;
	}
}
void SoundEngine::Init()
{
	if (!init)
	{
		/*
			Create a System object and initialize.
		*/
		result = FMOD::System_Create(&system);
		FmodErrorCheck(result);
		if (result != FMOD_OK) return;

		result = system->getVersion(&version);
		FmodErrorCheck(result);

		result = system->init(100, FMOD_INIT_NORMAL, extradriverdata);
		FmodErrorCheck(result);

		/*
			Set the distance units. (meters/feet etc).
		*/
		result = system->set3DSettings(1.0, 1.0f, 1.0f);
		FmodErrorCheck(result);

	}

	init = true;
}

void SoundEngine::Update()
{
	if (init)
	{
		// UPDATE THE LISTENER
		result = system->set3DListenerAttributes(0, &listener.Pos, &listener.Vel, &listener.Forward, &listener.Up);
		FmodErrorCheck(result);
		result = system->update(); //Updating FMOD. If you don't call each frame of loop, nothing gets updated. CALL ONLY ONCE
		FmodErrorCheck(result);
	}

}

FMOD_RESULT Sound::result;
SoundEngine Sound::engine;

Sound::~Sound()
{
	if (init)
	{
		result = sound->release();
		FmodErrorCheck(result);
		init = false;
	}
}

bool Sound::Load(const char * fileName)
{
	engine.Init();

	if (!init)
	{
		//Load some sound
		result = engine.system->createSound(fileName, FMOD_3D, 0, &sound);
		FmodErrorCheck(result);
		if (result != FMOD_OK) return false;
		result = sound->set3DMinMaxDistance(1.0f, 500.0f);
		FmodErrorCheck(result);
		init = true;
	}

	return true;
}

FMOD::Channel * Sound::Play(bool loop)
{


	//Play sounds at certain positions
	result = engine.system->playSound(sound, 0, true, &channel);
	FmodErrorCheck(result);
	result = channel->set3DAttributes(&pos, &vel);
	FmodErrorCheck(result);
	result = channel->setPaused(false);
	FmodErrorCheck(result);

	if (loop)
	{
		channel->setMode(FMOD_LOOP_NORMAL);
		channel->setLoopCount(-1);
	}

	else { channel->setMode(FMOD_LOOP_OFF); }
	
	return channel;
}

FMOD::Channel * Sound::setModeLinear(bool mode)
{
	if (mode)
	{
		channel->setMode(FMOD_3D_LINEARROLLOFF);
	}

	else
	{
		channel->setMode(FMOD_3D_INVERSEROLLOFF);
	}

	std::cout << "is Linear: " << mode << std::endl;

	return channel;
}

void Sound::SetPosition(FMOD::Channel * thisChannel, FMOD_VECTOR newPos, FMOD_VECTOR newVec)
{

	static bool isPlay;
	thisChannel->isPlaying(&isPlay);

	if (isPlay)
	{
		result = thisChannel->set3DAttributes(&newPos, &newVec);
		FmodErrorCheck(result);
	}

}
