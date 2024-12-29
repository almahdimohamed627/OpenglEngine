

void DrawGLScene(void)
{
	glClearColor(1, 1, 1, 0.0f);						// Set background to white
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear both color and depth buffers

	// --- 3D Rendering ---
	glMatrixMode(GL_MODELVIEW); // Ensure we're in the modelview matrix mode
	glLoadIdentity();			// Reset transformations

	GLfloat position[] = {0, 10000, 0, 0}; // Light position
	glLightfv(GL_LIGHT0, GL_POSITION, position);

	gluLookAt(Ex, E, Ez, Ex + cos(th), E, Ez + sin(th), 0, 1, 0); // Camera setup

	if (rotateScene)
	{
		glRotated(90, 0, 0, 1); // Rotate the scene if needed
	}

	// Draw the background grid
	glPushMatrix();
	glColor3f(0.7f, 0.7f, 0.7f); // Set the line color to gray
	glLineWidth(1.0f);			 // Set the line width

	// Draw vertical grid lines
	for (int i = -150; i <= 150; i++)
	{
		glBegin(GL_LINES);
		glVertex3f(i * 2.0f, 0.0f, -300.0f); // Line start
		glVertex3f(i * 2.0f, 0.0f, 300.0f);	 // Line end
		glEnd();
	}

	// Draw horizontal grid lines
	for (int i = -150; i <= 150; i++)
	{
		glBegin(GL_LINES);
		glVertex3f(-300.0f, 0.0f, i * 2.0f); // Line start
		glVertex3f(300.0f, 0.0f, i * 2.0f);	 // Line end
		glEnd();
	}

	for (Entity *e : entities)
	{
		e->display();
	}

	glPopMatrix();
	// --- Switch to 2D for UI rendering ---
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0); // Set orthographic projection (2D)

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	glDisable(GL_DEPTH_TEST); // Disable depth testing for 2D UI rendering

	// Draw the center red point
	glPushMatrix();
	glColor3f(1.0f, 0.0f, 0.0f); // Red color
	glPointSize(10.0f);			 // Large point
	glBegin(GL_POINTS);
	glVertex3f(0.0f, 0.0f, 0.0f); // Transform coordinates
	glEnd();
	glPopMatrix();

	// Render 2D UI elements (buttons, labels, etc.)
	Sphere_button.display();
	TeaPot_button.display();
    Cube_button.display();
    Transformation::display();
    !entities.empty()? entities[Entity::selected()]->displayInfo() : donothing() ;
	printFPS();				 // Print FPS
	glEnable(GL_DEPTH_TEST); // Re-enable depth testing for 3D rendering after UI

	glPopMatrix(); // Restore modelview matrix
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();	   // Restore projection matrix
	glutSwapBuffers(); // Swap buffers to display the rendered content
}


