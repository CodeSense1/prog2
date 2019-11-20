/* Module: Loan
 * ------------
 * This class and its bahaviour should be defined by the student.
 *
 * TIE-0220x S2019
 * */
#ifndef LOAN_HH
#define LOAN_HH

#include "book.hh"
#include "date.hh"

const int DEFAULT_RENEWAL_AMOUNT = 6;
const int DEFAULT_RENEWAL_DAYS = 28;

class Loan
{
public:
    Loan(std::string person, std::string bookName, Date loanDate);
    ~Loan();

    std::string getLoaner();
    std::string getLoanedBook();
    std::string getDueDate();
    void printLoanInfo(Date* currentDate, bool includeName = true);
    bool renewLoan();

private:

    std::string person_;
    std::string title_;
    Date loanDate_;
    int renewsAvailable;

};

#endif // LOAN_HH
