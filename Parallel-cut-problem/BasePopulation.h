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
	BasePopulation(BaseSettingsHolder * settingsHolder) {};
	virtual bool Step() = 0;
	virtual void Mutate() = 0;
	virtual void Sort() = 0;
	virtual void Crossingover() = 0;
	virtual bool CheckStop() = 0;
	//void MpiSendUnit(int unitNumber, int destination, MPI_Comm communicator) {}
	//void MpiReceiveUnit(int source, MPI_Comm communicator) {}
};