#include "AudioMaster.h"

#include <AL/al.h>
#include <vorbis/vorbisfile.h>
#include <vector>
#include <iostream>

namespace AudioEngine
{


struct AudioImpl
{
	ALuint id;

	~AudioImpl()
	{
		alDeleteBuffers(1, &id);
	}

	void load_ogg(std::string _filePath, std::vector<char> &_buffer, ALenum &_format, ALsizei &_freq)
	{
		int endian = 0;
		int bitStream = 0;
		long bytes = 0;
		char array[2048] = { 0 };
		vorbis_info *pInfo = NULL;
		OggVorbis_File oggFile = { 0 };

		//using the inbuilt fopen to create a file descriptor
		if (ov_fopen(_filePath.c_str(), &oggFile) != 0)
		{
			std::cout << "Failed to open file '" << _filePath << "' for decoding" << std::endl;
			throw std::exception();
		}

		//extract information from the file header
		pInfo = ov_info(&oggFile, -1);

		//record the format required by OpenAL
		if (pInfo->channels == 1)
		{
			_format = AL_FORMAT_MONO16;
		}
		else
		{
			_format = AL_FORMAT_STEREO16;
		}

		//record the sample rate required by OpenAL
		_freq = pInfo->rate;

		//keep reading bytes from the file to populate the output buffer
		while (true)
		{
			//read bytes into temporary array
			bytes = ov_read(&oggFile, array, 2048, endian, 2, 1, &bitStream);

			if (bytes < 0)
			{
				ov_clear(&oggFile);
				std::cout << "Failed to decode file '" << _filePath << "'." << std::endl;
				throw std::exception();
			}

			else if (bytes == 0)
			{
				break;
			}

			//copy from temporary array into output buffer
			_buffer.insert(_buffer.end(), array, array + bytes);
		}

		//clean up and close the file
		ov_clear(&oggFile);
	}
};

AudioMaster::AudioMaster()
{}

AudioMaster::AudioMaster(std::string _filePath)
{
	InitAudio();

	Load(_filePath);
}


void AudioMaster::InitAudio()
{
	m_device = alcOpenDevice(NULL);
	if (!m_device)
	{
		throw std::exception();
	}

	m_context = alcCreateContext(m_device, NULL);
	if (!m_context)
	{
		alcCloseDevice(m_device);
		throw std::exception();
	}

	if (!alcMakeContextCurrent(m_context))
	{
		alcDestroyContext(m_context);
		alcCloseDevice(m_device);
		throw std::exception();
	}
}

void AudioMaster::Load(std::string _filePath)
{
	m_impl = std::make_shared<AudioImpl>();

	ALenum format = 0;
	ALsizei freq = 0;
	std::vector<char> bufferData;

	alGenBuffers(1, &m_impl->id);

	m_impl->load_ogg(_filePath.c_str(), bufferData, format, freq);

	alBufferData(m_impl->id, format, &bufferData[0], static_cast<ALsizei>(bufferData.size()), freq);
}

void AudioMaster::Play()
{
	ALuint sourceID = 0;

	alGenSources(1, &sourceID);
	alListener3f(AL_POSITION, m_listenerPosX, m_listenerPosY, m_listenerPosZ);

	alSource3f(sourceID, AL_POSITION, m_sourcePosX, m_sourcePosY, m_sourcePosZ);
	alSourcei(sourceID, AL_BUFFER, m_impl->id);
	alSourcePlay(sourceID);
}

void AudioMaster::SetListener(float _x, float _y, float _z)
{
	m_listenerPosX = _x;
	m_listenerPosY = _y;
	m_listenerPosZ = _z;
}

void AudioMaster::SetSource(float _x, float _y, float _z)
{
	m_sourcePosX = _x;
	m_sourcePosY = _y;
	m_sourcePosZ = _z;
}

AudioMaster::~AudioMaster()
{
	alcDestroyContext(m_context);
	alcMakeContextCurrent(NULL);
	alcCloseDevice(m_device);
}

}
