// A behavioral desgin pattern that restricts direct communications between objects and forces them to collaborate only via a central mediator

#include <iostream>
#include <memory>
#include <string>
#include <vector>

using namespace std;

// mediator interface
class ChatRoom{
public:
    virtual ~ChatRoom() = default;
    virtual void sendMessage(const string &message, const string &colleagueName) = 0;
};

// components
class User{
private:
    string name;
    ChatRoom *chatRoom;
public:
    User(const string &name) : name(name), chatRoom(nullptr) {}
    void setChatRoom(ChatRoom *room){
        chatRoom = room;
    }
    void sendMessage(const string &message){
        if(chatRoom){
            chatRoom->sendMessage(message, name);
        }
    }
    void receiveMessage(const string &message, const string &senderName){
        cout << name << " received a message from " << senderName << ": " << message << endl;
    }
};

// concrete mediator
class SlackChannel : public ChatRoom{
private:
    vector<User *> users;
public:
    void addUser(User *user){
        users.push_back(user);
        user->setChatRoom(this);
    }
    void sendMessage(const string &message, const string &colleagueName) override {
        for(auto user : users){
            user->receiveMessage(message, colleagueName);
        }
    }
};

int main(){
    SlackChannel channel;
    
    User alice("Alice");
    User bob("Bob");
    User charlie("Charlie");

    channel.addUser(&alice);
    channel.addUser(&bob);
    channel.addUser(&charlie);

    alice.sendMessage("Hello everyone!");
    bob.sendMessage("Hi Alice!");
    charlie.sendMessage("Hey Alice and Bob!");

    return 0;
}