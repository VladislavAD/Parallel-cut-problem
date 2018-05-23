#pragma once
#include "MpiFriendly.h"
//#ifndef CutGene_H
//#define CutGene_H

class CutGene {
public:
	float positionX;
	float rotation;
	int order;

	CutGene();

	CutGene(float positionX, float rotation, int order);

	/*CutGene& operator=(const CutGene& obj) {
		if (this != &obj) {
			this->positionX = obj.positionX;
			this->rotation = obj.rotation;
			this->order = obj.order;
		}
		return *this;
	}*/
};

//#endif // CutGene_H
