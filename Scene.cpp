#include "Scene.h"

Scene::Scene()
{
	//setup camera object
	camera = Camera();
	camera.position = Vector3(0.0f, 0.0f, -20.0f);

	//setup back wall object
	backWall = GameObject();
	backWall.SetScale(Vector3(20.0f, 20.0f, 0.5f));
	backWall.SetPosition(Vector3(0.0f, 0.0f, 5.0f));
	backWall.SetDirection(Vector3(0.0f, 0.0f, 0.0f));
	backWall.SetVelocity(0.0f);
	backWall.SetColour(Vector3(0.5f, 0.5f, 0.5f));

	//setup left wall object
	leftWall = GameObject();
	leftWall.SetScale(Vector3(0.5f, 20.0f, 0.5f));
	leftWall.Translate(Vector3(11.0f, 0.0f, 0.0f));
	leftWall.SetDirection(Vector3(0.0f, 0.0f, 0.0f));
	leftWall.SetVelocity(0.0f);

	//setup right wall object
	rightWall = GameObject();
	rightWall.SetScale(Vector3(0.5f, 20.0f, 0.5f));
	rightWall.Translate(Vector3(-11.0f, 0.0f, 0.0f));
	rightWall.SetDirection(Vector3(0.0f, 0.0f, 0.0f));
	rightWall.SetVelocity(0.0f);

	//setup floor object
	floor = GameObject();
	floor.SetScale(Vector3(20.0f, 0.5f, 0.5f));
	floor.Translate(Vector3(0.0f, -8.0f, 0.0f));
	floor.SetDirection(Vector3(0.0f, 0.0f, 0.0f));
	floor.SetVelocity(0.0f);

	//setup ceiling object
	ceiling = GameObject();
	ceiling.SetScale(Vector3(20.f, 0.5f, 0.5f));
	ceiling.Translate(Vector3(0.0f, 8.0f, 0.0f));
	ceiling.SetDirection(Vector3(0.0f, 0.0f, 0.0f));
	ceiling.SetVelocity(0.0f);

	//setup player (paddle) object
	player = GameObject();
	player.SetScale(Vector3(1.5f, 0.5f, 0.5f));
	player.Translate(Vector3(0.0f, -6.0f, 0.0f));
	player.SetDirection(Vector3(0.0f, 0.0f, 0.0f));
	player.SetVelocity(0.2f);
	player.SetColour(Colours::Green());

	//setup ball object
	ball = GameObject();
	ball.SetScale(Vector3(0.5f, 0.5f, 0.5f));
	ball.Translate(Vector3(0.0f, -2.0f, 0.0f));
	ball.SetDirection(Vector3(1.0f, -1.0f, 0.0f));
	ball.SetVelocity(0.1f);
	ball.SetColour(Colours::Blue());

	//create list of blocks
	blocks = list<Block>();
	
	//load the level data from the file
	LoadLevel();
}

Scene::~Scene()
{
}

void Scene::LoadLevel()
{
	//create a file stream from the level data file
	fstream f = fstream("LevelData.txt");

	//if data is present
	if(f)
	{
		//get the length of the file
		f.seekg(0, f.end);
		int length = f.tellg();
		f.seekg(0, f.beg);

		//create a buffer of the file's length
		char* buffer = new char[length];

		//fill the buffer with file data
		f.read(buffer, length);

		//create a scale vector to use for all blocks
		Vector3 blockScale = Vector3(1.5f, 0.5f, 0.5f);

		//iterate through each character in the level file
		for(int i = 0; i < length; i++)
		{
			//if the character is not 0
			if(buffer[i] != '0')
			{
				//create a new block object
				Block block = Block();

				//set the block's scale
				block.SetScale(blockScale);

				//sets the amount of lives
				block.SetLives(buffer[i] - '0');

				//if the block has more than one life, it is orange
				//if not, it is yellow
				if(block.GetLives() > 1)
				{
					block.SetColour(Colours::Orange());
				}
				else
				{
					block.SetColour(Colours::Yellow());
				}

				//position vector
				//x position is firstX - (index*(numberOfBlocks/3))
				//y position is 3.0f, 0.0f, or -3.0f depending on row
				//z position is 0.0f
				Vector3 pos;

				//first row of blocks
				if(i < length/3)
				{
					pos = Vector3(10.0f - float(i)*(length/3), 3.0f, 0.0f);
				}
				//second row of blocks
				else if(i < (length/3) * 2)
				{
					pos = Vector3(10.0f - float(i-(length/3))*(length/3), 0.0f, 0.0f);
				}
				//third row of blocks
				else
				{
					pos = Vector3(10.0f - float(i-((length/3)*2))*(length/3), -3.0f, 0.0f);
				}

				//set block's position
				block.SetPosition(pos);

				//add the block to the list
				blocks.push_back(block);
			}
		}

		//cleanup
		delete[] buffer;
	}
}

