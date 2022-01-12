#pragma once
#include <math.h>
#include "Point2D.h"

class NextNode
{
private:
	Point2D* _source_point;
	Point2D* _target_point;
	NextNode* _parent_node;
	int _f;
	int _g;
	void CalculateF();
	void SetG(int);
	void SetPoint(int, int);
	int GetHeuristicDistance();
public:
	NextNode();
	~NextNode();
	NextNode(Point2D*, Point2D*);
	NextNode(const NextNode*);
	Point2D* GetSourcePoint();
	void SetParentNode(NextNode*);
	void TryMove(int, int);
	void FixG();
	void FixPoint(int, int);
	int GetF();
};

