#pragma once
#include "BaseUnit.h"
#include "MpiFriendly.h"

class BaseSettingsHolder : public MpiFriendly{
public:
	int unitsSize;
	int maximumSteps;
	int newMutateUnits;
	int newCrossingoverUnits;
	virtual void Initialize() = 0;
	virtual BaseUnit * CreateUnit() = 0;
};