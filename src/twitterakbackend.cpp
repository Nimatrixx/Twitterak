#include "../include/twitterakbackend.h"

using namespace std;

TwitterakBackend::TwitterakBackend(QObject *parent)
    : QObject{parent}
{

}

QString TwitterakBackend::get_username() const{
    return QString::fromStdString(user->get_username());
}
QString TwitterakBackend::get_password() const{
    return QString::fromStdString(user->get_password());
}
QString TwitterakBackend::get_name() const{
    return QString::fromStdString(user->get_name());
}
QString TwitterakBackend::get_phoneNumber() const{
    return QString::fromStdString(user->get_phoneNumber());
}
QString TwitterakBackend::get_bio() const{
    return QString::fromStdString(user->get_bio());
}
QString TwitterakBackend::get_country() const{
    return QString::fromStdString(user->get_country());
}
QString TwitterakBackend::get_link() const{
    return QString::fromStdString(user->get_link());
}
QString TwitterakBackend::get_office () const{
    return  QString::fromStdString(p_user.get_office());
}
QString TwitterakBackend::get_ceo () const{
    return  QString::fromStdString(o_user.get_CEO());
}
int TwitterakBackend::get_dayOfBirth() const{
    return user->get_dateOfBirth().getDay();
}
int TwitterakBackend::get_monthOfBirth() const{
    return user->get_dateOfBirth().getMonth();
}
int TwitterakBackend::get_yearOfBirth() const{
    return user->get_dateOfBirth().getYear();
}
QString TwitterakBackend::get_id() const{
    return QString::fromStdString(user->get_id());
}
int TwitterakBackend::get_followers() const{
    return user->get_followers().size();
}
int TwitterakBackend::get_followings() const{
    return user->get_followings().size();
}
QString TwitterakBackend::get_profilePicture() const{
    return QString::fromStdString(user->get_profilePicture());
}
QString TwitterakBackend::get_header() const{
    return QString::fromStdString(user->get_header());
}


QString TwitterakBackend::get_temp_username() const{
    return QString::fromStdString(tempUser.get_username());
}
QString TwitterakBackend::get_temp_password() const{
    return QString::fromStdString(tempUser.get_password());
}
QString TwitterakBackend::get_temp_name() const{
    return QString::fromStdString(tempUser.get_name());
}
QString TwitterakBackend::get_temp_phoneNumber() const{
    return QString::fromStdString(tempUser.get_phoneNumber());
}
QString TwitterakBackend::get_temp_bio() const{
    return QString::fromStdString(tempUser.get_bio());
}
QString TwitterakBackend::get_temp_country() const{
    return QString::fromStdString(tempUser.get_country());
}
QString TwitterakBackend::get_temp_link() const{
    return QString::fromStdString(tempUser.get_link());
}
int TwitterakBackend::get_temp_dayOfBirth() const{
    return tempUser.get_dateOfBirth().getDay();
}
int TwitterakBackend::get_temp_monthOfBirth() const{
    return tempUser.get_dateOfBirth().getMonth();
}
int TwitterakBackend::get_temp_yearOfBirth() const{
    return tempUser.get_dateOfBirth().getYear();
}
QString TwitterakBackend::get_temp_id() const{
    return QString::fromStdString(tempUser.get_id());
}
int TwitterakBackend::get_temp_followers() const{
    return tempUser.get_followers().size();
}
int TwitterakBackend::get_temp_followings() const{
    return tempUser.get_followings().size();
}
QString TwitterakBackend::get_temp_profilePicture() const{
    return QString::fromStdString(tempUser.get_profilePicture());
}
QString TwitterakBackend::get_temp_header() const{
    return QString::fromStdString(tempUser.get_header());
}


