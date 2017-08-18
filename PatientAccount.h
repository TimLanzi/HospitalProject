#ifndef PatientAccountH
#define PatientAccountH
#include <string>

using namespace std;

class PatientAccount
{
    public:
        PatientAccount(string f="", string l="", string m="");
        PatientAccount(const PatientAccount &account);      //copy constructor needed for sort
        void addDays(int additionalDays = 1);
        void addSurgeryCharge(double surgeryCharge);
        void addPharmacyCharge(double pharmacyyCharge);
        double getRoomCharge();
        double getSurgeryCharge();
        double getPharmacyCharge();
        double getTotalCharge();
        string firstName;
        string lastName;
        string midInitial;
        int numDays;
        double roomCharge;
        double surgeryCharge;
        double pharmCharge;
        string getFullName();
};





#endif