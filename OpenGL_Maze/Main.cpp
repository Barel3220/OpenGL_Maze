#include <gl/glut.h>
#include <stdlib.h>
#include <time.h>

using namespace std;

// declaring variables
const int HEIGHT = 600;
const int WIDTH = 600;

// declaring const ints for numbering the maze
const int SPACE = 0;
const int START = 1;
const int WALL = 2;

const int MAZE_SIZE = 200;
const double SQAURE_SIZE = 2.0 / MAZE_SIZE;

int _maze[MAZE_SIZE][MAZE_SIZE];

void init()
{
	// clear maze
	for (int row = 0; row < MAZE_SIZE; row++)
		for (int column = 0; column < MAZE_SIZE; column++)
			_maze[row][column] = 0;

	// start point
	_maze[MAZE_SIZE / 2][MAZE_SIZE / 2] = 1;

	// drawing outer walls
	for (int i = 0; i < MAZE_SIZE; i++)
		// left // right // top // bottom
		_maze[i][0] = _maze[i][MAZE_SIZE - 1] = _maze[0][i] = _maze[MAZE_SIZE - 1][i] = 2;
	
}

// this function will be called by GLUT every time the window needs to be painted.
void renderDisplay()
{	
	// indicates the buffers currently enabled for color writing.
	glClear(GL_COLOR_BUFFER_BIT);

	// switch case for indicating what color to draw the square
	for (int row = 0; row < MAZE_SIZE; row++)
		for (int column = 0; column < MAZE_SIZE; column++)
		{
			switch (_maze[row][column])
			{
			case SPACE:
				glColor3d(1, 1, 1); // white;
				break;
			case START:
				glColor3d(0, 0, 1); // blue;
				break;
			case WALL:
				glColor3d(.4, 0, 0); // dark red;
				break;
			default:
				break;
			}
			// drawing square for every color
			glBegin(GL_POLYGON);
			glVertex2d(column * SQAURE_SIZE - 1 - SQAURE_SIZE / 2, row * SQAURE_SIZE - 1 + SQAURE_SIZE / 2);
			glVertex2d(column * SQAURE_SIZE - 1 + SQAURE_SIZE / 2, row * SQAURE_SIZE - 1 + SQAURE_SIZE / 2);
			glVertex2d(column * SQAURE_SIZE - 1 + SQAURE_SIZE / 2, row * SQAURE_SIZE - 1 - SQAURE_SIZE / 2);
			glVertex2d(column * SQAURE_SIZE - 1 - SQAURE_SIZE / 2, row * SQAURE_SIZE - 1 - SQAURE_SIZE / 2);
			glEnd();
		}

	glutSwapBuffers();
}

void main(int argc, char* argv[])
{
	// init GLUT
	// must first initializing GLUT function to be able using glut-functions
	glutInit(&argc, argv);
	// top left corner position
	glutInitWindowPosition(200, 100);
	glutInitWindowSize(WIDTH, HEIGHT);
	// the mode parameter is a boolean combination (OR bit wise) of the possible values in the GLUT library
	// must specify the color mode, number and type of buffers.
	// here the color mode is RGB and the buffer is a double buffer which required for smooth animation.
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	// creating the window and assigning a title
	glutCreateWindow("Test Window Title");
	
	// register callbacks // refresh function
	glutDisplayFunc(renderDisplay);

	// sketching the maze
	init();

	// start GLUT event processing cycle
	glutMainLoop();
}