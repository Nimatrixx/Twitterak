#include "../include/AnonymousUser.h"
#include <iostream>
using namespace std;

AnonymousUser::AnonymousUser(): User()
{
    set_name("Anonymous User");
}
