
#ifndef Date_h
#define Date_h

class Date{

    public:

    Date(unsigned year, unsigned month, unsigned day);

    void setYear(unsigned year);
    void setMonth(unsigned month);
    void setDay(unsigned day);

    unsigned getYear() const;
    unsigned getMonth() const;
    unsigned getDay() const;

    private:

    unsigned m_year = 1900;
    unsigned m_month = 1;
    unsigned m_day = 1;
};

#endif