#pragma once
#include "NextNode.h"
class CompareNodes
{
public:
	CompareNodes();
	~CompareNodes();
	bool operator () (NextNode& node_1, NextNode& node_2);
};

