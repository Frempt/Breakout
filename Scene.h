#ifndef SCENE_H
#define SCENE_H

#include "GameObject.h"
#include "Block.h"
#include "Camera.h"
#include "Vector3.h"
#include "Colours.h"
#include <fstream>
#include <list>

using namespace::std;

class Scene
{
public:

	Scene();
	~Scene();

	void LoadLevel();

	void RenderScene();
	void Update(float);
	void Controls(bool[]);

	void RenderObject(GameObject);
	void RenderObject(GameObject, Vector3);

	void DrawCube();

private:
	GameObject player;
	GameObject ball;

	GameObject leftWall;
	GameObject rightWall;
	GameObject floor;
	GameObject ceiling;
	GameObject backWall;

	std::list<Block> blocks;
	Vector3 blockPositionsTop[15];
	Vector3 blockPositionsMiddle[15];
	Vector3 blockPositionsBottom[15];

	Camera camera;
};

#endif