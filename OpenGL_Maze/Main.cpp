#include <gl/glut.h>
#include <stdlib.h>
#include <time.h>

using namespace std;

// declaring variables
const int HEIGHT = 800;
const int WIDTH = 800;

// declaring const ints for numbering the maze
const int SPACE = 0;
const int WALL = 1;
const int START = 2;
const int TARGET = 3;

const int MAZE_SIZE = 200;
const double SQAURE_SIZE = 2.0 / MAZE_SIZE;

int _maze[MAZE_SIZE][MAZE_SIZE];

void Init()
{
	// clear maze
	for (int row = 0; row < MAZE_SIZE; row++)
		for (int column = 0; column < MAZE_SIZE; column++)
			_maze[row][column] = SPACE;

	// drawing random walls to create the maze picture
	for (int row = 1; row < MAZE_SIZE - 1; row++)
		for (int column = 1; column < MAZE_SIZE - 1; column++)
			if (!(row % 2) && (rand() % (MAZE_SIZE / 2) < 40))
				_maze[row][column] = WALL;
			else if (rand() % (MAZE_SIZE / 2) < 20)
				_maze[row][column] = WALL;

	// drawing outer walls
	for (int i = 0; i < MAZE_SIZE; i++)
		// left // right // top // bottom
		_maze[i][0] = _maze[i][MAZE_SIZE - 1] = _maze[0][i] = _maze[MAZE_SIZE - 1][i] = WALL;

	// start point
	_maze[MAZE_SIZE / 2][MAZE_SIZE / 2] = START;

	// target point
	_maze[rand() % MAZE_SIZE][rand() % MAZE_SIZE] = TARGET;
	
}

void DrawMazeSquares()
{
	// switch case for indicating what color to draw the square
	for (int row = 0; row < MAZE_SIZE; row++)
		for (int column = 0; column < MAZE_SIZE; column++)
		{
			switch (_maze[row][column])
			{
			case SPACE:
				glColor3d(1, 1, 1); // white;
				break;
			case WALL:
				glColor3d(.4, 0, 0); // dark red;
				break;
			case START:
				glColor3d(0, 0, 1); // blue;
				break;
			case TARGET:
				glColor3d(0, 1, 0); // green;
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
}

// this function will be called by GLUT every time the window needs to be painted.
void RenderDisplay()
{	
	// indicates the buffers currently enabled for color writing.
	glClear(GL_COLOR_BUFFER_BIT);

	// drawing the squares with colors
	DrawMazeSquares();

	glutSwapBuffers();
}

void RightClickMenu(int choise)
{
	switch (choise)
	{
	case 1:
		Init();
		// calls indirectly to display method
		glutPostRedisplay();
		break;
	default:
		break;
	}
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
	glutDisplayFunc(RenderDisplay);

	// sketching the maze
	Init();

	// creating a menu to re-draw the maze
	glutCreateMenu(RightClickMenu);
	// adding options to the menu
	glutAddMenuEntry("Draw Maze", 1);
	// attaching the right button to the menu
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	// start GLUT event processing cycle
	glutMainLoop();
}