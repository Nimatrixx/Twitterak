#include "../include/twitterakbackend.h"

using namespace std;

TwitterakBackend::TwitterakBackend(QObject *parent)
    : QObject{parent}
{

}

bool TwitterakBackend::signUpFirstStep(int type, QObject* username, QObject* password, QObject* usernameWarn, QObject* passwordWarn)
{
    if(type == 0)
        user = &a_user;
    else if(type == 1)
        user = &p_user;
    else if(type == 2)
        user = &o_user;
    else
        throw invalid_argument("type is not valid");


    bool successfullySignup = 1;

    try
    {
        user->set_username(username->property("text").toString().toStdString());
        usernameWarn->setProperty("visible", false);
        username->setProperty("error", false);
    }
    catch(invalid_argument &e)
    {
        QVariant qv(QString(e.what()));
        usernameWarn->setProperty("text", qv);
        usernameWarn->setProperty("visible", true);

        username->setProperty("error", true);
        successfullySignup = 0;
    }

    try
    {
        user->set_password(password->property("text").toString().toStdString());
        passwordWarn->setProperty("visible", false);
        password->setProperty("error", false);
    }
    catch(invalid_argument &e)
    {
        QVariant qv(QString(e.what()));
        passwordWarn->setProperty("text", qv);
        passwordWarn->setProperty("visible", true);

        password->setProperty("error", true);
        successfullySignup = 0;
    }

    return successfullySignup;
}


bool TwitterakBackend::signup(int type, QObject* name, QObject* phone,QObject* country,QObject* year,QObject* month,QObject* day,QObject* bio,QObject* link,QObject* custom,QObject* warn)
{
    bool successfullyPassed = 1;

    //name
    user->set_name(name->property( "text").toString().toStdString());
    
    //phonenumber
    string phoneNum = phone->property( "text").toString().toStdString();
    if(phoneNum != ""){
        try{
            user->set_phoneNumber(phone->property( "text").toString().toStdString());

            phone->setProperty("error", false);
        }
        catch(invalid_argument &e){
            successfullyPassed = 0;
            QVariant qv(QString(e.what()));
            warn->setProperty("text", qv);
            warn->setProperty("visible", true);

            phone->setProperty("error", true);
        }
    }


    //country
    user->set_country(country->property( "text").toString().toStdString());


    //birth date
    if(year->property("text").toString() != "")
    {
        try{
            int birthYear = year->property("text").toInt();
            int birthMonth = month->property("text").toInt();
            int birthDay = day->property("text").toInt();
            Date birthDate(birthYear,birthMonth,birthDay);
            user->set_dateOfBirth(birthDate);
        }
        catch(invalid_argument &e){
            successfullyPassed = 0;
            QVariant qv(QString(e.what()));
            warn->setProperty("text", qv);
            warn->setProperty("visible", true);
        }
    }


    //bio
    string bioTxt = bio->property("text").toString().toStdString();
    if(bioTxt != ""){
        try{
            user->set_bio(bioTxt);
        }
        catch(invalid_argument &e){
            successfullyPassed = 0;
            QVariant qv(QString(e.what()));
            warn->setProperty("text", qv);
            warn->setProperty("visible", true);
        }
    }


    //link
    string linkTxt = link->property("text").toString().toStdString();
    if(linkTxt != ""){
        try{
            user->set_link(linkTxt);

            link->setProperty("error",false);
        }
        catch(invalid_argument &e){
            successfullyPassed = 0;
            QVariant qv(QString(e.what()));
            warn->setProperty("text", qv);
            warn->setProperty("visible", true);

            link->setProperty("error",true);
        }
    }

    //custom
    if(type == 1)
    {
        p_user.set_office(custom->property("text").toString().toStdString());
    }
    else if(type == 2)
    {
        o_user.set_CEO(custom->property("text").toString().toStdString());
    }

    //register user and create an ID for him
    if(successfullyPassed){
        warn->setProperty("visible", false);

        //create ID
        string newId = "1";
        ifstream file ("userkeys.txt", ios::out);
        if(file)
        {
            file.seekg(0,ios::end);
            do{
                file.unget();
                file.unget();
                cout << file.tellg() << " ";
            }while(file.get() != '\n' && file.tellg() > 1);
            if(file.tellg() == 1)file.seekg(0,ios::beg);

            string r_id , r_username;
            file >> r_id >> r_username;

            r_id.erase(r_id.length()-1);

            newId = to_string(stoi(r_id) + 1);
        }
        file.close();

        if(type == 0)
            newId += 'a';
        else if(type == 1)
            newId += 'p';
        else if(type == 2)
            newId += 'o';

        //set ID
        user->set_id(newId);

        qDebug() << "register profile";
        //register user profile in "/user/ID.txt"
        saveProfile(type);

        qDebug() << "add ID and username";
        //add user ID and Username in userkeys.txt
        ofstream out("userkeys.txt", ios::app);
        out << newId << " " << user->get_username() << " " << user->get_password() << endl;
        out.close();
    }

    return successfullyPassed;
}


