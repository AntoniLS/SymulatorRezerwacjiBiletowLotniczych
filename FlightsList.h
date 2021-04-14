/** @file */
#ifndef REZERWACJEBILETOWLOTNICZYCH_LOTYLISTA_H
#define REZERWACJEBILETOWLOTNICZYCH_LOTYLISTA_H
#include<iostream>


/** struktura zawierajaca datę lotu */
struct Date{
    std::string day; ///< dzien
    std::string month; ///< miesiac
    std::string year; ///< rok
    std::string hour; ///< godzina
    std::string minute; ///< minuta
};
/** klasa zajmująca się samym lotem i operacjach z nim związanymi */
class Flight{
    std::string from; ///< lot z
    std::string to; ///< lot do
    Date date; ///< struktura zawierajaca dane
    int price; ///< cena
    int seats; ///< siedzenia
    int numberInList; ///< numer w liscie lotow
    int numberInSpecifiedList; ///< numer przy szukaniu konkretnego lotu
public:
    /**
     *  funkcja tworzy obiekt lot, bazujac na danych przekazanych w linijce z pliku zawartej w string
     *  @retrun zwraca obiekt lot którego wszystkie pola są statyczne
     * */
    friend Flight getFlightFromLine(const std::string&, int);
    /**
     *  operator strumieniowy
     * */
    friend std::ostream& operator<<(std::ostream&, Flight&);
    /**
     * getter
     * @retrun zwraca numer lotu na liscie
     * */
    int getNumberInList(){
        return numberInList;
    };
    /**
     * getter
     * @retrun zwraca cene
     * */
    int getPrice(){
      return price;
    };
    /**
     * getter
     * zwraca ilosc miejsc w samolocie
     * */
    int getSeats(){
        return seats;
    };
    /**
     * getter
     * @retrun zwraca miejsce z którego dokonywany jest lot
     * */
    std::string getFrom(){
        return from;
    };
    /**
     * getter
     * @retrun zwraca miejsce do którego dokonywany jest lot
     * */
    std::string getTo(){
        return to;
    }
    /**
     * getter
     * @retrun zwraca referencje do struktury zawierajaca dane o dacie lotu
     * */
    Date& getDate(){
        return date;
    }
    /** setter */
    void setSeats(int x){
        seats = x;
    }
    /** setter */
    void setSpecifiedNumberInList(int x){
        numberInSpecifiedList = x;
    }
    /** getter */
    int getSpecifiedNumberInList(){
        return numberInSpecifiedList;
    }

};
/** element listy */
struct ListElement{
  ListElement* pNext;
  Flight flight;
};

/**  klasa lista lotów */
class FlightsList{ /// lista lotow
private:
    ListElement* pHead; ///<wskaznik na nastepny element listy
public:
    FlightsList(){
        this->pHead = nullptr;///<automatycznie ustawia nullptr dla glowy listy
    }
    /**
     * metoda tworząca nowy element listy, zawierajacy lot
     * @param dane na temat lotu
     * */
    void addFlightNode(Flight&);
    /**
     * metoda czytajaca wszystkie loty w opowiednim formacie
     * */
    void readFlightList(); // wyświetlenie listy
    /**
     * metoda usuwajaca lot ktorego miejsca sa rowne 0
     * */
    void deleteNodeWithsSeatsEqualZero(); // usunięcie wskazanego node'a
    /**
     * metoda czytajaca wyszystkie loty łączenie z ich numerami na liscie
     * */
    void readFlightListWithNumbers();
    /**
     * metoda szukajaca wybranego przez uzytkownika
     * @param numer wybranego lotu
     * @retrun wskaznik na lot
     * */
    Flight* searchForFlightThatMatters(int);
    /** destruktor listy lotow ( w nim zwolnienie pamieci z zaalokowamych nodeów)*/
    ~FlightsList();

    /**
     * medota wyszukująca konkretny wybrany przez użytkownika lot
     * */
    Flight* searchForFlight();
    /**
     * metoda pozbywajaca sie przypisanego do lotu numery wymaganego do wybrania go podczas rezerwacji
     * */
    void clearNumberInSpecifiedList();

    /**
     * metoda sprawdzająca czy istnieje lot o danym numerze
     * */
    bool checkIfThereIsFlightWithSuchNumber(int x);

    /**
     * metoda zwaracajaca konkretny lot
     * */
    Flight* returnThatOne(int x);
};
/**
   * funkcja tworzy obiekt lot, bazujac na danych przekazanych w linijce z pliku zawartej w string
   * @retrun zwraca obiekt lot którego wszystkie pola są statyczne
*/
Flight getFlightFromLine(const std::string&, int);

#endif //REZERWACJEBILETOWLOTNICZYCH_LOTYLISTA_H
