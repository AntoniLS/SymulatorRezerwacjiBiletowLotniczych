/** @file */
#ifndef PROJEKT_PROGRAMBRAIN_H
#define PROJEKT_PROGRAMBRAIN_H

#include "UserInteractionHelper.h"
#include "FileHelper.h"
#include "FlightsList.h"
#include "ProfileListHelper.h"

/** Klasa zarzadzajaca calym programem i jego przebiegiem*/
class ProgramBrain {
    bool loginTime; ///< zawiera wartosc logiczna pozwalajaca/ lub nie na zalogowanie sie uzytkownika
    FileHelper mainArgs; ///< Obiekt zawierajacy operacje na plikach
    FlightsList baseList; ///< Obiekt zawierajacy operacje na liscie lotów
    ProfileListHelper profs;
    int entryDecission; /// decyzja wejściowa którą ścierzkę w programie obierzemy
    int profilesMenuDecission; /// decyzja w menu profilow
    int reservationMenuDecission; /// decyzja w menu rezerwacji
public:
    explicit ProgramBrain(FileHelper& args, bool t) : mainArgs(args), entryDecission(0), loginTime(t){}; // konstruktor inicjalizuje istotne pola
    /**
     * włącz aplikacje główną
     * */
    void runMainApp();
    /**
     * wyswietl podstawowe menu
     * */
    void runDefaultMenu();
    /**
     * menu rezerwacji
     * */
    void reservationMenuRun();
    /**
     * menu profilu
     * */
    void profileMenu();

};


#endif //PROJEKT_PROGRAMBRAIN_H
