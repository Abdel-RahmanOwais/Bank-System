#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsCurrency.h"
#include "clsInputValidate.h"
#include <iomanip>


class clsFindCurrencyScreen : protected clsScreen
{

    static void _PrintCurrencyCard(clsCurrency Currency)
    {
        cout << "\n" << setw(37) << left << "" << "______________________________________________\n";
        cout << "\n" << setw(37) << left << "" << "\t\t  Currency Card : ";
        cout << "\n" << setw(37) << left << "" << "______________________________________________";
        cout << "\n" << setw(37) << left << "" << "Country  Name   : " << Currency.GetCountry() << endl;
        cout << "\n" << setw(37) << left << "" << "Country  Code   : " << Currency.GetCurrencyCode() << endl;
        cout << "\n" << setw(37) << left << "" << "Currency Name   : " << Currency.GetCurrencyName() << endl;
        cout << "\n" << setw(37) << left << "" << "Correcny Rate   : " << Currency.Rate << endl;
        cout << setw(37) << left << "" << "______________________________________________\n" << endl;
    }

    static void _ShowResults(clsCurrency Currency) {
        if (!Currency.IsEmpty())
        {
            cout << "\n" << setw(37) << left << "" << "==============================================\n";
            cout << "\n" << setw(37) << left << "" << "\t        Currency Found :-)\n";
            cout << "\n" << setw(37) << left << "" << "==============================================\n";
            _PrintCurrencyCard(Currency);
        }
        else
        {
            cout << "\n" << setw(37) << left << "" << "==============================================\n";
            cout << "\n" << setw(37) << left << "" << "\t          Currency Was not Found :-(\n";
            cout << "\n" << setw(37) << left << "" << "==============================================\n";
        }
    }

public:

	static void ShowFindCurrencyScreen() {

        _DrawScreenHeader("\t\t   Find Currency Screen");

        short Answer = 1;
        cout << "\n" << setw(37) << left << "" << "Find By : [1] Code or [2] Country Name : ";
        Answer = clsInputValidate::ReadNumberBetween(1, 2, "\n\t\t\t\t     Error, You Must Enter Number Between [1] to [2]");
       

        if (Answer == 1) {
            string CurrencyCode;

            cout << "\n" << setw(37) << left << "" << "Please Enter Country Code : ";
            CurrencyCode = clsInputValidate::ReadString();

            while (!clsCurrency::IsCurrencyExistByCode(CurrencyCode))
            {
                cout << "\n" << setw(37) << left << "" << "Currency Is NOT Found, Choose Another One: ";
                CurrencyCode = clsInputValidate::ReadString();
            }

            clsCurrency Currency = clsCurrency::FindByCode(CurrencyCode);
            _ShowResults(Currency);

        }
        else 
        {
            string Country;
            cout << "\n" << setw(37) << left << "" << "Please Enter Country Name : ";
            Country = clsInputValidate::ReadString();
        

            while (!clsCurrency::IsCurrencyExistByCountryName(Country))
            {
                cout << "\n" << setw(37) << left << "" << "Country Is NOT Found, Choose Another One: ";
                Country = clsInputValidate::ReadString();
            }

            clsCurrency Currency = clsCurrency::FindByCountry(Country);
            _ShowResults(Currency);

        }


	}

};

