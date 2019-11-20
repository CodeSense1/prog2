#include "library.hh"
#include <iostream>
#include <algorithm>


// Let's use the date when the project was published as the first date.
Library::Library():
    today_(new Date(13, 11, 2019)),
    books_({}),
    authors_({}),
    accounts_({}),
    loans_({})
{

}

Library::~Library()
{
    // Free all memory reserved with the keyword new.
    delete today_; today_ = nullptr;
    for ( std::pair<std::string, Book*> book : books_ ){
        delete book.second;
        book.second = nullptr;
    }
    for ( std::pair<std::string, Person*> author : authors_ ){
        delete author.second;
        author.second = nullptr;
    }
    for ( std::pair<std::string, Person*> account : accounts_ ){
        delete account.second;
        account.second = nullptr;
    }
    for (Loan* loan : loans_) {
        delete loan;
        loan = nullptr;
    }

}

void Library::all_books()
    // Prints all books
{
    for ( std::pair<std::string, Book*> book : books_ ){
        std::cout << book.first << std::endl;
    }
}

void Library::all_books_with_info()
    // Prints all books with more information
{
    std::cout << SEPARATOR_LINE << std::endl;
    for ( std::pair<std::string, Book*> book : books_ ){
        book.second->print_info();
        std::cout << SEPARATOR_LINE << std::endl;
    }
}

void Library::all_borrowers()
{
    for ( std::pair<std::string, Person*> borrower : accounts_ ){
        std::cout << borrower.first << std::endl;
    }
}

void Library::all_borrowers_with_info()
{
    std::cout << SEPARATOR_LINE << std::endl;
    for ( std::pair<std::string, Person*> borrower : accounts_ ){
        borrower.second->print_info();
        std::cout << SEPARATOR_LINE << std::endl;
    }
}

bool Library::add_book(const std::string &title, const std::vector<std::string> authors, const std::string &description, const std::set<std::string> genres)
{
    if ( authors.empty() ){
        std::cout << MISSING_AUTHOR_ERROR << std::endl;
        return false;
    }
    std::vector<Person*> author_ptrs;
    for ( std::string author : authors ){
        Person* n_person;
        if ( authors_.find(author) == authors_.end() ){
            n_person = new Person(author, "", "");
            authors_.insert({author, n_person});
        } else {
            n_person = authors_.at(author);
        }
        author_ptrs.push_back(n_person);
    }
    Book* n_book = new Book(title, author_ptrs, description, genres);
    books_.insert({title, n_book});
    return true;
}

void Library::add_borrower(const std::string &name, const std::string &email,
                           const std::string &address)
{
    if ( isAccountRegistered(name) ){
        std::cout << DUPLICATE_PERSON_ERROR << std::endl;
        return;
    }

    Person* n_person = new Person(name, email, address);
    accounts_.insert({name, n_person});
}

void Library::set_date(int day, int month, int year)
{
    delete today_;
    today_ = new Date(static_cast<unsigned int>(day),
                      static_cast<unsigned int>(month),
                      static_cast<unsigned int>(year));
    today_->show();
}

void Library::advance_date(int days)
{
    today_->advance_by(static_cast<unsigned int>(days));
    today_->show();
}

void Library::loaned_books()
    // Tulostaa kaikki lainassa olevat kirjat
{
    if (loans_.size() == 0) {
        return;
    }
    std::cout << LOAN_INFO << std::endl;
    for (const auto& loan : loans_) {
        loan->printLoanInfo(today_);
    }
}

void Library::loans_by(const std::string &borrower)
    // Tulostaa kaikki tietyllä henkilöllä lainassa olevat kirjat
{
    // Account valid
    if (!isAccountRegistered(borrower)) {
        std::cout << CANT_FIND_ACCOUNT_ERROR << std::endl;
        return;
    }

    // Loan valid
    for (Loan* loan : loans_) {
        if (loan->getLoaner() == borrower) {
            loan->printLoanInfo(today_, false);
        }
    }
}

void Library::loan(const std::string &book_title, const std::string &borrower_id)
    // Tekee uuden lainan borrower_id:lle. Lisää uuden lainan tietorakenteeseen
{
    // Construct new loan
    // step 1: does person exist
    if (!isAccountRegistered(borrower_id)) {
        // No account found!
        std::cout << CANT_FIND_ACCOUNT_ERROR << std::endl;
        return;
    }
    // step 2: does book exist, is it already loaned?
    if (!isBookValid(book_title)) {
        std::cout << CANT_FIND_BOOK_ERROR << std::endl;
        return;
    }

    if (!isBookLoaned(book_title)) {
        // Loan book
        loans_.push_back(new Loan(borrower_id, book_title, *today_));


    } else {
        std::cout << ALREADY_LOANED_ERROR << std::endl;
    }


}

void Library::renew_loan(const std::string &book_title)
    // Siirtää kirjan book_title eräpäivää
{
    if (!isBookValid(book_title)) {
        std::cout << CANT_FIND_BOOK_ERROR << std::endl;
        return;
    }
    Loan* loan = findLoanByBookTitle(book_title);

    if (loan != nullptr) {
        if (loan->renewLoan()) {
            std::cout << RENEWAL_SUCCESSFUL
                      << loan->getDueDate()
                      << std::endl;

        } else {
            std::cout << OUT_OF_RENEWALS_ERROR << std::endl;
        }
    } else {
        std::cout << LOAN_NOT_FOUND_ERROR << std::endl;
    }

}

void Library::return_loan(const std::string &book_title)
    // Palauttaa lainassa olevan kirjan (book_title)
{
    if (!isBookValid(book_title)) {
        std::cout << CANT_FIND_BOOK_ERROR << std::endl;
        return;
    }
    std::vector<Loan*>::iterator it;
    it = std::find_if(loans_.begin(), loans_.end(), [&](Loan* const& l) {
        return l->getLoanedBook() == book_title;
    });


    if (it != loans_.end()) {
        // Loan was found, let's delete and remove it
        int index = std::distance(loans_.begin(), it);

        delete loans_.at(static_cast<unsigned int>(index));
        loans_.at(static_cast<unsigned int>(index)) = nullptr;
        // Loan was found
        loans_.erase(it);
        std::cout << RETURN_SUCCESSFUL << std::endl;
    } else {
        // Loan was NOT found
        std::cout << LOAN_NOT_FOUND_ERROR << std::endl;
    }
}

bool Library::isBookLoaned(const std::string &book_title)
    // Onko kirja (book_title) lainassa?
{
    // Is book already borrowed?
    std::map< std::string, Loan* >::iterator it;

    for (const auto& loan : loans_) {
        if (loan->getLoanedBook() == book_title) {
            return true;
        }
    }
    return false;
}

Loan* Library::findLoanByBookTitle(const std::string &bookTitle) {
    // Palauttaa osoittimen Loan-olioon kirjan nimen perusteella

    for (const auto& loan : loans_) {
        if (loan->getLoanedBook() == bookTitle) {
            return loan;
        }
    }

    return nullptr;
}


bool Library::isAccountRegistered(const std::string &accountName) {
    // Palauttaa, löytyykö accountName accounts_ tietorakenteesta
    return ( accounts_.find(accountName) != accounts_.end() );


}

bool Library::isBookValid(const std::string &bookTitle) {
    // Palauttaa, löytyykö bookTitle books_ tietorakenteesta
    return ( books_.find(bookTitle) != books_.end() );

}






