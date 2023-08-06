#include <iostream>
#include <fstream>
#include <vector>
#include "../include/User.h"
#include "../include/UserKey.h"
#include "../include/Date.h"
using namespace std;

User::User(){}

User::User(string newId): id(newId){}

string User::get_id() const
{
    return id;
}
void User::set_username(string newUsername)
{
    int usersize = newUsername.length();
    if (usersize < 5){
        throw invalid_argument(
            "* Username must have at least 5 characters."
        );
    }

    if (isdigit(newUsername[0])){
        throw invalid_argument (
            "* The beginning of the username cannot be a number."
        );
    }

    for (int i=0 ; i < usersize ; i++){
        if (!isalnum(newUsername[i])){
            throw invalid_argument(
                "* Username can only contains letters and numbers."
            );
        }
    }

    if (newUsername == "signup" || newUsername =="login" || newUsername == "logout" || newUsername == "tweet"
    || newUsername == "profile"|| newUsername == "retweet" || newUsername == "newUsername" || newUsername == "password"
    || newUsername =="country" || newUsername == "birthdate" || newUsername == "account" || newUsername == "tweets"){
        throw invalid_argument ("* This is a reserved word. You can not choose it as your username.");
    }

    //check repeatation of username
    ifstream file ("userkeys.txt", ios::out | ios::binary);
    if(file)
    {
        UserKey key("","");
        while(!file.eof())
        {
            string r_id , r_username;
            file >> r_id >> r_username;
            if(r_username == newUsername)
            {
                throw invalid_argument ("* Username is already taken.");
            }
        }
    }
    file.close();
    


    username = newUsername;
} 

string User::get_username() const{
    return username;
}

void User::set_password(std::string password){
    if(password.length() < 8)
    {
        throw invalid_argument("* password must have at least 8 characters");
    }

    unsigned digits = 0;
    for(size_t i{0}; i < password.length(); i++)
    {
        if(isdigit(password[i]))digits++;
    }
    if(digits == 0 || digits == password.length())
    {
        throw invalid_argument("* password must contain letters and numbers");
    }

    this -> password = password;
}

string User::get_password()const {
    return password;
}

void User::set_name(string name){
    this->name = name;
}

string User::get_name() const{
    return name;
}

void User::set_phoneNumber(string phone){
    int size = phone.size();
    if (phone.size() == 13){
        phoneNumber = phone;
    }
    else {
        throw invalid_argument (
            "* the phone number must be 13 digits."
        );
    }
    for (size_t i=0 ; i<size ; i++){
        if ( !isdigit(phone[i]) ){
            throw invalid_argument (
            "* the phone number is incorrect."
            );
        }
    }
}

string User::get_phoneNumber() const {
    return phoneNumber;
}

void User::set_bio(string bio){
    if (bio.size()<160){
        this -> bio = bio;
    }
    else {
        throw invalid_argument(
            "* the maximum length is 160 characters."
        );
    }
}

string User::get_bio () const{
    return bio;
}

void User::set_country (string country){
    this -> country = country;
}

string User:: get_country () const{
    return country;
}

void User::set_link (string link){
    if(link.substr(0,4) != "http")
    {
        string prefix = "https://";
        link = prefix + link;
    }else if(link.substr(0,5) == "http:")
    {
        link.insert(4,"s");
    }
    this -> link = link;
}

 
string User::get_link () const{
    return link;
}

void User::set_dateOfBirth(Date date){
    birthDate = date;
}

Date User::get_dateOfBirth() const{
    return birthDate;
}

vector<string> User::get_followers() const
{
    return followers;
}

vector<string> User::get_followings() const
{
    return followings;
}

bool User::follow(string userId)
{
    for(size_t i{0}; i < followings.size(); i++)
    {
        if(followings[i] == userId)
            return 0;
    }

    followings.push_back(userId);

    return 1;
}

bool User::unfollow(string userId)
{
    for(size_t i{0}; i < followings.size(); i++)
    {
        if(followings[i] == userId)
        {
            followings.erase(followings.begin() + i);
            return 1;
        }
            
    }

    return 0;
}
