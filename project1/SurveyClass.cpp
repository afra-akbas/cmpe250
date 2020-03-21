#include "SurveyClass.h"

SurveyClass::SurveyClass(){
    this->members = NULL;
}

SurveyClass::SurveyClass(const SurveyClass &other) {
    this->members = other.members;
}

SurveyClass& SurveyClass::operator=(const SurveyClass &list) {
    this->members = list.members;
    return *this;
}

//if members is null it creates new linkedlist
//then it adds member to tail

void SurveyClass::addMember(const Member &newMember) {
    if (this->members == NULL) {
        this->members = new LinkedList();
    }
    this->members->pushTail(newMember);

}

//if it has no member return 0 else it adds all them and divides linkedlist' length

float SurveyClass::calculateAverageAge() {
    float sum = 0;
    if(this->members == NULL)
        return 0;
    else{
        Node *cur = this->members->head;
        while(cur != NULL){
            sum += cur->data.age;
            cur = cur->next;
        }
        return sum/this->members->length;
    }


}

//str keeps the color if member is null return empty string
//cur takes the current node
//iter makes the iteration and compares current with the other nodes
//int max keeps the number of theMostFavColor

string SurveyClass::findMostFavouriteColor() {
    string str = "";
    if(this->members == NULL)
        return str;
    else{
        Node *cur = this->members->head;
        str = cur->data.color;
        int max = 0;
        while(cur->next != NULL){
            Node *iter = cur;
            int count = 1;
            while(iter->next != NULL){
                if(iter->data.color != iter->next->data.color)
                    break;
                count++;
                iter = iter->next;
            }
            if(count > max){
                max = count;
                str = cur->data.color;
            }
            cur = cur->next;
        }
        return str;
    }

}

SurveyClass::~SurveyClass() {
    if(members)
        delete members->head;

}
