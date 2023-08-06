#include "../include/UserKey.h"
#include <iostream>
using namespace std;


UserKey::UserKey(string u, string i): username(u), id(i){}


string UserKey::getUsername() const
{
    return username;
}

string UserKey::getId() const
{
    return id;
}
