#ifndef TWITTERAKBACKEND_H
#define TWITTERAKBACKEND_H

#include <QObject>
#include <stdexcept>
#include <QString>
#include <QVariant>
#include <QDebug>
#include <fstream>
#include <string>

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

public slots:
    bool signUpFirstStep(int type ,QObject* username, QObject* password, QObject* usernameWarn, QObject* passwordWarn);
    bool signup(int type, QObject* name, QObject* phone,QObject* county,QObject* year,QObject* month,QObject* day,QObject* bio,QObject* link,QObject* custom,QObject* warn);
    bool loginBtn(QObject* usernameField, QObject* passwordField, QObject* usernameWarn, QObject* passwordWarn);
    bool saveProfile(int type);
    bool loadProfile(std::string id);
    std::string findIdbyUsername(std::string username);
signals:

private:
   // User user;
    User tempUser;
    User* user;
    AnonymousUser a_user;
    PersonalUser p_user;
    OrganisationUser o_user;
};

#endif // TWITTERAKBACKEND_H
