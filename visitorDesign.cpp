// a behavioral design pattern that allows you to add further operations to objects without having modify the classes of those objects. It achieves this by letting you define a new operation without changing the classes of the elements on which it operates.

#include <iostream>
#include <memory>
#include <string>
#include <vector>

using namespace std;

// visitor interface
class Visitor{
public:
    virtual ~Visitor() = default;
    virtual void visitBook(class Book *book) = 0;
    virtual void visitDVD(class DVD *dvd) = 0;
};

// element interface
class Product{
public:
    virtual ~Product() = default;
    virtual void accept(Visitor *visitor) = 0;
};

// concrete elements
class Book : public Product{
private:
    string title;
    double price;
public:
    Book(const string &t, double p) : title(t), price(p) {}
    string getTitle() const { return title; }
    double getPrice() const { return price; }
    void accept(Visitor *visitor) override {
        visitor->visitBook(this);
    }
};

class DVD : public Product{
private:
    string title;
    double price;
public:
    DVD(const string &t, double p) : title(t), price(p) {}
    string getTitle() const { return title; }
    double getPrice() const { return price; }
    void accept(Visitor *visitor) override {
        visitor->visitDVD(this);
    }
};

class TaxCalculator : public Visitor{
private:
    double totalTax = 0.0;
public:
    void visitBook(Book *book) override {
        double tax = book->getPrice() * 0.1; // 10%
        totalTax += tax;
        cout << "Tax for book \"" << book->getTitle() << "\": $" << tax << endl;
    }
    void visitDVD(DVD *dvd) override {
        double tax = dvd->getPrice() * 0.15; // 15%
        totalTax += tax;
        cout << "Tax for DVD \"" << dvd->getTitle() << "\": $" << tax << endl;
    }

    double getTotalTax() const { return totalTax; }
};

class JSONExporter : public Visitor{
public:
    void visitBook(Book *book) override {
        cout << "{ \"type\": \"Book\", \"title\": \"" << book->getTitle() << "\", \"price\": " << book->getPrice() << " }" << endl;
    }
    void visitDVD(DVD *dvd) override {
        cout << "{ \"type\": \"DVD\", \"title\": \"" << dvd->getTitle() << "\", \"price\": " << dvd->getPrice() << " }" << endl;
    }
};

int main(){
    vector<unique_ptr<Product>> products;
    products.push_back(make_unique<Book>("The Great Gatsby", 10.99));
    products.push_back(make_unique<DVD>("Inception", 14.99));

    TaxCalculator taxCalc;
    JSONExporter jsonExporter;

    for(const auto &product : products){
        product->accept(&taxCalc);
        product->accept(&jsonExporter);
    }

    cout << "Total Tax: $" << taxCalc.getTotalTax() << endl;

    return 0;
}