#pragma once
#include "mpi.h"

class MpiFriendly {
public:
	virtual void MpiSend(int destination, MPI_Comm communicator) {}
	virtual void MpiReceive(int source, MPI_Comm communicator) {}
};