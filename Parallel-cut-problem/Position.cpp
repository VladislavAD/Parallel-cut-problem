#pragma once
#include "Point.cpp"

class Position : public Point {
public:
	float r;

	Position() {}

	Position(float x, float y, float r) : Point(x,y) {
		this->r = r;
	}

	Position Add(Position second) {
		this->x += second.x;
		this->y += second.y;
		this->r += second.r;
	}
};