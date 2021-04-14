#include<fstream>
#include "FileHelper.h"
#include "FlightsList.h"
#include "ProfileListHelper.h"

void FileHelper::checkFilesInsideOBJ() {
    std::cout<<"1. "<<fileNameFlights<<" 2. "<<fileNameProfiles<<std::endl;
}

void FileHelper::addCurrentFlightList(FlightsList& list){
    int counter = 1;
    std::ifstream flightFile(this->fileNameFlights);
    if(flightFile.is_open()){
        std::cout<<"opened flights list\n";
        std::string tempLine;
        while(getline(flightFile,tempLine)){
            //std::cout<<tempLine<<std::endl; //sprawdzenie
            Flight temporary = getFlightFromLine(tempLine, counter);
            list.addFlightNode(temporary);
            counter++;
        }
        flightFile.close();
    }else{
        std::cout<<"problem ocurred with opening Flights file\n";
    }
}

void FileHelper::addCurrentProfiles(ProfileListHelper& list){

    std::ifstream profFile(this->fileNameProfiles);
    if(profFile.is_open()){
        std::cout<<"opened profiles list\n";
        std::string tempLine;
        while(getline(profFile, tempLine)){
            Profile temporary = getProfileDataFromLine(tempLine);
            list.addProfileNode(temporary);
        }
        profFile.close();
    }else{
        std::cout<<"problem ocurred with opening profiles file\n";
    }
}

void FileHelper::exitAndReplaceProfileDataBase(ProfileListElement* list) { 

    ProfileListElement* t = list;
    std::ofstream profFile(this->fileNameProfiles);
    if(profFile.is_open()){
        std::cout<<"opened profiles list to replace\n";
        while(t){
            std::cout<<"next prof"<<std::endl;
            printToStream(profFile,&(t->profile));
            t=t->pNext;
        }
        profFile.close();
    }else{
        std::cout<<"failed to open profile list to replace\n";
    }

}
void FileHelper::printBookingConfirmation(ReservationListElement * rl) {

    auto list = rl;
    std::ofstream bConfirmation("CONFIRMATION");
    if(bConfirmation.is_open()){
        std::cout<<"opened booking confirmation file\n";
        while(list){
            bConfirmation<<"---------------------------------------------------------\n";
            bConfirmation<<list->pRes->getInfoForConfirmation()<<"\n";
            list=list->pNext;
        }
        bConfirmation.close();
    }else{
        std::cout<<"failed to open booking confirmation file\n";
    }

}


