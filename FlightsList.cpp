#include "FlightsList.h"
#include <iostream>
#include <sstream>

void FlightsList::readFlightList() {
    auto t = pHead;
    if(t){
        while(t){
            std::cout<<(t->flight);
            t = t->pNext;
        }
    }else{
        std::cout<<"Brak planowanych lotów"<<std::endl;
    }
}
void FlightsList::readFlightListWithNumbers(){
    auto t = pHead;
    if(t){
        while(t){
            std::cout<<"["<<t->flight.getNumberInList()<<"] ";
            std::cout<<(t->flight);
            t = t->pNext;
        }
    }else{
        std::cout<<"Brak planowanych lotów"<<std::endl;
    }
}

Flight getFlightFromLine(const std::string & line, int x){
    Flight temporaryFlight;
    std::stringstream ss(line);
    std::string temp;
    ss >> temporaryFlight.from >> temp >> temporaryFlight.to >> temp >> temporaryFlight.date.day >>temp>> temporaryFlight.date.month
    >> temp >> temporaryFlight.date.year >> temp >> temporaryFlight.date.hour >> temp >> temporaryFlight.date.minute >> temp >> temporaryFlight.price
    >> temp >> temporaryFlight.seats;
    temporaryFlight.numberInList = x;
    return temporaryFlight;
}
void FlightsList::addFlightNode(Flight& passedFlight){
    int counter = 0;
    ListElement* temp = new ListElement;
    temp->pNext = nullptr;
    temp->flight = passedFlight;

    if(!pHead){
        pHead = temp;
        std::cout<<"created first node\n";
        return;
    }else{
        auto t = pHead;
        while(t->pNext){
            t = t->pNext;
        }
        t->pNext = temp;
        std::cout<<"created new node\n";
        return;
    }
}
std::ostream& operator<<(std::ostream& os, Flight& x){
    os<<x.from<<" -> "<<x.to<<" Date: "<<x.date.day<<":"<<x.date.month<<":"<<x.date.year<<" Time: "<<x.date.hour<<":"<<x.date.minute<<" Price: "<<x.price<<" Seats left: "<<x.seats<<"\n";
    return os;
}


//Flight getFlightFromLine(const std::string &) {
//    return Flight();
//}

FlightsList::~FlightsList(){
    ListElement* temp = pHead;
    while(temp){
        ListElement* temptemp = temp;
        temp = temp->pNext;
        delete temptemp;
        std::cout<<"deleted flightNode!"<<std::endl;
    }
    pHead = nullptr;
}
Flight* FlightsList::searchForFlightThatMatters(int chosen){
    auto t = pHead;
    if(t){
        while(t){
            if(t->flight.getNumberInList() == chosen){
                return &(t->flight);
            }
            t = t->pNext;
        }
    }else{
        std::cout<<"Brak planowanych lotów"<<std::endl;
        return nullptr;
    }
}

Flight* FlightsList::searchForFlight() {
    bool srch = true;
    do {
        std::cout << "Search flight:\nFROM >" << std::flush;
        std::string tempFrom = UserInteractionHelper::inputString();
        std::cout << "TO >" << std::flush;
        std::string tempTo = UserInteractionHelper::inputString();

        UserInteractionHelper::toUpperCase(tempFrom);
        UserInteractionHelper::toUpperCase(tempTo);

        ListElement *t = pHead;
        bool thereWasOrThereWasnt = true;
        int counter = 1;
        while (t) {
            if (tempFrom == t->flight.getFrom()) {
                std::cout << t->flight << std::endl;
                t->flight.setSpecifiedNumberInList(counter);
                counter++;
                thereWasOrThereWasnt = false;
            }
            t = t->pNext;
        }
        UserInteractionHelper::waiting();
        if (thereWasOrThereWasnt) {
            std::cout << "There aren't any flights From or To this location";
        } else {
            std::cout << "Do you want to make reservation for one of them?\n";
            std::cout << "[1] Yes\n[2] No\n" << std::flush;
            int answ = UserInteractionHelper::chooseValidOption();
            switch (answ) {
                case 1: {
                    ListElement *t2 = pHead;
                    while (t2) {
                        if (tempFrom == t2->flight.getFrom()) {
                            std::cout << "[" << t2->flight.getSpecifiedNumberInList() << "] " << t2->flight
                                      << std::endl;
                        }
                        t2 = t2->pNext;
                    }
                    int answ = UserInteractionHelper::chooseValidOption();
                    bool check = checkIfThereIsFlightWithSuchNumber(answ);
                    if (check) {
                        return returnThatOne(answ);
                    }
                    std::cout << "Wrong input" << std::endl;
                    std::cout << "Retruning to reservations menu" << std::endl;
                    srch = false;
                    break;
                }
                case 2: {
                    srch = false;
                    break;
                }
                default:
                    break;
            }
            //zerowanie pod koniec gdy nie jest juz potrzebne;
            clearNumberInSpecifiedList();
        }
    } while (srch);
    return nullptr;
}


void FlightsList::clearNumberInSpecifiedList(){
    ListElement* temp = pHead;
    while(temp){
        temp->flight.setSpecifiedNumberInList(0);
        temp = temp->pNext;
    }
}
bool FlightsList::checkIfThereIsFlightWithSuchNumber(int x){
    ListElement* temp = pHead;
    while(temp){
        if(temp->flight.getSpecifiedNumberInList() == x){
            return true;
        }
        temp = temp->pNext;
    }
    return false;
}
Flight* FlightsList::returnThatOne(int x){
    ListElement* temp = pHead;
    while(temp){
        if(temp->flight.getSpecifiedNumberInList() == x){
            return &temp->flight;
        }
        temp = temp->pNext;
    }
    return nullptr;
}