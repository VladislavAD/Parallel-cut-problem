#pragma once
#include "CutUnit.h"
#include "BaseSettingsHolder.h"

class CutSettingsHolder : public BaseSettingsHolder {
public:
	//int unitsSize = 10;
	//int maximumSteps = 10;
	//int newMutateUnits = 1;
	//int newCrossingoverUnits = 1;
	float lineWidth = 2.1;
	std::vector<Figure2D*> figures;

	//CutSettingsHolder();
	//~CutSettingsHolder();

	//void Initialize();
	//BaseUnit * CreateUnit();
	void MpiSend(int destination, MPI_Comm communicator);
	void MpiReceive(int source, MPI_Comm communicator);

};
