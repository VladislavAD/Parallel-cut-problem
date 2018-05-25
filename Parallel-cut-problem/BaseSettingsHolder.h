#pragma once
#include "BaseUnit.h"
#include "MpiFriendly.h"

class BaseSettingsHolder : public MpiFriendly{
public:
	virtual void Initialize() = 0;
	virtual BaseUnit * CreateUnit() = 0;
};