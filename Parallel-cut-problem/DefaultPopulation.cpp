#pragma once
#include "DefaultPopulation.h"

DefaultPopulation::DefaultPopulation(BaseSettingsHolder * settingsHolder) : BasePopulation(settingsHolder) {
	this->settingsHolder = settingsHolder;
	this->settingsHolder->Initialize();
	units = std::vector<BaseUnit*>(0);
	newUnits = std::vector<BaseUnit*>(0);
	for (int i = 0; i < this->settingsHolder->unitsSize; i++) {
		BaseUnit * newUnit = this->settingsHolder->CreateUnit();
		units.push_back(newUnit);
	}
}

bool DefaultPopulation::Step() {
	if (!CheckStop()) {
		units[0]->MpiSend();
		Sort();
		std::cout << units[0]->GetEvaluation() << std::endl;
		Mutate();
		Crossingover();
		return true;
	}
	else {
		return false;
	}
}

void DefaultPopulation::Mutate() {
	for (int i = 0; i < settingsHolder->newMutateUnits; i++) {
		int randomUnit = rand() % units.size();
		BaseUnit * newMutateUnit = units[randomUnit]->Copy();
		int randomGene = rand() % newMutateUnit->GetGenesCount();
		newMutateUnit->MutateGene(randomGene);
		newUnits.push_back(newMutateUnit);
	}
}

void DefaultPopulation::Sort() {
	//units.insert(units.end(), newUnits.begin(), newUnits.end());
	for (int i = 0; i < newUnits.size(); i++)
	{
		units.push_back(newUnits[i]->Copy());
		newUnits[i]->Delete();
	}
	newUnits.clear();
	for (int i = 0; i < units.size(); i++) {
		units[i]->Evaluate();
	}

	std::sort(units.begin(), units.end(), BaseUnit::sortFunction);

	while (units.size() > settingsHolder->unitsSize)
	{
		units.back()->Delete();
		units.pop_back();
	}

}

void DefaultPopulation::Crossingover() {
	for (int i = 0; i < settingsHolder->newCrossingoverUnits; i++) {
		int firstRandomUnit = rand() % units.size();
		int secondRandomUnit = rand() % units.size();
		BaseUnit * newCrossingoverUnit = units[firstRandomUnit]->Copy();
		newCrossingoverUnit->CrossingoverWithUnit(units[secondRandomUnit]);
		newUnits.push_back(newCrossingoverUnit);
	}
}

bool DefaultPopulation::CheckStop() {
	if (steps >= settingsHolder->maximumSteps) {
		return true;
	}
	return false;
}
