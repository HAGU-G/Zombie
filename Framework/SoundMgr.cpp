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
	bgm[frontBGMIndex].setVolume(bgmVolume);
	bgm[backBGMIndex].setVolume(bgmVolume);

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
	if (InputMgr::GetKeyDown(sf::Keyboard::Home))
	{
		UpVolumeBGM(10.f);
	}
	if (InputMgr::GetKeyDown(sf::Keyboard::End))
	{
		DownVolumeBGM(10.f);
	}

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

	if (isFading)
	{
		MixingBGM(dt);
	}


}

void SoundMgr::PlayBGM(const std::string& id, bool crossFade, bool loop)
{
	const sf::SoundBuffer& buffer = RES_MGR_SOUND_BUFFER.Get(id);
	if (!crossFade)
	{
		bgm[frontBGMIndex].stop();
		bgm[backBGMIndex].stop();
		bgm[frontBGMIndex].setBuffer(buffer);
		bgm[frontBGMIndex].setLoop(loop);
		bgm[frontBGMIndex].play();
	}
	else if (!isFading)
	{
		bgm[backBGMIndex].setBuffer(buffer);
		bgm[backBGMIndex].setLoop(loop);
		bgm[backBGMIndex].setVolume(0.f);
		bgm[backBGMIndex].play();

		int temp = frontBGMIndex;
		frontBGMIndex = backBGMIndex;
		backBGMIndex = temp;
		isFading = true;
	}
}

void SoundMgr::StopBGM(const std::string& id)
{
	for (int i = 0; i < _countof(bgm); i++)
	{
		bgm[i].stop();
		isFading = false;
	}
}

void SoundMgr::PlaySfx(const std::string& id, bool loop)
{
	PlaySfx(RES_MGR_SOUND_BUFFER.Get(id), loop);
}



void SoundMgr::MixingBGM(float dt)
{
	//크로스 페이드 도중 페이드 시간이 변해도 초기값을 유지하기 위한 변수
	static float fadeDu = fadeDuration;

	//증감 속도를 각자 설정 (동시에 목표 볼륨에 도달하기 위함)
	if (fadeTimer == 0.f)
	{
		frontMixingSpeed = bgmVolume - bgm[frontBGMIndex].getVolume();
		backMixingSpeed = 0.0f - bgm[backBGMIndex].getVolume();
		fadeDu = fadeDuration;
	}

	//크로스 페이드
	float frontVol = bgm[frontBGMIndex].getVolume() + frontMixingSpeed * dt / fadeDu;
	float backVol = bgm[backBGMIndex].getVolume() + backMixingSpeed * dt / fadeDu;
	bgm[frontBGMIndex].setVolume(frontVol >= bgmVolume ? bgmVolume : frontVol);
	bgm[backBGMIndex].setVolume(backVol <= 0.f ? 0.f : backVol);

	//크로스 페이드 종료
	fadeTimer += dt;
	if (fadeTimer >= fadeDuration)
	{
		fadeTimer = 0.f;
		bgm[backBGMIndex].stop();
		isFading = false;
	}

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
	else if (value > 100.0f)
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
	float preBgmVol = bgmVolume;
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


	if (!isFading)
	{
		bgm[frontBGMIndex].setVolume(bgmVolume);
		bgm[backBGMIndex].setVolume(bgmVolume);
	}
	else
	{
		float frontVol = bgm[frontBGMIndex].getVolume() * (preBgmVol == 0.f ? 0.f : (bgmVolume / preBgmVol));
		bgm[frontBGMIndex].setVolume(frontVol >= 100.f ? 100.f : frontVol);
		frontMixingSpeed *= preBgmVol == 0.f ? 0.f : (bgmVolume / preBgmVol);

		float backVol = bgm[backBGMIndex].getVolume() * (preBgmVol == 0.f ? 0.f : (bgmVolume / preBgmVol));
		bgm[backBGMIndex].setVolume(backVol >= 100.f ? 100.f : backVol);
		backMixingSpeed *= preBgmVol == 0.f ? 0.f : (bgmVolume / preBgmVol);

	}

}

void SoundMgr::UpVolumeBGM(float value)
{
	SetVolumeBGM(bgmVolume + value);
}

void SoundMgr::DownVolumeBGM(float value)
{
	SetVolumeBGM(bgmVolume - value);
}
