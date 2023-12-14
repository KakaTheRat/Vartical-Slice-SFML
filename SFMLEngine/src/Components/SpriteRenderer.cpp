#include "Components/SpriteRenderer.h"
#include "SFML/Graphics/Texture.hpp"
#include <iostream>

SpriteRenderer::SpriteRenderer() {
	sprite = new sf::Sprite();
	texture = new sf::Texture();
	sprite->setTextureRect(sf::IntRect(animation.x * texture_size_x + offset_x, animation.y * texture_size_y + offset_y, texture_size_x, texture_size_y));
	//sprite->setOrigin(sprite->getLocalBounds().width / 2.f, sprite->getLocalBounds().height / 2.f);
}

SpriteRenderer::~SpriteRenderer() {
	delete sprite;
	delete texture;
	sprite = nullptr;
	texture = nullptr;
}

void SpriteRenderer::LoadSprite(std::string _name) {
	texture = new sf::Texture;
		if (!texture->loadFromFile("../Assets/Sprites/" + _name)) {	
	}

	sprite->setTexture(*texture);
}

void SpriteRenderer::SetOffset(const Maths::Vector2i _offset) {
	offset_x = _offset.x;
	offset_y = _offset.y;
	sprite->setTextureRect(sf::IntRect(animation.x * texture_size_x + offset_x, animation.y * texture_size_y + offset_y, texture_size_x, texture_size_y));
}

void SpriteRenderer::Update(float _delta_time) {
	if (autoIncrement)
		IncrementCount(_delta_time);

	if (direction != lastDirection) {
		animation = beginTexture;
		//std::cout << "new Direction" << std::endl;
	}
	if (count > anim_speed) {
		animation.x++;
		if (animation.x * texture_size_x >= texture->getSize().x) {
			animation.x = 0;
			animation.y++;
			
		}
		if (animation.x == endTexture.x && animation.y == endTexture.y) {
			
			animation = beginTexture;
		}
		sprite->setTextureRect(sf::IntRect(animation.x * texture_size_x + offset_x, animation.y * texture_size_y + offset_y, texture_size_x, texture_size_y));
		count = 0;
	}
	lastDirection = direction;
}

void SpriteRenderer::Render(sf::RenderWindow* _window)
{
	ARendererComponent::Render(_window);

	const GameObject* owner = GetOwner();

	const Maths::Vector2<float> position = owner->GetPosition();
	sprite->setPosition(position.x, position.y);
	sprite->setRotation(owner->GetRotation());

	_window->draw(*sprite);
}
