#ifndef COLOURS_H
#define COLOURS_H

#include "Vector3.h"
#include <random>

class Colours
{
public:

	static Vector3 RandomColour()
	{
		int rng = rand() % numberOfColours + 1;

		switch (rng)
		{
		case 1:
			return Red();

			case 2:
			return Green();

			case 3:
			return Blue();

			case 4:
			return Yellow();

			case 5:
			return Cyan();

			case 6:
			return White();

			case 7:
			return Black();

			case 8:
			return Pink();

			case 9:
			return Orange();

			default:
				return Red();
		}
	}

	static Vector3 Red()
	{
		Vector3 returnVal = Vector3(1.0f, 0.0f, 0.0f);
		return returnVal;
	}

	static Vector3 Green()
	{
		Vector3 returnVal = Vector3(0.0f, 1.0f, 0.0f);
		return returnVal;
	}

	static Vector3 Blue()
	{
		Vector3 returnVal = Vector3(0.0f, 0.0f, 1.0f);
		return returnVal;
	}

	static Vector3 Yellow()
	{
		Vector3 returnVal = Vector3(1.0f, 1.0f, 0.0f);
		return returnVal;
	}

	static Vector3 White()
	{
		Vector3 returnVal = Vector3(1.0f, 1.0f, 1.0f);
		return returnVal;
	}

	static Vector3 Black()
	{
		Vector3 returnVal = Vector3(0.0f, 0.0f, 0.0f);
		return returnVal;
	}

	static Vector3 Cyan()
	{
		Vector3 returnVal = Vector3(0.0f, 1.0f, 1.0f);
		return returnVal;
	}

	static Vector3 Pink()
	{
		Vector3 returnVal = Vector3(1.0f, 0.0f, 1.0f);
		return returnVal;
	}

	static Vector3 Orange()
	{
		Vector3 returnVal = Vector3(1.0f, 0.5f, 0.0f);
		return returnVal;
	}

private:

	Colours();
	~Colours();

	static const int numberOfColours = 9;
};

#endif