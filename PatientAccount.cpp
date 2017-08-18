#include "PatientAccount.h"

PatientAccount::PatientAccount(string first, string last, string mi) :
    firstName(first), lastName(last), midInitial(mi),
    numDays(0), roomCharge(0.0), surgeryCharge(0.0), pharmCharge(0.0)
{

}
PatientAccount::PatientAccount(const PatientAccount &a) :
    firstName(a.firstName), lastName(a.lastName), midInitial(a.midInitial),
    numDays(a.numDays), roomCharge(a.roomCharge), surgeryCharge(a.surgeryCharge),
    pharmCharge(a.pharmCharge)
{

}
void PatientAccount::addDays(int additionalDays)
{
    numDays += additionalDays;
}
void PatientAccount::addSurgeryCharge(double charge)
{
    surgeryCharge += charge;
}
void PatientAccount::addPharmacyCharge(double charge)
{
    pharmCharge += charge;
}
double PatientAccount::getRoomCharge()
{
    return 500.0 * double(numDays);
}
double PatientAccount::getSurgeryCharge()
{
    return surgeryCharge;
}
double PatientAccount::getPharmacyCharge()
{
    return pharmCharge;
}
double PatientAccount::getTotalCharge()
{
    return 500.0 * double(numDays) + surgeryCharge + pharmCharge;
}
string PatientAccount::getFullName()
{
    return lastName + ", " + firstName;
}
