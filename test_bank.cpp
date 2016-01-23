#include "gsb.h"
#include <iostream>
#include <assert.h>

using namespace std;
int main() {
	
    cout << "start testu banku" << endl;
	
    // rejestracja obywateli na poszczególnych planetach
    auto& captain = earth().registerCitizen("Jean-Luc Picard");
    auto& officer = qonos().registerCitizen("Worf");
    auto& b0 = bynaus().registerCitizen("00000000");
    auto& b1 = bynaus().registerCitizen("11111111");
    auto& binarius = bynaus().registerCitizen(b0, b1);

    // możemy odszukać obywatela, o ile znamy jego identyfikator...
    
    auto& found = earth().findCitizen(captain.id());
    cout <<"captain.id" << captain.id() <<endl;
    try {
        auto& spock = earth().findCitizen(10);
    } catch (...) {
        // ...jeśli nie istnieje, to zgłaszany jest wyjątek
        ::std::cout << "Spock not found" << ::std::endl;
    }

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
        
    // możemy otwierać różne rodzaje kont dla obywateli Zjednoczonej Federacji Planet
    auto& picardsChecking = enterpriseBank.openCheckingAccount(captain);
    auto& picardsSaving = enterpriseBank.openSavingAccount(captain);
    auto& binariusCurrency = raisaBank.openCurrencyAccount(binarius, Currency::DIL);
	

    // operacje na koncie rozliczeniowym
    picardsChecking.deposit(101.5);
    picardsChecking.withdraw({1.5, Currency::ENC});
    picardsChecking.transfer(100, picardsSaving.id());
    
    cerr << "Wypisanie konta po wplacie 101.5, wyplacie 1.5, i przeslaniu na konto oszczednosciowe" << endl;    
    cerr << picardsChecking << endl;

    // operacje na koncie oszczędnościowym
    picardsSaving.transfer(49.99, binariusCurrency.id(), "for binarius");
    cerr << "Przesłanie z oszczednoscioweko 49.99 na binarius walutowego, oplata za tranzakcje to 1 =" <<enterpriseBank.transferCharge(ParametersBank::AccountType::SAVING) <<endl;
    cerr << picardsSaving << endl;


    interstellarClock().nextMonth().nextDay();
	cout << "date: " << interstellarClock().date() << endl;
    cerr << "Po minięciu 31 dni" << endl;
    cerr << picardsChecking << endl;

    cerr << "Koszty dla tego konta to -2 co miesiąc i +5%" << endl;
    cerr << picardsSaving << endl;
    cerr << binariusCurrency << endl; 
    // operacje na koncie walutowym
    // domyślnie kurs jest 1 do 1
    binariusCurrency.withdraw(1);
    binariusCurrency.withdraw({1, Currency::ENC});
    cerr << "Po 2 wpłatach: 1DIL , 1ENC, kurs: 1:1" << endl;
    cerr << binariusCurrency << endl;

    // zmiana kursu waluty i wypłata
    raisaBank.exchangeTable().exchangeRate(Currency::DIL).buyingRate(2.0).sellingRate(3.0);
    cerr << "sel_Dil 3 = "<< raisaBank.exchange_selling_rate(Currency::DIL) << endl;
    cerr << "sel_Dil 2 = "<< raisaBank.exchange_buying_rate(Currency::DIL) << endl;

 
    binariusCurrency.withdraw({1, Currency::ENC});
    binariusCurrency.withdraw({1.0, Currency::DIL});

    cerr << "Po 2 wpłatach: 1EN , 1DIL" << endl;
    cerr << binariusCurrency << endl;


    // stan konta rozliczeniowego Picarda
    ::std::cout << picardsChecking.balance() << ::std::endl;
    

    ::std::cout << picardsChecking.history() << ::std::endl;
   
    // stan konta oszczędnościowego Picarda
    ::std::cout << picardsSaving << ::std::endl;

    // stan konta walutowego Binariusa
    ::std::cout << binariusCurrency << ::std::endl;
    
    
/*
    // próba przelewu na nieistniejące konto...
    try {
        binariusCurrency.transfer(1, "Far Far In a Galaxy");
    } catch (...) {
        // ...powinna zakończyć się wyjątkiem
        ::std::cout << "Account not found" << ::std::endl;
    } */
	cout << "test banku: OK" << endl;
	return 0;
}
