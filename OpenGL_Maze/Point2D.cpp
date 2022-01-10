#include "Point2D.h"

Point2D::Point2D() : x(0), y(0)
{
}

Point2D::~Point2D()
{
}

Point2D::Point2D(int y, int x)
{
	this->y = y;
	this->x = x;
}

int Point2D::GetX() const
{
	return this->x;
}

int Point2D::GetY() const
{
	return this->y;
}

void Point2D::SetX(int x)
{
	this->x = x;
}

void Point2D::SetY(int y)
{
	this->y = y;
}
