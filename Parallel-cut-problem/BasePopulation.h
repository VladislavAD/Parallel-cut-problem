#pragma once
#include "BaseUnit.h"
#include "BaseSettingsHolder.h"
#include <vector>

class BasePopulation {
protected:
	BaseSettingsHolder * settingsHolder;
	std::vector<BaseUnit*> units;
	std::vector<BaseUnit*> newUnits;
	int steps = 0;

public:
	BasePopulation(BaseSettingsHolder * settingsHolder) {}

	bool Step() {}

	void Mutate() {}

	void Sort() {}

	void Crossingover() {}

	bool CheckStop() {}
};