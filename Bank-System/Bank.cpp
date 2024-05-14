#include <iostream>
#include "clsBankClient.h"
#include "clsInputValidate.h"
#include "clsUtil.h"
#include <iomanip>
#include "clsMainScreen.h"
#include "clsLoginScreen.h"

using namespace std;


int main() {
	
	//clsMainScreen::ShowMainMeune();

	while (true) {

		if (!clsLoginScreen::ShowLoginScreen()) {
			break; // this will get out of the program
		}
	
	}
	

	system("pause>0");
	return 0;
}