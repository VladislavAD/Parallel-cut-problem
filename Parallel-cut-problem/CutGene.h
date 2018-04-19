#pragma once
#include <list>
#include "Point.cpp"
#include "Position.cpp"

class CutGene {
public:
	float positionX;
	float rotation;
	int order;

	CutGene() {}

	CutGene(float positionX, float rotation, int order) {
		this->positionX = positionX;
		this->rotation = rotation;
		this->order = order;
	}

	/*CutGene& operator=(const CutGene& obj) {
		if (this != &obj) {
			this->positionX = obj.positionX;
			this->rotation = obj.rotation;
			this->order = obj.order;
		}
		return *this;
	}*/
};