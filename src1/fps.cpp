#include <GL/glut.h>
#include <math.h>

float cameraSpeed = 0.1f;
float cameraSensitivity = 0.1f;
float cameraYaw = 0.0f;
float cameraPitch = 0.0f;
float cameraX = 0.0f, cameraY = 0.0f, cameraZ = 0.0f;

void keyboard(unsigned char key, int x, int y)
{
    switch (key) {
        case 'w':
            cameraX += sin(cameraYaw) * cameraSpeed;
            cameraZ += -cos(cameraYaw) * cameraSpeed;
            break;
        case 's':
            cameraX -= sin(cameraYaw) * cameraSpeed;
            cameraZ -= -cos(cameraYaw) * cameraSpeed;
            break;
        case 'a':
            cameraX += sin(cameraYaw + M_PI_2) * cameraSpeed;
            cameraZ += -cos(cameraYaw + M_PI_2) * cameraSpeed;
            break;
        case 'd':
            cameraX -= sin(cameraYaw + M_PI_2) * cameraSpeed;
            cameraZ -= -cos(cameraYaw + M_PI_2) * cameraSpeed;
            break;
    }
}

void mouse(int x, int y)
{
    cameraYaw += (x - glutGet(GLUT_WINDOW_WIDTH) / 2) * cameraSensitivity;
    cameraPitch += (y - glutGet(GLUT_WINDOW_HEIGHT) / 2) * cameraSensitivity;

    if (cameraPitch > M_PI / 2) cameraPitch = M_PI / 2;
    if (cameraPitch < -M_PI / 2) cameraPitch = -M_PI / 2;

    glutWarpPointer(glutGet(GLUT_WINDOW_WIDTH) / 2, glutGet(GLUT_WINDOW_HEIGHT) / 2);
}

void display()
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(cameraX, cameraY, cameraZ, cameraX + sin(cameraYaw) * cos(cameraPitch), cameraY + sin(cameraPitch), cameraZ - cos(cameraYaw) * cos(cameraPitch), 0.0f, 1.0f, 0.0f);
    // Render your scene here
    glutSwapBuffers();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Camera Movement");
    glutKeyboardFunc(keyboard);
    glutPassiveMotionFunc(mouse);
    glutDisplayFunc(display);
    glutWarpPointer(glutGet(GLUT_WINDOW_WIDTH) / 2, glutGet(GLUT_WINDOW_HEIGHT) / 2);
    // Other GLUT initialization
    glutMainLoop();
    return 0;
}
