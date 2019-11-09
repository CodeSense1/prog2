#include "cards.hh"

// TODO: Implement the methods here

Cards::Cards() : top_(nullptr) //top on tyhjä osoitin
{

}

void Cards::add(int id)
{
    Card_data* new_card = new Card_data;
    new_card->data = id;
    new_card->next = top_;

    top_ = new_card;
}

void Cards::print_from_top_to_bottom(std::ostream &s)
{
    Card_data* current = top_;  //pitää kirjaa
    int number = 1;

    while(current != nullptr){
        s << number << ": " << current->data << std::endl;
        ++number;
        current = current->next;        //current on currentista seuraava
    }
}

bool Cards::remove(int &id)
{

    if(top_ == nullptr){    //jos päällimmäinne on nullptr niin on tyhjä pakka
        return false;
    }

    id = top_->data;
    Card_data* temp = top_;     //ensimmäinen kortti tempiksi
    top_ = top_->next;          //siirrytään seuraavaan korttiin
    delete temp;        //poistetaan eka kortti


    return true;
}

bool Cards::bottom_to_top()
{
    //haetaan toiseksi viimeinen ja viimeinen kortti ja laitetaan last(viimeinen) osoittamaan ekaan ja top osoittamaan vikaan(joka uusi päälimmäinen)

    if(top_ == nullptr){
        return false;
    }
    if(top_->next == nullptr){
        return true;
    }

    Card_data* second_last = top_;

    while(second_last->next->next != nullptr){        //tämä luuppi etsii toiseksi viimeisen
        second_last = second_last->next;
    }
    //second last known
    Card_data* last = second_last->next;
    last->next = top_;
    top_ = last;
    second_last->next = nullptr;

    return true;

}

bool Cards::top_to_bottom()
{

    if(top_ == nullptr){
        return false;
    }


    //tarvitaan tieto vikasta kortista, vika osoittamaan ekaan, top osoittamaan keskimmäiseen
    Card_data* last = top_;
    while(last->next != nullptr){
        last = last->next;
    }

    //top osoittaa päälimmäiseen ja päälimmäinen osoittaa maahan (ainakin vain yhden kortin tapauksessa)
    last->next = top_;
    top_ = top_->next;
    last->next->next = nullptr;

    return true;

}

void Cards::print_from_bottom_to_top(std::ostream &s)
{
    //main kutsuu tätä ja tämä kutsuu recursive funktiota
    recursive_print(top_, s);


}

Cards::~Cards(){
    Card_data* current = top_;  //pitää kirjaa mikä halutaan poistaa

    while(top_ != nullptr){     //loopataan kunnes top on nullptr eli ollaan päästy vikaan korttiin
        current = top_;     //otetaan top currentiksi
        top_ = top_->next;  //top on itsestään seuraava
        delete current;

    }
    current = nullptr;  //varmistamaan, että osoittaa tyhjyyteen ettei käytetä currentia väärin. ei varma testataanko tätä


}

int Cards::recursive_print(Cards::Card_data* current, std::ostream &s) //muista päivittää current myös hh tiedostoon (taitaa olla top_ siellä)
{
    //mennään rekursion avulla eteenpäin kunnes löydetään vika kortti ja sit tullaan sieltä taaksepäin
    if(current == nullptr){
        return 1;
    }

    int number = recursive_print(current->next, s);
    s << number << ": " << current->data << std::endl;
    return number +1;

}
