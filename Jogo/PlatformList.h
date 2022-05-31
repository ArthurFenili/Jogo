#pragma once

#include "List.h"
#include "Platform.h"

class PlatformList
{
private:
	List<Platform> platformList;  // Lista de objetos da classe Platform

public:
	PlatformList();
	~PlatformList();

	// Insere o objeto da classe Platform na lista
	void addPlatform(Platform* platform) { this->platformList.push(platform); }

	// Retorna o tamanho da lista
	int getSize() { return platformList.getSize(); }

	Platform* operator[](int index) { return this->platformList[index]; }

	// Remove todos os elementos da lista
	void clearList() { this->platformList.clear(); }
};

