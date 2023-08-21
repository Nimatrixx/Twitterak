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
QString TwitterakBackend::get_custom() const{

    int type = get_type();
    if(type == 1)
        return QString::fromStdString(p_user.get_office());
    if(type == 2)
        return QString::fromStdString(o_user.get_CEO());
    else
        return QString::fromStdString("NULL");
}


QString TwitterakBackend::get_temp_username() const{
    return QString::fromStdString(tempUser->get_username());
}
QString TwitterakBackend::get_temp_password() const{
    return QString::fromStdString(tempUser->get_password());
}
QString TwitterakBackend::get_temp_name() const{
    return QString::fromStdString(tempUser->get_name());
}
QString TwitterakBackend::get_temp_phoneNumber() const{
    return QString::fromStdString(tempUser->get_phoneNumber());
}
QString TwitterakBackend::get_temp_bio() const{
    return QString::fromStdString(tempUser->get_bio());
}
QString TwitterakBackend::get_temp_country() const{
    return QString::fromStdString(tempUser->get_country());
}
QString TwitterakBackend::get_temp_link() const{
    return QString::fromStdString(tempUser->get_link());
}
int TwitterakBackend::get_temp_dayOfBirth() const{
    return tempUser->get_dateOfBirth().getDay();
}
int TwitterakBackend::get_temp_monthOfBirth() const{
    return tempUser->get_dateOfBirth().getMonth();
}
int TwitterakBackend::get_temp_yearOfBirth() const{
    return tempUser->get_dateOfBirth().getYear();
}
QString TwitterakBackend::get_temp_id() const{
    return QString::fromStdString(tempUser->get_id());
}
int TwitterakBackend::get_temp_followers() const{
    return tempUser->get_followers().size();
}
int TwitterakBackend::get_temp_followings() const{
    return tempUser->get_followings().size();
}
QString TwitterakBackend::get_temp_profilePicture() const{
    return QString::fromStdString(tempUser->get_profilePicture());
}
QString TwitterakBackend::get_temp_header() const{
    return QString::fromStdString(tempUser->get_header());
}
QString TwitterakBackend::get_temp_custom() const{

    int type = get_temp_type();
    if(type == 1)
        return QString::fromStdString(temp_p_user.get_office());
    if(type == 2)
        return QString::fromStdString(temp_o_user.get_CEO());
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


bool TwitterakBackend::setMainInfo(int type, QObject* username, QObject* password, QObject* usernameWarn, QObject* passwordWarn)
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

bool TwitterakBackend::setSecondaryInfo(int type, QObject* name, QObject* phone,QObject* country,QObject* year,QObject* month,QObject* day,QObject* bio,QObject* link,QObject* custom,QObject* warn, QString profile, QString header)
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

    //profile
    user->set_profilePicture(profile.toStdString());

    //header
    user->set_header(header.toStdString());

    //custom
    if(type != 0)
    {
        string customUsername;
        customUsername = custom->property("text").toString().toStdString();
        if(customUsername.empty() == 0)
        {
             //check validation of entered username
            bool found{0};
            ifstream file ("userkeys.txt", ios::out);
            if(file)
            {
                while(!file.eof())
                {
                    string r_id , r_username, r_password;
                    file >> r_id >> r_username >> r_password;
                    if(r_username == customUsername)
                    {
                        char lastCh = r_id[r_id.length() - 1];
                        if(type == 1)
                        {
                            if(lastCh == 'o')
                            {
                                p_user.set_office(customUsername);
                                found = 1;
                            }
                        }
                        else if(type == 2)
                        {
                            if(lastCh == 'p')
                            {
                                o_user.set_CEO(customUsername);
                                found = 1;
                            }
                        }
                        break;
                    }
                }
            }
            file.close();

            if(found == 0)
            {
                successfullyPassed = 0;
                QVariant qv;
                if(type == 1)
                    qv = QString("* office username is not valid");
                else
                    qv = QString("* ceo username is not valid");
                warn->setProperty("text", qv);
                warn->setProperty("visible", true);
            }
        }
    }


    if(successfullyPassed){
        warn->setProperty("visible", false);
    }

    return successfullyPassed;
}

void TwitterakBackend::registerUser(int type)
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
}

