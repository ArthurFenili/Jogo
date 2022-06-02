#include "EntitiesList.h"

EntitiesList::EntitiesList()
{
}

EntitiesList::~EntitiesList()
{
	this->clearList();
}

void EntitiesList::addEntity(Entity* pE)
{
	if (pE)
		this->entList.push(pE);
	else
		std::cout << "ERROR! pE is NULL" << std::endl;
}

Entity* EntitiesList::removeEntity(Entity* pE)
{
	if (pE)
		return this->entList.pop(pE);
	else {
		std::cout << "ERROR! pE is NULL" << std::endl;
		return NULL;
	}
}

Entity* EntitiesList::operator[](int index)
{
	return this->entList[index];
}

void EntitiesList::clearList()
{
	this->entList.clear();
}
