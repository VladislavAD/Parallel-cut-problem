#pragma once
#include "DefaultPopulation.h"
#include "CutSettingsHolder.h"

int main() {
	CutSettingsHolder * settingsHolder = new CutSettingsHolder();
	settingsHolder->unitsSize = 10;
	settingsHolder->newMutateUnits = 2;
	settingsHolder->newCrossingoverUnits = 2;
	for (int i = 0; i < 4; i++)
	{
		settingsHolder->figures.push_back(new Figure2D());
	}
	DefaultPopulation population = DefaultPopulation(settingsHolder);
	while (population.Step()) {}
	return 0;
}