//bring in header files
#include <iostream>
#include <iomanip>
#include <cctype>
#include <string>
#include "PatientAccount.h"
#include "Pharmacy.h"
#include "Surgery.h"

using namespace std;

//declare function prototypes
int linearSearch(PatientAccount[], int, string);
void bubbleSort(PatientAccount[], int, char);
bool compare(PatientAccount, PatientAccount, char);

int main()
{
	//declare variables
	int numOfPatients;			//number of patients
	char choice;				//used to store user's choice where prompted
	string searchName;			//full name of a patient being searched for in format Last, First
	string searchFirstName;		//first name of a patient being searched for
	string searchLastName;		//last name of a patient being searched for
	int wantedIndex;			//returned index of a patient being searched for
	PatientAccount *patients;	//array of PatientAccount objects with dynamic memory
	Surgery surgery;			//object of the Surgery class
	Pharmacy pharmacy;			//object of the Pharmacy class
	int moreDays;				//number of additional days spent in hospital if there is an additional stay


	//asks for number of patients
	cout << "How many patients are there?" << endl;
	cin >> numOfPatients;

	//checks for invalid patient number and exits program if so
	if (numOfPatients < 0)
	{
		cout << "The number of patients must be a positive number. Exiting program..." << endl;
		return -1;
	}

	//initializes patients array with size of numOfPatients
	patients = new PatientAccount[numOfPatients];

	//bring in all patient info
	for (int i = 0; i<numOfPatients; i++)
	{
		//bring in first name
		cout << "Input patient #" << (i + 1) << "'s first name:  ";
		cin >> patients[i].firstName;

		//bring in last name
		cout << "Input patient #" << (i + 1) << "'s last name:  ";
		cin >> patients[i].lastName;

		//bring in middle initial
		cout << "Input patient #" << (i + 1) << "'s middle initial:  ";
		cin >> patients[i].midInitial;

		//ask for how many days spent at hospital until a valid number is input
		do
		{
			cout << "Input the number of days spent in the hospital by " << patients[i].firstName << " " << patients[i].lastName << endl;
			cin >> patients[i].numDays;
		} while (patients[i].numDays < 1);

		//asks for surgery type and displays surgery menu
		cout << "What type of surgery(s) did " << patients[i].firstName << " " << patients[i].lastName << " have? (Input -1 to stop)" << endl;
		cout << "1 - Tonsillectomy\n2 - Foot\n3 - Knee\n4 - Shoulder\n5 - Appendectomy\n";
		cout << "Input surgery type number: ";
		cin >> surgery.type;
		//continues asking for multiple surgery types until invalid option is input
		while (surgery.type > 0 && surgery.type <= 5)
		{
			//break out of loop if negative number is input
			if (surgery.type <= 0)
			{
				break;
			}
			surgery.chargePatient(&patients[i]);	//charge the amount of the surgery to the patient's account
			//asks for another surgery type in case of multiple surgeries
			cout << "Input another surgery type number (Input -1 to stop): ";
			cin >> surgery.type;
		}

		//asks for medication type and displays pharmacy menu
		cout << "What type of medication(s) did " << patients[i].firstName << " " << patients[i].lastName << " need? (Input -1 to stop)" << endl;
		cout << "1 - Antibiotic\n2 - Anti-nausea\n3 - Anti-Inflammatory\n4 - Light Pain\n5 - Strong Pain\n";
		cout << "Input medication type number: ";
		cin >> pharmacy.type;
		//continues asking for multiple medications until invalid option is input
		while (pharmacy.type > 0 && pharmacy.type <= 5)
		{
			//break out of loop if negative number is input
			if (pharmacy.type <= 0)
			{
				break;
			}
			pharmacy.chargePatient(&patients[i]);	//charge the amount of medication to the patient's account
			//asks for another medication type in case of medications
			cout << "Input another medication type number(Input -1 to stop): ";
			cin >> pharmacy.type;
		}

	}

	//displays menu for patient database
	cout << "================================" << endl;
	cout << "Patient Fee Information Database" << endl;
	cout << "================================" << endl;
	cout << "V - View Patient Fee Information Database\nF - Find Patient Fee Information by Patient Name\n"
		<< "S - Sort Patient Fee Information\nA - Add Patient Fee\nQ - Quit Program" << endl;

	//asks for an option from the menu until Q is entered
	do
	{
		//asks for menu choice
		cout << "Select which menu option you would like to perform: ";
		cin >> choice;
		//if input is not one of the choices then try again
		if (toupper(choice) != 'V' && toupper(choice) != 'F' && toupper(choice) != 'S' && toupper(choice) != 'A' && toupper(choice) != 'Q')
		{
			cout << "Invalid choice. Please input an option from the choices given..." << endl;
		}
		//if choice is V then display list of patients and their information
		else if (toupper(choice) == 'V')
		{
			cout << "Patient list:" << endl << endl;
			cout << fixed << setw(12) << left << "Last" << setw(12) << "First" << setw(2) << "M.   " << setw(10) << "Room" << setw(10) << "Surgery" << setw(10) << "Pharmacy" << setw(10) << "Total" << endl;
			for (int i = 0; i < numOfPatients; i++)
			{
				cout << fixed << setw(12) << left << (patients[i].lastName + ',') << setw(12) << patients[i].firstName << setw(1) << patients[i].midInitial << ".   "
					<< setw(10) << setprecision(2) << showpoint << patients[i].getRoomCharge() << setw(10) << patients[i].getSurgeryCharge() << setw(10) << patients[i].getPharmacyCharge()
					<< setw(10) << patients[i].getTotalCharge() << endl;
			}
		}
		else if (toupper(choice) == 'F')
		{
			do
			{
				cout << "Enter the first and last name of the patient of which you would like information" << endl;
				cout << "First: ";
				cin >> searchFirstName;
				cout << "Last: ";
				cin >> searchLastName;
				searchName = searchLastName + ", " + searchFirstName;
				wantedIndex = linearSearch(patients, numOfPatients, searchName);
				if (wantedIndex >= 0)
				{
					cout << patients[wantedIndex].getFullName() << "'s patient information:" << endl << endl;
					cout << fixed << setw(12) << left << "Last" << setw(12) << "First" << setw(2) << "M.   " << setw(10) << "Room" << setw(10) << "Surgery" << setw(10) << "Pharmacy" << setw(10) << "Total" << endl;
					cout << fixed << setw(12) << left << (patients[wantedIndex].lastName + ',') << setw(12) << patients[wantedIndex].firstName << setw(1) << patients[wantedIndex].midInitial << ".   "
						<< setw(10) << setprecision(2) << showpoint << patients[wantedIndex].getRoomCharge() << setw(10) << patients[wantedIndex].getSurgeryCharge() << setw(10) << patients[wantedIndex].getPharmacyCharge()
						<< setw(10) << patients[wantedIndex].getTotalCharge() << endl;
				}
				//if wantedIndex wasn't found then print invalid message and user tries again
				else
				{
					cout << searchName << " was not found in the database. Try again..." << endl << endl;
				}
			} while (wantedIndex < 0);
		}
		else if (toupper(choice) == 'S')
		{
			cout << "Would you like to sort patient information by name or by charge?" << endl;
			cout << "N - Sort by Name\nC - Sort by charge" << endl;
			cin >> choice;
			bubbleSort(patients, numOfPatients, toupper(choice));

			cout << "Sorted patient list:" << endl << endl;
			cout << fixed << setw(12) << left << "Last" << setw(12) << "First" << setw(2) << "M.   " << setw(10) << "Room" << setw(10) << "Surgery" << setw(10) << "Pharmacy" << setw(10) << "Total" << endl;
			for (int i = 0; i < numOfPatients; i++)
			{
				cout << fixed << setw(12) << left << (patients[i].lastName + ',') << setw(12) << patients[i].firstName << setw(1) << patients[i].midInitial << ".   "
					<< setw(10) << setprecision(2) << showpoint << patients[i].getRoomCharge() << setw(10) << patients[i].getSurgeryCharge() << setw(10) << patients[i].getPharmacyCharge()
					<< setw(10) << patients[i].getTotalCharge() << endl;
			}
		}
		else if (toupper(choice) == 'A')
		{
			do
			{
				cout << "Enter the name of the patient to which you would like to add a charge." << endl;
				cout << "First: ";
				cin >> searchFirstName;
				cout << "Last: ";
				cin >> searchLastName;
				searchName = searchLastName + ", " + searchFirstName;
				wantedIndex = linearSearch(patients, numOfPatients, searchName);
				if (wantedIndex >= 0)
				{
					cout << "What type of charge is to be added?" << endl;
					cout << "R - Room charge\nS - Surgery charge\nP - Pharmacy charge\n";
					cin >> choice;
					do
					{
						if (toupper(choice) == 'R')
						{
							cout << "How many more days will " << patients[wantedIndex].firstName << " " << patients[wantedIndex].lastName << " stay?" << endl;
							cin >> moreDays;
							patients[wantedIndex].addDays(moreDays);
						}
						else if (toupper(choice) == 'S')
						{
							cout << "What other type of surgery(s) did " << patients[wantedIndex].firstName << " " << patients[wantedIndex].lastName << " have?" << endl;
							cout << "1 - Tonsillectomy\n2 - Foot\n3 - Knee\n4 - Shoulder\n5 - Appendectomy\n";
							do
							{
								cout << "Input surgery type number: ";
								cin >> surgery.type;
								if (surgery.type > 0 && surgery.type <= 5)
								{
									surgery.chargePatient(&patients[wantedIndex]);
									break;
								}
								else
								{
									cout << "Invalid input. Please chose from the menu of choices." << endl;
								}

							} while (true);
						}
						else if (toupper(choice) == 'P')
						{
							cout << "What other type of medication(s) did " << patients[wantedIndex].firstName << " " << patients[wantedIndex].lastName << " need?" << endl;
							cout << "1 - Antibiotic\n2 - Anti-nausea\n3 - Anti-Inflammatory\n4 - Light Pain\n5 - Strong Pain\n";
							do
							{
								cout << "Input medication type number: ";
								cin >> pharmacy.type;
								if (pharmacy.type > 0 && pharmacy.type <= 5)
								{
									pharmacy.chargePatient(&patients[wantedIndex]);
									break;
								}
								else
								{
									cout << "Invalid input. Please chose from the menu of choices." << endl;
								}

							} while (true);
						}
						else
						{
							cout << "Invalid input. Please chose from the menu of choices." << endl;
						}
					} while (toupper(choice) != 'R' && toupper(choice) != 'S' && toupper(choice) != 'P');

				}
				else
				{
					cout << searchName << " was not found in the database. Try again..." << endl << endl;
				}
			} while (wantedIndex < 0);
		}
		else if (toupper(choice) == 'Q')
		{
			cout << "Goodbye..." << endl;
		}
	} while (toupper(choice) != 'Q');


	delete[] patients;
	return 0;
}

