#ifndef LICENSE_H
#define LICENSE_H
#include<string>
#include<memory>
#include<vector>
#include<iostream>
#include<map>

class License: public std::enable_shared_from_this<License>{
private:
    std::string name;
    unsigned int salary;
    unsigned int counter = 0; 
public:
    License(std::string name, unsigned int salary);
    std::string get_guildname() const;
    unsigned int get_salary() const;
    bool valid() const;
    bool use();
    std::ostream& print(std::ostream& o) const;
    friend std::ostream& operator<<(std::ostream& o, const License& l);
};

#endif 
