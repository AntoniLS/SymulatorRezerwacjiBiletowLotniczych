#include <iostream>
#include "ProgramBrain.cpp"
#include "FileHelper.cpp"
#include "UserInteractionHelper.cpp"
#include "FlightsList.cpp"
#include "ProfileListHelper.cpp"
#include "ReservationsClass.cpp"

int main(int argc, char* argv[]){
    /// zapisanie nazw argumentów wejsciowych do łańcuchów znaków
    char* nameOfEntryFileWithFlights;
    char* clientsProfiles;
    /// sprawdzenie czy argumenty zostaly wprowadzone poprawnie
    for(int counter = 0; counter < argc ; counter++){
        char* param = argv[counter];
        if(!strcmp(param,"-i")){
            printf("correct input file\n");
            nameOfEntryFileWithFlights = argv[counter + 1];
            std::cout<<nameOfEntryFileWithFlights<<std::endl;
        }
        if(!strcmp(param,"-icp")){
            printf("correct  input file\n");
            clientsProfiles = argv[counter + 1];
            std::cout<<clientsProfiles<<std::endl;
        }
    }
    /// utworzenie obiektu zarządzającego plikami
    FileHelper fh(nameOfEntryFileWithFlights, clientsProfiles);
    /// utworzenie obiektu głównego programu
    ProgramBrain mainRun(fh, true); // przekazywanie obiektu zaweirajacego argumenty programu
    /// włączenie głównego programu
    mainRun.runMainApp();

}
