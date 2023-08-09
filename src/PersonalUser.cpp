#include "../include/PersonalUser.h"

#include <iostream>

PersonalUser::PersonalUser(): User() {}

void PersonalUser::set_office(std::string officeId)
{
    office = officeId;
}

std::string PersonalUser::get_office() const
{
    return office;
}
