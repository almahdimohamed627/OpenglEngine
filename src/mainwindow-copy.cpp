void printFPS()
{
	glPushMatrix();
	timeSinceStart = glutGet(GLUT_ELAPSED_TIME);
	deltaTime = timeSinceStart - oldTimeSinceStart;
	oldTimeSinceStart = timeSinceStart;
	char buffer[100];															 // Allocate a buffer for the formatted string
	sprintf(buffer, "FPS:%d X:%.2f Y:%.2f Z:%.2f", 1000 / deltaTime, Ex, E, Ez); // Format the string
	renderBitmapText(0.5, 0.95, buffer, GLUT_BITMAP_HELVETICA_18);				 // Pass the formatted string																				 // std::cout << '\r' << 1000 / deltaTime << " " << Ex << " " << E << " " << Ez << std::flush;
	glPopMatrix();
}