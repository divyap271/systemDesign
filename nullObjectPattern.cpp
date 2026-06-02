// a behavioral design pattern that provides a way to handle the absence of an object of a particular type.

#include <iostream>
#include <memory>
#include <string>

using namespace std;

// interface
class Logger{
public:
    virtual ~Logger() = default;
    virtual void log(const string &message) = 0;
};

// real object
class ConsoleLogger : public Logger{
public:
    void log(const string &message) override {
        cout << "Console Logger: " << message << endl;
    }
};

// null object
class NullLogger : public Logger{
public:
    void log(const string &message) override {
        // Do nothing
    }
};

int main(){
    unique_ptr<Logger> logger;

    // Suppose we have a configuration that determines whether to use a real logger or a null logger
    bool enableLogging = false; // Change this to true to see the real logger in action

    if(enableLogging){
        logger = make_unique<ConsoleLogger>();
    } else {
        logger = make_unique<NullLogger>();
    }

    // Now we can use the logger without worrying about null checks
    logger->log("This is a log message.");

    return 0;
}