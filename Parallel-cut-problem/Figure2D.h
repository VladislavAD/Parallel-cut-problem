#pragma once
#include <list>
#include "Point.cpp"

class Figure2D {
private:

	std::list<Point> verticies;

public:

	Figure2D() {};

	Figure2D(std::list<Point> verticies) {
		this->verticies = verticies;
	}

};