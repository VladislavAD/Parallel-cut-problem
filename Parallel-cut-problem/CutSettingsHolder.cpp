#include "CutSettingsHolder.h"

void CutSettingsHolder::Initialize() {
	CutUnit::SetLineWidth(lineWidth);
	for (int i = 0; i < figures.size(); i++)
	{
		CutUnit::AddFigure(figures[i]);
	}
}

BaseUnit * CutSettingsHolder::CreateUnit() { 
	CutUnit newUnit = CutUnit();
	return new CutUnit();
}