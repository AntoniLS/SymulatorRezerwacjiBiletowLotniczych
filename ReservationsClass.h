/** @file */
#ifndef REZERWACJEBILETOWLOTNICZYCH_RESERVATIONSCLASS_H
#define REZERWACJEBILETOWLOTNICZYCH_RESERVATIONSCLASS_H

#include<iostream>
#include"FlightsList.h"
#include "ProfileListHelper.h"

/** klasa będaca klasą bazową rezerwacji */
class Reservation {
public:
    Flight flyingTo; ///< Obiekt Lot nie zawiera dynamicznie alokowanej pamieci wiec przez wartosc
    std::string name;///< nazwa profilu dokonujacego rezerwacje
    std::string additionalText; ///< dodatkowe uwagi
    int seats; ///<ilosc miejsc zarezerwowanych
    double acctualPrice; ///< KOSZT PRAWDZIWY, po naliczeniu ew rabatu pomnozony przez ilosc miejsc
    Reservation(): name("unknown"), flyingTo(), additionalText(""),seats(0) {};/// konstruktor domuslny
    /** konstruktor wieloargumentowy */
    Reservation(std::string name, std::string additionalText, int seats, Flight flyingTo, double price) {
        this->name = name;
        this->additionalText = additionalText;
        this->seats = seats;
        this->flyingTo = flyingTo;
        this->acctualPrice = price;
    };
    /**
     * operator strumieniowy (w programie) służący do wypisania rezerwacji do strumienia plikowego
     * */
    friend std::ostream& operator<<(std::ostream& os, Reservation& x);
    /**
     * Metoda wirtualna, wykorzystywana przy potwierdzaniu rezerwacji (polimorfizm)
     * */
    virtual std::string getInfoForConfirmation();
};

/** Klasa RezerwacjaPremium dziedzicząca po zwykłej rezerwacji wykorzystywana do polimorfizmu*/
class ReservationPremium : public Reservation{
    int premiumSeats; ///<ilosc siedzen premium
public:

    ReservationPremium(): premiumSeats(0), Reservation() {};/// konstruktor inicjalizujacy obiekt klasy bazowej konstr. bezargumentowym, nastepnie swoje pola
    /** kosntruktor wieloargumentowy inicjalizujacy klase bazową nastepnie swoje pola */
    ReservationPremium(std::string name, std::string additionalText, int seats, Flight flyingTo, double price): Reservation(name, additionalText, seats, flyingTo, price){};
    /**
     * Metoda wirtualna, wykorzystywana przy potwierdzaniu rezerwacji (polimorfizm)
     * */
    virtual std::string getInfoForConfirmation();
};


/////////////LISTA///////////////////

/** element listy rezerwacji */
struct ReservationListElement{
    ReservationListElement* pNext;
    Reservation* pRes;
};
/** klasa zarządzajaca lista jednokierunkowa rezerwacji*/
class ReservationList{
    ReservationListElement* pHead; ///< wskaznik na piewrszy element listy
public:
    ReservationList() : pHead(nullptr){}; ///konstruktor bezargumentowy
    ~ReservationList(){ ///destruktor
        cancelReservations(); /// zwalnienie pamieci
    }
    ReservationListElement* getPHead(){ ///< zwraca wskaznik na poczatek listy rezerwacji
        return pHead;
    }
    /**
     * metoda wybierajaca lot
     * @return zwraca wpisana liczbe calkowita
     * */
    int chooseFlight();
    /**
     * wyswietl liste zarezerwowanych lotow
     * */
    void showReservations();
    /**
     * metoda odopwiadajaca za proces rezerwacji
     * @param lista lotow
     * @param nazwa uzytkowanika
     * */
    void reservationProcess(FlightsList*, const std::string&);
    /**
     * dodaj nowa rezerwacje klasy Reservation/PremiumReservation w zaleznosci od dokonanego wyboru
     * @param rodzaj rezerwacji
     * @param cena lotu
     * @param ilosc miejsc
     * @param wybrany lot
     * @param nazwa uzytkowanika, ktory dokonuje rezerwacji
     * @param dodatkowe uwagi zawarte przez uzytkowanika dokonujacego rezerwacji premium
     * */
    void addNewReservationNode(int ticketType, double price,int seats, Flight* chosen, const std::string&, const std::string&);
    /**
     * metoda anulująca rezerwacje.
     * */
    void cancelReservations();
    /**
     * metoda dodajaca rezerwacje, przyjmując kontretny lot jako argument
     * */
    void makeReservation(Flight*, const std::string&);
};


#endif //REZERWACJEBILETOWLOTNICZYCH_RESERVATIONSCLASS_H
