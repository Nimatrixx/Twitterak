#include "AnonymousUser.h"
#include <iostream>
using namespace std;

AnonymousUser::AnonymousUser(std::string id): User(id)
{
    set_name("Anonymous User");
}
