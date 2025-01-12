#ifndef GETCODE_H
#define GETCODE_H

#include <string>
#include <vector>
#include "Entity.h"
#include "Shape.h"
#include "List.h"
#include "Sphere.h"
#include "Cube.h"
#include "FileHandler.h"

template <typename T>
void input(T &value)
{
    if constexpr (std::is_same<T, std::string>::value)
    {
        std::getline(std::cin, value); // Read the whole line (including spaces)
        return;
    }
    while (!(std::cin >> value))
    {
        std::cout << "Invalid input. Please try again: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

void getCode()
{
    std::vector<std::pair<std::string, int>> lists;
    std::string name;
    std::cout << "Enter Code Name: " << std::flush;
    input(name);
    try
    {
        char buffer[100];
        sprintf(buffer, "OutputCode/%s.cpp", name.c_str());
        FileHandler::writeToFile(buffer, "");                                                                                  // Save with pretty formatting
        FileHandler::writeLineToFile(buffer, "#include <GL/freeglut.h>");                                                      // Save with pretty formatting
        FileHandler::writeLineToFile(buffer, "#include <math.h>");                                                             // Save with pretty formatting
        FileHandler::writeLineToFile(buffer, "#include <iostream>");                                                           // Save with pretty formatting
        FileHandler::writeLineToFile(buffer, "using namespace std;");                                                          // Save with pretty formatting
        FileHandler::writeLineToFile(buffer, "");                                                                              // Save with pretty formatting
        FileHandler::writeLineToFile(buffer, "double th = 0;  // for camera");                                                 // Save with pretty formatting
        FileHandler::writeLineToFile(buffer, "double Ex = 0;");                                                                // Save with pretty formatting
        FileHandler::writeLineToFile(buffer, "double Ez = 0;");                                                                // Save with pretty formatting
        FileHandler::writeLineToFile(buffer, "double E = 0;");                                                                 // Save with pretty formatting
        FileHandler::writeLineToFile(buffer, "bool sprinting = false;");                                                       // Save with pretty formatting
        FileHandler::writeLineToFile(buffer, "bool light = false;");                                                           // Save with pretty formatting
        FileHandler::writeLineToFile(buffer, "bool lighting = false;");                                                        // Save with pretty formatting
        FileHandler::writeLineToFile(buffer, "bool rotateScene = false;");                                                     // Save with pretty formatting
        FileHandler::writeLineToFile(buffer, "int mouseX, mouseY;");                                                           // Save with pretty formatting
        FileHandler::writeLineToFile(buffer, "double mouseTh;");                                                               // Save with pretty formatting
        FileHandler::writeLineToFile(buffer, "");                                                                              // Save with pretty formatting
        FileHandler::writeLineToFile(buffer, "GLUquadricObj *a = gluNewQuadric();");                                           // Save with pretty formatting
        FileHandler::writeLineToFile(buffer, "");                                                                              // Save with pretty formatting
        FileHandler::writeLineToFile(buffer, "");                                                                              // Save with pretty formatting
        FileHandler::writeLineToFile(buffer, "void mouseButton(int button, int state, int x, int y)  // handle mouse clicks"); // Save with pretty formatting
        FileHandler::writeLineToFile(buffer, "{");                                                                             // Save with pretty formatting
        FileHandler::writeLineToFile(buffer, "if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)");                         // Save with pretty formatting
        FileHandler::writeLineToFile(buffer, "{");                                                                             // Save with pretty formatting
        FileHandler::writeLineToFile(buffer, "mouseX = x;");                                                                   // Save with pretty formatting
        FileHandler::writeLineToFile(buffer, "mouseY = y;");                                                                   // Save with pretty formatting
        FileHandler::writeLineToFile(buffer, "mouseTh = th;");                                                                 // Save with pretty formatting
        FileHandler::writeLineToFile(buffer, "}");                                                                             // Save with pretty formatting
        FileHandler::writeLineToFile(buffer, "}");                                                                             // Save with pretty formatting
        FileHandler::writeLineToFile(buffer, "");                                                                              // Save with pretty formatting
        FileHandler::writeLineToFile(buffer, "void keyboard(unsigned char key, int x, int y)  // handle keyboard input");      // Save with pretty formatting
        FileHandler::writeLineToFile(buffer, "{");                                                                             // Save with pretty formatting
        FileHandler::writeLineToFile(buffer, "switch (key)");                                                                  // Save with pretty formatting
        FileHandler::writeLineToFile(buffer, "{");                                                                             // Save with pretty formatting
        FileHandler::writeLineToFile(buffer, "case 27: /* Escape key */");                                                     // Save with pretty formatting
        FileHandler::writeLineToFile(buffer, "exit(0);");                                                                      // Save with pretty formatting
        FileHandler::writeLineToFile(buffer, "break;");                                                                        // Save with pretty formatting
        FileHandler::writeLineToFile(buffer, "case 'R':");                                                                     // Save with pretty formatting
        FileHandler::writeLineToFile(buffer, "if (rotateScene)");                                                              // Save with pretty formatting
        FileHandler::writeLineToFile(buffer, "rotateScene = false;");                                                          // Save with pretty formatting
        FileHandler::writeLineToFile(buffer, "else");                                                                          // Save with pretty formatting
        FileHandler::writeLineToFile(buffer, "rotateScene = true;");                                                           // Save with pretty formatting
        FileHandler::writeLineToFile(buffer, "break;");                                                                        // Save with pretty formatting
        FileHandler::writeLineToFile(buffer, "case 'l':");                                                                     // Save with pretty formatting
        FileHandler::writeLineToFile(buffer, "if (light)");                                                                    // Save with pretty formatting
        FileHandler::writeLineToFile(buffer, "light = false;");                                                                // Save with pretty formatting
        FileHandler::writeLineToFile(buffer, "else");                                                                          // Save with pretty formatting
        FileHandler::writeLineToFile(buffer, "light = true;");                                                                 // Save with pretty formatting
        FileHandler::writeLineToFile(buffer, "break;");                                                                        // Save with pretty formatting
        FileHandler::writeLineToFile(buffer, "case 'L':");                                                                     // Save with pretty formatting
        FileHandler::writeLineToFile(buffer, "if (lighting)");                                                                 // Save with pretty formatting
        FileHandler::writeLineToFile(buffer, "lighting = false;");                                                             // Save with pretty formatting
        FileHandler::writeLineToFile(buffer, "else");                                                                          // Save with pretty formatting
        FileHandler::writeLineToFile(buffer, "lighting = true;");                                                              // Save with pretty formatting
        FileHandler::writeLineToFile(buffer, "break;");                                                                        // Save with pretty formatting
        FileHandler::writeLineToFile(buffer, "case 'd':");                                                                     // Save with pretty formatting
        FileHandler::writeLineToFile(buffer, "if (sprinting)");                                                                // Save with pretty formatting
        FileHandler::writeLineToFile(buffer, "{");                                                                             // Save with pretty formatting
        FileHandler::writeLineToFile(buffer, "Ex = Ex - 5 * sin(th);");                                                        // Save with pretty formatting
        FileHandler::writeLineToFile(buffer, "Ez = Ez + 5 * cos(th);");                                                        // Save with pretty formatting
        FileHandler::writeLineToFile(buffer, "}");                                                                             // Save with pretty formatting
        FileHandler::writeLineToFile(buffer, "else");                                                                          // Save with pretty formatting
        FileHandler::writeLineToFile(buffer, "{");                                                                             // Save with pretty formatting
        FileHandler::writeLineToFile(buffer, "Ex = Ex - 2 * sin(th);");                                                        // Save with pretty formatting
        FileHandler::writeLineToFile(buffer, "Ez = Ez + 2 * cos(th);");                                                        // Save with pretty formatting
        FileHandler::writeLineToFile(buffer, "}");                                                                             // Save with pretty formatting
        FileHandler::writeLineToFile(buffer, "break;");                                                                        // Save with pretty formatting
        FileHandler::writeLineToFile(buffer, "case 'a':");                                                                     // Save with pretty formatting
        FileHandler::writeLineToFile(buffer, "if (sprinting)");                                                                // Save with pretty formatting
        FileHandler::writeLineToFile(buffer, "{");                                                                             // Save with pretty formatting
        FileHandler::writeLineToFile(buffer, "Ex = Ex + 5 * sin(th);");                                                        // Save with pretty formatting
        FileHandler::writeLineToFile(buffer, "Ez = Ez - 5 * cos(th);");                                                        // Save with pretty formatting
        FileHandler::writeLineToFile(buffer, "}");                                                                             // Save with pretty formatting
        FileHandler::writeLineToFile(buffer, "else");                                                                          // Save with pretty formatting
        FileHandler::writeLineToFile(buffer, "{");                                                                             // Save with pretty formatting
        FileHandler::writeLineToFile(buffer, "Ex = Ex + 2 * sin(th);");                                                        // Save with pretty formatting
        FileHandler::writeLineToFile(buffer, "Ez = Ez - 2 * cos(th);");                                                        // Save with pretty formatting
        FileHandler::writeLineToFile(buffer, "}");                                                                             // Save with pretty formatting
        FileHandler::writeLineToFile(buffer, "break;");                                                                        // Save with pretty formatting
        FileHandler::writeLineToFile(buffer, "case 'w':");                                                                     // Save with pretty formatting
        FileHandler::writeLineToFile(buffer, "if (sprinting)");                                                                // Save with pretty formatting
        FileHandler::writeLineToFile(buffer, "{");                                                                             // Save with pretty formatting
        FileHandler::writeLineToFile(buffer, "Ex = Ex + 5 * cos(th);");                                                        // Save with pretty formatting
        FileHandler::writeLineToFile(buffer, "Ez = Ez + 5 * sin(th);");                                                        // Save with pretty formatting
        FileHandler::writeLineToFile(buffer, "}");                                                                             // Save with pretty formatting
        FileHandler::writeLineToFile(buffer, "else");                                                                          // Save with pretty formatting
        FileHandler::writeLineToFile(buffer, "{");                                                                             // Save with pretty formatting
        FileHandler::writeLineToFile(buffer, "Ex = Ex + 2 * cos(th);");                                                        // Save with pretty formatting
        FileHandler::writeLineToFile(buffer, "Ez = Ez + 2 * sin(th);");                                                        // Save with pretty formatting
        FileHandler::writeLineToFile(buffer, "}");                                                                             // Save with pretty formatting
        FileHandler::writeLineToFile(buffer, "break;");                                                                        // Save with pretty formatting
        FileHandler::writeLineToFile(buffer, "case 's':");                                                                     // Save with pretty formatting
        FileHandler::writeLineToFile(buffer, "if (sprinting)");                                                                // Save with pretty formatting
        FileHandler::writeLineToFile(buffer, "{");                                                                             // Save with pretty formatting
        FileHandler::writeLineToFile(buffer, "Ex = Ex - 5 * cos(th);");                                                        // Save with pretty formatting
        FileHandler::writeLineToFile(buffer, "Ez = Ez - 5 * sin(th);");                                                        // Save with pretty formatting
        FileHandler::writeLineToFile(buffer, "}");                                                                             // Save with pretty formatting
        FileHandler::writeLineToFile(buffer, "else");                                                                          // Save with pretty formatting
        FileHandler::writeLineToFile(buffer, "{");                                                                             // Save with pretty formatting
        FileHandler::writeLineToFile(buffer, "Ex = Ex - 2 * cos(th);");                                                        // Save with pretty formatting
        FileHandler::writeLineToFile(buffer, "Ez = Ez - 2 * sin(th);");                                                        // Save with pretty formatting
        FileHandler::writeLineToFile(buffer, "}");                                                                             // Save with pretty formatting
        FileHandler::writeLineToFile(buffer, "break;");                                                                        // Save with pretty formatting
        FileHandler::writeLineToFile(buffer, "default:");                                                                      // Save with pretty formatting
        FileHandler::writeLineToFile(buffer, "break;");                                                                        // Save with pretty formatting
        FileHandler::writeLineToFile(buffer, "}");                                                                             // Save with pretty formatting
        FileHandler::writeLineToFile(buffer, "}");                                                                             // Save with pretty formatting
        FileHandler::writeLineToFile(buffer, "");                                                                              // Save with pretty formatting                                                                             // Save with pretty formatting
        FileHandler::writeLineToFile(buffer, "");                                                                              // Save with pretty formatting
        FileHandler::writeLineToFile(buffer, "void mouseMotion(int x, int y)   // handle mouse drag");                         // Save with pretty formatting
        FileHandler::writeLineToFile(buffer, "{");                                                                             // Save with pretty formatting
        FileHandler::writeLineToFile(buffer, "th = (x - mouseX) / 360.0 + mouseTh;");                                          // Save with pretty formatting
        FileHandler::writeLineToFile(buffer, "}");                                                                             // Save with pretty formatting
        FileHandler::writeLineToFile(buffer, "");                                                                              // Save with pretty formatting
        FileHandler::writeLineToFile(buffer, "void mouseWheel(int wheel, int direction, int x, int y)");                       // Save with pretty formatting
        FileHandler::writeLineToFile(buffer, "{");                                                                             // Save with pretty formatting
        FileHandler::writeLineToFile(buffer, "if (direction > 0) // Scroll up");                                               // Save with pretty formatting
        FileHandler::writeLineToFile(buffer, "{");                                                                             // Save with pretty formatting
        FileHandler::writeLineToFile(buffer, "E += 1.0;   // make the camera higher");                                         // Save with pretty formatting
        FileHandler::writeLineToFile(buffer, "}");                                                                             // Save with pretty formatting
        FileHandler::writeLineToFile(buffer, "else if (direction < 0)");                                                       // Save with pretty formatting
        FileHandler::writeLineToFile(buffer, "{");                                                                             // Save with pretty formatting
        FileHandler::writeLineToFile(buffer, "E -= 1.0;   // lower the camera");                                               // Save with pretty formatting
        FileHandler::writeLineToFile(buffer, "}");                                                                             // Save with pretty formatting
        FileHandler::writeLineToFile(buffer, "glutPostRedisplay();");                                                          // Save with pretty formatting
        FileHandler::writeLineToFile(buffer, "}");                                                                             // Save with pretty formatting
        FileHandler::writeLineToFile(buffer, "");                                                                              // Save with pretty formatting
        FileHandler::writeLineToFile(buffer, "void InitGL(void)");                                                             // Save with pretty formatting
        FileHandler::writeLineToFile(buffer, "{");                                                                             // Save with pretty formatting
        FileHandler::writeLineToFile(buffer, "glShadeModel(GL_SMOOTH); // Enable Smooth Shading");                             // Save with pretty formatting
        FileHandler::writeLineToFile(buffer, "glEnable(GL_DEPTH_TEST); // Enables Depth Testing");                             // Save with pretty formatting
        FileHandler::writeLineToFile(buffer, "glDepthFunc(GL_LEQUAL);");                                                       // Save with pretty formatting
        FileHandler::writeLineToFile(buffer, "glEnable(GL_COLOR_MATERIAL);");                                                  // Save with pretty formatting
        FileHandler::writeLineToFile(buffer, "glEnable(GL_BLEND); // for transperancy");                                       // Save with pretty formatting
        FileHandler::writeLineToFile(buffer, "glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);");                            // Save with pretty formatting
        FileHandler::writeLineToFile(buffer, "glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);");                  // Save with pretty formatting
        FileHandler::writeLineToFile(buffer, "GLfloat am[] = {0.4, 0.4, 0.4, 0.5};");                                          // Save with pretty formatting
        FileHandler::writeLineToFile(buffer, "glLightfv(GL_LIGHT0, GL_AMBIENT, am);");                                         // Save with pretty formatting
        FileHandler::writeLineToFile(buffer, "GLfloat di[] = {0.8, 0.8, 0.8, 0.5};");                                          // Save with pretty formatting
        FileHandler::writeLineToFile(buffer, "glLightfv(GL_LIGHT0, GL_DIFFUSE, di);");                                         // Save with pretty formatting
        FileHandler::writeLineToFile(buffer, "GLfloat sp[] = {0.9, 0.9, 0.9, 0.5};");                                          // Save with pretty formatting
        FileHandler::writeLineToFile(buffer, "glLightfv(GL_LIGHT0, GL_SPECULAR, sp);");                                        // Save with pretty formatting
        FileHandler::writeLineToFile(buffer, "glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);");                            // Save with pretty formatting
        FileHandler::writeLineToFile(buffer, "GLenum error = glGetError();");                                                  // Save with pretty formatting
        FileHandler::writeLineToFile(buffer, "if (error != GL_NO_ERROR)");                                                     // Save with pretty formatting
        FileHandler::writeLineToFile(buffer, "{");                                                                             // Save with pretty formatting
        FileHandler::writeLineToFile(buffer, "printf(\"OpenGL Error: %s\\n\", gluErrorString(error));");                       // Save with pretty formatting
        FileHandler::writeLineToFile(buffer, "}");
        FileHandler::writeLineToFile(buffer, "");
        FileHandler::writeLineToFile(buffer, "  /////  lists /////"); // Save with pretty formatting

        for (Entity *e : entities)
        {
            // Check if the entity is of type "List"
            if (e->getType() == "List")
            {
                // Check if the name of this entity exists in the 'lists' container
                std::vector<std::pair<std::string, int>>::iterator it = std::find_if(lists.begin(), lists.end(),
                                                                                     [&e](const std::pair<std::string, int> &pair)
                                                                                     {
                                                                                         return pair.first == e->getName();
                                                                                     });

                if (it == lists.end()) // If not found
                {
                    lists.push_back({e->getName(), e->getId() + 1});
                    FileHandler::writeLineToFile(buffer, dynamic_cast<List *>(e)->getListCode(e->getId() + 1).c_str());
                }
            }
        }

        FileHandler::writeLineToFile(buffer, "}");                                                                                         // Save with pretty formatting
        FileHandler::writeLineToFile(buffer, "");                                                                                          // Save with pretty formatting
        FileHandler::writeLineToFile(buffer, "void ReSizeGLScene(int w, int h)");                                                          // Save with pretty formatting
        FileHandler::writeLineToFile(buffer, "{");                                                                                         // Save with pretty formatting
        FileHandler::writeLineToFile(buffer, "glViewport(0, 0, (GLsizei)w, (GLsizei)h);");                                                 // Save with pretty formatting
        FileHandler::writeLineToFile(buffer, "glMatrixMode(GL_PROJECTION);");                                                              // Save with pretty formatting
        FileHandler::writeLineToFile(buffer, "glLoadIdentity();");                                                                         // Save with pretty formatting
        FileHandler::writeLineToFile(buffer, "gluPerspective(45.0f, (GLfloat)w / (GLfloat)h, 0.1f, 1000.0f);");                            // Save with pretty formatting
        FileHandler::writeLineToFile(buffer, "glMatrixMode(GL_MODELVIEW);");                                                               // Save with pretty formatting
        FileHandler::writeLineToFile(buffer, "glLoadIdentity();");                                                                         // Save with pretty formatting
        FileHandler::writeLineToFile(buffer, "}");                                                                                         // Save with pretty formatting
        FileHandler::writeLineToFile(buffer, "");                                                                                          // Save with pretty formatting
        FileHandler::writeLineToFile(buffer, "void DrawGLScene(void)");                                                                    // Save with pretty formatting
        FileHandler::writeLineToFile(buffer, "{");                                                                                         // Save with pretty formatting
        FileHandler::writeLineToFile(buffer, "glClearColor(1, 1, 1, 0.0f);  // set background color to white");                            // Save with pretty formatting
        FileHandler::writeLineToFile(buffer, "glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear both color and depth buffers"); // Save with pretty formatting
        FileHandler::writeLineToFile(buffer, "glMatrixMode(GL_MODELVIEW); // Ensure we're in the modelview matrix mode");                  // Save with pretty formatting
        FileHandler::writeLineToFile(buffer, "    glLoadIdentity();           // Reset transformations");                                  // Save with pretty formatting
        FileHandler::writeLineToFile(buffer, "    GLfloat position[] = {0, 10000, 0, 0}; // Light position");                              // Save with pretty formatting
        FileHandler::writeLineToFile(buffer, "    glLightfv(GL_LIGHT0, GL_POSITION, position);");                                          // Save with pretty formatting
        FileHandler::writeLineToFile(buffer, "    gluLookAt(Ex, E, Ez, Ex + cos(th), E, Ez + sin(th), 0, 1, 0); // Camera setup");         // Save with pretty formatting
        FileHandler::writeLineToFile(buffer, "    if (rotateScene)");                                                                      // Save with pretty formatting
        FileHandler::writeLineToFile(buffer, "{");                                                                                         // Save with pretty formatting
        FileHandler::writeLineToFile(buffer, "        glRotated(90, 0, 0, 1); // Rotate the scene if needed");                             // Save with pretty formatting
        FileHandler::writeLineToFile(buffer, "}");                                                                                         // Save with pretty formatting
        FileHandler::writeLineToFile(buffer, "");                                                                                          // Save with pretty formatting
        FileHandler::writeLineToFile(buffer, "    if (lighting)  // for lighting calculations");                                           // Save with pretty formatting
        FileHandler::writeLineToFile(buffer, "{");                                                                                         // Save with pretty formatting
        FileHandler::writeLineToFile(buffer, "glEnable(GL_LIGHTING);");                                                                    // Save with pretty formatting
        FileHandler::writeLineToFile(buffer, "}");                                                                                         // Save with pretty formatting
        FileHandler::writeLineToFile(buffer, "else");                                                                                      // Save with pretty formatting
        FileHandler::writeLineToFile(buffer, "{");                                                                                         // Save with pretty formatting
        FileHandler::writeLineToFile(buffer, "glDisable(GL_LIGHTING);");                                                                   // Save with pretty formatting
        FileHandler::writeLineToFile(buffer, "}");                                                                                         // Save with pretty formatting
        FileHandler::writeLineToFile(buffer, "    if (light)");                                                                            // Save with pretty formatting
        FileHandler::writeLineToFile(buffer, "{");                                                                                         // Save with pretty formatting
        FileHandler::writeLineToFile(buffer, "glEnable(GL_LIGHT0);   // for the light source");                                            // Save with pretty formatting
        FileHandler::writeLineToFile(buffer, "}");                                                                                         // Save with pretty formatting
        FileHandler::writeLineToFile(buffer, "else");                                                                                      // Save with pretty formatting
        FileHandler::writeLineToFile(buffer, "{");                                                                                         // Save with pretty formatting
        FileHandler::writeLineToFile(buffer, "glDisable(GL_LIGHT0);");                                                                     // Save with pretty formatting
        FileHandler::writeLineToFile(buffer, "}");                                                                                         // Save with pretty formatting                                                                                     // Save with pretty formatting
        FileHandler::writeLineToFile(buffer, "      //// start drawing scene ////");                                                       // Save with pretty formatting                                                                                     // Save with pretty formatting
        FileHandler::writeLineToFile(buffer, "");                                                                                          // Save with pretty formatting                                                                                     // Save with pretty formatting

        for (Entity *e : entities)
        {
            FileHandler::writeLineToFile(buffer, "");                                      // Save with pretty formatting
            FileHandler::writeLineToFile(buffer, "/////////////////////////////////////"); // Save with pretty formatting
            FileHandler::writeLineToFile(buffer, "");
            for (std::pair<std::string, int> list : lists)
            {
                if (list.first == e->getName())
                {
                    FileHandler::writeLineToFile(buffer, dynamic_cast<List *>(e)->getDisplayCode(list.second).c_str()); // Save with pretty formatting
                    break;
                }
            }
            FileHandler::writeLineToFile(buffer, e->getDisplayCode().c_str()); // Save with pretty formatting
        }

        FileHandler::writeLineToFile(buffer, "");                                                                                          // Save with pretty formatting
        FileHandler::writeLineToFile(buffer, "glutSwapBuffers(); // Swap buffers to display the rendered content");                        // Save with pretty formatting
        FileHandler::writeLineToFile(buffer, "}");                                                                                         // Save with pretty formatting
        FileHandler::writeLineToFile(buffer, "");                                                                                          // Save with pretty formatting
        FileHandler::writeLineToFile(buffer, "void Timer(int)");                                                                           // Save with pretty formatting
        FileHandler::writeLineToFile(buffer, "{");                                                                                         // Save with pretty formatting
        FileHandler::writeLineToFile(buffer, "	glutTimerFunc(16, Timer, 0);");                                                            // Save with pretty formatting
        FileHandler::writeLineToFile(buffer, "	glutPostRedisplay();");                                                                    // Save with pretty formatting
        FileHandler::writeLineToFile(buffer, "}");                                                                                         // Save with pretty formatting
        FileHandler::writeLineToFile(buffer, "");                                                                                          // Save with pretty formatting
        FileHandler::writeLineToFile(buffer, "void setupprojection()");                                                                    // Save with pretty formatting
        FileHandler::writeLineToFile(buffer, "{");                                                                                         // Save with pretty formatting
        FileHandler::writeLineToFile(buffer, "	int w = glutGet(GLUT_WINDOW_WIDTH);");                                                     // Save with pretty formatting
        FileHandler::writeLineToFile(buffer, "	int h = glutGet(GLUT_WINDOW_HEIGHT);");                                                    // Save with pretty formatting
        FileHandler::writeLineToFile(buffer, "	float aspect = (float)w / (float)h;");                                                     // Save with pretty formatting
        FileHandler::writeLineToFile(buffer, "	glMatrixMode(GL_PROJECTION);");                                                            // Save with pretty formatting
        FileHandler::writeLineToFile(buffer, "	glLoadIdentity();");                                                                       // Save with pretty formatting
        FileHandler::writeLineToFile(buffer, "	gluPerspective(60.0, aspect, 1.0, 100.0);");                                               // Save with pretty formatting
        FileHandler::writeLineToFile(buffer, "}");                                                                                         // Save with pretty formatting
        FileHandler::writeLineToFile(buffer, "");                                                                                          // Save with pretty formatting
        FileHandler::writeLineToFile(buffer, "int main(int argc, char **argv)");                                                           // Save with pretty formatting
        FileHandler::writeLineToFile(buffer, "{");                                                                                         // Save with pretty formatting
        FileHandler::writeLineToFile(buffer, "	glutInit(&argc, argv);");                                                                  // Save with pretty formatting
        FileHandler::writeLineToFile(buffer, "	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); // Use single display buffer."); // Save with pretty formatting
        FileHandler::writeLineToFile(buffer, "	glutInitWindowSize(1500, 800);");                                                          // Save with pretty formatting
        char temp[100];
        sprintf(temp, "	glutCreateWindow(\"%s\");", name.c_str());
        FileHandler::writeLineToFile(buffer, temp);                                                                                                 // Save with pretty formatting
        FileHandler::writeLineToFile(buffer, "	InitGL();");                                                                                        // Save with pretty formatting
        FileHandler::writeLineToFile(buffer, "	glutReshapeFunc(ReSizeGLScene);");                                                                  // Save with pretty formatting
        FileHandler::writeLineToFile(buffer, "	glutKeyboardFunc(keyboard);");                                                                      // Save with pretty formatting
        FileHandler::writeLineToFile(buffer, "	glutMouseFunc(mouseButton);				   // For mouse button presses");                           // Save with pretty formatting
        FileHandler::writeLineToFile(buffer, "	glutMotionFunc(mouseMotion);			   // For mouse dragging (motion while holding a button)"); // Save with pretty formatting
        FileHandler::writeLineToFile(buffer, "	glutMouseWheelFunc(mouseWheel);");                                                                  // Save with pretty formatting
        FileHandler::writeLineToFile(buffer, "	Timer(0);");                                                                                        // Save with pretty formatting
        FileHandler::writeLineToFile(buffer, "	glutDisplayFunc(DrawGLScene);");                                                                    // Save with pretty formatting
        FileHandler::writeLineToFile(buffer, "	setupprojection();");                                                                               // Save with pretty formatting
        FileHandler::writeLineToFile(buffer, "	glutMainLoop();");                                                                                  // Save with pretty formatting
        FileHandler::writeLineToFile(buffer, "	return 0;");                                                                                        // Save with pretty formatting
        FileHandler::writeLineToFile(buffer, "}");                                                                                                  // Save with pretty formatting
        FileHandler::writeLineToFile(buffer, "");                                                                                                   // Save with pretty formatting
        FileHandler::writeLineToFile(buffer, "");                                                                                                   // Save with pretty formatting
        std::cout << "Code saved to " << buffer << " successfully." << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error saving file: " << e.what() << std::endl;
    }
}

#endif // GETCODE_H
