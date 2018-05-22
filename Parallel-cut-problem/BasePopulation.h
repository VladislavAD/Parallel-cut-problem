#pragma once
#include "BaseUnit.h"
#include "BaseSettingsHolder.h"
#include <vector>

class BasePopulation : public MpiFriendly {
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
	void MpiSendUnit(int unitNumber, int destination, MPI_Comm communicator) {}
	void MpiReceiveUnit(int source, MPI_Comm communicator) {}
};