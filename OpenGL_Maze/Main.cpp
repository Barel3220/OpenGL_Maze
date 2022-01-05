#include <gl/glut.h>

using namespace std;

// this function will be called by GLUT every time the window needs to be painted.
void renderDisplay()
{	
	glClear(GL_COLOR_BUFFER_BIT);

	// drawing triangle
	glBegin(GL_TRIANGLES);
	glVertex3f(-.5, -.5, .0);
	glVertex3f(.5, .0, .0);
	glVertex3f(.0, .5, .0);
	glEnd();

	glutSwapBuffers();
}

void main(int argc, char* argv[])
{
	// init GLUT
	// must first initializing GLUT function to be able using glut-functions
	glutInit(&argc, argv);
	// top left corner position
	glutInitWindowPosition(200, 100);
	glutInitWindowSize(600, 600);
	// the mode parameter is a boolean combination (OR bit wise) of the possible values in the GLUT library
	// must specify the color mode, number and type of buffers.
	// here the color mode is RGB and the buffer is a double buffer which required for smooth animation.
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	// creating the window and assigning a title
	glutCreateWindow("Test Window Title");
	
	// register callbacks // refresh function
	glutDisplayFunc(renderDisplay);

	// start GLUT event processing cycle
	glutMainLoop();
}