#include "CompareNodes.h"

CompareNodes::CompareNodes()
{
}

CompareNodes::~CompareNodes()
{
}

bool CompareNodes::operator()(NextNode* node_1, NextNode* node_2)
{
	if (node_1->GetF() > node_2->GetF())
		return true;
	else
		return false;
}
