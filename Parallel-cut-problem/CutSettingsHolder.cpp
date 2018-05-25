#include "CutSettingsHolder.h"

CutSettingsHolder::CutSettingsHolder()
{
	figures = std::vector<Figure2D*>(0);
}

CutSettingsHolder::~CutSettingsHolder()
{
}

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

void CutSettingsHolder::MpiSend(int destination, MPI_Comm communicator)
{
	int figuresCount = figures.size();
	MPI_Send(&figuresCount, 1, MPI_INT, destination, 0, communicator);
	MPI_Send(&lineWidth, 1, MPI_FLOAT, destination, 0, communicator);
	for (int i = 0; i < figures.size(); i++) {
		figures[i]->MpiSend(destination, communicator);
	}
}

void CutSettingsHolder::MpiReceive(int source, MPI_Comm communicator)
{
	MPI_Status status;
	int figuresCount = figures.size();
	MPI_Recv(&figuresCount, 1, MPI_INT, source, 0, communicator, &status);
	MPI_Recv(&lineWidth, 1, MPI_FLOAT, source, 0, communicator, &status);
	figures = std::vector<Figure2D*>(figuresCount);
	for (int i = 0; i < figuresCount; i++) {
		figures[i]->MpiReceive(source, communicator);
	}
}