bool TwitterakBackend::saveUserInfo(bool saveTempUser)
{
    User* userPtr = saveTempUser ? tempUser : user;

    string id = userPtr->get_id();
    char type = id[id.length()-1];

    ofstream out("users/" + userPtr->get_id() + ".txt", ofstream::trunc);

    if(out){
        //id
        out << "1 " << userPtr->get_id() << endl;
        //username
        out << "2 " << userPtr->get_username() << endl;
        //password
        out << "3 " << userPtr->get_password() << endl;
        //name
        out << "4 " <<userPtr->get_name() << endl;
        //profile picture
        out << "5 " <<userPtr->get_profilePicture() << endl;
        //header
        out << "6 " <<userPtr->get_header() << endl;
        //phone number
        if(type != 'a')
            out << "7 " << userPtr->get_phoneNumber() << endl;
        //country
        if(userPtr->get_country() != "")
            out << "8 " << userPtr->get_country() << endl;
        //date of birth
        if(type != 'o' && userPtr->get_dateOfBirth().getYear())
            out << "9 " << userPtr->get_dateOfBirth().getYear() << " " << user->get_dateOfBirth().getMonth() << " " << user->get_dateOfBirth().getDay() << endl;
        //bio
        if(userPtr->get_bio() != "")
            out << "10 " << userPtr->get_bio() << '~' << endl;
        //link
        if(userPtr->get_link() != "")
            out << "11 " << userPtr->get_link() << endl;
        //custom
        if(type == 'p')
        {
            if(tempUser)
            {
                if(!temp_p_user.get_office().empty())
                    out <<"12 " <<  temp_p_user.get_office() << endl;
            }
            else
            {
                if(!p_user.get_office().empty())
                    out <<"12 " <<  p_user.get_office() << endl;
            }

        }
        if(type == 'o')
        {
            if(tempUser)
            {
                if(!temp_o_user.get_CEO().empty())
                    out <<"12 " <<  temp_o_user.get_CEO() << endl;
            }
            else
            {
                if(!o_user.get_CEO().empty())
                    out <<"12 " <<  o_user.get_CEO() << endl;
            }
        }
        vector<string> followers = userPtr->get_followers();
        qDebug() << "save " << followers.size() << " followers for " << userPtr->get_username();
        if(followers.size())
        {
            size_t len = followers.size();
            out << "13 " << len;
            for(size_t i{0}; i < len; i++)
                out << " " << followers[i];
            out << endl;
        }
        vector<string> followings = userPtr->get_followings();
        qDebug() << "save " << followings.size() << " followings for " << userPtr->get_username();
        if(followings.size())
        {
            size_t len = followings.size();
            out << "14 " << len;
            for(size_t i{0}; i < len; i++)
                out << " " << followings[i];
            out << endl;
        }
    }
    else
    {
        out.close();
        system("mkdir users");
        system("mkdir tweets");
        saveUserInfo(saveTempUser);
    }

    out.close();

    return 1;
}


