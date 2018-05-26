#pragma once
#include "BaseUnit.h"
#include "MpiFriendly.h"

class BaseSettingsHolder : public MpiFriendly{
public:
	int unitsSize = 10;
	int maximumSteps = 10;
	int newMutateUnits = 1;
	int newCrossingoverUnits = 1;

	virtual void Initialize() = 0;
	virtual BaseUnit * CreateUnit() = 0;
};