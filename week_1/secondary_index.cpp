#include "test_runner.h"

#include <iostream>
#include <map>
#include <string>
#include <unordered_map>

using namespace std;

struct Record
{
    string id;
    string title;
    string user;
    int timestamp;
    int karma;
};

// Реализуйте этот класс
class Database
{
public:
    bool Put(const Record &record)
    {
        auto [it, insert_result] = data_storage.insert({record.id, {record, {}, {}, {}}});
        if (!insert_result)
        {
            return false;
        }
        auto &data = it->second;
        // const Record *ptr = &data.record;
        data.iterator_user = data_user.insert({data.record.user, &data.record});
        data.iterator_timestamp = data_timestamp.insert({data.record.timestamp, &data.record});
        data.iterator_karma = data_karma.insert({data.record.karma, &data.record});
        return true;
    }
    const Record *GetById(const string &id) const
    {
        auto it = data_storage.find(id);
        if (it == data_storage.end())
        {
            return nullptr;
        }
        return &it->second.record;
    }
    bool Erase(const string &id)
    {
        auto it = data_storage.find(id);
        if (it == data_storage.end())
        {
            return false;
        }
        const auto &data = it->second;
        data_user.erase(data.iterator_user);
        data_timestamp.erase(data.iterator_timestamp);
        data_karma.erase(data.iterator_karma);
        data_storage.erase(it);
        return true;
    }

    template <typename Callback>
    void RangeByTimestamp(int low, int high, Callback callback) const
    {
        auto it = data_timestamp.lower_bound(low);
        auto it_end = data_timestamp.upper_bound(high);
        while (it != it_end)
        {
            if (!callback(*(it++)->second))
            {
                break;
            }
        }
    }

    template <typename Callback>
    void RangeByKarma(int low, int high, Callback callback) const
    {
        auto it = data_karma.lower_bound(low);
        auto it_end = data_karma.upper_bound(high);
        while (it != it_end)
        {
            if (!callback(*(it++)->second))
            {
                break;
            }
        }
    }

    template <typename Callback>
    void AllByUser(const string &user, Callback callback) const
    {
        auto [it, it_end] = data_user.equal_range(user);
        while (it != it_end)
        {
            if (!callback(*(it++)->second))
            {
                break;
            }
        }
    }

private:
    struct Data
    {
        Record record;
        multimap<string, const Record *>::iterator iterator_user;
        multimap<int, const Record *>::iterator iterator_timestamp;
        multimap<int, const Record *>::iterator iterator_karma;
    };

private:
    unordered_map<string, Data> data_storage;
    multimap<string, const Record *> data_user;
    multimap<int, const Record *> data_timestamp;
    multimap<int, const Record *> data_karma;
};

void TestRangeBoundaries()
{
    const int good_karma = 1000;
    const int bad_karma = -10;

    Database db;
    db.Put({"id1", "Hello there", "master", 1536107260, good_karma});
    db.Put({"id2", "O>>-<", "general2", 1536107260, bad_karma});

    int count = 0;
    db.RangeByKarma(bad_karma, good_karma, [&count](const Record &)
                    {
    ++count;
    return true; });

    ASSERT_EQUAL(2, count);
}

void TestSameUser()
{
    Database db;
    db.Put({"id1", "Don't sell", "master", 1536107260, 1000});
    db.Put({"id2", "Rethink life", "master", 1536107260, 2000});

    int count = 0;
    db.AllByUser("master", [&count](const Record &)
                 {
    ++count;
    return true; });

    ASSERT_EQUAL(2, count);
}

void TestReplacement()
{
    const string final_body = "Feeling sad";

    Database db;
    db.Put({"id", "Have a hand", "not-master", 1536107260, 10});
    db.Erase("id");
    db.Put({"id", final_body, "not-master", 1536107260, -10});

    auto record = db.GetById("id");
    ASSERT(record != nullptr);
    ASSERT_EQUAL(final_body, record->title);
}

int main(int argc, char **argv)
{
    TestRunner tr;
    RUN_TEST(tr, TestRangeBoundaries);
    RUN_TEST(tr, TestSameUser);
    RUN_TEST(tr, TestReplacement);
    return 0;
}
