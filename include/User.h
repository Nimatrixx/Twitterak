
#ifndef User_h
#define User_h

#include <iostream>
#include <vector>
#include "Date.h"

class User
{   
public:
    User();
    User(std::string);
    std::string get_id() const;
    void set_username(std::string);
    std::string get_username() const;
    void set_password(std::string);
    std::string get_password() const;
    void set_name(std::string);
    std::string get_name() const;
    void set_phoneNumber(std::string);
    std::string get_phoneNumber() const;
    virtual void set_bio(std::string);
    std::string get_bio() const;
    void set_country (std::string);
    std::string get_country () const;
    void set_link (std::string);
    std::string get_link () const;
    void set_dateOfBirth(Date);
    Date get_dateOfBirth() const;
    std::vector<std::string> get_followers() const;
    std::vector<std::string> get_followings() const;
    bool follow(std::string);
    bool unfollow(std::string);

protected:
    std::string bio;
    
private:
    std::string id;

    std::string username;
    std::string password;

    std::string name;
    std::string phoneNumber;
    std::string country;
    std::string link;
    Date birthDate;

    std::vector<std::string> followers;
    std::vector<std::string> followings;
};

#endif
