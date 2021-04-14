/** @file */

#ifndef PROJEKT_USERINTERACTIONHELPER_H
#define PROJEKT_USERINTERACTIONHELPER_H

/** klasa zawierajaca same metody statyczne służące do interakcji z użytkownikiem */
class UserInteractionHelper {
public:
    /**
     *  Wyczyść bufor
     * */
    static void clearBuffer();

    /**
     *  Kontrola czy wpisywana wartość wyboru jest poprawna
     * */
     static int chooseValidOption();

     /**
      *  Kontrola postępu programu, poprzez potwierdzenia w celu dalszego wczytania funkcji (pauza)
      * */
     static void waiting();

     static std::string inputString();
     /**
      * funkcja zmieniająca wielkość liter zmiennej typu std::string na wielkie litery
      * */
     static void toUpperCase(std::string&);
};


#endif //PROJEKT_USERINTERACTIONHELPER_H
