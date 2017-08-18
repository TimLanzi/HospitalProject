#include "Surgery.h"

Surgery::Surgery():
type(0)
{

};

double Surgery::getCost()
{
	double cost[] = { 0.0, 100.0, 200.0, 300.0, 400.0, 500.0 };
	return cost[type];
}

void Surgery::chargePatient(PatientAccount *patient)
{
	patient->addSurgeryCharge(getCost());
}