#pragma once
#include <iostream>
#include "clsCurrency.h"
#include "clsScreen.h"
#include "clsInputValidate.h"
#include <iomanip>
#include "clsCurrenciesListScreen.h"
#include "clsFindCurrencyScreen.h"
#include "clsUpdateCurrencyRateScreen.h"
#include "clsCurrencyCalculatorScreen.h"


class clsCurrencyExchangeMainScreen : protected clsScreen
{
    enum enCurrencyExchangeOptions {
        eCurrenciesList = 1, eFindCurrency = 2,
        eUpdateRate = 3, eCurrencyCalculator = 4,
        eMainScreen = 5
    };

    static short _ReadCurrencyExchangeOptions() {
        cout << setw(37) << left << "" << "Choose What Do You Want To Do [1] to [5] : ";
        short Chois = clsInputValidate::ReadNumberBetween(1, 5, "\n\t\t\t\t     Erorr, You Must Chois Number Between [1] to [5] : ");

        return Chois;
    }

    static void _GoBackToCurrencyExchangeMenue() {
        cout << "\n\t\t\t\t     Press any key to go back in currency exchange menue...";
        system("pause>0");
        ShowMainCurrencyExchange();
    }

    static void _ShowCurrenciesList() {
        //cout << "Currencies List Will Came Nearly." << endl << endl;

        clsCurrenciesListScreen::ShowCurreciesListScreen();
    }    
    
    static void _ShowFindCurrency() {
        //cout << "Find Currency List Will Came Nearly." << endl << endl;
    
        clsFindCurrencyScreen::ShowFindCurrencyScreen();
    }  
    
    static void _ShowUpdateRate() {
        //cout << "Update Rate Will Came Nearly." << endl << endl;
    
        clsUpdateCurrencyRateScreen::ShowUpdateRateScreen();
    }
    
    static void _ShowCurrencyCalculator() {
        //cout << "Currency Calculator Will Came Nearly." << endl << endl;

        clsCurrencyCalculatorScreen::ShowCurrencyCalculatorScreen();
    }


    static void _PerformCurrencyExchangeOptios(enCurrencyExchangeOptions CurrencyOptions) {
        switch (CurrencyOptions)
        {
        case clsCurrencyExchangeMainScreen::eCurrenciesList:
            system("cls");
            _ShowCurrenciesList();
            _GoBackToCurrencyExchangeMenue();
            break;
        case clsCurrencyExchangeMainScreen::eFindCurrency:
            system("cls");
            _ShowFindCurrency();
            _GoBackToCurrencyExchangeMenue();
            break;
        case clsCurrencyExchangeMainScreen::eUpdateRate:
            system("cls");
            _ShowUpdateRate();
            _GoBackToCurrencyExchangeMenue();
            break;
        case clsCurrencyExchangeMainScreen::eCurrencyCalculator:
            system("cls");
            _ShowCurrencyCalculator();
            _GoBackToCurrencyExchangeMenue();
            break;
        case clsCurrencyExchangeMainScreen::eMainScreen:

            //do nothing here the main screen will handle it :-) ;
            cout << "\n\n";
            break;
        }

    }


public:

	static void ShowMainCurrencyExchange() {
        system("cls");

		_DrawScreenHeader("\t     Currency Exchange Main Screen");


        cout << setw(37) << left << "" << "==============================================\n";
        cout << setw(37) << left << "" << "\t\t Currency Exchange Menue" << endl;
        cout << setw(37) << left << "" << "==============================================\n";
        cout << setw(37) << left << "" << "\t[1] Show Currencies List\n";
        cout << setw(37) << left << "" << "\t[2] Find Currency\n";
        cout << setw(37) << left << "" << "\t[3] Update Rate\n";
        cout << setw(37) << left << "" << "\t[4] Currency Calculator\n";
        cout << setw(37) << left << "" << "\t[5] Main Screen\n";
        cout << setw(37) << left << "" << "==============================================\n";

        _PerformCurrencyExchangeOptios(enCurrencyExchangeOptions(_ReadCurrencyExchangeOptions()));
	}

};

