#pragma once
#include "MpiFriendly.h"

class BaseUnit : public MpiFriendly {
public:
	BaseUnit() {};
	~BaseUnit() {};
	virtual int GetGenesCount() { return 0; }
	virtual void MutateGene(int number) {}
	virtual float GetEvaluation() { return 0; }
	virtual BaseUnit * CrossingoverWithUnit(BaseUnit * unit) { return unit; }
	virtual void * ExtractGene(int geneNumber) { return nullptr; }
	virtual void Evaluate() {}
	virtual void Delete() {}
	virtual BaseUnit * Copy() { return nullptr; }
	//virtual void MpiSend() {};

	static bool sortFunction(BaseUnit * left, BaseUnit * right) {
		if (left->GetEvaluation() < right->GetEvaluation()) {
			return true;
		}
		else {
			return false;
		}
	}
};