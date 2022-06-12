#include "InputManager.h"

InputManager::InputManager()
{
}

InputManager::~InputManager()
{
}
std::string InputManager::readString(GraphicsManager* graphicsManager)
{
	saved = false;
	while (!saved) {
		while (graphicsManager->pollEvent(&ev))
		{
			if (ev.type == sf::Event::TextEntered)
			{
				if (ev.text.unicode < 128) {
					strtmp += static_cast<char>(ev.text.unicode);
				}
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter)) {
				saved = true;
			}
		}
	}
	return strtmp;
}