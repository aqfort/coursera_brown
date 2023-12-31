#include "test_runner.h"
#include <functional>
#include <memory>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;

struct Email
{
    string from;
    string to;
    string body;
};

class Worker
{
public:
    virtual ~Worker() = default;
    virtual void Process(unique_ptr<Email> email) = 0;
    virtual void Run()
    {
        // только первому worker-у в пайплайне нужно это имплементировать
        throw logic_error("Unimplemented");
    }

protected:
    // реализации должны вызывать PassOn, чтобы передать объект дальше
    // по цепочке обработчиков
    void PassOn(unique_ptr<Email> email) const
    {
        if (next_)
        {
            next_->Process(move(email));
        }
    }

public:
    void SetNext(unique_ptr<Worker> next)
    {
        next_ = move(next);
    }

private:
    unique_ptr<Worker> next_;
};

class Reader : public Worker
{
public:
    // реализуйте класс
    explicit Reader(istream &in) : in_(in) {}

    virtual void Process(unique_ptr<Email> email) override {}

    virtual void Run() override
    {
        while (1)
        {
            auto email = make_unique<Email>();
            getline(in_, email->from);
            getline(in_, email->to);
            getline(in_, email->body);
            if (in_)
            {
                PassOn(move(email));
            }
            else
            {
                break;
            }
        }
    }

private:
    istream &in_;
};

class Filter : public Worker
{
public:
    using Function = function<bool(const Email &)>;

    // реализуйте класс
    explicit Filter(Function function) : function_(move(function)) {}

    virtual void Process(unique_ptr<Email> email) override
    {
        if (function_(*email))
        {
            PassOn(move(email));
        }
    }

private:
    Function function_;
};

class Copier : public Worker
{
public:
    // реализуйте класс
    explicit Copier(string to) : to_(move(to)) {}

    virtual void Process(unique_ptr<Email> email) override
    {
        if (email->to == to_)
        {
            PassOn(move(email));
        }
        else
        {
            auto copy = make_unique<Email>(*email);
            copy->to = to_;
            PassOn(move(email));
            PassOn(move(copy));
        }
    }

private:
    string to_;
};

class Sender : public Worker
{
public:
    // реализуйте класс
    explicit Sender(ostream &out) : out_(out) {}

    virtual void Process(unique_ptr<Email> email) override
    {
        out_ << email->from << endl
             << email->to << endl
             << email->body << endl;
        PassOn(move(email));
    }

private:
    ostream &out_;
};

// реализуйте класс
class PipelineBuilder
{
public:
    // добавляет в качестве первого обработчика Reader
    explicit PipelineBuilder(istream &in)
    {
        pipeline_.emplace_back(make_unique<Reader>(in));
    }

    // добавляет новый обработчик Filter
    PipelineBuilder &FilterBy(Filter::Function filter)
    {
        pipeline_.emplace_back(make_unique<Filter>(move(filter)));
        return *this;
    }

    // добавляет новый обработчик Copier
    PipelineBuilder &CopyTo(string recipient)
    {
        pipeline_.emplace_back(make_unique<Copier>(move(recipient)));
        return *this;
    }

    // добавляет новый обработчик Sender
    PipelineBuilder &Send(ostream &out)
    {
        pipeline_.emplace_back(make_unique<Sender>(out));
        return *this;
    }

    // возвращает готовую цепочку обработчиков
    unique_ptr<Worker> Build()
    {
        for (size_t i = pipeline_.size() - 1; i > 0; --i)
        {
            pipeline_[i - 1]->SetNext(move(pipeline_[i]));
        }
        return move(pipeline_[0]);
    }

private:
    vector<unique_ptr<Worker>> pipeline_;
};

void TestSanity()
{
    string input = ("erich@example.com\n"
                    "richard@example.com\n"
                    "Hello there\n"

                    "erich@example.com\n"
                    "ralph@example.com\n"
                    "Are you sure you pressed the right button?\n"

                    "ralph@example.com\n"
                    "erich@example.com\n"
                    "I do not make mistakes of that kind\n");
    istringstream inStream(input);
    ostringstream outStream;

    PipelineBuilder builder(inStream);
    builder.FilterBy([](const Email &email)
                     { return email.from == "erich@example.com"; });
    builder.CopyTo("richard@example.com");
    builder.Send(outStream);
    auto pipeline = builder.Build();

    pipeline->Run();

    string expectedOutput = ("erich@example.com\n"
                             "richard@example.com\n"
                             "Hello there\n"

                             "erich@example.com\n"
                             "ralph@example.com\n"
                             "Are you sure you pressed the right button?\n"

                             "erich@example.com\n"
                             "richard@example.com\n"
                             "Are you sure you pressed the right button?\n");

    ASSERT_EQUAL(expectedOutput, outStream.str());
}

int main()
{
    TestRunner tr;
    RUN_TEST(tr, TestSanity);
    return 0;
}
