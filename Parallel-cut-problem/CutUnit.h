#include "IUnit.h"
#include "CutGene.h"
#include <list>

class CutUnit : public IUnit {
public: 
	
private:
	std::list<CutGene> genesList;
	float evaluation;
	
};