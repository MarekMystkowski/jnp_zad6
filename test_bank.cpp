#include "bank.h"
#include "planet.h"
#include "citizen.h"
#include <iostream>
#include <assert.h>

using namespace std;
int main() {
	
	cout << "start testu banku" << endl;
	auto jan = earth().registerCitizen("Jan");
	auto ala = earth().registerCitizen("Ala");
	
	auto& captain = earth().registerCitizen("Jean-Luc Picard");
    auto& officer = qonos().registerCitizen("Worf");
    auto& b0 = bynaus().registerCitizen("00000000");
    auto& b1 = bynaus().registerCitizen("11111111");

    auto& binarius = bynaus().registerCitizen(b0, b1);
    
    
     // nowe banki otwieramy poprzez wniosek do Gwiezdnej Komisji Bankowej
    // hint: wzorzec Builder oraz fluent interface
    // opłaty zawsze w ENC
    auto& enterpriseBank = gkb().bankApplication()
        .name("Enterprise Bank")
        .checkingAccount()
        .savingAccount().monthlyCharge(2.00).transferCharge(1.00).interestRate(5)
        .currencyAccount().transferCharge(2.00).interestRate(1.5)
        .createBank();
    
    // domyślnie brak opłat oraz 0 oprocentowanie
    auto& raisaBank = gkb().bankApplication()
        .name("Raisa Bank")
        .createBank();
        
    auto& picardsChecking = enterpriseBank.openCheckingAccount(captain);
    
    assert (picardsChecking.id() == 0);
    
	cout << "test banku: OK" << endl;
	return 0;
}
