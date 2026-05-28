// simple factory: you create a single class or a static method that ontains a giant if-else or switch statement.
// factor method: you create a base creator class with a virtual method you then let subclasses decide which exact object to instantiate.
// abstract factory: The Abstract Factory provides an interface to create an entire family of related objects safely.

#include <iostream>
#include <string>
#include <memory>

using namespace std;

class Button{
    public:
    virtual void render() = 0;
};

class Checkbox{
    public:
    virtual void render() = 0;
};

class WindowButton : public Button{
    public:
    void render() override{
        cout << "Rendering a button in a window style" << endl;
    }
};

class MacButton : public Button{
    public:
    void render() override{
        cout << "Rendering a button in a mac style" << endl;
    }
};

class WindowCheckbox : public Checkbox{
    public:
    void render() override{
        cout << "Rendering a checkbox in a window style" << endl;
    }
};

class MacCheckbox : public Checkbox{
    public:
    void render() override{
        cout << "Rendering a checkbox in a mac style" << endl;
    }
};

// simple factory
class ButtonFactory{
    public:
    static unique_ptr<Button> createButton(const string &type){
        if(type == "Window"){
            return make_unique<WindowButton>();
        } else if(type == "Mac"){   
            return make_unique<MacButton>();
        }
        return nullptr;
    }
};

// factor method
class ButtonCreator{
    public:
    virtual unique_ptr<Button> createButton() = 0;
};

class WindowButtonCreator : public ButtonCreator{
    public:
    unique_ptr<Button> createButton() override{
        return make_unique<WindowButton>();
    }
};

class MacButtonCreator : public ButtonCreator{
    public:
    unique_ptr<Button> createButton() override{
        return make_unique<MacButton>();
    }
};

// abstract factory
class GUIFactory {
public:
    virtual unique_ptr<Button> createButton() = 0;
    virtual unique_ptr<Checkbox> createCheckbox() = 0; // <-- This makes it an Abstract Factory!
};

class WindowFactory : public GUIFactory {
public:
    unique_ptr<Button> createButton() override {
        return make_unique<WindowButton>();
    }
    unique_ptr<Checkbox> createCheckbox() override {
        return make_unique<WindowCheckbox>();
    }
};

class MacFactory : public GUIFactory {
public:
    unique_ptr<Button> createButton() override {
        return make_unique<MacButton>();
    }
    unique_ptr<Checkbox> createCheckbox() override {
        return make_unique<MacCheckbox>();
    }
};
// Factory Method is a single method inside a class. Its only job is to let subclasses decide which one specific object to instantiate.
// Abstract Factory is a whole class. Its job is to group multiple Factory Methods together so you don't accidentally put a MacCheckbox on a screen next to a WindowButton.