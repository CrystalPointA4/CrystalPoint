#include "Sound.h"

#include <iostream>
#ifdef WIN32
#include <windows.h>
#include <al.h>
#else
#include <AL/al.h>
typedef unsigned long DWORD;
typedef unsigned short WORD;
typedef unsigned int UNINT32;
typedef unsigned char BYTE;
#endif


Sound::Sound(const char* inWavPath, bool inLooping):
	buffer_id(0),
	source_id(0),
	is_looping(inLooping)
{
	const char* path = inWavPath;

	FILE *fp = fopen(path, "rb");													// Open the WAVE file
	if (!fp)
		return;																		// Could not open file

	// Check that the WAVE file is OK
	char type[4];
	fread(type, sizeof(char), 4, fp);												// Reads the first bytes in the file
	if (type[0] != 'R' || type[1] != 'I' || type[2] != 'F' || type[3] != 'F')		// Should be "RIFF"
		return;																// Not RIFF

	DWORD size;
	fread(&size, sizeof(DWORD), 1, fp);												// Continue to read the file
	fread(type, sizeof(char), 4, fp);												// Continue to read the file
	if (type[0] != 'W' || type[1] != 'A' || type[2] != 'V' || type[3] != 'E')		// This part should be "WAVE"
		return;																		// Not WAVE

	fread(type, sizeof(char), 4, fp);												// Continue to read the file
	if (type[0] != 'f' || type[1] != 'm' || type[2] != 't' || type[3] != ' ')		// This part should be "fmt "
		return;																		// Not fmt 

	// Now we know that the file is a acceptable WAVE file
	// Info about the WAVE data is now read and stored
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
	ALenum format = 0;																// The audio format (bits per sample, number of channels)
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
	if (!format)
		return;																		// Not valid format

	fread(type, sizeof(char), 4, fp);
	if (type[0] != 'd' || type[1] != 'a' || type[2] != 't' || type[3] != 'a')       // This part should be "data"
		return;																		// not data

	DWORD dataSize;
	fread(&dataSize, sizeof(DWORD), 1, fp);											// The size of the sound data is read

	// Display the info about the WAVE file
	std::cout << "Chunk Size: " << chunkSize << "\n";
	std::cout << "Format Type: " << formatType << "\n";
	std::cout << "Channels: " << channels << "\n";
	std::cout << "Sample Rate: " << sampleRate << "\n";
	std::cout << "Average Bytes Per Second: " << avgBytesPerSec << "\n";
	std::cout << "Bytes Per Sample: " << bytesPerSample << "\n";
	std::cout << "Bits Per Sample: " << bitsPerSample << "\n";
	std::cout << "Data Size: " << dataSize << "\n";

	unsigned char* buf = new unsigned char[dataSize];								// Allocate memory for the sound data
	std::cout << fread(buf, sizeof(BYTE), dataSize, fp) << " bytes loaded\n";		// Read the sound data and display the 
	fclose(fp);

	alGenBuffers(1, &buffer_id);														// Generate one OpenAL Buffer and link to "buffer"
	alGenSources(1, &source_id);														// Generate one OpenAL Source and link to "source"
	if (alGetError() != AL_NO_ERROR)
		return;																		// Error during buffer/source generation

	alBufferData(buffer_id, format, buf, dataSize, sampleRate);						// Store the sound data in the OpenAL Buffer
	if (alGetError() != AL_NO_ERROR)
		return;																		// Error during buffer loading

	delete[] buf;																// Delete the sound data buffer
}


Sound::~Sound()
{
	alSourceStop(source_id);
	alDeleteSources(1, &source_id);												// Delete the OpenAL Source
	alDeleteBuffers(1, &buffer_id);												// Delete the OpenAL Buffer
}


void Sound::SetPos(const Vec3f& inPos, const Vec3f& inVel)
{
	alSourcei(source_id, AL_BUFFER, buffer_id);									// Link the buffer to the source
	alSourcef(source_id, AL_PITCH, 1.0f);										// Set the pitch of the source
	alSourcef(source_id, AL_GAIN, 1.0f);										// Set the gain of the source
	alSourcefv(source_id, AL_POSITION, inPos.v);								// Set the position of the source
	alSourcefv(source_id, AL_VELOCITY, inVel.v);								// Set the velocity of the source
	alSourcei(source_id, AL_LOOPING, is_looping ? AL_TRUE : AL_FALSE);			// Set if source is looping sound
}


void Sound::Play()
{
	alSourcePlay(source_id);
	int e = alGetError(); // != AL_NO_ERROR) return;
}


void Sound::Pause()
{
	alSourcePause(source_id);
}


void Sound::Stop()
{
	alSourceStop(source_id);
}

bool Sound::IsPlaying()
{
	ALenum state;

	alGetSourcei(source_id, AL_SOURCE_STATE, &state);

	return (state == AL_PLAYING);
}

bool Sound::IsStopped()
{
	ALenum state;

	alGetSourcei(source_id, AL_SOURCE_STATE, &state);

	std::cout << "MUSIC STATE: " << state << std::endl;

	return (state == AL_STOPPED);
}

