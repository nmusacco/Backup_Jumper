/**********************************
 *         Nicholas Musacco       *
 *              Sounds            *
 *********************************/

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <AL/alut.h>



//As you can tell this is 99% code that Gordon wrote in his openAl example. 
//The only real change I made was breaking up the code into functions,
//and I added a second play sound type of function expect it was for looping sound
//which is only used for the background music


//As for the sound files I used. All sounds were made using my mouth, except for the background music.
//The background music is from the video game Doom 1.
//I took the audio from this youtube video: https://www.youtube.com/watch?v=CofjdOuv68U

//TODO: Increase volume on sounds. Nobody wants to turn up their system volume that loud!
int NUM_SOUNDS = 9;

ALuint alBuffer;	//variables for sounds
ALuint alSource[9];

ALuint Buffer;		//variables for the menu sounds
ALuint Source;

void setupSound()
{
	/*//Get started right here.
	alutInit(0, NULL);
	if (alGetError() != AL_NO_ERROR) {
		printf("ERROR: alutInit()\n");
		return;
	}
	//Clear error state.
	alGetError();
	alGenSources(NUM_SOUNDS, alSource);
	//Setup the listener
	//Forward and up vectors are used.
	float vec[6] = {0.0f,0.0f,1.0f, 0.0f,1.0f,0.0f};
	alListener3f(AL_POSITION, 0.0f, 0.0f, 0.0f);
	alListenerfv(AL_ORIENTATION, vec);
	alListenerf(AL_GAIN, 1.0f);*/
}

void playSound(int num)
{
    /*
	//Buffer holds the sound info
	//Source refers to the sound.
	num -=1;
	//Generate a source, and store it in a buffer.
	
	alSourcei(alSource[num], AL_BUFFER, alBuffer);
	//Set volume and pitch to normal, no looping of sound.
	alSourcef(alSource[num], AL_GAIN, 1.0f);
	alSourcef(alSource[num], AL_PITCH, 1.0f);
	alSourcei(alSource[num], AL_LOOPING, AL_FALSE);
	if (alGetError() != AL_NO_ERROR) {
		printf("ERROR: setting source\n");
		return;
	}

	alSourcePlay(alSource[num]);

*/
	return;
}
void cleanupSound()
{
/*
		//First delete the source.
//	for(int i = 0; i < NUM_SOUNDS; i++)
	alDeleteSources(NUM_SOUNDS, alSource);

	//Delete the buffer.
	alDeleteBuffers(1, &alBuffer);
	
	alDeleteBuffers(1, &Buffer);

	alDeleteSources(1, &Source);

	//alDeleteBuffers(1, &song);
	//Close out OpenAL itself.
	//Get active context.
	ALCcontext *Context = alcGetCurrentContext();
	//Get device for active context.
	ALCdevice *Device = alcGetContextsDevice(Context);
	//Disable context.
	alcMakeContextCurrent(NULL);
	//Release context(s).
	alcDestroyContext(Context);
	//Close device.
	alcCloseDevice(Device);
	return;*/
}

void playBackgroundSound()
{
    /*
	//Buffer holds the sound info
	//Source refers to the sound.


	//Generate a source, and store it in a buffer.
	alGenSources(1, &Source);
	alSourcei(Source, AL_BUFFER, Buffer);
	//Set volume and pitch to normal, no looping of sound.
	alSourcef(Source, AL_GAIN, 0.4f);
	alSourcef(Source, AL_PITCH, 1.0f);
	alSourcei(Source, AL_LOOPING, AL_TRUE);
	if (alGetError() != AL_NO_ERROR) {
		printf("ERROR: setting source\n");
		return;
	}

	alSourcePlay(Source);

*/
	return;
}

