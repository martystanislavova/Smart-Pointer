#include<string>
#include<memory>
#include<vector>
#include<iostream>
#include<map>
#include "license.h"

License::License(std::string name, unsigned int salary) : name{name}, salary{salary} {
    if(name.empty() || salary <= 0) throw std::runtime_error("Der Name oder der Lohn sind ungueltig");
}

std::string License::get_guildname() const{
    return name;
}

unsigned int License::get_salary() const{
    return salary;
}

bool License::valid() const{
    return counter <= 3;
}

bool License::use(){
    if(!this->valid()) return false;
    else {
        counter++;
        return true;
    }
}

std::ostream& License::print(std::ostream& o) const{
    return o << "[License for " << this->get_guildname() << ", Salary: " << get_salary() << ", Used: " << counter << "]" ;
}
std::ostream& operator<<(std::ostream& o, const License& l){
    return l.print(o);
} 
