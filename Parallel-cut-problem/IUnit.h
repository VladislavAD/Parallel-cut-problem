#pragma once

class IUnit {
public:
	virtual int getGenesCount();
	virtual void mutateGene(int number);
	virtual float getEvaluation();
	virtual IUnit crossingoverWithUnit(IUnit unit);
};