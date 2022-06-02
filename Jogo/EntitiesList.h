#pragma once
#include "List.h"
#include "Entity.h"

class EntitiesList
{
private:
	List<Entity> entList;
public:

	EntitiesList();
	~EntitiesList();

	void addEntity(Entity* pE);
	Entity* removeEntity(Entity* pE);

	int getSize() { return entList.getSize(); }

	Entity* operator[](int index);

	void clearList();
};

