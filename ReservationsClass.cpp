#include <iostream>
#include "ReservationsClass.h"


void ReservationList::reservationProcess(FlightsList* list, const std::string& un){
    bool priceLoop = true;
    bool seatsLoop = true;
    int ticketType = 0; // 0 - nic, 1-normal, 2-premium;
    int option = this->chooseFlight();
    double price;
    int howManySeats;
    Flight* chosen = list->searchForFlightThatMatters(option);
    if(chosen == nullptr){
        std::cout<<"Wrong number, reservation cancelled"<<std::endl;
        return;
    }
//////////////
    do {
        std::cout << "Which version of ticket would you like to choose?" << std::endl;
        std::cout << "[1] Normal : PriceTag per seat -> " << chosen->getPrice() << std::endl;
        std::cout << "[2] Premium : PriceTag per seat -> " << chosen->getPrice() * 2 << std::endl;
        UserInteractionHelper::clearBuffer();
        int priceOpt = UserInteractionHelper::chooseValidOption();
        if (priceOpt == 1) {
            ticketType = 1;
            price = chosen->getPrice();
            std::cout<<"Normal type\n";
            priceLoop = false;
        } else if (priceOpt == 2) {
            ticketType = 2;
            price = chosen->getPrice() * 2;
            std::cout<<"Premium type!\n";
            priceLoop = false;
        }
    }while(priceLoop);
//////////////
    do {
        std::cout << "How many seats would you like to reserve?" << std::endl;
        std::cout << "> " << std::flush;
        howManySeats = UserInteractionHelper::chooseValidOption();
        if (howManySeats <= chosen->getSeats()) {
            price*=howManySeats;
            int temp = chosen->getSeats() - howManySeats;
            chosen->setSeats(temp);
            seatsLoop = false;
        }else {
            std::cout << "Not enough places inside plane! \n";
        }
    }while(seatsLoop);
///////////////
   if(this->pHead == nullptr){
       int doYouWant;
       bool offLoop = true;
       do{
           std::cout<<"ITS YOUR 1st RESERVATION! -> do you want to claim 30% off for your first flight?"<<std::endl;
           std::cout<<"[1] Yes"<<std::endl;
           std::cout<<"[2] No"<<std::endl;
           UserInteractionHelper::clearBuffer();
           doYouWant = UserInteractionHelper::chooseValidOption();
           if(doYouWant == 1){
            offLoop = false;
            price = price - ((1.0*price)*0.3);
            std::cout<<"Price after discount! -> "<<price<<std::endl;
           }else if(doYouWant == 2){
               offLoop = false;
           }
       }while(offLoop);
   }
////////////////
    std::string at = "";
    if(ticketType == 2) {
        std::cout << "if you have any comments please post them below, then press enter \n >";
        UserInteractionHelper::clearBuffer();
        getline(std::cin, at);
    }
///////////////
    addNewReservationNode(ticketType, price,howManySeats, chosen, un, at);
}

