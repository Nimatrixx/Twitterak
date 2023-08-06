#ifndef OrganisationUser_h
#define OrganisationUser_h

#include "User.h"
#include <iostream>

class OrganisationUser : public User
{
public:
    OrganisationUser(std::string);
    void set_bio(std::string);
    void set_CEO(std::string);
    std::string get_CEO() const;
private:
    std::string CEO;
};

#endif
