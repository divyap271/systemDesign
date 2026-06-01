// the chain of responsibility pattern is a behavoirial design pattern that allows you to pass requests along a chain of handlers. Upon receiving a request each handler decides either to process the request itself or to pass it along to the next handler in the chain.

#include <iostream>
#include <string>
#include <memory>

using namespace std;

// the request object
struct Ticket{
    string description;
    int severity;
};

// base handler interface
class SupportHandler{
protected:
    shared_ptr<SupportHandler> nextHandler;
public:
    virtual ~SupportHandler() = default;

    shared_ptr<SupportHandler> setNext(shared_ptr<SupportHandler> next){
        nextHandler = next;
        return next;
    }

    // sets the next link in the chain and returns it to allow method chaining
    virtual void handleRequest(const Ticket& ticket){
        if(nextHandler){
            nextHandler->handleRequest(ticket);
        }
        else{
            cout<<"[End of chain] No handler available for ticket: "<<ticket.description<<endl;
        }
    }
};

// concrete handlers
class AiChatbot: public SupportHandler{
public:
    void handleRequest(const Ticket &ticket) override{
        if(ticket.severity == 1){
            cout << "[AI Chatbot] Automatically resolved: "<<ticket.description<<endl;
        }
        else{
            cout<<"[AI Chatbot] Cannot handle ticket: "<<ticket.description<<". Escalating to human agent..."<<endl;
            SupportHandler::handleRequest(ticket);
        }
    }
};

class HumanAgent: public SupportHandler{
public:    
    void handleRequest(const Ticket &ticket) override{
        if(ticket.severity == 2){
            cout << "[Human Agent] Resolved: "<<ticket.description<<endl;
        }
        else{
            cout<<"[Human Agent] Cannot handle ticket: "<<ticket.description<<". Escalating to supervisor..."<<endl;
            SupportHandler::handleRequest(ticket);
        }
    }
};

class TechLead : public SupportHandler{
public:
    void handleRequest(const Ticket &ticket) override{
        if(ticket.severity == 3){
            cout << "[Tech Lead] Resolved: "<<ticket.description<<endl;
        }
        else{
            cout<<"[Tech Lead] Cannot handle ticket: "<<ticket.description<<". Escalating to manager..."<<endl;
            SupportHandler::handleRequest(ticket);
        }
    }
};

// the client
int main(){
    auto chatbot = make_shared<AiChatbot>();
    auto humanAgent = make_shared<HumanAgent>();
    auto techLead = make_shared<TechLead>();

    chatbot->setNext(humanAgent)->setNext(techLead);

    Ticket ticket1{"Password reset request", 1};
    Ticket ticket2{"Software bug causing crashes", 2};
    Ticket ticket3{"Critical security vulnerability", 3};
    Ticket ticket4{"Unknown issue with no handler", 4};

    chatbot->handleRequest(ticket1);
    chatbot->handleRequest(ticket2);
    chatbot->handleRequest(ticket3);
    chatbot->handleRequest(ticket4);

    return 0;
}