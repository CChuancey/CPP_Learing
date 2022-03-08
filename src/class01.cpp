#include "class01.h"

Sales_data::Sales_data(std::istream& is) {
    // double price = 0;
    // is >> bookno >> units_sold >> price;
    // revenue = price * units_sold;
    read(is, *this);
}

Sales_data& Sales_data::combine(const Sales_data& item) {
    units_sold += item.units_sold;
    revenue += item.revenue;
    return *this;
}

Sales_data add(const Sales_data& lhs, const Sales_data& rhs) {
    Sales_data sum = lhs;
    sum.combine(rhs);
    return sum;
}

std::istream& read(std::istream& is, Sales_data& item) {
    double price = 0;
    is >> item.bookno >> item.units_sold >> price;
    return is;
}

std::ostream& print(std::ostream& os, const Sales_data& item) {
    os << item.isbn() << " " << item.units_sold << " " << item.revenue
       << item.avg_price();
    return os;
}

/*******************/
void Account::rate(double rate) { interstRate = rate; }

double Account::initRate() { return interstRate = 0; }

double Account::interstRate = initRate();

int main(int argc, char* argv[]) {
    std::vector<double> verc(10);
    std::vector<int>::value_type x = 10;
    return 0;
}
