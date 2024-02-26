#include "pch.h"
#include "SoundMgr.h"

SoundMgr::SoundMgr()
{
}

SoundMgr::~SoundMgr()
{
	Release();
}

void SoundMgr::Init(int totalChannels)
{
	Release();

	for (int i = 0; i < totalChannels; i++)
	{
		waiting.push_back(new sf::Sound());
	}
	for (int i = 0; i < 2; i++)
	{
		bgm.push_back(sf::Sound());
	}

}

void SoundMgr::Release()
{
	//StopAllSfx();
	//StopBGM();
	for (auto ptr : playing)
	{
		delete ptr;
	}
	playing.clear();
	for (auto ptr : waiting)
	{
		delete ptr;
	}
	waiting.clear();


}

void SoundMgr::Update(float dt)
{

	auto it = playing.begin();
	while (it != playing.end())
	{
		if ((*it)->getStatus() == sf::SoundSource::Stopped)
		{
			waiting.push_back(*it);
			playing.erase(it++);
		}
		else
		{
			it++;
		}
	}
	if (InputMgr::GetKeyDown(sf::Keyboard::Home))
	{
		SetVolumeBGM(50.f);
	}
}

void SoundMgr::PlayBGM(const std::string& id, bool loop, bool crossFade)
{
	const sf::SoundBuffer& buffer = RES_MGR_SOUND_BUFFER.Get(id);
	if (crossFade)
	{
		bgm[frontBGMIndex].setBuffer(buffer);
		bgm[frontBGMIndex].stop();
		bgm[frontBGMIndex].setLoop(loop);
		bgm[frontBGMIndex].play();
	}
}

void SoundMgr::StopBGM(const std::string& id)
{
}

void SoundMgr::PlaySfx(const std::string& id, bool loop)
{
	PlaySfx(RES_MGR_SOUND_BUFFER.Get(id), loop);
}

void SoundMgr::PlaySfx(sf::SoundBuffer& buffer, bool loop)
{
	sf::Sound* sound = nullptr;
	if (waiting.empty())
	{
		sound = playing.front();
		playing.pop_front();
		sound->stop();

	}
	else
	{
		sound = waiting.front();
		waiting.pop_front();
	}


	sound->setBuffer(buffer);
	sound->setLoop(loop);
	sound->setVolume(sfxVolume);
	playing.push_back(sound);
	sound->play();

}

void SoundMgr::StopAllSfx()
{
	for (auto ptr : playing)
	{
		ptr->stop();
		waiting.push_back(ptr);
	}
	playing.clear();
}

void SoundMgr::SetVolumeSfx(float value)
{
	if (value < 0.0f)
	{
		sfxVolume = 0.f;
	}
	else if(value > 100.0f)
	{
		sfxVolume = 100.f;
	}
	else
	{
		sfxVolume = value;
	}

}

void SoundMgr::SetVolumeBGM(float value)
{
	if (value < 0.0f)
	{
		bgmVolume = 0.f;
	}
	else if (value > 100.0f)
	{
		bgmVolume = 100.f;
	}
	else
	{
		bgmVolume = value;
	}

	for (auto& sound : bgm)
	{
		sound.setVolume(bgmVolume);
	}

}

void SoundMgr::UpVolumeBGM(float value)
{
	SetVolumeBGM(bgmVolume + value);
}

void SoundMgr::DownVolumeBGM(float value)
{
	SetVolumeBGM(bgmVolume + value);
}
