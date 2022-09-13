#include<string>
#include<memory>
#include<vector>
#include<iostream>
#include<stdexcept>
#include<set>
#include<algorithm>
#include<map>
#include "guild.h"
#include "license.h"
#include "person.h"


Guild::Guild(std::string name, unsigned int fee, unsigned int sal, const std::vector<std::shared_ptr<Person>>& members)  {
    this->name=name;
    this->fee=fee;
    this->salary=sal;
  
    if(name.empty()) throw std::runtime_error("Name ist ungueltig");
    if(fee <= 0 || salary <= 0) throw std::runtime_error("Parameter ist ungueltig");
   
    for(std::size_t i=0; i < members.size(); i++){
        if(this->members.count(members.at(i)->get_name())) throw std::runtime_error("Person ist schon in der Map");
            this->members[members.at(i)->get_name()] = members.at(i);
    }
}

bool Guild::add_member(std::shared_ptr<Person> p){
    for(auto it = members.begin(); it != members.end(); it++){
        std::shared_ptr<Person> temporary = it->second;
        if(temporary == p) return false;
    }
    members[p->get_name()] = p;
    return true;
}

bool Guild::remove_member(std::string n){
    if(members.erase(n))return true;
    else return false;
}

void Guild::grant_license(std::string n){
    if(members.find(n) == members.end()) throw std::runtime_error("Gildenmitglied existiert nicht");
    for (auto it= members.begin(); it != members.end(); it++)
        if (it->first == n && it->second->pay_fee(fee)) {
            it->second->receive_license(std::make_unique<License>(name,salary));
            return;
        }
    throw std::runtime_error("Gildenmitglied Lizenzgebuhr nicht genuegend");
}

bool Guild::offer_job(std::shared_ptr<Person> p) const{
    if (members.count(p->get_name())) {
        p->work(salary*2);
        return true;
    }
    if (!members.count(p->get_name()) && p->eligible(name)) {
        p->work(name);
        return true;
    }
    return false;
}

std::ostream& Guild::print(std::ostream& o) const{
    bool first{true};
    o << '[' << name << ", License fee: " << fee << ", Job salary: " << salary << ", {";
    for (const auto& mem : members) {
        if (first) {
            o<< mem.first;
            first = false;
        } else
            o << ", " << mem.first;
    }
    return o << "}]";
}

std::ostream& operator<<(std::ostream& o, const Guild& g){
    return g.print(o);
}
