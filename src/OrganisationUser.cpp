#include "../include/OrganisationUser.h"

#include <iostream>
using namespace std;

OrganisationUser::OrganisationUser():User(){}

void OrganisationUser::set_bio(string newBio){
    if (newBio.size()<1100){
        bio = newBio;
    }
    else {
        throw invalid_argument(
            "* the maximum length is 1100 characters."
        );
    }
}

void OrganisationUser::set_CEO(string id)
{
    CEO = id;
}

string OrganisationUser::get_CEO() const
{
    return CEO;
}

void OrganisationUser::clear()
{
    User::clear();
    CEO.clear();
}
