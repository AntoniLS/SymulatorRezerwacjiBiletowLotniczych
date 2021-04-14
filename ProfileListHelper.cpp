
#include <iostream>
#include <sstream>
#include "ProfileListHelper.h"

void ProfileListHelper::addProfileNode(Profile &x) {
    ProfileListElement* temp = new ProfileListElement;
    temp->pNext = nullptr;
    temp->profile = x;

    if(!pHead){
        pHead = temp;
        std::cout<<"created first profile\n";
        return;
    }else{
        auto t = pHead;
        while(t->pNext){
            t = t->pNext;
        }
        t->pNext = temp;
        std::cout<<"created new profile\n";
        return;
    }

}
Profile getProfileDataFromLine(const std::string& line){
    Profile temporaryProf;
    std::stringstream ss(line);
    ss>>temporaryProf.name>>temporaryProf.password;
    return temporaryProf;
}
void ProfileListHelper::loginToProfile(){
    bool loginTime = true;
        int yORn;
        std::string usernameAttempt;
        std::string passwordAttempt;
        do{
            std::cout<<"Username >"<<std::flush;
            //UserInteractionHelper::clearBuffer();
            std::cin>>usernameAttempt;
            std::cout<<"Password >"<<std::flush;
            UserInteractionHelper::clearBuffer();
            std::cin>>passwordAttempt;

            if(ProfileListHelper::searchForProfile(usernameAttempt, passwordAttempt)){
                loginTime = false;
            }else{
                continue;
            }
         }while(loginTime);
}

bool ProfileListHelper::searchForProfile(const std::string& log, const std::string& pas) {
    ProfileListElement* t = pHead;
    if(t){
        while(t){
            if(t->profile.cmpName(log)){
                if(t->profile.cmpPass(pas)){
                    std::cout<<"logged in successfully!"<<std::endl;
                    this->current = &(t->profile);
                    return true;
                }
            }
            t= t->pNext;
        }
        std::cout<<"wrong username or password"<<std::endl;
        return false;
    }else{
        std::cout<<"Profile List Empty!"<<std::endl;// todo exception albo przejscie do kreatora
        return false;
    }
}
bool Profile::cmpName(const std::string& username) const{
    if(username == name){
        return true;
    }
    return false;
}
bool Profile::cmpPass(const std::string &pass) const {
    if(pass == password){
        return true;
    }
    return false;
}

void ProfileListHelper::changeUsernameOrPassword() {
    std::cout<<"Do you want to change: "<<std::endl;
    std::cout<<"[1] Username"<<std::endl;
    std::cout<<"[2] Password"<<std::endl;
    std::cout<<"> "<<std::flush;
    int temp = UserInteractionHelper::chooseValidOption();
    std::string usernameAttempt;
    std::string passwordAttempt;
    switch (temp){
        case 1:
            std::cout<<"Username >"<<std::flush;
            UserInteractionHelper::clearBuffer();
            std::cin>>usernameAttempt;
            std::cout<<"successfully changed!\n";
            current->setName(usernameAttempt);
            break;
        case 2:
            std::cout<<"Password >"<<std::flush;
            UserInteractionHelper::clearBuffer();
            std::cin>>passwordAttempt;
            std::cout<<"successfully changed!\n";
            current->setName(passwordAttempt);
            break;
        default:
            std::cout<<"Wrong input"<<std::endl;
            break;
    }


}
void Profile::setName(const std::string& x){
    name = x;
}
void Profile::setPass(const std::string& x){
    password = x;
}
std::string Profile::getName() const{
    return name;
}
std::string Profile::getPassword() const{
    return password;
}
void ProfileListHelper::currentSession() {
    std::cout<<current->getName()<<std::endl;
}
ProfileListElement* ProfileListHelper::getPHead(){
    return pHead;
}

void printToStream(std::ostream & ss, const Profile * p) { 
    ss << p->getName()<<" "<<p->getPassword()<<"\n";
}
Profile* ProfileListHelper::getCurrent(){
    return current;
}

ProfileListHelper::~ProfileListHelper() {
    ProfileListElement* temp = pHead;
    while(temp){
        auto tt = temp;
        temp = temp->pNext;
        delete tt;
        std::cout<<"Deleted ProfNode"<<std::endl;
    }
    pHead = nullptr;
}

ReservationList* Profile::getAccessToObj(){
    return &reservations;
}
