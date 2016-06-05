#include "OpenAL.h"
#include <cstdlib>
#include <iostream>
#include <windows.h>
#include <al.h>
#include <alc.h>

SoundSystem::SoundSystem():
	device(nullptr),
	context(nullptr)
{
	device = alcOpenDevice(nullptr);
	if (!device) 
		return;
	context = alcCreateContext(device, nullptr);
	if (!context)
		return;
	alcMakeContextCurrent(context);
}

SoundSystem::~SoundSystem()
{
	alcMakeContextCurrent(nullptr);                                             //Make no context current
	alcDestroyContext(context);                                                 //Destroy the OpenAL Context
	alcCloseDevice(device);                                                     //Close the OpenAL Device
}





void SoundSystem::Play(ESoundID inID)
{
	ALuint buffer;
	alGenBuffers(1, &buffer);                                                    //Generate one OpenAL Buffer and link to "buffer"
	ALuint source;
	alGenSources(1, &source);                                                   //Generate one OpenAL Source and link to "source"
	if (alGetError() != AL_NO_ERROR) return ;     //Error during buffer/source generation

																				 //Figure out the format of the WAVE file
	ALenum format = 0;                                                            //The audio format (bits per sample, number of channels)
	if (bitsPerSample == 8)
	{
		if (channels == 1)
			format = AL_FORMAT_MONO8;
		else if (channels == 2)
			format = AL_FORMAT_STEREO8;
	}
	else if (bitsPerSample == 16)
	{
		if (channels == 1)
			format = AL_FORMAT_MONO16;
		else if (channels == 2)
			format = AL_FORMAT_STEREO16;
	}
	if (!format) return;                      //Not valid format

	ALuint frequency = sampleRate;                                               //The Sample Rate of the WAVE file
	alBufferData(buffer, format, buf, dataSize, frequency);                    //Store the sound data in the OpenAL Buffer
	if (alGetError() != AL_NO_ERROR)
		return EndWithError("Error loading ALBuffer");                              //Error during buffer loading

																					//Sound setting variables
	ALfloat SourcePos[] = { 0.0, 0.0, 0.0 };                                    //Position of the source sound
	ALfloat SourceVel[] = { 0.0, 0.0, 0.0 };                                    //Velocity of the source sound
	ALfloat ListenerPos[] = { 0.0, 0.0, 0.0 };                                  //Position of the listener
	ALfloat ListenerVel[] = { 0.0, 0.0, 0.0 };                                  //Velocity of the listener
	ALfloat ListenerOri[] = { 0.0, 0.0, -1.0,  0.0, 1.0, 0.0 };                 //Orientation of the listener
																				//First direction vector, then vector pointing up) 
																				//Listener                                                                               
	alListenerfv(AL_POSITION, ListenerPos);                                  //Set position of the listener
	alListenerfv(AL_VELOCITY, ListenerVel);                                  //Set velocity of the listener
	alListenerfv(AL_ORIENTATION, ListenerOri);                                  //Set orientation of the listener

																				//Source
	alSourcei(source, AL_BUFFER, buffer);                                 //Link the buffer to the source
	alSourcef(source, AL_PITCH, 1.0f);                                 //Set the pitch of the source
	alSourcef(source, AL_GAIN, 1.0f);                                 //Set the gain of the source
	alSourcefv(source, AL_POSITION, SourcePos);                                 //Set the position of the source
	alSourcefv(source, AL_VELOCITY, SourceVel);                                 //Set the velocity of the source
	alSourcei(source, AL_LOOPING, AL_FALSE);                                 //Set if source is looping sound

																			 //PLAY 
	alSourcePlay(source);                                                       //Play the sound buffer linked to the source
	if (alGetError() != AL_NO_ERROR) return EndWithError("Error playing sound"); //Error when playing sound
	system("PAUSE");                                                            //Pause to let the sound play

																				//Clean-up
	fclose(fp);                                                                 //Close the WAVE file
	delete[] buf;                                                               //Delete the sound data buffer
	alDeleteSources(1, &source);                                                //Delete the OpenAL Source
	alDeleteBuffers(1, &buffer);                                                 //Delete the OpenAL Buffer

	return ;
}


void SoundSystem::Pause(ESoundID inID)
{

}


void SoundSystem::Stop(ESoundID inID)
{

}




const char* SoundSystem::GetWaveFile(ESoundID inID)
{

}

bool SoundSystem::LoadWave(ESoundID inID)
{
	const char* path = GetWaveFile(inID);

	FILE *fp = fopen(path, "rb");													//Open the WAVE file
	if (!fp)
		return false;																// Could not open file

																					//Check that the WAVE file is OK
	char type[4];
	fread(type, sizeof(char), 4, fp);												// Reads the first bytes in the file
	if (type[0] != 'R' || type[1] != 'I' || type[2] != 'F' || type[3] != 'F')		// Should be "RIFF"
		return false;																// Not RIFF

	DWORD size;
	fread(&size, sizeof(DWORD), 1, fp);												// Continue to read the file
	fread(type, sizeof(char), 4, fp);												// Continue to read the file
	if (type[0] != 'W' || type[1] != 'A' || type[2] != 'V' || type[3] != 'E')		//This part should be "WAVE"
		return false;																//Not WAVE

	fread(type, sizeof(char), 4, fp);												//Continue to read the file
	if (type[0] != 'f' || type[1] != 'm' || type[2] != 't' || type[3] != ' ')		//This part should be "fmt "
		return false;																//Not fmt 

	//Now we know that the file is a acceptable WAVE file
	//Info about the WAVE data is now read and stored
	DWORD chunkSize;
	fread(&chunkSize, sizeof(DWORD), 1, fp);
	short formatType;
	fread(&formatType, sizeof(short), 1, fp);
	short channels;
	fread(&channels, sizeof(short), 1, fp);
	DWORD sampleRate;
	fread(&sampleRate, sizeof(DWORD), 1, fp);
	DWORD avgBytesPerSec;
	fread(&avgBytesPerSec, sizeof(DWORD), 1, fp);
	short bytesPerSample;
	fread(&bytesPerSample, sizeof(short), 1, fp);
	short bitsPerSample;
	fread(&bitsPerSample, sizeof(short), 1, fp);

	fread(type, sizeof(char), 4, fp);
	if (type[0] != 'd' || type[1] != 'a' || type[2] != 't' || type[3] != 'a')       //This part should be "data"
		return false;																//not data

	DWORD dataSize;
	fread(&dataSize, sizeof(DWORD), 1, fp);                                        //The size of the sound data is read

																				   //Display the info about the WAVE file
	std::cout << "Chunk Size: " << chunkSize << "\n";
	std::cout << "Format Type: " << formatType << "\n";
	std::cout << "Channels: " << channels << "\n";
	std::cout << "Sample Rate: " << sampleRate << "\n";
	std::cout << "Average Bytes Per Second: " << avgBytesPerSec << "\n";
	std::cout << "Bytes Per Sample: " << bytesPerSample << "\n";
	std::cout << "Bits Per Sample: " << bitsPerSample << "\n";
	std::cout << "Data Size: " << dataSize << "\n";

	unsigned char* buf = new unsigned char[dataSize];                            //Allocate memory for the sound data
	std::cout << fread(buf, sizeof(BYTE), dataSize, fp) << " bytes loaded\n";           //Read the sound data and display the 

	return true;
}

