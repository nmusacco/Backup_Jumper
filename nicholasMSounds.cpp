//Finally a simple OpenAL example program.
//Gordon Griesel
//2015
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <AL/alut.h>


ALuint alBuffer;
ALuint alSource;
ALuint Buffer;
ALuint Source;
//ALuint song = alutCreateBufferFromFile("./Sounds/death1.wav");
//ALuint songSource;

void setupSound()
{
	//Get started right here.
	alutInit(0, NULL);
	if (alGetError() != AL_NO_ERROR) {
		printf("ERROR: alutInit()\n");
		return;
	}
	//Clear error state.
	alGetError();
	
	//Setup the listener
	//Forward and up vectors are used.
	float vec[6] = {0.0f,0.0f,1.0f, 0.0f,1.0f,0.0f};
	alListener3f(AL_POSITION, 0.0f, 0.0f, 0.0f);
	alListenerfv(AL_ORIENTATION, vec);
	alListenerf(AL_GAIN, 1.0f);
}

void playSound()
{
	//Buffer holds the sound info
	//Source refers to the sound.
	
	
	//Generate a source, and store it in a buffer.
	alGenSources(1, &alSource);
	alSourcei(alSource, AL_BUFFER, alBuffer);
	//Set volume and pitch to normal, no looping of sound.
	alSourcef(alSource, AL_GAIN, 1.0f);
	alSourcef(alSource, AL_PITCH, 1.0f);
	alSourcei(alSource, AL_LOOPING, AL_FALSE);
	if (alGetError() != AL_NO_ERROR) {
		printf("ERROR: setting source\n");
		return;
	}
	
	alSourcePlay(alSource);


        return;
}
void cleanupSound()
{
	//First delete the source.
	alDeleteSources(1, &alSource);
	//Delete the buffer.
	alDeleteBuffers(1, &alBuffer);

	alDeleteBuffers(1, &Buffer);

	alDeleteBuffers(1, &Source);

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
	return;
}

void playBackgroundSound()
{
	//Buffer holds the sound info
	//Source refers to the sound.
	 
	
	//Generate a source, and store it in a buffer.
	alGenSources(1, &Source);
	alSourcei(Source, AL_BUFFER, Buffer);
	//Set volume and pitch to normal, no looping of sound.
	alSourcef(Source, AL_GAIN, 0.3f);
	alSourcef(Source, AL_PITCH, 1.0f);
	alSourcei(Source, AL_LOOPING, AL_TRUE);
	if (alGetError() != AL_NO_ERROR) {
		printf("ERROR: setting source\n");
		return;
	}
	
	alSourcePlay(Source);


        return;
}

