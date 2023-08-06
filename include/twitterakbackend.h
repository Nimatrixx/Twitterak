#ifndef TWITTERAKBACKEND_H
#define TWITTERAKBACKEND_H

#include <QObject>
#include "User.h"
#include <iostream>
using namespace std;

class TwitterakBackend : public QObject
{
    Q_OBJECT
public:
    explicit TwitterakBackend(QObject *parent = nullptr);

public slots:
    bool signUpFirstRound(QObject* username, QObject* password, QObject* usernameWarn, QObject* passwordWarn);
    bool loginBtn(QObject* usernameField, QObject* passwordField, QObject* usernameWarn, QObject* passwordWarn);
signals:

private:
    User user;
};

#endif // TWITTERAKBACKEND_H
