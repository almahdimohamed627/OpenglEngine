void drawGroundFloor()
{
	glPushMatrix();

	glColor4ub(14.4, 188.0, 185, 255);
	glBegin(GL_QUADS);
	glVertex3f(0, 0, -24);
	glVertex3f(80, 0, -24);
	glVertex3f(80, 0, 24);
	glVertex3f(0, 0, 24);
	glEnd();

	glPushMatrix();
	glTranslated(48, 0, -4);
	glRotated(90, 0, 0, 0);
	glScaled(1, 1, -1);
	drawPrepationRoom();
	glPopMatrix();

	glPushMatrix();
	glTranslated(64, 0, -4);
	glRotated(90, 0, 0, 0);
	glScaled(1, 1, -1);
	drawOpRoom();
	glPopMatrix();

	glPushMatrix();
	glTranslated(64, 0, 4);
	glRotated(90, 0, 0, 0);
	glScaled(1, 1, 1);
	drawLab();
	glPopMatrix();

	glPushMatrix();
	glTranslated(0, 0, 4);
	glCallList(30);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0, 0, -4);
	glScaled(1, 1, -1);
	glCallList(29);
	glPopMatrix();

	glPushMatrix();
	glTranslated(20, 0, 4);
	glRotated(90, 0, 1, 0);
	glScaled(1, 1, 1);
	glCallList(36);
	glColor4ub(215.1, 196.6, 169.5, 255);
	glBegin(GL_QUADS);
	glVertex3f(0, 0, 4);
	glVertex3f(0, 10, 4);
	glVertex3f(0, 10, 12);
	glVertex3f(0, 0, 12);
	glEnd();
	glColor4ub(70, 70, 70, 255);
	glPushMatrix();
	glTranslated(0, 4, 8);
	glScaled(0.2, 8, 6.5);
	glutSolidCube(1);
	glPopMatrix();
	glPopMatrix();

	glPushMatrix();
	glTranslated(32, 0, 4);
	glRotated(90, 0, 0, 0);
	glScaled(1, 1, 1);
	drawDoctorRoom();
	glPopMatrix();

	glPushMatrix();
	glTranslated(48, 0, 4);
	glRotated(90, 0, 0, 0);
	glScaled(1, 1, 1);
	drawCTRoom();
	glPopMatrix();

	glPushMatrix();
	glTranslated(32, 0, -4);
	glRotated(90, 0, 0, 0);
	glScaled(1, 1, -1);
	drawPharmacy();
	glPopMatrix();


	glPushMatrix();
	glTranslated(72, 0, 0);
	glScaled(-1, 1, 1);
	glCallList(36);
	glPopMatrix();

	glPopMatrix();
}