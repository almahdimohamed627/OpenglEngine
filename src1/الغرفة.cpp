	//wall
	//اليسار تبع الشباك
	glColor3f(0.9294f, 0.8216f, 0.9353f);
	glBegin(GL_QUADS);
	glVertex3f(-10.0f, 0.0f, -10.0f);
	glVertex3f(-10.0f,7.0f, -10.0f);
	glVertex3f(10.0f, 7.0f, -10.0f);
	glVertex3f(10.0f, 0.0f, -10.0f);
	glEnd();

	//wall
	// الحيط تبع اللوح 
	glColor3f(0.9294f, 0.8216f, 0.9353f);
	glBegin(GL_QUADS);
	glVertex3f(-10.0f, 0.0f, -10.0f);
	glVertex3f(-10.0f, 7.0f, -10.0f);
	glVertex3f(-10.0f, 7.0f, 10.0f);
	glVertex3f(-10.0f, 0.0f, 10.0f);
	glEnd();

	//اللوح
	glPushMatrix();
	glTranslated(-6.9, 1, 0);
	glBegin(GL_QUADS);
	glColor3f(250, 100, 45);
	glVertex3f(-3.0f, 0.0f, -3.0f);
	glVertex3f(-3.0f, 3.0f, -3.0f);
	glVertex3f(-3.0f, 3.0f, 3.0f);
	glVertex3f(-3.0f, 0.0f, 3.0f);
	glEnd();
	glPopMatrix();
//
	glPushMatrix();
	glTranslated(-9.9, 1, 0);
	glScalef(0.1, 0.1, 5.5);
	glColor3f(1, 0, 0);
	glutSolidCube(1);
	glPopMatrix();
	
	//الحيط تبع الباب من جهة اللوح 
	glColor3f(0.9294f, 0.8216f, 0.9353f);
	glBegin(GL_QUADS);
	glVertex3f(-10.0f, 0.0f, 10.0f);
	glVertex3f(-10.0f, 7.0f, 10.0f);
	glVertex3f(-6.0f, 7.0f, 10.0f);
	glVertex3f(-6.0f, 0.0f, 10.0f);
	glEnd();
//	الحيط تبع الباب من جهة تانية
	glColor3f(0.9294f, 0.8216f, 0.9353f);
	glBegin(GL_QUADS);
	glVertex3f(-3.0f, 0.0f, 10.0f);
	glVertex3f(-3.0f, 7.0f, 10.0f);
	glVertex3f(10.0f, 7.0f, 10.0f);
	glVertex3f(10.0f, 0.0f, 10.0f);
	glEnd();
	//الحيط فوق الباب
	glColor3f(0.9294f, 0.8216f, 0.9353f);
	glBegin(GL_QUADS);
	glVertex3f(-6.0f, 7.0f, 10.0f);
	glVertex3f(-6.0f, 5.0f, 10.0f);
	glVertex3f(-3.0f, 5.0f, 10.0f);
	glVertex3f(-3.0f, 7.0f, 10.0f);
	glEnd();
	//حواف الباب 
	glColor3f(0.4f, 0.2f, 0.0f);
	glLineWidth(30.0f);
	glBegin(GL_LINES);
	glVertex3f(-6.0f, 5.0f, 10.01f);
	glVertex3f(-3.0f, 5.0f, 10.01f);
	glEnd();

	glBegin(GL_LINES);
	glVertex3f(-6.0f, 5.0f, 10.01f);
	glVertex3f(-6.0f, 0.0f, 10.01f);
	glEnd();


	glBegin(GL_LINES);
	glVertex3f(-3.0f, 0.0f, 10.01f);
	glVertex3f(-3.0f, 5.0f, 10.01f);
	glEnd();

	//الحيط يلي بالصدر 
	glColor3f(0.9294f, 0.8216f, 0.9353f);
	glBegin(GL_QUADS);
	glVertex3f(10.0f, 0.0f, -10.0f);
	glVertex3f(10.0f, 7.0f, -10.0f);
	glVertex3f(10.0f, 7.0f, 10.0f);
	glVertex3f(10.0f, 0.0f, 10.0f);
	glEnd();