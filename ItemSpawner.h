#pragma once
#include "Spawner.h"
#include "Item2.h"


class ItemSpawner : public Spawner
{
protected:
	std::vector<Item2::Types> itemTypes;


public:
	ItemSpawner(const std::string& name = "ItemSpawner");
	~ItemSpawner()override = default;

	void Reset() override;

	GameObject* Create() override;
};

