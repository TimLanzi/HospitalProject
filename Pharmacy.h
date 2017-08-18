#ifndef PharmacyH
#define PharmacyH
#include "PatientAccount.h"

class Pharmacy
{
public:
	Pharmacy();
	int type;
	double getCost();
	void chargePatient(PatientAccount *patient);
};

#endif