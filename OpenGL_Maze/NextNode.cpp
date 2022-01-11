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
	this->SetPoint(this->_source_point->GetY() + y_direction, this->_source_point->GetX() + x_direction);
	// updating _g
	// calculating f
}

void NextNode::SetPoint(int y, int x)
{
	this->_source_point->SetY(y);
	this->_source_point->SetX(x);
}
