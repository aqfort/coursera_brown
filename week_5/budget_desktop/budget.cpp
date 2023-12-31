#include <iostream>
#include <sstream>
#include <ctime>
#include <algorithm>
#include <string>
#include <vector>

#include "test_runner.h"
#include "profile.h"

class Date
{
public:
    explicit Date() = default;
    explicit Date(int year, int month, int day) : year_(year), month_(month), day_(day) {}

    time_t AsTimestamp() const;
    static int ComputeDaysDiff(const Date &date_from, const Date &date_to);
    static size_t GetIndexFromDay(const Date &date);

    int GetYear() const { return year_; }
    int GetMonth() const { return month_; }
    int GetDay() const { return day_; }

private:
    friend std::istream &operator>>(std::istream &input, Date &date);

private:
    int year_;
    int month_;
    int day_;
};

std::ostream &operator<<(std::ostream &output, const Date &date)
{
    output << date.GetYear() << '-' << date.GetMonth() << '-' << date.GetDay();

    return output;
}

std::istream &operator>>(std::istream &input, Date &date)
{
    std::string date_string;
    input >> date_string;
    std::replace(date_string.begin(), date_string.end(), '-', ' ');
    std::stringstream date_string_stream(date_string);
    date_string_stream >> date.year_ >> date.month_ >> date.day_;

    return input;
}

time_t Date::AsTimestamp() const
{
    std::tm t;
    t.tm_sec = 0;
    t.tm_min = 0;
    t.tm_hour = 0;
    t.tm_mday = day_;
    t.tm_mon = month_ - 1;
    t.tm_year = year_ - 1900;
    t.tm_isdst = 0;

    return mktime(&t);
}

int Date::ComputeDaysDiff(const Date &date_from, const Date &date_to)
{
    const time_t timestamp_to = date_to.AsTimestamp();
    const time_t timestamp_from = date_from.AsTimestamp();
    static const int SECONDS_IN_DAY = 60 * 60 * 24;
    return (timestamp_to - timestamp_from) / SECONDS_IN_DAY;
}

size_t Date::GetIndexFromDay(const Date &date)
{
    return static_cast<size_t>(ComputeDaysDiff(Date(2000, 1, 1), date));
}

class BudgetManager
{
public:
    BudgetManager() { daily_cash_flow_.reserve(36600); } // 36525 days in [2000; 2099]
    double ComputeIncome(const Date &from, const Date &to) const;
    void Earn(const Date &from, const Date &to, double value);
    void PayTax(const Date &from, const Date &to, double tax);
    void Spend(const Date &from, const Date &to, double value);

private:
    struct DailyCashFlow
    {
        double earned = 0;
        double spent = 0;
    };

private:
    double tax_ = 13.0;
    std::vector<DailyCashFlow> daily_cash_flow_;
};

double BudgetManager::ComputeIncome(const Date &from, const Date &to) const
{
    double result = 0;
    const auto to_index = Date::GetIndexFromDay(to);
    for (auto i = Date::GetIndexFromDay(from); i <= to_index; ++i)
    {
        result += (daily_cash_flow_[i].earned - daily_cash_flow_[i].spent);
    }
    return result;
}

void BudgetManager::Earn(const Date &from, const Date &to, double value)
{
    const double income_per_day = value / (static_cast<double>(Date::ComputeDaysDiff(from, to)) + 1);
    const auto to_index = Date::GetIndexFromDay(to);
    for (auto i = Date::GetIndexFromDay(from); i <= to_index; ++i)
    {
        daily_cash_flow_[i].earned += income_per_day;
    }
}

void BudgetManager::PayTax(const Date &from, const Date &to, double tax)
{
    tax_ = tax;
    const auto to_index = Date::GetIndexFromDay(to);
    for (auto i = Date::GetIndexFromDay(from); i <= to_index; ++i)
    {
        daily_cash_flow_[i].earned *= ((100.0 - tax_) / 100.0);
    }
}

void BudgetManager::Spend(const Date &from, const Date &to, double value)
{
    const double outgo_per_day = value / (static_cast<double>(Date::ComputeDaysDiff(from, to)) + 1);
    const auto to_index = Date::GetIndexFromDay(to);
    for (auto i = Date::GetIndexFromDay(from); i <= to_index; ++i)
    {
        daily_cash_flow_[i].spent += outgo_per_day;
    }
}

void PerformBudgetQueries(std::istream &input = std::cin, std::ostream &output = std::cout)
{
    input.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int number_of_queries;
    double value;
    std::string query;
    Date from, to;
    BudgetManager budget_manager;

    input >> number_of_queries;

    for (int i = 0; i < number_of_queries; ++i)
    {
        input >> query >> from >> to;
        if (query == "ComputeIncome")
        {
            // output.precision(25);
            output << budget_manager.ComputeIncome(from, to) << '\n';
        }
        else if (query == "Earn")
        {
            input >> value;
            budget_manager.Earn(from, to, value);
        }
        else if (query == "PayTax")
        {
            input >> value;
            budget_manager.PayTax(from, to, value);
        }
        else if (query == "Spend")
        {
            input >> value;
            budget_manager.Spend(from, to, value);
        }
    }
}

void Test()
{
    std::istringstream input(R"(8
Earn 2000-01-02 2000-01-06 20
ComputeIncome 2000-01-01 2001-01-01
PayTax 2000-01-02 2000-01-03 13
ComputeIncome 2000-01-01 2001-01-01
Spend 2000-12-30 2001-01-02 14
ComputeIncome 2000-01-01 2001-01-01
PayTax 2000-12-30 2000-12-30 13
ComputeIncome 2000-01-01 2001-01-01
)");
    std::ostringstream output;
    PerformBudgetQueries(input, output);
    std::string output_expected = R"(20
18.96
8.46
8.46
)";
    ASSERT_EQUAL(output.str(), output_expected);
}

int main()
{
    TestRunner runner;
    RUN_TEST(runner, Test);
    // PerformBudgetQueries();
    return 0;
}
