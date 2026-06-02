// the singleton design patern is a creational pattern that ensures a class has only one instance while providing a global of sccess to that instance

// The Rules of a C++ Singleton
// To enforce that only one instance is ever created, a C++ Singleton must do three things:
// Hide the constructor so outside code cannot call new or instantiate it.
// Delete the copy constructor and assignment operator so outside code cannot duplicate it.
// Provide a static method that creates (if necessary) and returns the single instance.

#include <iostream>
#include <string>

using namespace std;

class ConfigurationManager{
    private:
    string configData;
    
    // The constructor is private to prevent direct instantiation
    ConfigurationManager(){
        cout<<"Confuguration Initialized"<<endl;
        configData = "Default Config";
    }

    ~ConfigurationManager() {
        cout << "Configuration Manager destroyed" << endl;
    }
    public:
    // Delete copy constructor and assignment operator to prevent copying
    ConfigurationManager(const ConfigurationManager&) = delete;
    ConfigurationManager& operator=(const ConfigurationManager&) = delete;

    // Static method to get the single instance of the class
    static ConfigurationManager& getInstance(){
        static ConfigurationManager instance; // This will be created only once and is thread-safe in C++11 and later
        return instance;
    }

    void setConfig(const string &config){
        configData = config;
    }
    
    string getConfig() const {
        return configData;
    }
};

int main(){
    // Access the singleton instance and set configuration
    ConfigurationManager::getInstance().setConfig("Custom Config");
    
    // Access the singleton instance again and get configuration
    cout << "Current Config: " << ConfigurationManager::getInstance().getConfig() << endl;

    return 0;
}