int ReservationList::chooseFlight(){

    std::cout<<"Choose flight you want to reserve, "<<std::flush;
    UserInteractionHelper::clearBuffer();
    int option = UserInteractionHelper::chooseValidOption();

    return option;
}
void ReservationList::addNewReservationNode(int ticketType, double price, int seats, Flight* chosen, const std::string& un, const std::string& at){
        ReservationListElement * newOne = new ReservationListElement;
        newOne->pNext = nullptr;
        newOne->pRes = nullptr;
    if(!pHead){
        //1-normal, 2-premium
        std::cout<<"First Reservation!"<<std::endl;
        if(ticketType == 1){
            Reservation* temp = new Reservation(un,at,seats,*chosen,price);
            newOne->pRes = temp;
        }else if(ticketType == 2){
            ReservationPremium* temp = new ReservationPremium(un,at,seats,*chosen,price);
            newOne->pRes = temp;
        }
        pHead = newOne;
    }
    else{
        auto t = pHead;
        while(t->pNext){
            t= t->pNext;
        }
        std::cout<<"another Reservation!"<<std::endl;
        if(ticketType == 1){
            Reservation* temp = new Reservation(un,at,seats,*chosen,price);
            newOne->pRes = temp;
        }else if(ticketType == 2){
            ReservationPremium* temp = new ReservationPremium(un,at,seats,*chosen,price);
            newOne->pRes = temp;
        }
        t->pNext = newOne;
    }
}
void ReservationList::showReservations(){
    auto t = pHead;
    if(t){
        while(t){
            std::cout<<*(t->pRes)<<std::endl;
            t = t->pNext;
        }
    }else{
        std::cout<<"Brak planowanych lotów"<<std::endl;
    }
}
//std::string name, std::string additionalText, int seats, Flight flyingTo
std::ostream &operator<<(std::ostream& os,Reservation &x) {
    os<<"Reservation for flight: "<<x.flyingTo.getFrom()<<" -> "<<x.flyingTo.getTo()<<" Time: "<<x.flyingTo.getDate().day<<"."<<x.flyingTo.getDate().month<<"."<<x.flyingTo.getDate().year<<" "<<x.flyingTo.getDate().hour<<":"<<x.flyingTo.getDate().minute<<" Number of Seats: "<<x.seats<<" Price for all seats: "<<x.acctualPrice;
    return os;
}
std::string Reservation::getInfoForConfirmation(){
    std::string t = "NORMAL TICKET";
    t.append(" - ");
    t.append(flyingTo.getFrom());
    t.append(" -> ");
    t.append(flyingTo.getTo());
    t.append(" Date: ");
    t.append(flyingTo.getDate().day);
    t.append(":");
    t.append(flyingTo.getDate().month);
    t.append(":");
    t.append(flyingTo.getDate().year);
    t.append(" ");
    t.append(flyingTo.getDate().hour);
    t.append(":");
    t.append(flyingTo.getDate().minute);
    t.append(" Number of Seats: ");
    t.append(std::to_string(seats));
    t.append(" Price for all seats: ");
    t.append(std::to_string(((int)acctualPrice)));
    t.append(" CONFIRMED by RezerwacjeBiletowLotniczych");

    return t;
}
std::string ReservationPremium::getInfoForConfirmation() {
    std::string t = "PREMIUM TICKET";
    t.append(" - ");
    t.append(flyingTo.getFrom());
    t.append(" -> ");
    t.append(flyingTo.getTo());
    t.append(" Date: ");
    t.append(flyingTo.getDate().day);
    t.append(":");
    t.append(flyingTo.getDate().month);
    t.append(":");
    t.append(flyingTo.getDate().year);
    t.append(" ");
    t.append(flyingTo.getDate().hour);
    t.append(":");
    t.append(flyingTo.getDate().minute);
    t.append(" Number of Seats: ");
    t.append(std::to_string(seats));
    t.append(" Price for all seats: ");
    t.append(std::to_string(((int)acctualPrice)));
    t.append(" CONFIRMED by RezerwacjeBiletowLotniczych\n");
    t.append("additional comment/request : ");
    t.append(additionalText);

    return t;
}

void ReservationList::cancelReservations() {
    ReservationListElement* temp = pHead;
    while(temp){
        auto temptemp = temp;
        temp = temp->pNext;
        delete temptemp->pRes;
        temptemp->pRes = nullptr;
        delete temptemp;
        std::cout<<"deleted reservation!"<<std::endl;
    }
    pHead = nullptr;
}

void ReservationList::makeReservation(Flight* chosen, const std::string& un) {
    bool priceLoop = true;
    bool seatsLoop = true;
    int ticketType = 0; // 0 - nic, 1-normal, 2-premium;
    double price;
    int howManySeats;

    do {
        std::cout << "Which version of ticket would you like to choose?" << std::endl;
        std::cout << "[1] Normal : PriceTag per seat -> " << chosen->getPrice() << std::endl;
        std::cout << "[2] Premium : PriceTag per seat -> " << chosen->getPrice() * 2 << std::endl;
        UserInteractionHelper::clearBuffer();
        int priceOpt = UserInteractionHelper::chooseValidOption();
        if (priceOpt == 1) {
            ticketType = 1;
            price = chosen->getPrice();
            std::cout << "Normal type\n";
            priceLoop = false;
        } else if (priceOpt == 2) {
            ticketType = 2;
            price = chosen->getPrice() * 2;
            std::cout << "Premium type!\n";
            priceLoop = false;
        }
    } while (priceLoop);
//////////////
    do {
        std::cout << "How many seats would you like to reserve?" << std::endl;
        std::cout << "> " << std::flush;
        howManySeats = UserInteractionHelper::chooseValidOption();
        if (howManySeats <= chosen->getSeats()) {
            price *= howManySeats;
            seatsLoop = false;
        } else {
            std::cout << "Not enough places inside plane! \n";
        }
    } while (seatsLoop);
///////////////
    if (this->pHead == nullptr) {
        int doYouWant;
        bool offLoop = true;
        do {
            std::cout << "ITS YOUR 1st RESERVATION! -> do you want to claim 30% off for your first flight?"
                      << std::endl;
            std::cout << "[1] Yes" << std::endl;
            std::cout << "[2] No" << std::endl;
            UserInteractionHelper::clearBuffer();
            doYouWant = UserInteractionHelper::chooseValidOption();
            if (doYouWant == 1) {
                offLoop = false;
                price = price - ((1.0 * price) * 0.3);
                std::cout << "Price after discount! -> " << price << std::endl;
            } else if (doYouWant == 2) {
                offLoop = false;
            }
        } while (offLoop);
    }
/////////////////////////
    std::string at = "";
    if(ticketType == 2) {
        std::cout << "if you have any comments please post them below, then press enter \n >";
        UserInteractionHelper::clearBuffer();
        getline(std::cin, at);
    }
///////////////
    addNewReservationNode(ticketType, price,howManySeats, chosen, un, at);
}
