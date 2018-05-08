#pragma once
#include "CutUnit.h"
#include <vector>
#include <iostream>
#include <fstream>

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
		CutUnit::SetLineWidth(2.1);
		units = std::vector<CutUnit>(0);
		newUnits = std::vector<CutUnit>(0);
		for (int i = 0; i < 4; i++) {
			CutUnit::AddFigure(Figure2D());
		}
		for (int i = 0; i < unitsSize; i++) {
			CutUnit newUnit = CutUnit();
			newUnit.InitializeGenes();
			units.push_back(newUnit);
		}
	}

	bool Step() {
		if (!CheckStop()) {
			Sort();
			std::cout << units[0].GetEvaluation() << std::endl;
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
		std::string output = "";
		output = CutUnit::PrintFigures() + std::to_string(units.size()) + '\n';
		units.insert(units.end(), newUnits.begin(), newUnits.end());
		for (int i = 0; i < units.size(); i++) {
			units[i].Evaluate();
		}

		std::sort(units.begin(), units.end(), CutUnit::sortFunction);

		while (units.size() > unitsSize)
		{
			units.pop_back();
		}

		for (int i = 0; i < units.size(); i++) {
			output += units[i].GetPositions();
		}

		// ��� ����� �������������� ����
		std::ofstream out("output.txt");
		out << output;
		out.close();
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

	void PrintPopulation() {

	}
};
