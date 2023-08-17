
#ifndef Date_h
#define Date_h

class Date{

    public:
    Date();
    Date(unsigned year, unsigned month, unsigned day);

    void setYear(unsigned year);
    void setMonth(unsigned month);
    void setDay(unsigned day);

    unsigned getYear() const;
    unsigned getMonth() const;
    unsigned getDay() const;

    void clear();

    private:

    unsigned m_year{0};
    unsigned m_month{0};
    unsigned m_day{0};
};

#endif
