#include <SFML/Graphics.hpp>
#include <SFML\OpenGL.hpp>
#include "Cube.h"
int main(int argc, char *argv)
{
	sf::RenderWindow window(sf::VideoMode(400, 400), "Template", sf::Style::Titlebar | sf::Style::Close);


	sf::Image dogeImage;
	dogeImage.loadFromFile("res/elefantitos.jpg");
	sf::Image ladrillos;
	ladrillos.loadFromFile("res/ladrillos.jpg");

	// Tell OpenGL that we want to use 2D textures. 
	glEnable(GL_TEXTURE_2D);

	// Tell OpenGL that we want to use lighting.
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);


	/* Tell OpenGL that we want to test the depth of each vertex to make sure that things that
	* are closer appear closer. */
	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);
	glDepthFunc(GL_LESS);

	glEnable(GL_CULL_FACE);

	glFrontFace(GL_CW);
	// Generate a texture in OpenGL, and retrieve its ID so that we can access it.
	GLuint dogeTextureID;
	glGenTextures(1, &dogeTextureID);
	
	/* 'Bind' our texture to the active texture space so that all of our operations
	* are done to it. */
	glBindTexture(GL_TEXTURE_2D, dogeTextureID);

	glTexImage2D(GL_TEXTURE_2D, // specifies that we're working on the active texture.
		0, // ignore.
		GL_RGBA, // specifies that making a texture that has RGBA data.
		dogeImage.getSize().x, // specify the width of the texture.
		dogeImage.getSize().y, // specify the height of the texture.
		0, // no border
		GL_RGBA, // specifies that we're working with an image that has RGBA data.
		GL_UNSIGNED_BYTE, // specifies the format of the RGBA data (in this case, everything is 0-255)
		dogeImage.getPixelsPtr() // specifies the actual image data.
		);
	

	

	/* Telling OpenGL that we want our active texture to magnify and minimize in
	* linear fashion. */
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	/* Telling OpenGL how we want to represent our texture when we try to draw past its bounds. */
	//glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	Cube cube = Cube(dogeTextureID);

	GLuint ladTextureID;
	glGenTextures(1, &ladTextureID);

	/* 'Bind' our texture to the active texture space so that all of our operations
	* are done to it. */
	glBindTexture(GL_TEXTURE_2D, ladTextureID);
	glTexImage2D(GL_TEXTURE_2D, // specifies that we're working on the active texture.
		0, // ignore.
		GL_RGBA, // specifies that making a texture that has RGBA data.
		ladrillos.getSize().x, // specify the width of the texture.
		ladrillos.getSize().y, // specify the height of the texture.
		0, // no border
		GL_RGBA, // specifies that we're working with an image that has RGBA data.
		GL_UNSIGNED_BYTE, // specifies the format of the RGBA data (in this case, everything is 0-255)
		ladrillos.getPixelsPtr() // specifies the actual image data.
		);
	/* Telling OpenGL that we want our active texture to magnify and minimize in
	* linear fashion. */
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	/* Telling OpenGL how we want to represent our texture when we try to draw past its bounds. */
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	float positionZ = 0.5f;
	float angle = 0.0f;

	sf::Event evt;
	sf::Clock appTimer;
	
	Cube cube2 = Cube(ladTextureID);
	boolean keyHeld1 = true;
	boolean keyHeld2 = false;
	boolean keyHeld3 = false;
	boolean keyHeld4 = false;
	boolean up = false;
	boolean down = false;
	boolean hold = false;
	while (window.isOpen()) {
		float deltaTime = appTimer.restart().asSeconds();

		while (window.pollEvent(evt)) {
			if (evt.type == sf::Event::Closed) {
				window.close();
			}
			else if (evt.type == sf::Event::KeyPressed && (evt.key.code == sf::Keyboard::Key::Num1 || evt.key.code == sf::Keyboard::Key::Numpad1) )
			{
				keyHeld1 = true;
				keyHeld2 = false;
				keyHeld3 = false;
				keyHeld4 = false;
			}
			else if (evt.type == sf::Event::KeyPressed && (evt.key.code == sf::Keyboard::Key::Num2 || evt.key.code == sf::Keyboard::Key::Numpad2))
			{
				keyHeld2 = true;
				keyHeld1 = false;
				keyHeld3 = false;
				keyHeld4 = false;

			}
			else if (evt.type == sf::Event::KeyPressed && (evt.key.code == sf::Keyboard::Key::Num3 || evt.key.code == sf::Keyboard::Key::Numpad3))
			{
				keyHeld3 = true;
				keyHeld1 = false;
				keyHeld2 = false;
				keyHeld4 = false;

			}
			else if (evt.type == sf::Event::KeyPressed && (evt.key.code == sf::Keyboard::Key::Num4 || evt.key.code == sf::Keyboard::Key::Numpad4))
			{
				keyHeld4 = true;
				keyHeld1 = false;
				keyHeld2 = false;
				keyHeld3 = false;
				

			}
			else if (evt.type == sf::Event::KeyPressed && evt.key.code == sf::Keyboard::Key::Up){
				hold = true;
				up = true;
				down = false;
			
			}
			else if (evt.type == sf::Event::KeyPressed && evt.key.code == sf::Keyboard::Key::Down){
				hold = true;
				up = false;
				down = true;

			}
			else if (evt.type == sf::Event::KeyReleased){
				hold = false;
				up = false;
				down = false;
			}
			
		}

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		GLenum error = glGetError();

		float offset = 0.25f;
		angle += 90.0f * deltaTime;

		//draw stuff
		GLfloat position[] = { positionZ, -0.1, positionZ, 0.0f };
		glLightfv(GL_LIGHT0, GL_POSITION, position);

		glPushMatrix();
		
		if (up && hold){
			glRotatef(angle, 1.0f, 0.0f, 0.0f);
		}
		else if (down && hold){
			glRotatef(-angle, 1.0f, 0.0f, 0.0f);
		}
		
		if (keyHeld1){
			
			cube.Draw(GL_QUADS);
			cube.Update(deltaTime);
		
		}
		else if (keyHeld2){
			
			cube.Draw(GL_QUAD_STRIP);
			cube.Update(deltaTime);

		}
		else if (keyHeld3){
			
			cube2.Draw(GL_TRIANGLES);
			cube2.Update(deltaTime);

		}
		else if (keyHeld4){
			cube2.Draw(GL_TRIANGLE_STRIP);
			cube2.Update(deltaTime);

		}
		//cube.DrawTriangles(GL_TRIANGLES);
		//cube.DrawTriangles(GL_TRIANGLE_STRIP);
		//cube.DrawQuadsStrip(GL_QUAD_STRIP);
		// Begin our drawing block.
		//glBegin(GL_QUADS);

		

		window.display();
	}

	return 0;
}