bool TwitterakBackend::login(QObject* usernameField, QObject* passwordField, QObject* usernameWarn, QObject* passwordWarn)
{

    string username = usernameField->property("text").toString().toStdString();
    string password = passwordField->property("text").toString().toStdString();

    if(username.empty())
        return 0;

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
                    loadProfile(QString::fromStdString(r_id), 0);
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

bool TwitterakBackend::loadProfile(QString id, bool loadToTemp)
{
    User* userPtr;
    string id_s = id.toStdString();
    char type = id_s[id_s.length()-1];
    if(loadToTemp)
    {
        if(type == 'p')
            tempUser = &temp_p_user;
        else if(type == 'o')
            tempUser = &temp_o_user;
        else
            tempUser = &temp_a_user;
        userPtr = tempUser;
    }
    else
    {
        if(type == 'p')
            user = &p_user;
        else if(type == 'o')
            user = &o_user;
        else
            user = &a_user;
        userPtr = user;
    }


    ifstream in("users/" + id_s + ".txt");
    if(in){
        int step;
        try{
            while(!in.eof())
            {
                step = 0;
                in >> step;

                string value;
                switch(step)
                {
                case 1:
                    in >> value;
                    userPtr->set_id(value);
                    break;
                case 2:
                    in >> value;
                    userPtr->set_username(value);
                    qDebug() << "new usename :" << userPtr->get_username();
                    break;
                case 3:
                    in >> value;
                    userPtr->set_password(value);
                    break;
                case 4:
                    in.ignore(1);
                    getline(in,value);
                    userPtr->set_name(value);
                    break;
                case 5:
                    in >> value;
                    userPtr->set_profilePicture(value);
                    break;
                case 6:
                    in >> value;
                    userPtr->set_header(value);
                    break;
                case 7:
                    in >> value;
                    userPtr->set_phoneNumber(value);
                    break;
                case 8:
                    in.ignore(1);
                    getline(in,value);
                    userPtr->set_country(value);
                    break;
                case 9:{
                    int day, month, year;
                    in >> year >> month >> day;
                    Date date(year,month,day);
                    userPtr->set_dateOfBirth(date);
                    break;}
                case 10:
                    in.ignore(1);
                    getline(in,value,'~');
                    userPtr->set_bio(value);
                    break;
                case 11:
                    in >> value;
                    userPtr->set_link(value);
                    break;
                case 12:
                    in >> value;
                    if(loadToTemp)
                    {
                        if(type == 'p')
                            temp_p_user.set_office(value);
                        else if(type == 'o')
                            temp_o_user.set_CEO(value);
                    }
                    else
                    {
                        if(type == 'p')
                            p_user.set_office(value);
                        else if(type == 'o')
                            o_user.set_CEO(value);
                    }

                    break;
                case 13:{
                    vector<string> followers;
                    size_t len;
                    in >> len;
                    for(size_t i{0}; i < len; i++){
                        in >> value;
                        followers.push_back(value);
                    }
                    userPtr->set_followers(followers);
                    break;}
                case 14:{
                    vector<string> followings;
                    size_t len;
                    in >> len;
                    for(size_t i{0}; i < len; i++){
                        in >> value;
                        followings.push_back(value);
                    }
                    userPtr->set_followings(followings);
                    break;}
                default:
                    break;
                }
            }
            qDebug() << "loaded successfully";
        }
        catch(exception &e)
        {
            qDebug() << "error while loading profile : " << e.what();
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
            if(r_id.empty())
                continue;
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

int TwitterakBackend::get_type() const{
    string id = user->get_id();
    char lastCh = id[id.length() - 1];

    if(lastCh == 'a')
        return 0;
    else if(lastCh == 'p')
        return 1;
    else
        return 2;
}

int TwitterakBackend::get_temp_type() const{
    string id = tempUser->get_id();
    char lastCh = id[id.length() - 1];

    if(lastCh == 'a')
        return 0;
    else if(lastCh == 'p')
        return 1;
    else
        return 2;
}

void TwitterakBackend::tweet(QObject* tweetBox)
{
    //get tweet text
    string text = tweetBox->property("text").toString().toStdString();

    if(text.empty())
        return;

    //get current date
    const auto now = std::chrono::system_clock::now();
    const std::time_t t_c = std::chrono::system_clock::to_time_t(now);
    string date = std::ctime(&t_c);

    //create id for tweet
    long int id_int = time(NULL);
    string id = to_string(id_int);

    ofstream out("tweets/" + user->get_id() + "/" + id + ".txt");
    if(out){
        out << date;
        out << text;
        out << '~' << endl;
        out << 0;
        out.close();
    }
    else
    {
        out.close();
        const char* x = ("mkdir tweets/" + user->get_id()).c_str();
        system(x);
        tweet(tweetBox);
    }
}

void TwitterakBackend::loadTweets(QObject* listModel, QString id)
{
    string path = "tweets/" + id.toStdString();
    vector<long int> fileNames;
    if(filesystem::exists(path))
    {
        for (const auto & entry : filesystem::directory_iterator(path))
        {
            string fileName = entry.path();
            //erase ".txt"
            fileName.erase(fileName.length() - 4, 4);

            //erase "path before file name"
            for(size_t i{0}; i < fileName.length(); i++)
            {
                if(fileName[i] == '/')
                {
                    fileName.erase(0,i+1);
                    i = 0;
                }
            }

            //convert file name to long int
            long int fileName_int = stol(fileName, nullptr, 10);

            //add fileName_int to vector of file names in increasing order
            bool added = false;
            if(fileNames.size() == 0)
            {
                fileNames.push_back(fileName_int);
                added = 1;
            }
            for(size_t i{0}; i < fileNames.size() ; i++)
            {
                if(fileName_int < fileNames[i]){
                    fileNames.insert(fileNames.begin() + i,fileName_int);
                    added = 1;
                    break;
                }
            }
            if(added == 0)
                fileNames.push_back(fileName_int);
        }

        for(int i{fileNames.size()-1}; i >= 0; i--)
        {
            ifstream in("tweets/"+ id.toStdString() + "/" + to_string(fileNames[i]) + ".txt");
            string txt, date;
            getline(in, date);
            getline(in,txt,'~');

            int likes;
            in >> likes;


            bool isLiked = 0;
            string id_t;
            string userId = user->get_id();
            while(!in.eof())
            {
                in >> id_t;
                if(id_t == userId)
                {
                    isLiked = 1;
                    break;
                }
            }

            QMetaObject::invokeMethod(
                listModel,
                "addElement",
                Q_ARG(QString, QString::fromStdString(to_string(fileNames[i]))),
                Q_ARG(QString, QString::fromStdString(txt)),
                Q_ARG(QString, QString::fromStdString(date)),
                Q_ARG(int , likes),
                Q_ARG(bool, isLiked)
            );
        }

    }
}

void TwitterakBackend::likeTweet(QString tweetOwnerId, QString tweetId, bool isLiked)
{
    string path = "tweets/" + tweetOwnerId.toStdString() + "/" + tweetId.toStdString() + ".txt";
    string path_t = "tweets/" + tweetOwnerId.toStdString() + "/." + tweetId.toStdString() + ".txt";

    ifstream in(path);

    if(in)
    {
        ofstream out(path_t);
        string buffer;
        getline(in,buffer,'~');
        out << buffer << '~' << endl;

        int likes;
        in >> likes;

        string id = user->get_id();
        if(isLiked)
        {
            likes++;
            out << likes;
            out << " " << id ;
            buffer.clear();
            getline(in, buffer);
            out << buffer;
        }
        else
        {
            qDebug() << "unlike";
            likes--;
            out << likes;
            while(!in.eof())
            {
                in >> buffer;
                qDebug() << buffer;
                if(buffer != id)
                {
                    out << " " << buffer;
                }
                else
                {
                    buffer.clear();
                    getline(in, buffer);
                    out << buffer;
                }
            }
        }
        out.close();
        in.close();

        const char* path_c = path.c_str();
        const char* path_t_c = path_t.c_str();
        rename(path_t_c, path_c);
    }
    else
    {
        qDebug() << "couldnt find tweet file";
    }
}

bool TwitterakBackend::searchUser(QString username)
{
    ifstream in("userkeys.txt");
    string username_s = username.toStdString();
    if(in)
    {
        while(!in.eof())
        {
            string id_t , username_t, password_t;
            in >> id_t >> username_t >> password_t;

            if(username_t == username_s)
            {
                loadProfile(QString::fromStdString(id_t), 1);
                return 1;
            }
        }

        return 0;
    }
    else
    {
        return 0;
    }
}

void TwitterakBackend::logout()
{
    //clear user
    user->clear();
}

void TwitterakBackend::follow(QString id)
{
    user->follow(id.toStdString());
    tempUser->followed(user->get_id());
    saveUserInfo(0);
    saveUserInfo(1);
    qDebug() << "temp followers : " << tempUser->get_followers().size() << " followings" << tempUser->get_followings().size();
}

void TwitterakBackend::unfollow(QString id)
{
    user->unfollow(id.toStdString());
    tempUser->unfollowed(user->get_id());
    saveUserInfo(0);
    saveUserInfo(1);
}

bool TwitterakBackend::isFollowed(QString id)
{
    string id_s = id.toStdString();

    vector<string> followings = user->get_followings();

    for(size_t i{0}; i < followings.size(); i++)
    {
        if(followings[i] == id_s)
        {
            return 1;
        }
    }
    return 0;
}

bool TwitterakBackend::loadFollowings(QObject* followingsModel)
{
    vector<string> followings = user->get_followings();
    unsigned len = followings.size();

    if(len == 0)
        return 0;

    for(size_t i{0}; i < len; i++)
    {
        loadProfile(QString::fromStdString(followings[i]), 1);

        QMetaObject::invokeMethod(
            followingsModel,
            "addElement",
            Q_ARG(QString, get_temp_id()),
            Q_ARG(QString, get_temp_name()),
            Q_ARG(QString, get_temp_profilePicture())
            );
    }

    return 1;
}
