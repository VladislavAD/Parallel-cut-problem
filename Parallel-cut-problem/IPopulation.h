#pragma once
#include "IUnit.h"
#include <vector>

class IPopulation {
private:
	std::vector<IUnit> units;

public:
	IPopulation() {};
	~IPopulation() {};
	virtual IUnit * GetUnit(int unitNumber) = 0;
	virtual void AddUnit(IUnit unit) = 0;
	virtual void Step() = 0;
};