
#include "ProgramBrain.h"


void ProgramBrain::runMainApp() {
    mainArgs.addCurrentProfiles(profs);
    std::cout<<"____________________________\n";
    std::cout<<"|  LOG IN TO YOUR ACCOUNT  |\n";
    std::cout<<"----------------------------\n";
    profs.loginToProfile();
    mainArgs.addCurrentFlightList(baseList);
    runDefaultMenu();
    mainArgs.exitAndReplaceProfileDataBase(profs.getPHead());
}
void ProgramBrain::runDefaultMenu() {
    bool repeat = true;
    do{
        std::cout<<"____________________________\n";
        std::cout<<"| [1] Flight List           |"<<std::endl;
        std::cout<<"| [2] Reservations          |"<<std::endl;
        std::cout<<"| [3] Profile               |"<<std::endl;
        std::cout<<"| [4] Exit                  |"<<std::endl;
        std::cout<<"----------------------------\n";

        this->entryDecission = UserInteractionHelper::chooseValidOption();
        switch(this->entryDecission){
            case 1:
                baseList.readFlightList();
                UserInteractionHelper::waiting();
                break;
            case 2:
                ProgramBrain::reservationMenuRun();
                break;
            case 3:
                ProgramBrain::profileMenu();
                break;
            case 4:
                repeat = false;
                break;
            default:
                std::cout<<"Incorrect Decission"<<std::endl;
                break;
        }
    }while(repeat);
}
void ProgramBrain::profileMenu(){
    bool repeat = true;
    do{
        std::cout<<"____________________________\n";
        std::cout<<"Current Session: ";
        profs.currentSession();
        std::cout<<"-------------------------------------\n";
        std::cout<<"| [1] Print reservation confirmation |"<<std::endl;
        std::cout<<"| [2] Change username or password    |"<<std::endl;
        std::cout<<"| [3] Exit to main Menu              |"<<std::endl;
        std::cout<<"-------------------------------------\n";
        this->profilesMenuDecission = UserInteractionHelper::chooseValidOption();
        switch(this->profilesMenuDecission){
            case 1:
                mainArgs.printBookingConfirmation(profs.current->getAccessToObj()->getPHead());
                UserInteractionHelper::waiting();
                break;
            case 2:
                profs.changeUsernameOrPassword();
                break;
            case 3:
                repeat = false;
                break;
            default:
                std::cout<<"Incorrect Decission"<<std::endl;
                break;
        }
    }while(repeat);

}

void ProgramBrain::reservationMenuRun() {

    bool repeat = true;
    do{
        std::cout<<"___________________________________\n";
        std::cout<<"| [1] Make Reservation            |"<<std::endl;
        std::cout<<"| [2] Show my Reservations        |"<<std::endl;
        std::cout<<"| [3] Delete Reservation          |"<<std::endl;
        std::cout<<"| [4] Search for specific flight  |"<<std::endl;
        std::cout<<"| [5] Exit to main Menu           |"<<std::endl;
        std::cout<<"-----------------------------------\n";
        this->reservationMenuDecission = UserInteractionHelper::chooseValidOption();
        switch(this->reservationMenuDecission) {
            case 1: {
                baseList.readFlightListWithNumbers();
                profs.current->getAccessToObj()->reservationProcess(&baseList, profs.current->getName());

                break;
            }
            case 2:
                profs.current->getAccessToObj()->showReservations();
                UserInteractionHelper::waiting();
                break;
            case 3:
                profs.current->getAccessToObj()->cancelReservations();
                break;
            case 5:
                repeat = false;
                break;
            case 4: {
                Flight *temp = baseList.searchForFlight();
                if (temp) {
                    profs.current->getAccessToObj()->makeReservation(temp, profs.current->getName());
                }
                break;
            }
            default:
                std::cout<<"Incorrect Decission"<<std::endl;
                break;
        }

    }while(repeat);
}
