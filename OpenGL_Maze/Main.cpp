#include <gl/glut.h>
#include <stdlib.h>
#include <time.h>
#include <vector>
#include <queue>
#include "Point2D.h"
#include "NextNode.h"
#include "CompareNodes.h"
#include <iostream>

using namespace std;

// declaring variables
const int HEIGHT = 800;
const int WIDTH = 800;

// declaring const ints for numbering the maze
const int SPACE = 0;
const int WALL = 1;
const int SOURCE = 2;
const int TARGET = 3;
const int VISITED_SOURCE_TARGET = 4;
const int VISITED_TARGET_SOURCE = 5;
const int VISITING = 6;
const int PATH = 9;

const int MAZE_SIZE = 200;
const double SQAURE_SIZE = 2.0 / MAZE_SIZE;

int _maze[MAZE_SIZE][MAZE_SIZE];

// boolean to start BDS
bool _bds_started = false;
// boolean to start A*
bool _a_star_started = false;

// source and target queues // declared here for initializing - BDS
vector<Point2D*> _source_queue;
vector<Point2D*> _target_queue;

// parents matrices - BDS
Point2D* _sources_parents[MAZE_SIZE][MAZE_SIZE];
Point2D* _targets_parents[MAZE_SIZE][MAZE_SIZE];

// priority queue - A*
priority_queue <NextNode*, vector<NextNode*>, CompareNodes> _priority_queue;

// vectors for gray and black queues
// gray for visiting nodes and black for visited nodes
vector <NextNode*> _gray;
vector <NextNode*> _black;

