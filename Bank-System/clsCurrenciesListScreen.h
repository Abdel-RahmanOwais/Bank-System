#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsCurrency.h"
#include <iomanip>

class clsCurrenciesListScreen : protected clsScreen
{

    static void _PrintCurrencyRecordLine(clsCurrency Currency)
    {

        cout << setw(8) << left << "" << "| " << setw(30) << left << Currency.GetCountry();
        cout << "| " << setw(6) << left << Currency.GetCurrencyCode();
        cout << "| " << setw(40) << left << Currency.GetCurrencyName();
        cout << "| " << setw(10) << left << Currency.Rate;
    }

public:

	static void ShowCurreciesListScreen() {
        vector <clsCurrency> vCurrencys = clsCurrency::GetCurrenciesList();

        string Title = "\n\t\t\t\t\t\t  Currency List Screen";
        string SubTitle = "\t\t    (" + to_string(vCurrencys.size()) + ") Currency(s).";

        _DrawScreenHeader(Title, SubTitle);

        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;

        cout << setw(8) << left << "" << "| " << left << setw(30) << "Country";
        cout << "| " << left << setw(6) << "Code";
        cout << "| " << left << setw(40) << "Name";
        cout << "| " << left << setw(10) << "Rate/(1$)";
        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;

        if (vCurrencys.size() == 0)
            cout << "\t\t\t\tNo Currencies Available In the System!";
        else

            for (clsCurrency Currency : vCurrencys)
            {

                _PrintCurrencyRecordLine(Currency);
                cout << setw(8) << left << "" << "\t" << endl;

            }

        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;

	}


};

