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

    Q_INVOKABLE int getType() const;

public slots:
    bool signUpFirstStep(int type ,QObject* username, QObject* password, QObject* usernameWarn, QObject* passwordWarn);
    bool saveUser(int type, QObject* name, QObject* phone,QObject* county,QObject* year,QObject* month,QObject* day,QObject* bio,QObject* link,QObject* custom,QObject* warn);
    bool loginBtn(QObject* usernameField, QObject* passwordField, QObject* usernameWarn, QObject* passwordWarn);
    bool saveProfile(int type);
    bool loadProfile(std::string id);
    void updateUserKey();
    void setProfilePicture(QString);
    void setHeader(QString);
    std::string findIdbyUsername(std::string username);

private:
    void addKeywordToUserHistory(std::string word);

    User tempUser;
    User* user;
    AnonymousUser a_user;
    PersonalUser p_user;
    OrganisationUser o_user;

};

#endif // TWITTERAKBACKEND_H
