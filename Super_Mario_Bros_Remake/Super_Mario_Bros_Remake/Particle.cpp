#include "Particle.h"

Particle::Particle(std::string spriteSheetPath, sf::Vector2f pos, sf::Vector2f vel, bool isFacingLeft)
{
	objectType = ObjectType::Particle;
	texture.loadFromFile(spriteSheetPath);
	sprite.setTexture(texture);

	position = pos;
	velocity = vel;
	facingLeft = isFacingLeft;

	sprite.setPosition(position);
	if (facingLeft)
	{
		sprite.setOrigin({ sprite.getLocalBounds().width, 0 });
		sprite.scale(-1, 1);
	}
	checkCollisions = false;
}

Particle::~Particle()
{
}

void Particle::update(float deltaTime)
{
	currentLifetime += deltaTime;
	if (currentLifetime >= maxLifetime)
	{
		alive = false;
	}

	velocity.y += GRAVITY * deltaTime;
	position = position + (velocity * deltaTime);
	sprite.setPosition(position);
}

void Particle::draw(sf::RenderWindow* window)
{
	window->draw(sprite);
}

void Particle::hit()
{
}