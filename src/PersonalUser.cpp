#include "../include/PersonalUser.h"

#include <iostream>
using namespace std;

PersonalUser::PersonalUser(string id): User(id) {}

void PersonalUser::set_office(string officeId)
{
    office = officeId;
}

string PersonalUser::get_office() const
{
    return office;
}
