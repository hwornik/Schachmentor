#pragma once
class Moving
{
public:
	Moving();
	~Moving();
	int getX();
	int getY();
	int getW();
	void setX(int x);
	void setY(int y);
	void setW(int w);
	Moving *getnext();
	void setNext(Moving *move);
private:
	int x, y, w;
	Moving *move;
};

