#ifndef TWITTERAKBACKEND_H
#define TWITTERAKBACKEND_H

#include <QObject>
#include <stdexcept>
#include <QString>
#include <QVariant>
#include <QDebug>
#include <fstream>
#include <string>
#include <stdio.h>
#include <chrono>
#include <filesystem>

#include "User.h"
#include "Date.h"
#include "PersonalUser.h"
#include "AnonymousUser.h"
#include "OrganisationUser.h"


class TwitterakBackend : public QObject
{
    Q_OBJECT
public:
    explicit TwitterakBackend(QObject *parent = nullptr);
    Q_INVOKABLE QString get_username() const;
    Q_INVOKABLE QString get_password() const;
    Q_INVOKABLE QString get_name() const;
    Q_INVOKABLE QString get_phoneNumber() const;
    Q_INVOKABLE QString get_bio() const;
    Q_INVOKABLE QString get_country () const;
    Q_INVOKABLE QString get_link () const;
    Q_INVOKABLE QString get_office () const;
    Q_INVOKABLE QString get_ceo () const;
    Q_INVOKABLE int get_dayOfBirth() const;
    Q_INVOKABLE int get_monthOfBirth() const;
    Q_INVOKABLE int get_yearOfBirth() const;
    Q_INVOKABLE QString get_id() const;
    Q_INVOKABLE int get_followers() const;
    Q_INVOKABLE int get_followings() const;
    Q_INVOKABLE QString get_profilePicture() const;
    Q_INVOKABLE QString get_header() const;
    Q_INVOKABLE QString get_custom() const;


    Q_INVOKABLE QString get_temp_username() const;
    Q_INVOKABLE QString get_temp_password() const;
    Q_INVOKABLE QString get_temp_name() const;
    Q_INVOKABLE QString get_temp_phoneNumber() const;
    Q_INVOKABLE QString get_temp_bio() const;
    Q_INVOKABLE QString get_temp_country () const;
    Q_INVOKABLE QString get_temp_link () const;
    Q_INVOKABLE int get_temp_dayOfBirth() const;
    Q_INVOKABLE int get_temp_monthOfBirth() const;
    Q_INVOKABLE int get_temp_yearOfBirth() const;
    Q_INVOKABLE QString get_temp_id() const;
    Q_INVOKABLE int get_temp_followers() const;
    Q_INVOKABLE int get_temp_followings() const;
    Q_INVOKABLE QString get_temp_profilePicture() const;
    Q_INVOKABLE QString get_temp_header() const;
    Q_INVOKABLE QString get_temp_custom() const;

    Q_INVOKABLE int get_type() const;
    Q_INVOKABLE int get_temp_type() const;

public slots:

    //set username and password
    //this func is called when user fills first register form or when user edits his/her profile
    bool setMainInfo(int type ,QObject* username, QObject* password, QObject* usernameWarn, QObject* passwordWarn);

    //set secondary info contains "name" "phone" "country" "date of birth" "bio" "link" "office/Ceo"(custom)
    //this func is called when user fills second register form or when user edits his/her profile
    bool setSecondaryInfo(int type, QObject* name, QObject* phone,QObject* county,QObject* year,QObject* month,QObject* day,QObject* bio,QObject* link, QObject* custom,QObject* warn , QString profile, QString header);

    //create an ID for user
    //save ID , username and password in userkeys.txt
    //this func is called when user fills both register forms successfully (sign up)
    void registerUser(int type);

    //save all user profiles info contains:
    //"ID" "username" "password" "name" "phone" "country" "date of birth" "bio" "link" "office/Ceo"(custom)
    //in users/"ID".txt
    bool saveUserInfo(bool saveTempUser);

    //validate entered username and password with userkeys.txt
    //if validation was successfull loads user profile and returns 1
    //else visible warn labels, assign a warn to text property and return 0
    bool login(QObject* usernameField, QObject* passwordField, QObject* usernameWarn, QObject* passwordWarn);

    bool loadProfile(QString id, bool loadToTemp);
    void updateUserKey();
    void tweet(QObject* tweetBox);
    void loadTweets(QObject* listModel, QString id);
    void likeTweet(QString tweetOwnerId, QString tweetId, bool isLiked);
    bool searchUser(QString username);
    void logout();
    void follow(QString id);
    void unfollow(QString id);
    bool isFollowed(QString id);
    bool loadFollowings(QObject* followingsModel);
    std::string findIdbyUsername(std::string username);


private:
    void addKeywordToUserHistory(std::string word);

    User* user;
    User* tempUser;
    AnonymousUser a_user, temp_a_user;
    PersonalUser p_user, temp_p_user;
    OrganisationUser o_user, temp_o_user;

};

#endif // TWITTERAKBACKEND_H
