//
// Created by Antoni Lis on 24/10/2020.
//
#include <iostream>
#include "UserInteractionHelper.h"

void UserInteractionHelper::clearBuffer() {
    std::cin.clear();
    while (std::cin.get() != '\n') {
        continue;
    }
}

int UserInteractionHelper::chooseValidOption() {
    int temp;
    std::cout<<"Choose >"<<std::flush;
    while (!(std::cin >> temp)) { // wybierz opcje i sprawdz czy wpisywana wartość jest do przyjęcia przez strumień wejsciowy
        std::cin.clear(); // jesli nie wyczysc bufor
        while (std::cin.get() != '\n') {
            continue;
        }
        std::cout << "\nType in vaild value >" << std::flush;
    }
    return temp;
}
void UserInteractionHelper::waiting(){ // czeka na reakcje uzytkownika
    clearBuffer();
    std::cout<<"Press enter to continue"<<std::endl;
    getchar(); // to temporary pause
}
std::string UserInteractionHelper::inputString(){
    std::string input;
    clearBuffer();
    std::cin>>input;
    return input;
}
void UserInteractionHelper::toUpperCase(std::string& x){
    for(int i= 0;i<x.size();i++){
        char t = x[i];
        t = toupper(t);
        x[i] = t;
    }
}