void Scene::RenderScene()
{
	//clear the screen and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	//load identity matrix
	glLoadIdentity();

	//create the camera
	//eye, look at, up
	gluLookAt(camera.position.x, camera.position.y, camera.position.z, 0.0f, 0.0f, 0.0f, 0, 1, 0);

	//push this matrix to the stack
	glPushMatrix();

	//render all game objects
	RenderObject(backWall);
	RenderObject(player);
	RenderObject(ball);
	RenderObject(leftWall);
	RenderObject(rightWall);
	RenderObject(floor);
	RenderObject(ceiling);

	list<Block>::iterator i;
	for(i = blocks.begin(); i != blocks.end(); ++i)
	{
		RenderObject(*i);
	}
}

void Scene::Update(float frameTime)
{
	//update all game objects
	ball.Update(frameTime);
	player.Update(frameTime);
	ceiling.Update(frameTime);
	floor.Update(frameTime);
	leftWall.Update(frameTime);
	rightWall.Update(frameTime);
	backWall.Update(frameTime);

	//if there are blocks in the scene
	if(!blocks.empty())
	{
		//create an iterator
		list<Block>::iterator i;

		//iterate through the list of blocks
		for(i = blocks.begin(); i != blocks.end();)
		{
			//update block
			i->Update(frameTime);

			//if the ball is colliding with the block
			if(ball.CollidesWith(*i))
			{
				//if the block is not immune (a.k.a collision has not yet been entered)
				if(!i->IsImmune())
				{
					//if the ball is above the block
					if(ball.GetTranslation().y >= i->GetTranslation().y)
					{
						//direction is up
						ball.SetDirection(Vector3(ball.GetDirection().x, 1.0f, 0.0f));
					}
					//if the ball is below the block
					else
					{
						//direction is down
						ball.SetDirection(Vector3(ball.GetDirection().x, -1.0f, 0.0f));
					}

					//if the block's lives are greater than 1
					if(i->GetLives() > 1)
					{
						//set the ball to a random colour
						ball.SetColour(Colours::RandomColour());
					}

					//remove a life from the block
					i->LoseLife();
					
					//make the block immune (a.k.a collision has already been entered)
					i->SetImmunity(true);
				}
			}
			//if the ball does not collide with the block
			else
			{
				//make the block not immune (a.k.a collision has not yet been entered)
				i->SetImmunity(false);
			}

			//if block is out of lives
			if(i->GetLives() <= 0)
			{
				//remove it from the list
				i = blocks.erase(i);
			}
			else
			{
				//increment iterator
				i++;
			}
		}
	}

	//if the ball collides with the player
	if(ball.CollidesWith(player))
	{
		//if player is moving
		if(player.GetDirection().x != 0)
		{
			//X direction is player's direction
			//Y direction is up
			ball.SetDirection(Vector3(player.GetDirection().x, 1.0f, 0.0f));
		}
		//if player is stationary
		else
		{
			//X direction is current ball direction
			//Y direction is up
			ball.SetDirection(Vector3(ball.GetDirection().x, 1.0f, 0.0f));
		}
	}

	//if the ball collides with the ceiling
	if(ball.CollidesWith(ceiling))
	{
		//direction is down
		ball.SetDirection(Vector3(ball.GetDirection().x, -1.0f, 0.0f));
	}

	//if the ball collides with the floor
	if(ball.CollidesWith(floor))
	{
		//direction is up
		ball.SetDirection(Vector3(ball.GetDirection().x, 1.0f, 0.0f));
	}

	//if the ball collides with the right wall
	if(ball.CollidesWith(rightWall))
	{
		//direction is left
		ball.SetDirection(Vector3(1.0f, ball.GetDirection().y, 0.0f));
	}

	//if the ball collides with the left wall
	if(ball.CollidesWith(leftWall))
	{
		//direction is right
		ball.SetDirection(Vector3(-1.0f, ball.GetDirection().y, 0.0f));
	}
}

void Scene::Controls(bool keys[])
{
	//set the player direction to a zero vector
	player.SetDirection(Vector3(0.0f, 0.0f, 0.0f));

	//if A is pressed
	if(keys['A'])
	{
		//if the player is not touching the left wall
		if(!player.CollidesWith(leftWall))
		{
			//direction is left
			player.SetDirection(Vector3(1.0f, 0.0f, 0.0f));
		}
	}
	//if the D key is pressed
	else if(keys['D'])
	{
		//if the player is not touching the right wall
		if(!player.CollidesWith(rightWall))
		{
			//direction is right
			player.SetDirection(Vector3(-1.0f, 0.0f, 0.0f));
		}
	}
}


void Scene::RenderObject(GameObject obj)
{
	//set the colour to the objects colour
	Vector3 rgb = obj.GetColour();
	glColor3f(rgb.x, rgb.y, rgb.z);

	//translate and scale the object
	//NOTE: OpenGL handles matrix transformations in reverse order specified
	glTranslatef(obj.GetTranslation().x, obj.GetTranslation().y, obj.GetTranslation().z);
	glScalef(obj.GetScale().x, obj.GetScale().y, obj.GetScale().z);

	//draw the mesh
	DrawCube();

	//return to the previous matrix
	glPopMatrix();
	glPushMatrix();
}

