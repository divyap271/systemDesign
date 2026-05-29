#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <algorithm>
#include <chrono>
#include <iomanip>
#include <sstream>

// The core Notification interface
class Notification {
public:
    virtual ~Notification() = default;
    virtual std::string getContent() const = 0;
};

// Concrete Component: Simple raw text notification
class SimpleNotification : public Notification {
private:
    std::string message;
public:
    explicit SimpleNotification(std::string msg) : message(std::move(msg)) {}
    std::string getContent() const override { return message; }
};

// Base Decorator interface
class NotificationDecorator : public Notification {
protected:
    std::unique_ptr<Notification> wrappedNotification;
public:
    explicit NotificationDecorator(std::unique_ptr<Notification> notification)
        : wrappedNotification(std::move(notification)) {}
};

// Concrete Decorator A: Adds an automatic localized timestamp
class TimestampDecorator : public NotificationDecorator {
private:
    std::string getCurrentTimestamp() const {
        auto now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
        std::stringstream ss;
        ss << std::put_time(std::localtime(&now), "[%Y-%m-%d %H:%M:%S] ");
        return ss.str();
    }
public:
    using NotificationDecorator::NotificationDecorator;
    std::string getContent() const override {
        return getCurrentTimestamp() + wrappedNotification->getContent();
    }
};

// Concrete Decorator B: Appends a standard organization signature
class SignatureDecorator : public NotificationDecorator {
public:
    using NotificationDecorator::NotificationDecorator;
    std::string getContent() const override {
        return wrappedNotification->getContent() + "\n-- Sent via Secure Notification Engine --";
    }
};

// Strategy interface defining transmission behavior
class NotificationStrategy {
public:
    virtual ~NotificationStrategy() = default;
    virtual void sendNotification(const std::string& finalContent) const = 0;
};

// Concrete Strategy A: Email
class EmailStrategy : public NotificationStrategy {
public:
    void sendNotification(const std::string& finalContent) const override {
        std::cout << "[SMTP PROTOCOL Gateway] Mailing content:\n" << finalContent << "\n\n";
    }
};

// Concrete Strategy B: SMS
class SmsStrategy : public NotificationStrategy {
public:
    void sendNotification(const std::string& finalContent) const override {
        std::cout << "[SMS CELL Gateway] Texting payload:\n" << finalContent << "\n\n";
    }
};

// Concrete Strategy C: Popup Display
class PopupStrategy : public NotificationStrategy {
public:
    void sendNotification(const std::string& finalContent) const override {
        std::cout << "[DESKTOP ENVIRONMENT UI] Modal Alert Rendered:\n" << finalContent << "\n\n";
    }
};

// Observer Interface
class IObserver {
public:
    virtual ~IObserver() = default;
    virtual void onNotificationProcessed(const std::string& messagePayload) = 0;
};

// Concrete Observer: Transaction Log Auditing System
class Logger : public IObserver {
public:
    void onNotificationProcessed(const std::string& messagePayload) override {
        std::cout << "[SYSTEM AUDIT LOG] Registered a log entry of length: " 
                  << messagePayload.length() << " characters.\n";
    }
};

// Observable (Subject) Interface
class IObservable {
public:
    virtual ~IObservable() = default;
    virtual void registerObserver(IObserver* observer) = 0;
    virtual void removeObserver(IObserver* observer) = 0;
    virtual void notifyObservers(const std::string& messagePayload) = 0;
};

// Concrete Observable tracker
class NotificationObservable : public IObservable {
private:
    std::vector<IObserver*> observers;
public:
    void registerObserver(IObserver* observer) override {
        observers.push_back(observer);
    }
    
    void removeObserver(IObserver* observer) override {
        observers.erase(std::remove(observers.begin(), observers.end(), observer), observers.end());
    }
    
    void notifyObservers(const std::string& messagePayload) override {
        for (auto* obs : observers) {
            obs->onNotificationProcessed(messagePayload);
        }
    }
};

// Notification Engine: Pure structural worker that applies strategy execution
class NotificationEngine {
public:
    void process(const Notification& notification, const NotificationStrategy& strategy) const {
        strategy.sendNotification(notification.getContent());
    }
};

// Notification Service: High-level system Facade organizing all patterns
class NotificationService {
private:
    NotificationEngine engine;
    NotificationObservable metricsObservable;
    std::unique_ptr<Logger> systemLogger;

public:
    NotificationService() {
        // Initialize and bind the auditing Logger automatically 
        systemLogger = std::make_unique<Logger>();
        metricsObservable.registerObserver(systemLogger.get());
    }

    // Dispatches execution combining Decorators, Strategy, and Observer systems
    void send(std::unique_ptr<Notification> preparedNotification, const NotificationStrategy& chosenStrategy) {
        // 1. Pass the decorated content to the Engine to distribute over chosen Strategy Channel
        engine.process(*preparedNotification, chosenStrategy);

        // 2. Trigger asynchronous/side-effect observers (Logger metrics)
        metricsObservable.notifyObservers(preparedNotification->getContent());
    }
};

int main() {
    // Instantiate the primary central service manager
    NotificationService notificationService;

    // Allocate the underlying notification strategies
    EmailStrategy emailChannel;
    SmsStrategy   smsChannel;
    PopupStrategy popupChannel;

    std::cout << "--- TRANSACTION 1: Fully Decorated Urgent Email ---\n";
    // Build a fully customized layered message component dynamically using decorators
    std::unique_ptr<Notification> message1 = std::make_unique<SimpleNotification>("CRITICAL: Database connection lost.");
    message1 = std::make_unique<TimestampDecorator>(std::move(message1));
    message1 = std::make_unique<SignatureDecorator>(std::move(message1));

    // Send via email channel
    notificationService.send(std::move(message1), emailChannel);

    std::cout << "\n--- TRANSACTION 2: Low-overhead SMS without Signatures ---\n";
    // Build a lightweight message with simple timestamp decoration only
    std::unique_ptr<Notification> message2 = std::make_unique<SimpleNotification>("Auth Code: 44921");
    message2 = std::make_unique<TimestampDecorator>(std::move(message2));

    // Send via short message channel
    notificationService.send(std::move(message2), smsChannel);

    std::cout << "\n--- TRANSACTION 3: Plain Unadorned UI Alert ---\n";
    // Send a completely raw message without applying any decorator layers
    std::unique_ptr<Notification> message3 = std::make_unique<SimpleNotification>("Battery Low (10%)");

    // Send via graphical overlay popups
    notificationService.send(std::move(message3), popupChannel);

    return 0;
}