void TwitterakBackend::addKeywordToUserHistory(string word)
{
    //add word in users/"id"_history.txt
    ofstream out("users/" + user->get_id() + "_history.txt", ios::app);
    if(out)
    {
        out << word << endl;
        out.close();
    }
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

    string username_s = username->property("text").toString().toStdString();
    string password_s = password->property("text").toString().toStdString();

    //check repetation of username or password in life time of account
    ifstream file("users/"+user->get_id()+"_history.txt");
    if(file)
    {
        string word;
        while(!file.eof())
        {
            file >> word;
            if(word == username_s)
            {
                file.close();
                QVariant qv(QString("you have used this before"));
                usernameWarn->setProperty("text", qv);
                usernameWarn->setProperty("visible", true);
                return 0;
            }
            if(word == password_s)
            {
                file.close();
                QVariant qv(QString("you have used this before"));
                passwordWarn->setProperty("text", qv);
                passwordWarn->setProperty("visible", true);
                return 0;
            }
        }
    }
    file.close();

    try
    {
        //check repeatation of username
        if(username_s != user->get_username())
        {
            ifstream file ("userkeys.txt", ios::out | ios::binary);
            if(file)
            {
                while(!file.eof())
                {
                    string r_id , r_username, r_password;
                    file >> r_id >> r_username >> r_password;
                    if(r_username == username_s)
                    {
                        throw invalid_argument ("* Username is already taken.");
                    }
                }
            }

            file.close();
        }


        user->set_username(username_s);
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
        user->set_password(password_s);
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

bool TwitterakBackend::saveUser(int type, QObject* name, QObject* phone,QObject* country,QObject* year,QObject* month,QObject* day,QObject* bio,QObject* link,QObject* custom,QObject* warn)
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

        if(user->get_id() == "")
        {
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

                if(r_id != "")
                {
                    r_id.erase(r_id.length()-1);

                    newId = to_string(stoi(r_id) + 1);
                }

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

            //add user ID , Username and password in userkeys.txt
            ofstream out("userkeys.txt", ios::app);
            out << user->get_id() << " " << user->get_username() << " " << user->get_password() << endl;
            out.close();

            //set profile picture
            user->set_profilePicture("../../img/avatar1.png");

            //set header
            user->set_header("lightblue");
        }


        //register user profile in "/user/ID.txt"
        saveProfile(type);
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
                    loadProfile(r_id);
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
    ofstream out("users/" + user->get_id() + ".txt", ofstream::trunc);

    if(out){
        qDebug() << "save header: " << user->get_header();
        out << "1 " << user->get_id() << endl;
        out << "2 " << user->get_username() << endl;
        out << "3 " << user->get_password() << endl;
        out << "4 " <<user->get_name() << endl;
        out << "5 " <<user->get_profilePicture() << endl;
        out << "6 " <<user->get_header() << endl;
        if(type != 0)
            out << "7 " << user->get_phoneNumber() << endl;
        if(user->get_country() != "")
            out << "8 " << user->get_country() << endl;
        if(type != 2 && user->get_dateOfBirth().getYear())
            out << "9 " << user->get_dateOfBirth().getYear() << " " << user->get_dateOfBirth().getMonth() << " " << user->get_dateOfBirth().getDay() << endl;
        if(user->get_bio() != "")
            out << "10 " << user->get_bio() << '~' << endl;
        if(user->get_link() != "")
            out << "11 " << user->get_link() << endl;
        if(type == 1 && p_user.get_office() != "")
            out <<"12 " <<  p_user.get_office() << endl;
        else if(type == 2 && o_user.get_CEO() != "")
            out <<"13 " <<  o_user.get_CEO() << endl;
        vector<string> followers = user->get_followers();
        if(followers.size())
        {
            size_t len = followers.size();
            out << "14 " << len;
            for(size_t i{0}; i < len; i++)
                out << " " << followers[i];
            out << endl;
        }
        vector<string> followings = user->get_followings();
        if(followings.size())
        {
            size_t len = followings.size();
            out << "15 " << len;
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
    qDebug() << type << " " << id;
    if(type == 'p')
        user = &p_user;
    else if(type == 'o')
        user = &o_user;
    else
        user = &a_user;

    ifstream in("users/" + id + ".txt");
    if(in){
        qDebug() << "found";
        int step;
        while(!in.eof())
        {
            step = 0;
            in >> step;

            string value;
            switch(step)
            {
            case 1:
                in >> value;
                user->set_id(value);
                qDebug() << "id: " << value << '\n';
                break;
            case 2:
                in >> value;
                qDebug() << "username: " << value << '\n';
                user->set_username(value);

                break;
            case 3:
                in >> value;
                user->set_password(value);
                qDebug() << "password: " << value << '\n';
                break;
            case 4:
                in.ignore(1);
                getline(in,value);
                user->set_name(value);
                qDebug() << "name: " << value << '\n';
                break;
            case 5:
                in >> value;
                user->set_profilePicture(value);
                break;
            case 6:
                in >> value;
                user->set_header(value);
                break;
            case 7:
                in >> value;
                user->set_phoneNumber(value);
                qDebug() << "phone: " << value << '\n';
                break;
            case 8:
                in.ignore(1);
                getline(in,value);
                user->set_country(value);
                qDebug() << "country: " << value << '\n';
                break;
            case 9:{
                int day, month, year;
                in >> year >> month >> day;
                Date date(year,month,day);
                user->set_dateOfBirth(date);
                qDebug() << "year: " << year << " month: " << month << " day: " << day <<  '\n';
                break;}
            case 10:
                in.ignore(1);
                getline(in,value,'~');
                user->set_bio(value);
                qDebug() << "bio: " << value << '\n';
                break;
            case 11:
                in >> value;
                user->set_link(value);
                qDebug() << "link: " << value << '\n';
                break;
            case 12:
                in >> value;
                if(type == 'p')
                    p_user.set_office(value);
                else if(type == 'o')
                    o_user.set_CEO(value);
                qDebug() << "custom: " << value << '\n';
                break;
            case 13:{
                vector<string> followers;
                size_t len;
                in >> len;
                for(size_t i{0}; i < len; i++){
                    in >> value;
                    followers.push_back(value);
                }
                user->set_followers(followers);
                break;}
            case 14:{
                vector<string> followings;
                size_t len;
                in >> len;
                for(size_t i{0}; i < len; i++){
                    in >> value;
                    followings.push_back(value);
                }
                user->set_followings(followings);
                break;}
            default:
                break;
            }
        }
        return 1;
    }
    else
        return 0;
}

void TwitterakBackend::updateUserKey()
{
    ifstream file ("userkeys.txt");
    if(file)
    {
        ofstream out("userkeys_temp.txt");
        while(!file.eof())
        {
            string r_id , r_username, r_password;
            file >> r_id >> r_username >> r_password;
            if(r_id != user->get_id())
            {
                out << r_id << " " << r_username << " " << r_password << '\n';
            }
            else
            {
                if(r_username != user->get_username())
                    addKeywordToUserHistory(r_username);
                if(r_password != user->get_password())
                    addKeywordToUserHistory(r_password);

                out << user->get_id() << " " << user->get_username() << " " << user->get_password() << '\n';
            }
        }
        out.close();
    }
    file.close();

    rename("userkeys_temp.txt","userkeys.txt");
}

int TwitterakBackend::getType() const{
    string id = user->get_id();
    char lastCh = id[id.length() - 1];

    if(lastCh == 'a')
        return 0;
    else if(lastCh == 'p')
        return 1;
    else
        return 2;
}

void TwitterakBackend::setProfilePicture(QString address)
{
    user->set_profilePicture(address.toStdString());
}

void TwitterakBackend::setHeader(QString color)
{
    user->set_header(color.toStdString());
}
