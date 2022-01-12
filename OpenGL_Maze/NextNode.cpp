#include "NextNode.h"

NextNode::NextNode() : _source_point(nullptr), _target_point(nullptr), _parent_node(nullptr), _g(0), _f(0)
{
}

NextNode::~NextNode()
{
}

NextNode::NextNode(Point2D* source, Point2D* target)
{
	this->_source_point = source;
	this->_target_point = target;
	this->_parent_node = nullptr;
	this->_f = 0;
	this->_g = 0;
}

NextNode::NextNode(const NextNode* other)
{
	this->_source_point = new Point2D(other->_source_point->GetY(), other->_source_point->GetX());
	this->_target_point = other->_target_point;
	this->_parent_node = other->_parent_node;
	this->_f = other->_f;
	this->_g = other->_g;
}

Point2D* NextNode::GetSourcePoint()
{
	return this->_source_point;
}

void NextNode::SetParentNode(NextNode* parent)
{
	this->_parent_node = parent;
}

void NextNode::TryMove(int y_direction, int x_direction)
{
	// updating the move
	this->SetPoint(this->_source_point->GetY() + y_direction, this->_source_point->GetX() + x_direction);
	// updating _g
	this->SetG(this->_g + 1);
	// calculating f
	this->CalculateF();
}

void NextNode::SetPoint(int y, int x)
{
	this->_source_point->SetY(y);
	this->_source_point->SetX(x);
}

void NextNode::FixG()
{
	this->_g--;
}

void NextNode::FixPoint(int y_direction, int x_direction)
{
	// correcting the move
	this->SetPoint(this->_source_point->GetY() - y_direction, this->_source_point->GetX() - x_direction);
}

NextNode* NextNode::GetParent()
{
	return this->_parent_node;
}

int NextNode::GetF()
{
	return this->_f;
}

void NextNode::SetG(int g)
{
	this->_g = g;
}

void NextNode::CalculateF()
{
	this->_f = (int)(.2 * this->_g + .8 * this->GetHeuristicDistance());
}

int NextNode::GetHeuristicDistance()
{
	int _y = this->_source_point->GetY() - this->_target_point->GetY();
	int _x = this->_source_point->GetX() - this->_target_point->GetX();
	
	return (int)sqrt(pow(_y, 2) + pow(_x, 2));
}
