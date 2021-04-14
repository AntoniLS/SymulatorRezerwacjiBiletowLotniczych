/** @file */
#ifndef PROJEKT_PROFILESHELPER_H
#define PROJEKT_PROFILESHELPER_H
#include <iostream>
#include "ReservationsClass.h"

/** klasa obsługująca profil i metody z nim związane */
class Profile{
    std::string name; ///<username uzytkownika
    std::string password; ///< haslo uzytkownika
    ReservationList reservations; ///< lista rezerwacji dokonanych przez uzytkownika
public:
    /** konstruktor domyslny */
    Profile() : name("default"), password("default") {};
    /**
     * funkcja tworzy obiekt Profil, bazujac na danych przekazanych w linijce z pliku zawartej w string
     * @params linia pochodzaca z pliku wejsciowego zawierajaca dane na temat profilu
     * */
    friend Profile getProfileDataFromLine(const std::string&);
    /**
     * metoda porownujaca username z wpisanym
     * @param proba wpisania nazwu
     * @retrun czy próba skonczyla sie pomyslnie
     * */
    bool cmpName(const std::string&) const;
    /**
     * metoda porownujaca password z wpisanym
     * @param proba wpisania hasla
     * @retrun czy próba skonczyla sie pomyslnie
     * */
    bool cmpPass(const std::string&) const;
    /**
     * setter, username
     * */
    void setName(const std::string&);
    /**
     * setter, password
     * */
    void setPass(const std::string&);
    /**
     * getter
     * @return name
     * */
    std::string getName() const;
    /**
    * getter
    * @return password
    * */
    std::string getPassword() const;
    /**
     * funkcja przekazujaca dane klasy do przekazanego przez parametr strumienia
     * @param strumień
     * @param profil
     * */
    friend void printToStream(std::ostream&,const Profile*);
    /**
     * metoda zwraca adres listy rezerwacji
     * */
    ReservationList* getAccessToObj();
};

/** element listy profilow */
struct ProfileListElement{
    ProfileListElement* pNext; ///< wskaznik na nastepny node
    Profile profile; /// obiekt profil
};
/** lista profilów */
class ProfileListHelper{
    ProfileListElement* pHead; ///< wskaznik na poczatek listy profilow
  //  Profile* current;
public:
    Profile* current; ///< wskaznik na profil aktualnie obsługiwany przez program po pomyslnym zaologowaniu sie
    ProfileListHelper() : pHead(nullptr), current(nullptr) {}; /// konstruktor domyślny
    ~ProfileListHelper(); /// destruktor
    void addProfileNode(Profile&);
    /**
     * Zwraca Profil który bedziemy modyfikowali
     * */
    void loginToProfile();
    /**
     * metoda przeszukująca liste w celu dopasowania danych podanych przez uzytkownika do istniejacego profliu wczytanego z pliku
     * */
    bool searchForProfile(const std::string&, const std::string&);
    /**
     * metoda pozwalaajaca na zmiane nazwy lub hasla aktualnie zalogowanego uzytkowanika
     * */
    void changeUsernameOrPassword();
    /**
     * metoda wyswietlajaca dane uzytkownika w aktualnej sesji
     * */
    void currentSession();
    /**
     * metoda zwracajaca wskaznik na poczatek listy
     * @return wskaznik na poczatek listy
     * */
    ProfileListElement* getPHead();
    /**
     * metoda zwracajaca wskaznin na akutaly profil, przy dopasowaniu w trakcie logowania
     * @retrun wskaznik na profil
     * */
    Profile* getCurrent();
};
/**
    * funkcja tworzy obiekt Profil, bazujac na danych przekazanych w linijce z pliku zawartej w string
    * @params linia pochodzaca z pliku wejsciowego zawierajaca dane na temat profilu
    * */
Profile getProfileDataFromLine(const std::string&);



#endif //PROJEKT_PROFILESHELPER_H
