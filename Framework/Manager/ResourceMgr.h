#pragma once
#include "Singleton.h"
struct AnimationClip;

template<typename T>
class ResourceMgr : public Singleton<ResourceMgr<T>>
{
	friend Singleton<ResourceMgr<T>>;

private:
	std::unordered_map<std::string, T*> resources;


	ResourceMgr() = default;
	virtual ~ResourceMgr()
	{
		UnloadAll();
	}

public:
	static T Empty;

	bool Load(const std::string& filePath)
	{
		T* res = new T();

		if (resources.find(filePath) != resources.end())
			return false;

		bool success = res->loadFromFile(filePath);
		if (success)
		{

			resources.insert({ filePath, res });
		}
		return success;
	}

	void UnloadAll()
	{
		for (const auto& pair : resources)
		{
			delete pair.second;
		}
		resources.clear();
	}

	bool Unload(const std::string& filePath)
	{
		auto it = resources.find(filePath);
		if (it == resources.end())
			return false;

		delete it->second;
		resources.erase(it);
		return true;
	}

	T& Get(const std::string& filePath, bool load = true)
	{
		//std::string newPath;
		//if (typeid(T).name() == typeid(AnimationClip).name())
		//{
		//	newPath = "data/" + filePath + ".csv";
		//}

		auto it = resources.find(filePath);
		if (it != resources.end())
			return *(it->second);

		if (!load || !Load(filePath))
		{
			return Empty;
		}
		return *(resources.find(filePath)->second);
	}

	ResourceMgr(const ResourceMgr&) = delete;
	ResourceMgr(ResourceMgr&&) = delete;

	ResourceMgr& operator=(const ResourceMgr&) = delete;
	ResourceMgr& operator=(ResourceMgr&&) = delete;
};

template<typename T>
T ResourceMgr<T>::Empty;

#define RES_MGR_TEXTURE (ResourceMgr<sf::Texture>::Instance())
#define RES_MGR_FONT (ResourceMgr<sf::Font>::Instance())
#define RES_MGR_SOUND_BUFFER (ResourceMgr<sf::SoundBuffer>::Instance())
#define RES_MGR_ANI_CLIP (ResourceMgr<AnimationClip>::Instance())