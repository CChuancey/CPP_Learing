#ifndef __CLASS01_H__
#define __CLASS01_H__

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

class Sales_data {
    friend Sales_data add(const Sales_data&, const Sales_data&);
    friend std::istream& read(std::istream&, Sales_data&);
    friend std::ostream& print(std::ostream&, const Sales_data&);

public:
    Sales_data() = default;
    Sales_data(const std::string& s, unsigned n, double p)
        : bookno(s), units_sold(n), revenue(p * n) {}
    Sales_data(const std::string& s) : bookno(s) {}
    Sales_data(std::istream&);
    std::string isbn() const { return bookno; }
    Sales_data& combine(const Sales_data&);

private:
    std::string bookno;
    unsigned units_sold = 0;
    double revenue = 0.0;
    double avg_price() const { return units_sold ? revenue / units_sold : 0; }
};

Sales_data add(const Sales_data&, const Sales_data&);
std::istream& read(std::istream&, Sales_data&);
std::ostream& print(std::ostream&, const Sales_data&);

// Account类
class Account {
public:
    Account() = default;
    void calculate() { amount += amount * interstRate; }
    static double rate() { return interstRate; }
    static void rate(double);

private:
    std::string owner;
    double amount = 0;
    // 静态成员不在类内进行初始化
    static double interstRate;
    static double initRate();
};

class EX {
public:
    static constexpr double rate = 1.0;
    static const int vecsize = 10;
    static std::vector<double> vec;
    static char test[vecsize];
};
// double EX::rate = 2.0;
std::vector<double> EX::vec(EX::vecsize);

#endif