
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
    void set_id(std::string);
    void set_username(std::string);
    void set_password(std::string);
    void set_name(std::string);
    void set_phoneNumber(std::string);
    virtual void set_bio(std::string);
    void set_country (std::string);
    void set_link (std::string);
    void set_dateOfBirth(Date);
    void set_followings(std::vector<std::string>);
    void set_followers(std::vector<std::string>);
    void set_profilePicture(std::string);
    void set_header(std::string);

    std::string get_username() const;
    std::string get_password() const;
    std::string get_name() const;
    std::string get_phoneNumber() const;
    std::string get_bio() const;
    std::string get_country () const;
    std::string get_link () const;
    Date get_dateOfBirth() const;
    std::string get_id() const;
    std::vector<std::string> get_followers() const;
    std::vector<std::string> get_followings() const;
    std::string get_profilePicture() const;
    std::string get_header() const;

    bool follow(std::string);
    bool unfollow(std::string);
    bool followed(std::string);
    bool unfollowed(std::string);

    virtual void clear();

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

    std::string profilePicture;
    std::string header;
    std::vector<std::string> followers;
    std::vector<std::string> followings;
};

#endif
