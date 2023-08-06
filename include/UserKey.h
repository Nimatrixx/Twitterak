#ifndef UserKey_h
#define UserKey_h

#include <iostream>
class UserKey{
    public:
    UserKey(std::string u, std::string i);
    std::string getUsername() const;
    std::string getId() const;

    private:
    std::string username;
    std::string id;
};

#endif
