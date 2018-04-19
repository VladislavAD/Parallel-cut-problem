#pragma once
#include "CutUnit.h"
#include <vector>

class DummyPopulation {
private:
	std::vector<CutUnit> units;
	std::vector<CutUnit> newUnits;
	int unitsSize;
	int maximumSteps;
	int steps = 0;
	int newMutateUnits;
	int newCrossingoverUnits;

public:
	DummyPopulation() {
		unitsSize = 100;
		maximumSteps = 1000;
		newMutateUnits = 10;
		newCrossingoverUnits = 10;
		for (int i = 0; i < 9; i++) {
			CutUnit::AddFigure(Figure2D());
		}
	}

	bool Step() {
		if (!CheckStop()) {
			Sort();
			Mutate();
			Crossingover();
			return true;
		}
		else {
			return false;
		}
	}

	void Mutate() {
		for (int i = 0; i < newMutateUnits; i++) {
			int randomUnit = rand() % units.size();
			CutUnit newMutateUnit = units[randomUnit];
			newMutateUnit.MutateGene();
			newUnits.push_back(newMutateUnit);
		}
	}

	void Sort() {
		units.insert(units.end(), newUnits.begin(), newUnits.end());
		for (int i = 0; i < units.size(); i++) {
			units[i].Evaluate();
		}

		std::sort(units.begin(), units.end(), CutUnit::sortFunction);

		while (units.size() > unitsSize)
		{
			units.pop_back();
		}
	}

	void Crossingover() {
		for (int i = 0; i < newCrossingoverUnits; i++) {
			int firstRandomUnit = rand() % units.size();
			int secondRandomUnit = rand() % units.size();
			CutUnit newCrossingoverUnit = units[firstRandomUnit];
			newCrossingoverUnit.DummyCrossingover(units[secondRandomUnit]);
			newUnits.push_back(newCrossingoverUnit);
		}
	}

	bool CheckStop() {
		if (steps >= maximumSteps) {
			return true;
		}
		return false;
	}
};
