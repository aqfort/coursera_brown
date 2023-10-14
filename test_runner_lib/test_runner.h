#pragma once

#include <iostream>
#include <sstream>
#include <vector>
#include <map>
#include <set>
#include <string>
#include <unordered_map>

#define ASSERT_EQUAL(x, y)                        \
    {                                             \
        std::ostringstream ASS_OS;                \
        ASS_OS << #x << " != " << #y << std::endl \
               << __FILE__ << ":" << __LINE__;    \
        AssertEqual(x, y, ASS_OS.str());          \
    }

#define ASSERT(x)                                \
    {                                            \
        std::ostringstream ASS_OS;               \
        ASS_OS << #x << " is false" << std::endl \
               << __FILE__ << ":" << __LINE__;   \
        Assert(x, ASS_OS.str());                 \
    }

#define RUN_TEST(tr, func)       \
    {                            \
        tr.RunTest(func, #func); \
    }

template <typename Collection>
[[maybe_unused]] std::string Join(const Collection &c, char d);

template <typename First, typename Second>
std::ostream &operator<<(std::ostream &out, const std::pair<First, Second> &p);

template <typename T>
std::ostream &operator<<(std::ostream &out, const std::vector<T> &v);

template <typename Key, typename Value>
std::ostream &operator<<(std::ostream &out, const std::map<Key, Value> &m);

template <typename T>
std::ostream &operator<<(std::ostream &out, const std::set<T> &s);

template <typename Key, typename Value>
std::ostream &operator<<(std::ostream &out, const std::unordered_map<Key, Value> &m);

template <class T, class U>
void AssertEqual(const T &t, const U &u, const std::string &hint);

inline void Assert(bool b, const std::string &hint)
{
    AssertEqual(b, true, hint);
}

class [[maybe_unused]] TestRunner
{
public:
    TestRunner();

    ~TestRunner();

    template <class TestFunction>
    void RunTest(TestFunction test, const std::string &test_name);

private:
    int fail_count = 0;
};

template <typename Collection>
std::string Join(const Collection &c, const std::string &d)
{
    std::stringstream ss;
    bool first = true;
    for (const auto &i : c)
    {
        if (!first)
        {
            ss << d << ' ';
        }
        first = false;
        ss << i;
    }
    return ss.str();
}

template <typename First, typename Second>
std::ostream &operator<<(std::ostream &out, const std::pair<First, Second> &p)
{
    return out << '(' << p.first << ", " << p.second << ')';
}

template <typename T>
std::ostream &operator<<(std::ostream &out, const std::vector<T> &v)
{
    return out << '[' << Join(v, ", ") << ']';
}

template <typename Key, typename Value>
std::ostream &operator<<(std::ostream &out, const std::map<Key, Value> &m)
{
    return out << '{' << Join(m, ", ") << '}';
}

template <typename T>
std::ostream &operator<<(std::ostream &out, const std::set<T> &s)
{
    return out << '{' << Join(s, ", ") << '}';
}

template <typename Key, typename Value>
std::ostream &operator<<(std::ostream &out, const std::unordered_map<Key, Value> &m)
{
    return out << '{' << Join(m, ", ") << '}';
}

template <class T, class U>
void AssertEqual(const T &t, const U &u, const std::string &hint)
{
    if (t != u)
    {
        std::ostringstream os;
        os << ">> Assertion failed" << std::endl
           << ">>      Got: " << t << std::endl
           << ">> Expected: " << u;
        if (!hint.empty())
        {
            os << std::endl
               << ">> Hint: " << hint;
        }
        throw std::runtime_error(os.str());
    }
}

template <class TestFunction>
void TestRunner::RunTest(TestFunction test, const std::string &test_name)
{
    try
    {
        test();
        std::cerr << test_name << " - OK" << std::endl
                  << std::endl;
    }
    catch (std::exception &e)
    {
        ++fail_count;
        std::cerr << test_name << " - FAIL" << std::endl
                  << e.what() << std::endl
                  << std::endl;
    }
    catch (...)
    {
        ++fail_count;
        std::cerr << "Unknown exception caught" << std::endl
                  << std::endl;
    }
}
