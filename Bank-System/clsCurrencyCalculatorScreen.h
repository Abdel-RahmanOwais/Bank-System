#pragma once
#include <iostream>
#include "clsCurrency.h"
#include "clsScreen.h"
#include "clsInputValidate.h"
#include <iomanip>

class clsCurrencyCalculatorScreen : protected clsScreen
{

    static double _ReadAmount() {
        cout << "\n" << setw(37) << left << "" << "Enter Amount To Exchange : ";

        double Amount = clsInputValidate::ReadDbNumber();

        return Amount;
    }

    static void _PrintCurrencyCard(clsCurrency Currency, string HeaderTitle = "Currency Care")
    {
        cout << "\n" << setw(37) << left << "" << "______________________________________________\n";
        cout << "\n" << setw(37) << left << "" << "\t\t  " << HeaderTitle << " : ";
        cout << "\n" << setw(37) << left << "" << "______________________________________________";
        cout << "\n" << setw(37) << left << "" << "Country  Name   : " << Currency.GetCountry() << endl;
        cout << "\n" << setw(37) << left << "" << "Country  Code   : " << Currency.GetCurrencyCode() << endl;
        cout << "\n" << setw(37) << left << "" << "Currency Name   : " << Currency.GetCurrencyName() << endl;
        cout << "\n" << setw(37) << left << "" << "Correcny Rate   : " << Currency.Rate << endl;
        cout << setw(37) << left << "" << "______________________________________________\n" << endl;
    }

    static void _PrintCalculationResults(double Amount, clsCurrency CurrencyFrom, clsCurrency CurrencyTo) {

        _PrintCurrencyCard(CurrencyFrom, "  Convert From");

        double AmountInUSD = CurrencyFrom.ConvertToUSD(Amount);

        cout << "\n" << setw(37) << left << "" << "==============================================\n";
        cout << "\n" << setw(37) << left << "" << Amount << " "
            << CurrencyFrom.GetCurrencyCode() << " = "
            << AmountInUSD << " " << " USD\n";
        cout << "\n" << setw(37) << left << "" << "==============================================\n";



        if (CurrencyTo.GetCurrencyCode() == "USD") {
            return;
        }

        cout << "\n" << setw(37) << left << "" << "Converting From USD To : ";
        _PrintCurrencyCard(CurrencyTo, "  Convert To");

        double AmountInCurrencyTo = CurrencyFrom.ConvertToOtherCurrency(Amount, CurrencyTo);

        cout << "\n" << setw(37) << left << "" << "==============================================\n";
        cout << "\n" << setw(37) << left << "" << Amount << " "
            << CurrencyFrom.GetCurrencyCode() << " = "
            << AmountInCurrencyTo << " " << CurrencyTo.GetCurrencyCode() << endl;
        cout << "\n" << setw(37) << left << "" << "==============================================\n";

    }

    static clsCurrency _GetCurrency(string Message) {
        string CurrencyCode;

        cout << "\n" << setw(37) << left << "" << Message;
        CurrencyCode = clsInputValidate::ReadString();

        while (!clsCurrency::IsCurrencyExistByCode(CurrencyCode))
        {
            cout << "\n" << setw(37) << left << "" << "Currency Is NOT Found, Choose Another One : ";
            CurrencyCode = clsInputValidate::ReadString();
        }

        clsCurrency Currency = clsCurrency::FindByCode(CurrencyCode);

        return Currency;
    }

public:

    static void ShowCurrencyCalculatorScreen() {
    
        char Continue = 'y';

        while (Continue == 'y' || Continue == 'Y') {

        system("cls");

        _DrawScreenHeader("\t\tCurrency Calculator Screen");

        clsCurrency CurrencyFrom = _GetCurrency("Please Enter Currency Code [1] : ");
        clsCurrency CurrencyTo   = _GetCurrency("Please Enter Currency Code [2] : ");

        double Amount = _ReadAmount();

        _PrintCalculationResults(Amount, CurrencyFrom, CurrencyTo);

        cout << "\n\n" << setw(37) << left << "" << "Are You Want To Perform Anthor Calculator [Y] or [N] : ";
        cin >> Continue;
        }


    }



};

