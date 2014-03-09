#ifndef BLOCK_H
#define BLOCK_H

#include "GameObject.h"
#include "Colours.h"

class Block : public GameObject
{
public:
	Block();
	~Block();

	void SetLives(int);
	int GetLives();
	void LoseLife();

	void SetImmunity(bool);
	bool IsImmune();

private:

	int lives;
	bool immune;
};

#endif