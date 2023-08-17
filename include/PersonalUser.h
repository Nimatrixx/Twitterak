#ifndef PersonalUser_h
#define PersonalUser_h

#include "User.h"

#include <iostream>

class PersonalUser : public User
{
public:
    PersonalUser();
    void set_office(std::string);
    std::string get_office() const;

    void clear();
private:
    std::string office;
};

#endif
