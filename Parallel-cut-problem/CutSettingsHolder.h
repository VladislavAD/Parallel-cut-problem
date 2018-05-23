#pragma once
#include "CutUnit.h"
#include "BaseSettingsHolder.h"

class CutSettingsHolder : public BaseSettingsHolder {
public:
	float lineWidth = 2.1;
	std::vector<Figure2D*> figures;

	void Initialize();
	BaseUnit * CreateUnit();
	void MpiSend(int destination, MPI_Comm communicator);
	void MpiReceive(int source, MPI_Comm communicator);

};
