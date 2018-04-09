#include <list>
#include "Point.cpp"
#include "Position.cpp"

class CutGene {
public:
	float positionX;
	int order;

	CutGene(float positionX, int order) {
		this->positionX = positionX;
		this->order = order;
	}
};