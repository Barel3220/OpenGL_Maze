#pragma once
#include "Point2D.h"
class NextNode
{
private:
	Point2D* _source_point;
	Point2D* _target_point;
	NextNode* _parent_node;
	int _f;
	int _g;
public:
	NextNode();
	~NextNode();
	NextNode(Point2D*, Point2D*);
};
