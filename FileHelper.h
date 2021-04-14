/** @file */
#ifndef PROJEKT_FILEHELPER_H
#define PROJEKT_FILEHELPER_H
#include <iostream>
#include "FlightsList.h"
#include "ProfileListHelper.h"

/** klasa zarządzająca plikami */
class FileHelper {
    std::string fileNameProfiles; ///< nazwa pliku z profilami przekazana do konstruktora poprzez parametry wywołania programu
    std::string fileNameFlights; ///< nazwa pliku z lotami przekazana do konstruktora poprzez parametry wywołania programu
public:
    /**
     * Konstruktor przekazujacy nazwe pliku do obiektu (jednoargumentowy)
     * */
    FileHelper(std::string fnF, std::string fnP) : fileNameFlights(fnF), fileNameProfiles(fnP) {};
    /** sprawdzenie czy nazwy plikow zostaly przekazane do obiektu pomyslnie */
    void checkFilesInsideOBJ();
    /**
     * Uzupełnienie listy lotami zawartymi w pliku wejsciowym
     * */
    void addCurrentFlightList(FlightsList&);
    /**
     * Uzupelnienie listy profilow, profilami zawartymi w pliku wejsciowym
     * */
    void addCurrentProfiles(ProfileListHelper&);
    /**
     * Przy wyjsciu zapisuje dane profilu (zmieniona nazwa/hasło)
     * */
    void exitAndReplaceProfileDataBase(ProfileListElement*);
    /**
     * Wypisz informacje, jako potwierdzenie rezerwacji do pliku w odpowiednio sformatowany sposób,
     * bazując na polimorfizmie -> funkcji virtualnych
     * */
    void printBookingConfirmation(ReservationListElement*);

};


#endif //PROJEKT_FILEHELPER_H