void Init()
{
	// clearing parents matrices
	for (int row = 0; row < MAZE_SIZE; row++)
		for (int column = 0; column < MAZE_SIZE; column++)
		{
			_sources_parents[row][column] = nullptr;
			_targets_parents[row][column] = nullptr;
		}

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

	// source point
	auto _temp_source_ptr = new Point2D(MAZE_SIZE / 2, MAZE_SIZE / 2);
	_maze[_temp_source_ptr->GetY()][_temp_source_ptr->GetX()] = SOURCE;
	_source_queue.push_back(_temp_source_ptr);

	// target point
	auto _temp_target_ptr = new Point2D(rand() % MAZE_SIZE, rand() % MAZE_SIZE);
	_maze[_temp_target_ptr->GetY()][_temp_target_ptr->GetX()] = TARGET;
	_target_queue.push_back(_temp_target_ptr);

	// entering the points into node
	auto _first_node = new NextNode(_temp_source_ptr, _temp_target_ptr);
	// updating the priority queue with the first node
	_priority_queue.emplace(_first_node);
	// updating gray vector for visiting first node
	_gray.push_back(_first_node);
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
			case SOURCE:
				glColor3d(0, 0, 1); // blue;
				break;
			case TARGET:
				glColor3d(0, 1, 0); // green;
				break;
			case VISITED_SOURCE_TARGET:
				glColor3d(.2, .5, .6); // pale blue
				break;
			case VISITED_TARGET_SOURCE:
				glColor3d(.4, .5, .1); // pale green
				break;
			case VISITING:
				glColor3d(1, .8, 0); // orange;
				break;
			case PATH:
				glColor3d(.8, .5, 1); // pink
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

void UpdateSourceParent_Queue(Point2D* temporary, int y_direction, int x_direction)
{
	auto temporary_ptr = new Point2D(temporary->GetY() + y_direction, temporary->GetX() + x_direction);
	// updating the parent of the point
	_sources_parents[temporary->GetY() + y_direction][temporary->GetX() + x_direction] = temporary;
	// updating the queue
	_source_queue.push_back(temporary_ptr);
}

void UpdateTargetParent_Queue(Point2D* temporary, int y_direction, int x_direction)
{
	auto temporary_ptr = new Point2D(temporary->GetY() + y_direction, temporary->GetX() + x_direction);
	// updating the parent of the point
	_targets_parents[temporary->GetY() + y_direction][temporary->GetX() + x_direction] = temporary;
	// updating the queue
	_target_queue.push_back(temporary_ptr);
}

void ShowBidirectionalSearchPath(Point2D* source, Point2D* target)
{
	while (_maze[source->GetY()][source->GetX()] != SOURCE)
	{
		_maze[source->GetY()][source->GetX()] = PATH;
		source = _sources_parents[source->GetY()][source->GetX()];
	}

	while (_maze[target->GetY()][target->GetX()] != TARGET)
	{
		_maze[target->GetY()][target->GetX()] = PATH;
		target = _targets_parents[target->GetY()][target->GetX()];
	}

	for (size_t i = 0; i < _source_queue.size(); i++)
		delete _source_queue[i];
	for (size_t i = 0; i < _target_queue.size(); i++)
		delete _target_queue[i];
}

void CheckMaze(Point2D* temporary, bool _is_source, int y_direction, int x_direction) {
	if (_is_source)
	{
		if (_maze[temporary->GetY() + y_direction][temporary->GetX() + x_direction] == VISITED_TARGET_SOURCE)
		{
			// stopping the search
			_bds_started = false;
			// marking the last point for drawing the path
			_maze[temporary->GetY() + y_direction][temporary->GetX() + x_direction] = PATH;
			// updating the parent for draw all the path
			auto last_ptr = _targets_parents[temporary->GetY() + y_direction][temporary->GetX() + x_direction];
			// drawing the path
			ShowBidirectionalSearchPath(temporary, last_ptr);
		}
	}
	else
		if (_maze[temporary->GetY() + y_direction][temporary->GetX() + x_direction] == VISITED_SOURCE_TARGET)
		{
			// stopping the search
			_bds_started = false;
			// marking the last point for drawing the path
			_maze[temporary->GetY() + y_direction][temporary->GetX() + x_direction] = PATH;
			// updating the parent for draw all the path
			auto last_ptr = _sources_parents[temporary->GetY() + y_direction][temporary->GetX() + x_direction];
			// drawing the path
			ShowBidirectionalSearchPath(last_ptr, temporary);
		}
}

void TryMove_BDS(Point2D* temporary, bool _is_source, int y_direction, int x_direction)
{
	// check if there's an intersection first
	CheckMaze(temporary, _is_source, y_direction, x_direction);
	// try to move
	if (_bds_started && _maze[temporary->GetY() + y_direction][temporary->GetX() + x_direction] == SPACE)
	{
		_maze[temporary->GetY() + y_direction][temporary->GetX() + x_direction] = VISITING;
		if (_is_source)
			UpdateSourceParent_Queue(temporary, y_direction, x_direction);
		else
			UpdateTargetParent_Queue(temporary, y_direction, x_direction);
	}
}

void BidirectionalSearch()
{
	/*
		bidirectional search is a graph search algorithm which find smallest path from source to target vertex.
		it runs two simultaneous search:
		1. forward search - from source to target
		2. backward search - from target to source
	*/

	// source and target points
	Point2D* _source_ptr;
	Point2D* _target_ptr;

	if (_source_queue.empty() || _target_queue.empty())
		_bds_started = false;
	else
	{
		// getting the source point from queue and removing it from the queue
		_source_ptr = _source_queue[0];
		_source_queue.erase(_source_queue.begin());
		// getting the target point from queue and removing it from the queue
		_target_ptr = _target_queue[0];
		_target_queue.erase(_target_queue.begin());

		// checking if there is an intersection between source and target
		if (_maze[_source_ptr->GetY()][_source_ptr->GetX()] == VISITED_TARGET_SOURCE ||
			_maze[_target_ptr->GetY()][_target_ptr->GetX()] == VISITED_SOURCE_TARGET)
			_bds_started = false;
		else
		{
			if (_maze[_source_ptr->GetY()][_source_ptr->GetX()] != SOURCE &&
				_maze[_target_ptr->GetY()][_target_ptr->GetX()] != TARGET)
			{
				_maze[_source_ptr->GetY()][_source_ptr->GetX()] = VISITED_SOURCE_TARGET;
				_maze[_target_ptr->GetY()][_target_ptr->GetX()] = VISITED_TARGET_SOURCE;
			}

			// try to move source up
			TryMove_BDS(_source_ptr, true, 1, 0);
			// try to move target up
			TryMove_BDS(_target_ptr, false, 1, 0);

			// try to move source down
			TryMove_BDS(_source_ptr, true, -1, 0);
			// try to move target down
			TryMove_BDS(_target_ptr, false, -1, 0);

			// try to move source right
			TryMove_BDS(_source_ptr, true, 0, 1);
			// try to move target right
			TryMove_BDS(_target_ptr, false, 0, 1);

			// try to move source left
			TryMove_BDS(_source_ptr, true, 0, -1);
			// try to move target left
			TryMove_BDS(_target_ptr, false, 0, -1);
		}
	}
}

void TryMove_A_Star(NextNode* temporary, int y_direction, int x_direction)
{
	// saving the current node as parent
	NextNode* _temporary_parent = new NextNode(temporary);
	// creating a temp pointer to current
	NextNode* _temporary_pointer;

	// gray iterator for gray vector
	vector<NextNode*>::iterator _gray_iterator;
	// black iterator for black vector
	vector<NextNode*>::iterator _black_iterator;

	if (_maze[temporary->GetSourcePoint()->GetY() + y_direction][temporary->GetSourcePoint()->GetX() + x_direction] == TARGET)
		_a_star_started = false;
	if (_a_star_started && _maze[temporary->GetSourcePoint()->GetY() + y_direction][temporary->GetSourcePoint()->GetX() + x_direction] == SPACE)
	{
		// marking the movement as visiting
		_maze[temporary->GetSourcePoint()->GetY() + y_direction][temporary->GetSourcePoint()->GetX() + x_direction] = VISITING;

		// make the move
		temporary->TryMove(y_direction, x_direction);

		_temporary_pointer = new NextNode(temporary);
		// updating the parent
		_temporary_pointer->SetParentNode(_temporary_parent);

		// fixing the g
		temporary->FixG();

		// getting the iterators
		_gray_iterator = find(_gray.begin(), _gray.end(), _temporary_pointer);
		_black_iterator = find(_black.begin(), _black.end(), _temporary_pointer);
		// checking if the updated current is in black or gray (already visited or about to be)
		if (_black_iterator == _black.end() && _gray_iterator == _gray.end())
		{
			_priority_queue.emplace(_temporary_pointer);
			_gray.push_back(_temporary_pointer);
		}
		// fixing the move we've being made - in case we didn't find target yet
		temporary->FixPoint(y_direction, x_direction);
	}

	if (!_a_star_started)
	{

	}
}

void A_StarSearch()
{
	/* 
		a* search algorithm is one of the best and popular technique used in path - finding and graph traversals.
		unlike other traversal technique, a* has "brains", it calculates the distance between current point to the
		target and prioritize the best option to complete the task.
	*/
	NextNode* _current_node;

	// gray iterator for gray vector
	vector<NextNode*>::iterator _gray_iterator;

	if (_priority_queue.empty())
		_a_star_started = false;
	else
	{
		// saving the current node for advancing the algorithm
		_current_node = _priority_queue.top();
		
		// taking out the node from the priority queue
		_priority_queue.pop();

		// entering the node into the black queue because we already checked it
		_black.push_back(_current_node);

		// finding the node in the gray queue and removing it
		_gray_iterator = find(_gray.begin(), _gray.end(), _current_node);
		_gray.erase(_gray_iterator);

		// checking if the current node is getting us to the target
		if (_maze[_current_node->GetSourcePoint()->GetY()][_current_node->GetSourcePoint()->GetX()] == TARGET)
			_a_star_started = false;
		else
		{
			if (_maze[_current_node->GetSourcePoint()->GetY()][_current_node->GetSourcePoint()->GetX()] != SOURCE)
				_maze[_current_node->GetSourcePoint()->GetY()][_current_node->GetSourcePoint()->GetX()] = VISITED_SOURCE_TARGET;

			// try to move up
			TryMove_A_Star(_current_node, 1, 0);

			// try to move down
			TryMove_A_Star(_current_node, -1, 0);

			// try to move right
			TryMove_A_Star(_current_node, 0, 1);

			// try to move left
			TryMove_A_Star(_current_node, 0, -1);
		}
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
		_bds_started = true;
		break;
	case 2:
		_a_star_started = true;
		break;
	default:
		break;
	}
}

void Idle()
{
	if (_bds_started)
		BidirectionalSearch();
	if (_a_star_started)
		A_StarSearch();
	// calls indirectly to display method
	glutPostRedisplay();
}

int main(int argc, char* argv[])
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
	glutCreateWindow("Maze Solver");
	
	// register callbacks // refresh function
	glutDisplayFunc(RenderDisplay);
	// idle function
	glutIdleFunc(Idle);

	// sketching the maze
	Init();

	// creating a menu to re-draw the maze
	glutCreateMenu(RightClickMenu);
	// adding options to the menu
	glutAddMenuEntry("BDS", 1);
	glutAddMenuEntry("A*", 2);
	// attaching the right button to the menu
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	// start GLUT event processing cycle
	glutMainLoop();

	return 0;
}