#pragma once
#include "GameObject.h"

class Enemy : public GameObject
{
public:
	Enemy();
	virtual ~Enemy();

protected:
	void move(float deltaTime);
};