int linearSearch(PatientAccount p[], int num, string value)
{
	int index = -1;

	//for loop goes through the array
	for (int i = 0; i < num; i++)
	{
		//if the name at index i is the same as value then set index to i and break out of loop
		if (p[i].getFullName() == value)
		{
			index = i;
			break;
		}
	}

	return index;       //return index 
}

bool compare(PatientAccount *patientA, PatientAccount *patientB, char choice)
{
	//if choice is N then sort by name
	if (choice == 'N')
	{
		return patientA->getFullName() > patientB->getFullName();
	}
	//otherwise sort by total charge
	return patientA->getTotalCharge() < patientB->getTotalCharge();
}

//bubbleSort function sorts students in either ascending or descending order
void bubbleSort(PatientAccount patients[], int num, char choice)
{
	bool swap;
	PatientAccount temp;

	do
	{
		swap = false;       //set swap initially to false
		//for loop goes through all array elements and sorts them
		for (int pos = 0; pos < (num - 1); pos++)
		{
			//compare function is called to determine ascending or descending order
			if (compare(&patients[pos], &patients[pos + 1], choice))
			{
				temp = patients[pos];
				patients[pos] = patients[pos + 1];
				patients[pos + 1] = temp;
				swap = true;
			}
		}
	} while (swap);
}