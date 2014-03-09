#include "Block.h"

Block::Block()
{
	//give the vectors initial values
	position = Vector3(0.0f, 0.0f, 0.0f);
	scale = Vector3(1.0f, 1.0f, 1.0f);
	rotation = Vector3(0.0f, 0.0f, 0.0f);

	colour = Colours::White();

	//set the lives to 1
	lives = 1;

	//set immunity to false
	immune = false;
}

Block::~Block()
{
}

void Block::SetLives(int nLives)
{
	lives = nLives;
}

int Block::GetLives()
{
	return lives;
}

void Block::LoseLife()
{
	lives--;

	//if the block only has 1 life
	if(lives == 1)
	{
		//colour is yellow
		colour = Colours::Yellow();
	}
}

void Block::SetImmunity(bool nImm)
{
	immune = nImm;
}

bool Block::IsImmune()
{
	return immune;
}