bool TwitterakBackend::loginBtn(QObject* usernameField, QObject* passwordField, QObject* usernameWarn, QObject* passwordWarn)
{
    string username = usernameField->property("text").toString().toStdString();
    string password = passwordField->property("text").toString().toStdString();

    ifstream file ("userkeys.txt", ios::out | ios::binary);
    if(file)
    {
        while(!file.eof())
        {
            string r_id , r_username, r_password;
            file >> r_id >> r_username >> r_password;
            if(r_username == username)
            {
                QVariant qv(QString(""));
                usernameWarn->setProperty("text", qv);

                if(r_password == password)
                {
                    file.close();
                    QVariant qv(QString(""));
                    passwordWarn->setProperty("text", qv);
                    return 1;
                }
                else
                {
                    QVariant qv(QString("* password is incorrect"));
                    passwordWarn->setProperty("text", qv);
                    file.close();
                    return 0;
                }

            }
        }
    }
    file.close();

    QVariant qv(QString("* username not found"));
    usernameWarn->setProperty("text", qv);

    return 0;
}

string TwitterakBackend::findIdbyUsername(string username)
{
    ifstream file ("userkeys.txt", ios::out | ios::binary);
    if(file)
    {
        while(!file.eof())
        {
            string r_id , r_username, r_password;
            file >> r_id >> r_username >> r_password;
            if(r_username == username)
            {
                file.close();
                return r_id;
            }
        }
    }
    file.close();
    return "unknown";
}

bool TwitterakBackend::saveProfile(int type)
{
    ofstream out("users/" + user->get_id() + ".txt");
    if(out){
        out << "1 " << user->get_id() << endl;
        out << "2 " << user->get_username() << endl;
        out << "3 " << user->get_password() << endl;
        out << "4 " <<user->get_name() << endl;
        if(type != 0)
            out << "5 " << user->get_phoneNumber() << endl;
        if(user->get_country() != "")
            out << "6 " << user->get_country() << endl;
        if(type != 2 && user->get_dateOfBirth().getYear())
            out << "7 " << user->get_dateOfBirth().getYear() << " " << user->get_dateOfBirth().getMonth() << " " << user->get_dateOfBirth().getDay() << endl;
        if(user->get_bio() != "")
            out << "8 " << user->get_bio() << '~' << endl;
        if(user->get_link() != "")
            out << "9 " << user->get_link() << endl;
        if(type == 1 && p_user.get_office() != "")
            out <<"10 " <<  p_user.get_office() << endl;
        else if(type == 2 && o_user.get_CEO() != "")
            out <<"10 " <<  o_user.get_CEO() << endl;
        vector<string> followers = user->get_followers();
        if(followers.size())
        {
            size_t len = followers.size();
            out << "11 " << len;
            for(size_t i{0}; i < len; i++)
                out << " " << followers[i];
            out << endl;
        }
        vector<string> followings = user->get_followings();
        if(followings.size())
        {
            size_t len = followings.size();
            out << "12 " << len;
            for(size_t i{0}; i < len; i++)
                out << " " << followings[i];
            out << endl;
        }

    }else{
        out.close();
        system("mkdir users");
        saveProfile(type);
    }

    out.close();

    return 1;
}

bool TwitterakBackend::loadProfile(string id)
{
    char type = id[id.length()-1];
    ifstream in("users/" + id + ".txt");
    if(in){
        int step;
        while(in.eof())
        {
            in >> step;

            string value;
            switch(step)
            {
            case 1:
                in >> value;
                user->set_id(value);
                break;
            case 2:
                in >> value;
                user->set_username(value);
                break;
            case 3:
                in >> value;
                user->set_password(value);
                break;
            case 4:
                getline(in,value);
                user->set_name(value);
                break;
            case 5:
                in >> value;
                user->set_phoneNumber(value);
                break;
            case 6:
                getline(in,value);
                user->set_country(value);
                break;
            case 7:{
                int day, month, year;
                in >> year >> month >> day;
                Date date(year,month,day);
                user->set_dateOfBirth(date);
                break;}
            case 8:
                getline(in,value,'~');
                user->set_bio(value);
                break;
            case 9:
                in >> value;
                user->set_link(value);
                break;
            case 10:
                in >> value;
                if(type == 'p')
                    p_user.set_office(value);
                else if(type == 'o')
                    o_user.set_CEO(value);
                break;
            case 11:{
                vector<string> followers;
                size_t len;
                in >> len;
                for(size_t i{0}; i < len; i++){
                    in >> value;
                    followers.push_back(value);
                }
                user->set_followers(followers);
                break;}
            case 12:{
                vector<string> followings;
                size_t len;
                in >> len;
                for(size_t i{0}; i < len; i++){
                    in >> value;
                    followings.push_back(value);
                }
                user->set_followings(followings);
                break;}

            }
        }
        return 1;
    }
    else
        return 0;
}
