#include "Game.h"
#include "FmodWrapper.h"
Game::Game()
{
}

Game::~Game()
{
	delete updateTimer;


	PassThrough.UnLoad();
	headMesh.Unload();
	audioMesh.Unload();
	//...
}

void Game::initializeGame()
{
	isLinear = false;
	isBopping = false;
	drum.setModeLinear(isLinear); //Sets the current rolloff to logarithmic 
	updateTimer = new Timer();
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

	drum.Load("media/Home.mp3");
	drumChannel = drum.Play(true);
		
	headMesh.LoadFromFile("./Assets/Models/Monkey.obj");
	audioMesh.LoadFromFile("./Assets/Models/Monkey.obj");

	headMesh.addChild(&audioMesh);

	if (!PassThrough.Load("./Assets/Shaders/Model.vert", "./Assets/Shaders/Model.frag"))
	{
		std::cout << "Shaders failed to initialize. \n" << std::endl;
		system("pause");
		exit(0);
	}


	if (!PassThrough2.Load("./Assets/Shaders/Model2.vert", "./Assets/Shaders/Model2.frag"))
	{
		std::cout << "Shaders failed to initialize. \n" << std::endl;
		system("pause");
		exit(0);
	}

	
	headMesh.setRotationAngleY(45.f);
	audioTransform.Scale(.5f);
	audioTransform.Translate(vec3(0.0f,3.0f,0.0f));
	CameraTransform.RotateX(-45.0f);
	CameraTransform.RotateY(45.0f);
	//CameraTransform.RotateZ(45.0f);
	CameraTransform.Translate(vec3(5.0f,6.0f,5.0f));
	CameraProjection = mat4::PerspectiveProjection(60.0f,(float)WINDOW_WIDTH/(float)WINDOW_HEIGHT,1.0f, 10000.0f);
	//...
}

void Game::update()
{
	// update our clock so we have the delta time since the last update
	updateTimer->tick();

	float deltaTime = updateTimer->getElapsedTimeSeconds();
	TotalGameTime += deltaTime;
	audioMesh.setPosition(vec3(3.0f, 3.0f, 3.0f)*vec3(cos(TotalGameTime),1,sin(TotalGameTime)));
	soundPos = { audioMesh.getPosition().x, audioMesh.getPosition().y, audioMesh.getPosition().z -5 };
	//audioTransform.Translate(vec3(0.f+deltaTime,0.f,0.f));
	//...

	if (isBopping)
	{
		
		headMesh.update(deltaTime);
		drum.SetPosition(drumChannel, soundPos);
	}
	drum.engine.Update();
	


	postProcessing();
}

void Game::draw(Mesh* meshToDraw)
{
	glBindVertexArray(meshToDraw->VAO);
	glDrawArrays(GL_TRIANGLES, 0, meshToDraw->GetNumVertices());
	glBindVertexArray(0);

}

void Game::postProcessing()
{
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	PassThrough.Bind();
	PassThrough.SendUniformMat4("uModel", headMesh.getLocalToWorldMatrix().data, true);
	PassThrough.SendUniformMat4("uView", CameraTransform.GetInverse().data, true);
	PassThrough.SendUniformMat4("uProj", CameraProjection.data, true);
	PassThrough.SendUniform("u_time", TotalGameTime);

	draw(&headMesh);

	PassThrough.UnBind();


	PassThrough2.Bind();
	PassThrough2.SendUniformMat4("uModel", audioMesh.getLocalToWorldMatrix().data, true);
	PassThrough2.SendUniformMat4("uView", CameraTransform.GetInverse().data, true);
	PassThrough2.SendUniformMat4("uProj", CameraProjection.data, true);
	PassThrough2.SendUniform("u_time", TotalGameTime);
	
	draw(&audioMesh);

	PassThrough2.UnBind();
	glutSwapBuffers();

}

void Game::keyboardDown(unsigned char key, int mouseX, int mouseY)
{
	switch(key)
	{
	case 27: // the escape key
	case 'q': // the 'q' key
		exit(1);
		break;
	}
}

void Game::keyboardUp(unsigned char key, int mouseX, int mouseY)
{
	switch(key)
	{
	case 32: // the space bar
		break;
	case 27: // the escape key
	case 'q': // the 'q' key
		exit(1);
		break;
	case 'r':
		if (!isLinear)
		{
			isLinear = true; //if not linear, set to linear
			drum.setModeLinear(isLinear); //Sets mode to linear rolloff
		}

		else
		{
			isLinear = false; //if  linear, set to logarithmic
			drum.setModeLinear(isLinear); // 
		}
	case 'p':
		if (!isBopping) // If the audio source is not moving
			isBopping = true;
		else
		{
			isBopping = false;
		}

	}
}

void Game::mouseClicked(int button, int state, int x, int y)
{
	if(state == GLUT_DOWN) 
	{
		switch(button)
		{
		case GLUT_LEFT_BUTTON:

			break;
		case GLUT_RIGHT_BUTTON:
		
			break;
		case GLUT_MIDDLE_BUTTON:

			break;
		}
	}
	else
	{

	}
}

/*
 * mouseMoved(x,y)
 * - this occurs only when the mouse is pressed down
 *   and the mouse has moved.  you are given the x,y locations
 *   in window coordinates (from the top left corner) and thus 
 *   must be converted to screen coordinates using the screen to window pixels ratio
 *   and the y must be flipped to make the bottom left corner the origin.
 */
void Game::mouseMoved(int x, int y)
{
}
