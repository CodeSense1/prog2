#include "loan.hh"
#include <iostream>


// Luo uuden lainan
/*
 * param:
 *
 *  person: Henkilö, joka tekee lainan
 *  bookName: Lainatun kirjan nimi
 *  loanDate: Milloin laina tehtiin, tämä muutetaan lainan eräpäiväksi
 */
Loan::Loan(std::string person, std::string bookName, Date loanDate) :
    person_(person), title_(bookName), loanDate_(loanDate)

{
    this->loanDate_.advance_by(DEFAULT_RENEWAL_DAYS);
    this->renewsAvailable = DEFAULT_RENEWAL_AMOUNT;
}

// Default destructor
Loan::~Loan() {}

std::string Loan::getLoaner() {
    // Palauttaa lainaajan nimen
    return this->person_;
}

void Loan::printLoanInfo(Date* currentDate, bool includeName) {
    /*
     * Tulostaa tiedot yhdestä lainauksesta
     *
     * param:
     *
     *  currentDate: Osoitin nykyisen päivän Date-olioon
     *  includeName: Halutaanko, että varaajan nimi näkyy myös tulostuksessa
     *
     */
    int late = (*currentDate < this->loanDate_) ? 0 : 1;


    // HUOM!! Tämän funktion toteutus voisi olla fiksumpikin
    // saman lopputuloksen saa varmasti saavutettua
    // ilman toisteisuutta, mutta sitä ei googlesta löytynyt
    if (includeName) {

        std::cout << this->title_ << " : "
                  << this->person_ << " : "
                  << this->loanDate_.to_string() << " : "
                  << late
                  << std::endl;
    } else {
        std::cout << this->title_ << " : "
                  << this->loanDate_.to_string() << " : "
                  << late
                  << std::endl;
    }
}

bool Loan::renewLoan() {

    // Uudistaa lainan (siirtää eräpäivää eteenpäin),
    // mikäli lainauskertoja on vielä jäljellä

    if (this->renewsAvailable <= 0) {
        return false;
    }

    // Can loan that is late still be renewed?
    this->loanDate_.advance_by(DEFAULT_RENEWAL_DAYS);
    this->renewsAvailable--;
    return true;

}

std::string Loan::getLoanedBook() {
    // Palauttaa lainatun kirjan nimen
    return this->title_;
}

std::string Loan::getDueDate() {
    // Palauttaa lainatun kirjan eräpäivän
    return this->loanDate_.to_string();
}




