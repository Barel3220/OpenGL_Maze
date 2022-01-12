#pragma once
class Point2D
{
private:
	int x;
	int y;
public:
	Point2D();
	~Point2D();
	Point2D(int, int);
	int GetX() const;
	int GetY() const;
	void SetX(int);
	void SetY(int);
};

