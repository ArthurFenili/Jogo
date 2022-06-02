#pragma once

#include "List.h"
#include "Entity.h"

class EntityList
{
private:
	List<Entity> entityList;

public:
	EntityList();
	~EntityList();

	void addEntity(Entity* platform) { this->entityList.push(platform); }

	// Retorna o tamanho da lista
	int getSize() { return entityList.getSize(); }

	Entity* operator[](int index) { return this->entityList[index]; }

	// Remove todos os elementos da lista
	void clearList() { this->entityList.clear(); }

	Entity* pop(Entity* entity) { return this->entityList.pop(entity); }
};

