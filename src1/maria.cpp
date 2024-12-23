void initDoctorRoom()
{
	///////مكتب
	glNewList(35, GL_COMPILE);
	glPushMatrix();
	//walls
	////////////////////////////////////////
	glPushMatrix();

	//windows wall
	glColor3ub(215.1, 196.6, 169.5);
	glBegin(GL_QUADS);
	glVertex3f(0, 0, 20);
	glVertex3f(0, 4, 20);
	glVertex3f(16, 4, 20);
	glVertex3f(16, 0, 20);
	glEnd();

	glBegin(GL_QUADS);
	glVertex3f(0, 7, 20);
	glVertex3f(0, 10, 20);
	glVertex3f(16, 10, 20);
	glVertex3f(16, 7, 20);
	glEnd();

	glBegin(GL_QUADS);
	glVertex3f(0, 4, 20);
	glVertex3f(0, 7, 20);
	glVertex3f(3, 7, 20);
	glVertex3f(3, 4, 20);
	glEnd();

	glBegin(GL_QUADS);
	glVertex3f(13, 4, 20);
	glVertex3f(13, 7, 20);
	glVertex3f(16, 7, 20);
	glVertex3f(16, 4, 20);
	glEnd();
	glColor3ub(95.1, 178.7, 252.6);
	glBegin(GL_QUADS);
	glVertex3f(3, 4, 20);
	glVertex3f(3, 7, 20);
	glVertex3f(13, 7, 20);
	glVertex3f(13, 4, 20);
	glEnd();

	//iner wall
	glColor3ub(215.1, 196.6, 169.5);
	glBegin(GL_QUADS);
	glVertex3f(16, 0, 20);
	glVertex3f(16, 10, 20);
	glVertex3f(16, 10, 0);
	glVertex3f(16, 0, 0);
	glEnd();

	//outer wall 
	glBegin(GL_QUADS);
	glVertex3f(0, 0, 20);
	glVertex3f(0, 10, 20);
	glVertex3f(0, 10, 0);
	glVertex3f(0, 0, 0);
	glEnd();

	//door wall
	glBegin(GL_QUADS);
	glVertex3f(0, 7, 0);
	glVertex3f(0, 10, 0);
	glVertex3f(16, 10, 0);
	glVertex3f(16, 7, 0);
	glEnd();

	glBegin(GL_QUADS);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 7, 0);
	glVertex3f(2.25, 7, 0);
	glVertex3f(2.25, 0, 0);
	glEnd();

	glBegin(GL_QUADS);
	glVertex3f(5.75, 0, 0);
	glVertex3f(5.75, 7, 0);
	glVertex3f(16, 7, 0);
	glVertex3f(16, 0, 0);
	glEnd();

	
	glPopMatrix();
	///////////////////////////////



	glPushMatrix();
	glTranslated(10.5, 1.75, 8);
	glRotated(90, -1, 0, 0);
	glRotated(90, 0, 0, -1);
	glScaled(0.13, 0.13, 0.13);



	glPushMatrix();

	glTranslated(30, 0, 0);

	glPushMatrix();

	glTranslated(0, 2, 0);
	glScaled(8, 5, 2);
	glColor3ub(105, 105, 105);
	glutSolidCube(4);

	glPopMatrix();

	glPushMatrix();

	glTranslated(12, -2, -6);
	glScaled(3, -2, 5);
	glColor3f(0.3, 0.3, 0.3);
	glutSolidCube(3);

	glPopMatrix();

	glPushMatrix();
	glTranslated(-12, -2, -6);
	glScaled(3, -2, 5);
	glColor3f(0.3, 0.3, 0.3);
	glutSolidCube(3);

	glPopMatrix();

	glPopMatrix();

	//////////
	//////
	//
	// كرسي المكتب

	glPushMatrix();
	glTranslated(26, 30, 15);
	// glScaled(2, 2, 0);
	glRotated(90, 90, 0, 1);

	// neck
	glPushMatrix();
	glTranslatef(0, -10, 1.2);
	glRotatef(-10, 1, 0, 0);
	glScalef(0.8, 2.4, 0.6);
	glutSolidCube(4);
	glPopMatrix();

	// leg
	glPushMatrix();
	glTranslatef(0, -28, 7);
	glRotatef(-90, 1, 0, 0);
	gluCylinder(a, 3, 3, 12, 100, 100);
	glPopMatrix();

	glColor3ub(20, 20, 15);
	// base
	glPushMatrix();
	glTranslatef(0, -28, 7);
	glRotatef(-90, 1, 0, 0);
	glutSolidTorus(0.6, 3.7, 100, 100);
	glPopMatrix();

	// back
	glPushMatrix();
	glRotatef(-5, 1, 0, 0);
	glScalef(1, 1.3, 0.4);
	gluSphere(a, 7, 100, 100);
	glPopMatrix();

	glColor3ub(100, 100, 100);
	// arms
	glPushMatrix();
	glTranslatef(5, -14, 4);
	glRotatef(-90, 1, -0.1, 0);
	gluCylinder(a, 0.4, 0.4, 7, 100, 100);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-5, -14, 4);
	glRotatef(-90, 1, 0.1, 0);
	gluCylinder(a, 0.4, 0.4, 7, 100, 100);
	glPopMatrix();

	glColor3ub(20, 20, 15);
	// handles
	glPushMatrix();
	glTranslatef(5.8, -7, 3.5);
	gluCylinder(a, 0.6, 0.6, 8, 100, 100);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-5.8, -7, 3.5);
	gluCylinder(a, 0.6, 0.6, 8, 100, 100);
	glPopMatrix();

	// seat
	glPushMatrix();
	glTranslatef(0, -15, 7);
	glScalef(1, 0.4, 1);
	gluSphere(a, 7, 100, 100);
	glPopMatrix();

	glPopMatrix();

	///////////لابتوب

	glPushMatrix();

	glTranslated(-25, -30, -16);

	glPushMatrix();

	glColor3b(1, 1, 1);
	glTranslated(50, 30, 20);
	glScaled(2, 2, 0.2);
	glutSolidCube(4);

	glPopMatrix();

	glPushMatrix();

	glColor3b(1, 1, 1);
	glTranslated(50, 26, 24);
	glScaled(2, 0.2, 2);
	glutSolidCube(4);

	glPopMatrix();
	glPopMatrix();

	/// مكتب على اليمين

	glPushMatrix();

	glTranslated(55, 10, 0);
	glRotated(-90, 0, 0, 1);

	glPushMatrix();

	glTranslated(30, 0, 0);

	glPushMatrix();

	glTranslated(0, 2, 0);
	glScaled(8, 5, 2);
	glColor3ub(105, 105, 105);
	glutSolidCube(4);

	glPopMatrix();

	glPushMatrix();

	glTranslated(12, -2, -6);
	glScaled(3, -2, 5);
	glColor3f(0.3, 0.3, 0.3);
	glutSolidCube(3);

	glPopMatrix();

	glPushMatrix();
	glTranslated(-12, -2, -6);
	glScaled(3, -2, 5);
	glColor3f(0.3, 0.3, 0.3);
	glutSolidCube(3);

	glPopMatrix();

	glPopMatrix();

	//////////
	//////
	//
	// كرسي المكتب

	glPushMatrix();
	glTranslated(26, 30, 15);
	// glScaled(2, 2, 0);
	glRotated(90, 90, 0, 1);

	// neck
	glPushMatrix();
	glTranslatef(0, -10, 1.2);
	glRotatef(-10, 1, 0, 0);
	glScalef(0.8, 2.4, 0.6);
	glutSolidCube(4);
	glPopMatrix();

	// leg
	glPushMatrix();
	glTranslatef(0, -28, 7);
	glRotatef(-90, 1, 0, 0);
	gluCylinder(a, 3, 3, 12, 100, 100);
	glPopMatrix();

	glColor3ub(20, 20, 15);
	// base
	glPushMatrix();
	glTranslatef(0, -28, 7);
	glRotatef(-90, 1, 0, 0);
	glutSolidTorus(0.6, 3.7, 100, 100);
	glPopMatrix();

	// back
	glPushMatrix();
	glRotatef(-5, 1, 0, 0);
	glScalef(1, 1.3, 0.4);
	gluSphere(a, 7, 100, 100);
	glPopMatrix();

	glColor3ub(100, 100, 100);
	// arms
	glPushMatrix();
	glTranslatef(5, -14, 4);
	glRotatef(-90, 1, -0.1, 0);
	gluCylinder(a, 0.4, 0.4, 7, 100, 100);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-5, -14, 4);
	glRotatef(-90, 1, 0.1, 0);
	gluCylinder(a, 0.4, 0.4, 7, 100, 100);
	glPopMatrix();

	glColor3ub(20, 20, 15);
	// handles
	glPushMatrix();
	glTranslatef(5.8, -7, 3.5);
	gluCylinder(a, 0.6, 0.6, 8, 100, 100);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-5.8, -7, 3.5);
	gluCylinder(a, 0.6, 0.6, 8, 100, 100);
	glPopMatrix();

	// seat
	glPushMatrix();
	glTranslatef(0, -15, 7);
	glScalef(1, 0.4, 1);
	gluSphere(a, 7, 100, 100);
	glPopMatrix();

	glPopMatrix();

	///////////لابتوب

	glPushMatrix();

	glTranslated(-25, -30, -16);

	glPushMatrix();

	glColor3b(1, 1, 1);
	glTranslated(50, 30, 20);
	glScaled(2, 2, 0.2);
	glutSolidCube(4);

	glPopMatrix();

	glPushMatrix();

	glColor3b(1, 1, 1);
	glTranslated(50, 26, 24);
	glScaled(2, 0.2, 2);
	glutSolidCube(4);

	glPopMatrix();
	glPopMatrix();

	glPopMatrix();

	/// //مكتب على اليسار

	glPushMatrix();

	glTranslated(-15, -50, 0);
	glRotated(90, 0, 0, 1);

	glPushMatrix();

	glTranslated(30, 0, 0);

	glPushMatrix();

	glTranslated(0, 2, 0);
	glScaled(8, 5, 2);
	glColor3ub(105, 105, 105);
	glutSolidCube(4);

	glPopMatrix();

	glPushMatrix();

	glTranslated(12, -2, -6);
	glScaled(3, -2, 5);
	glColor3f(0.3, 0.3, 0.3);
	glutSolidCube(3);

	glPopMatrix();

	glPushMatrix();
	glTranslated(-12, -2, -6);
	glScaled(3, -2, 5);
	glColor3f(0.3, 0.3, 0.3);
	glutSolidCube(3);

	glPopMatrix();

	glPopMatrix();

	//////////
	//////
	//
	// كرسي المكتب

	glPushMatrix();
	glTranslated(26, 30, 15);
	// glScaled(2, 2, 0);
	glRotated(90, 90, 0, 1);

	// neck
	glPushMatrix();
	glTranslatef(0, -10, 1.2);
	glRotatef(-10, 1, 0, 0);
	glScalef(0.8, 2.4, 0.6);
	glutSolidCube(4);
	glPopMatrix();

	// leg
	glPushMatrix();
	glTranslatef(0, -28, 7);
	glRotatef(-90, 1, 0, 0);
	gluCylinder(a, 3, 3, 12, 100, 100);
	glPopMatrix();

	glColor3ub(20, 20, 15);
	// base
	glPushMatrix();
	glTranslatef(0, -28, 7);
	glRotatef(-90, 1, 0, 0);
	glutSolidTorus(0.6, 3.7, 100, 100);
	glPopMatrix();

	// back
	glPushMatrix();
	glRotatef(-5, 1, 0, 0);
	glScalef(1, 1.3, 0.4);
	gluSphere(a, 7, 100, 100);
	glPopMatrix();

	glColor3ub(100, 100, 100);
	// arms
	glPushMatrix();
	glTranslatef(5, -14, 4);
	glRotatef(-90, 1, -0.1, 0);
	gluCylinder(a, 0.4, 0.4, 7, 100, 100);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-5, -14, 4);
	glRotatef(-90, 1, 0.1, 0);
	gluCylinder(a, 0.4, 0.4, 7, 100, 100);
	glPopMatrix();

	glColor3ub(20, 20, 15);
	// handles
	glPushMatrix();
	glTranslatef(5.8, -7, 3.5);
	gluCylinder(a, 0.6, 0.6, 8, 100, 100);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-5.8, -7, 3.5);
	gluCylinder(a, 0.6, 0.6, 8, 100, 100);
	glPopMatrix();

	// seat
	glPushMatrix();
	glTranslatef(0, -15, 7);
	glScalef(1, 0.4, 1);
	gluSphere(a, 7, 100, 100);
	glPopMatrix();

	glPopMatrix();
	glPopMatrix();

	/// /مكتب الطابعة

	glPushMatrix();

	glTranslated(-15, 30, 0);
	// glScaled(2, 0, 0);

	glPushMatrix();

	glTranslated(0, 2, 0);
	glScaled(8, 5, 2);
	glColor3f(0.3, 0.3, 0.3);
	glutSolidCube(4);

	glPopMatrix();

	glPushMatrix();

	glTranslated(12, -2, -6);
	glScaled(3, -2, 5);
	glColor3f(0.3, 0.3, 0.3);
	glutSolidCube(3);

	glPopMatrix();

	glPushMatrix();
	glTranslated(-12, -2, -6);
	glScaled(3, -2, 5);
	glColor3f(0.3, 0.3, 0.3);
	glutSolidCube(3);

	glPopMatrix();

	glPopMatrix();

	// طابعة

	glPushMatrix();
	glTranslated(-25, 30, 10.5);
	glScaled(2.5, 2.5, 2.5);
	glPushMatrix();

	
	glColor3ub(59, 59, 59);
	glutSolidCube(5);

	glPopMatrix();

	glPushMatrix();

	glTranslated(-1.5, 0, 3);
	glScalef(0.5, 1.5, 0.5);
	glColor3ub(59, 59, 59);
	glutSolidCube(4);

	glPopMatrix();

	glPushMatrix();

	glTranslated(1, 0, 3.5);
	glScaled(5, -3, 0);
	glColor3f(0.3, 0.3, 0.3);
	glutSolidCube(1);

	glPopMatrix();

    //	تفاصيل الطابعة

	glPushMatrix();
	glColor3f(0.06, 0.7, 0.3);
	glTranslated(0, -2.5, -2);
	glScaled(2.5, 1, 1);
	glutSolidCube(0.5);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.06, 0.7, 0.3);
	glTranslated(0, -2.5, -1);
	glScaled(2.5, 1, 1);
	glutSolidCube(0.5);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.07, 0.1, 0.45);
	glTranslated(-1.5, -2.5, 1.5);
	glScaled(2.5, 1, 1);
	glutSolidCube(0.8);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.07, 0.1, 0.45);
	glTranslated(1, -2.5, 1.5);
	glScaled(5, 0.1, 0.4);
	glutSolidCube(0.6);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.07, 0.1, 0.45);
	glTranslated(0, -2.5, -2);
	glScaled(1.5, 1, 1);
	glutSolidCube(0.3);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.07, 0.1, 0.45);
	glTranslated(0, -2.6, -2);
	glScaled(1.5, 1, 1);
	glutSolidCube(0.3);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.07, 0.1, 0.45);
	glTranslated(0, -2.6, -1);
	glScaled(1.5, 1, 1);
	glutSolidCube(0.3);
	glPopMatrix();

	glPopMatrix();

	glPushMatrix();
	glColor3f(546, 34, 45);
	glTranslated(-6, 25, 6);
	glScaled(1, 1, 0.3);
	glutSolidCube(7);
	glPopMatrix();



	glPushMatrix();
	glTranslated(-50, 40, 10);
	glScaled(15, 15, 15);
	glRotated(90, 45, 1, 0);
	for (int i = 0; i < 5; i++)
	{
		glTranslated(0, 0, 1.9);
		glCallList(5);
	}
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
	glEndList();


}