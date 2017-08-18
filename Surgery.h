#ifndef SurgeryH
#define SurgeryH
#include "PatientAccount.h"

class Surgery
{
public:
	Surgery();
	int type;
	double getCost();
	void chargePatient(PatientAccount *patient);
};

#endif