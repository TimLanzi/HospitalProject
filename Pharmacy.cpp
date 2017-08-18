#include "Pharmacy.h"

Pharmacy::Pharmacy() :
type(0)
{

};

double Pharmacy::getCost()
{
	double cost[] = { 0.0, 10.0, 20.0, 30.0, 40.0, 50.0 };
	return cost[type];
}

void Pharmacy::chargePatient(PatientAccount *patient)
{
	patient->addPharmacyCharge(getCost());
}