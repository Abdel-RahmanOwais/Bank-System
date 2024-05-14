#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsCurrency.h"
#include "clsInputValidate.h"
#include <iomanip>

class clsUpdateCurrencyRateScreen : protected clsScreen
{

    static void _PrintCurrencyCard(clsCurrency Currency)
    {
        cout << "\n" << setw(37) << left << "" << "______________________________________________\n";
        cout << "\n" << setw(37) << left << "" << "\t\t  Currency Card : ";
        cout << "\n" << setw(37) << left << "" << "______________________________________________";
        cout << "\n" << setw(37) << left << "" << "Country  Name   : " << Currency.GetCountry() << endl;
        cout << "\n" << setw(37) << left << "" << "Country  Code   : " << Currency.GetCurrencyCode() << endl;
        cout << "\n" << setw(37) << left << "" << "Currency Name   : " << Currency.GetCurrencyName() << endl;
        cout << "\n" << setw(37) << left << "" << "Correcny Rate   : " << Currency.GetRate() << endl;
        cout << setw(37) << left << "" << "______________________________________________\n" << endl;
    }

    static float _ReadNewRate() {
        float NewRate;

        cout << setw(37) << left << "" << "Enter New Rate : ";
        cin >> NewRate;

        return NewRate;
    }

public:

    static void ShowUpdateRateScreen() {
        _DrawScreenHeader("\t\tUpdate Currency Rate Screen");

        cout << "\n" << setw(37) << left << "" << "Please Enter Currency Code : ";
        string CurrencyCode = clsInputValidate::ReadString();

        while (!clsCurrency::IsCurrencyExistByCode(CurrencyCode)) {
            cout << "\n" << setw(37) << left << "" << "Currency Code Is NOT Found, Choose Anthor One : ";
            CurrencyCode = clsInputValidate::ReadString();
        }

        clsCurrency Currency = clsCurrency::FindByCode(CurrencyCode);
        _PrintCurrencyCard(Currency);

        cout << "\n" << setw(37) << left << "" << "Are You Sure You Want To Update Rate Of This Currency [Y] or [N] : ";
       
        char Answer = 'n';
        cin >> Answer;

        if (Answer == 'y' || Answer == 'Y') {
            cout << "\n" << setw(37) << left << "" << "Update Currency Rate : " << endl;
            cout << setw(37) << left << "" << "_______________________________\n" << endl;

            Currency.UpdateRate(_ReadNewRate());

            cout << "\n" << setw(37) << left << "" << "==============================================\n";
            cout << "\n" << setw(37) << left << "" << "\t  Currency Rate Updated Successfully :-)\n";
            cout << "\n" << setw(37) << left << "" << "==============================================\n";

            _PrintCurrencyCard(Currency);
        }
        else {
            cout << "\n" << setw(37) << left << "" << "==============================================\n";
            cout << "\n" << setw(37) << left << "" << "\t     Operation Was Cancelled :-(\n";
            cout << "\n" << setw(37) << left << "" << "==============================================\n";

        }

    }

};

