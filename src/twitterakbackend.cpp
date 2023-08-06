#include "../include/twitterakbackend.h"
#include <stdexcept>
#include <QString>
#include <QVariant>
#include <QDebug>
TwitterakBackend::TwitterakBackend(QObject *parent)
    : QObject{parent}
{

}

bool TwitterakBackend::signUpFirstRound(QObject* username, QObject* password, QObject* usernameWarn, QObject* passwordWarn)
{
    bool successfullySignup = 1;

    try
    {
        user.set_username(username->property("text").toString().toStdString());
        usernameWarn->setProperty("visible", false);
    }
    catch(invalid_argument &e)
    {
        QVariant qv(QString(e.what()));
        usernameWarn->setProperty("text", qv);
        usernameWarn->setProperty("visible", true);
        successfullySignup = 0;
    }

    try
    {
        user.set_password(password->property("text").toString().toStdString());
        passwordWarn->setProperty("visible", false);
    }
    catch(invalid_argument &e)
    {
        QVariant qv(QString(e.what()));
        passwordWarn->setProperty("text", qv);
        passwordWarn->setProperty("visible", true);
        successfullySignup = 0;
    }

    return successfullySignup;
}
