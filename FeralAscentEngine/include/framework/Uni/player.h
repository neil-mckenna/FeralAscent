//player.h
#pragma once
#include "framework/Uni/entity.h"


class Player : public Entity {
private:
	float _speed;

public:
	void Update(double dt) override;
	Player();
	void Render(sf::RenderWindow& window) const override;
};



