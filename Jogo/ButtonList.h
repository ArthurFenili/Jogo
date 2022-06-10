#pragma once

#include "List.h"
#include "Button.h"

class ButtonList
{
private:
	List<Button> buttonList;
public:
	ButtonList();
	~ButtonList();

	void addButton(Button* button) { this->buttonList.push(button); }

	// Retorna o tamanho da lista
	int getSize() { return buttonList.getSize(); }

	Button* operator[](int index) { return this->buttonList[index]; }

	// Remove todos os elementos da lista
	void clearList() { this->buttonList.clear(); }

	Button* pop(Button* button) { return this->buttonList.pop(button); }
};