void Scene::RenderObject(GameObject obj, Vector3 rgb)
{
	//set the colour to the specified colour
	glColor3f(rgb.x, rgb.y, rgb.z);

	//translate and scale the object
	//NOTE: OpenGL handles matrix transformations in reverse order specified
	glTranslatef(obj.GetTranslation().x, obj.GetTranslation().y, obj.GetTranslation().z);
	glScalef(obj.GetScale().x, obj.GetScale().y, obj.GetScale().z);

	//draw the mesh
	DrawCube();

	//return to the previous matrix
	glPopMatrix();
	glPushMatrix();
}

void Scene::DrawCube()
{
	//cube indices
	GLubyte CUBE_INDICES[]={1, 0, 3, 2,      //front
		4, 7, 6, 5,	     //back   
		8, 12, 15, 11,   //left 		
		9, 10, 14, 13,   //right
		19, 23, 22, 18,  //up
		16, 20, 21, 17,};//down

	//cube vertices
	float CUBE_VERTS[] = {	-1.0, -1.0, -1.0,			// Vertex #0
		1.0, -1.0, -1.0,			// Vertex #1
		1.0,  1.0, -1.0,			// Vertex #2
		-1.0,  1.0, -1.0,			// Vertex #3
		-1.0, -1.0,  1.0,			// Vertex #4
		1.0, -1.0,  1.0,			// Vertex #5
		1.0,  1.0,  1.0,			// Vertex #6
		-1.0,  1.0,  1.0,			// Vertex #7
		-1.0, -1.0, -1.0,			// Vertex #8
		1.0, -1.0, -1.0,			// Vertex #9
		1.0,  1.0, -1.0,			// Vertex #10
		-1.0,  1.0, -1.0,			// Vertex #11
		-1.0, -1.0,  1.0,			// Vertex #12
		1.0, -1.0,  1.0,			// Vertex #13
		1.0,  1.0,  1.0,			// Vertex #14
		-1.0,  1.0,  1.0,			// Vertex #15
		-1.0, -1.0, -1.0,			// Vertex #16
		1.0, -1.0, -1.0,			// Vertex #17
		1.0,  1.0, -1.0,			// Vertex #18
		-1.0,  1.0, -1.0,			// Vertex #19
		-1.0, -1.0,  1.0,			// Vertex #20
		1.0, -1.0,  1.0,			// Vertex #21
		1.0,  1.0,  1.0,			// Vertex #22
		-1.0,  1.0,  1.0};			// Vertex #23

	//cube normals
	float CUBE_NORMALS[] = { 0.5, 0.5, -0.5,			//0
		0.5, 0.5, -0.5,			//1
		0.5,  0.5, -0.5,			//2
		0.5,  0.5, -0.5,			//3
		0.5, 0.5, 0.5,			    //4
		0.5, 0.5, 0.5,			//5
		0.5,  0.5, 0.5,			//6
		0.5,  0.5, 0.5,			//7
		-0.5, 0.5, 0.5,			//8
		0.5, 0.5, 0.5,			//9
		0.5,  0.5, 0.5,			//10
		-0.5,  0.5, 0.5,			//11
		-0.5, 0.5, 0.5,			//12
		0.5, 0.5, 0.5,			//13
		0.5,  0.5, 0.5,			//14
		-0.5,  0.5, 0.5,			//15
		0.5, -0.5, 0.5,			//16
		0.5, -0.5, 0.5,			//17
		0.5,  0.5, 0.5,			//18
		0.5,  0.5, 0.5,			//19
		0.5, -0.5, 0.5,			//20
		0.5, -0.5, 0.5,			//21
		0.5,  0.5, 0.5,			//22
		0.5,  0.5, 0.5};			//23

	//cube texture coordinates
	float CUBE_T_COORDS[]= {1.0, 1.0, 			//0
		0.0, 1.0, 			//1
		0.0, 0.0, 			//2
		1.0, 0.0, 			//3
		1.0, 1.0, 			//4
		0.0, 1.0,			//5
		0.0, 0.0,			//6
		1.0, 0.0,			//7
		0.0, 1.0, 			//8
		0.0, 1.0, 			//9
		1.0, 1.0, 			//10
		1.0, 1.0, 			//11
		0.0, 0.0, 			//12
		1.0, 1.0,			//13
		1.0, 0.0,			//14
		1.0, 0.0,			//15
		0.0, 1.0, 			//16
		1.0, 1.0, 			//17
		1.0, 1.0, 			//18
		0.0, 1.0, 			//19
		0.0, 0.0, 			//20
		1.0, 0.0,			//21
		1.0, 0.0,			//22
		0.0, 0.0};			//23
	
	//get ready to draw
	glEnableClientState(GL_INDEX_ARRAY);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	//set the arrays
	glIndexPointer	 (GL_INT,	0, CUBE_INDICES);
	glVertexPointer	 (3, GL_FLOAT, 0, CUBE_VERTS);
	glNormalPointer	 (GL_FLOAT, 0, CUBE_NORMALS);
	glTexCoordPointer(2, GL_FLOAT, 0, CUBE_T_COORDS);

	//draw the cube
	glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, CUBE_INDICES);
}

