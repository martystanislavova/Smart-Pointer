#include<string>
#include<memory>
#include<vector>
#include<iostream>
#include<map>
#include "person.h"
#include "license.h"


Person::Person(std::string name, unsigned int wealth) : name{name}, wealth{wealth }{
    if(name.empty()) throw std::runtime_error("Name ist ungueltig");
}

unsigned int Person::get_wealth() const{
   return wealth;
}

void Person::work(std::string guild){
    if(licenses.empty()) throw std::runtime_error("Lizense ist nicht vorhanden");
     if(licenses.count(guild) && licenses[guild]->use())
       this->work(licenses[guild]->get_salary());
     else
       throw std::runtime_error("Lizenz ist nicht vorhanden oder kann nicht benutzt werden");
}

void Person::increase_wealth(unsigned int i){
    wealth += i;
}

std::string Person::get_name() const{
    return name;
}

bool Person::pay_fee(unsigned int i){
    if (wealth < i || i == 0) return false;
    wealth -= i;
    return true;
}

void Person::receive_license(std::unique_ptr<License> l){
    if(licenses.find(l->get_guildname()) != licenses.end()) {
        licenses.erase(l->get_guildname());
    }
    licenses.insert(std::pair<std::string, std::unique_ptr<License>>(l->get_guildname(), std::move(l)));
}

void Person::transfer_license(std::string l,std::shared_ptr<Person> p){
    if(licenses.find(l) == licenses.end()) throw std::runtime_error("Lizense mit diesen Name ungueltig");
    if(licenses.count(l)){
        p->receive_license(std::move(licenses[l]));
        licenses.erase(l);
    }
}

bool Person::eligible(std::string l) const{
    if(licenses.count(l) && licenses.find(l)->second->valid())
        return true;
    return false;
}

std::ostream& Person::print(std::ostream& o) const{
  bool first{true};
    o << name << ", " << wealth << " Coins, {";
    for(const auto& lic : licenses) {
        if(first){
            o << *(lic.second);
            first = false;
        }
        else
            o << ", " << *(lic.second);
    }
    return o << "}]";
}

std::ostream& operator<<(std::ostream& o, const Person& p){
    return p.print(o);
}

Worker::Worker(std::string name, unsigned int wealth) : Person{name, wealth} {}

void Worker::work(unsigned int i){
increase_wealth(i);
}

std::ostream& Worker::print(std::ostream& o) const{
    o << "[Worker ";
    return Person::print(o);
}

Superworker::Superworker(unsigned int fee, std::string name, unsigned int wealth): Person{name, wealth},fee{fee} {}
 
void Superworker::work(unsigned int i){
    increase_wealth(i + fee);
}

std::ostream& Superworker::print(std::ostream& o) const{
    o << "[Superworker ";
    return Person::print(o);
}
