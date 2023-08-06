#include <time.h>
#include <stdexcept>
#include "Date.h"

Date::Date(unsigned year = 1900, unsigned month = 1, unsigned day = 1)
{
    setYear(year);
    setMonth(month);
    setDay(day);
}

void Date::setYear(unsigned year)
{   
    //get current year
    time_t theTime = time(NULL);
    struct tm *aTime = localtime(&theTime);
    unsigned currentYear = aTime->tm_year + 1900;

    if(year >= 1900 && year <= currentYear)
    {
        m_year = year;
    }
    else
    {
        throw std::invalid_argument("year is invalid");
    }
}

void Date::setMonth(unsigned month)
{
    //get current month
    time_t theTime = time(NULL);
    struct tm *aTime = localtime(&theTime);
    unsigned currentYear = aTime->tm_year + 1900;
    unsigned currentMonth = aTime->tm_mon + 1;

    if(m_year < currentYear && !(month >= 1 && month <= 12) )
    {
        throw std::invalid_argument("month is invalid");
    }
    else if(!(month >= 1 && month <= currentMonth))
    {
        throw std::invalid_argument("month is invalid");
    }
    m_month = month;
}

void Date::setDay(unsigned day)
{
    //get current day
    time_t theTime = time(NULL);
    struct tm *aTime = localtime(&theTime);
    unsigned currentYear = aTime->tm_year + 1900;
    unsigned currentMonth = aTime->tm_mon + 1;
    unsigned currentDay = aTime->tm_mday;

    if(m_year < currentYear || m_month < currentMonth)
    {
        switch(m_month)
        {
            case 1:
            case 5:
            case 7:
            case 8:
            case 10:
            case 12:
                if(!(day >= 1 && day <= 31))
                    throw std::invalid_argument("day is invalid");
                break;
            case 4:
            case 6:
            case 9:
            case 11:
                if(!(day >= 1 && day <= 30))
                    throw std::invalid_argument("day is invalid");
                break;
            case 2:
                if(!(day >= 1 && day <= 28))
                    throw std::invalid_argument("day is invalid");
                break;
        }
    }
    else if(day > currentDay)
    {
        throw std::invalid_argument("day is invalid");
    }

    m_day = day;
}

unsigned Date::getYear() const
{
    return m_year;
}

unsigned Date::getMonth() const
{
    return m_month;
}

unsigned Date::getDay() const
{
    return m_day;
}