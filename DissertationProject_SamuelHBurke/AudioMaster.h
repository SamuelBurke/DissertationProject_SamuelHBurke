#ifndef AUDIOMASTER_H
#define AUDIOMASTER_H

#include <AL/al.h>
#include <AL/alc.h>
#include <memory>
#include <string>

namespace AudioEngine
{
struct AudioImpl;

class AudioMaster
{
public:
	AudioMaster();
	AudioMaster(std::string _filePath);
	~AudioMaster();

	void InitAudio();

	void Load(std::string _filePath);
	void Play();
	//void Play(float _volume, float _varianceMin, float _varianceMax); // Variety of play.

	void SetListener(float _x, float _y, float _z);
	void SetSource(float _x, float _y, float _z);

private:
	std::shared_ptr<AudioImpl> m_impl;

	ALCdevice* m_device;
	ALCcontext* m_context;

	float m_listenerPosX, m_listenerPosY, m_listenerPosZ;
	float m_sourcePosX, m_sourcePosY, m_sourcePosZ;
};

}

#endif // !AUDIOMASTER_H

