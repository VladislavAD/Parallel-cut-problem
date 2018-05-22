#pragma once
#include "BaseUnit.h"

class BaseSettingsHolder {
public:
	int unitsSize = 100;
	int maximumSteps = 1000;
	int newMutateUnits = 10;
	int newCrossingoverUnits = 10;
	virtual void Initialize() {};
	virtual BaseUnit * CreateUnit() { return nullptr; }
	virtual void MpiSend() {};
	virtual void MpiReceive() {};
};