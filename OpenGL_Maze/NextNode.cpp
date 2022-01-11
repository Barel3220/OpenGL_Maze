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
