#include "Collider.h"

Collider::Collider(sf::RectangleShape* body)
{
	this->body = body;
}

Collider::~Collider()
{
}

// Retorna true caso ocorra colisão entre o body do Collider que chamou a função (this) e o body do Collider "other"
bool Collider::isColliding(Collider* other, sf::Vector2f* direction)
{
	/* 

	Método de detecção de Colisões do tipo AABB
	Inspirado pelo vídeo do youtuber Hilze Vonck
	Link do vídeo: https://www.youtube.com/watch?v=l2iCYCLi6MU
	
	Simplificando a explicação de como é realizado o cálculo para descobrir se há colisão entre dois corpos, calculamos uma reta que parte
	do centro dos dois corpos a partir de 2 variáveis: deltaX e deltaY, as quais representam a diferença das posições
	dos dois corpos nas coordenadas X e Y.

	A partir dessas duas variáveis, calculamos a interseção de um objeto no outro em X e em Y. Para isso, subtraímos o valor absoluto
	de delta com o valor da soma da metade dos comprimentos do objeto.

	Caso o valor das interseções sejam negativos, isso indica que há colisão.
	
	*/

	/* 
	
	O vetor direction indica em qual direção está ocorrendo a colisão. Por exemplo:
	
	Se direction->x é igual a 1.0f, isso significa que a colisão está acontecendo para a direita do objeto.

	*/

	sf::Vector2f otherPosition = other->getPosition();
	sf::Vector2f otherHalfSize = other->getHalfSize();
	sf::Vector2f thisPosition = this->getPosition();
	sf::Vector2f thisHalfSize = this->getHalfSize();

	float deltaX = otherPosition.x - thisPosition.x;
	float deltaY = otherPosition.y - thisPosition.y;

	float intersectX = abs(deltaX) - (otherHalfSize.x + thisHalfSize.x);
	float intersectY = abs(deltaY) - (otherHalfSize.y + thisHalfSize.y);
		

	if (intersectX < 0.f && intersectY < 0.f) {

		if (intersectX > intersectY) {
			if (deltaX > 0.f) {
				this->move(0.f, 0.f);
				other->move(-intersectX, 0.f);

				direction->x = 1.0f;
				direction->y = 0.0f;
			}
			else {
				this->move(0.f, 0.f);
				other->move(intersectX, 0.f);

				direction->x = -1.0f;
				direction->y = 0.0f;
			}
		}
		else {
			if (deltaY > 0.f) {
				this->move(0.f, 0.f);
				other->move(0.f, -intersectY);

				direction->x = 0.0f;
				direction->y = 1.0f;
			}
			else {
				this->move(0.f, 0.f);
				other->move(0.f, intersectY);

				direction->x = 0.0f;
				direction->y = -1.0f;
			}
		}
		
		return true;
	}
		
	return false;
}
