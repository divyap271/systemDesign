// it is a behavorial design pattern that allows you to traverse the elements of a collection without exposing its underlying interna; representation.

#include <iostream>
#include <vector>
#include <memory>
#include <string>

using namespace std;

// interfaces
struct Book{
    string title;
    string author;
};

class Iterator{
public:
    virtual ~Iterator() = default;
    virtual bool hasNext() const = 0;
    virtual Book next() = 0;
};

class ICollection{
public:
    virtual ~ICollection() = default;
    virtual unique_ptr<Iterator> createIterator() const = 0;
};

// concrete collection & iterator
class Bookshelf;

class BookshelfIterator: public Iterator{
private:
    const Bookshelf& bookshelf;
    size_t index = 0;
public:
    explicit BookshelfIterator(const Bookshelf& shelf): bookshelf(shelf) {}
    bool hasNext() const override;
    Book next() override;
};

class Bookshelf: public ICollection{
private:
    vector<Book> books;
public:
    void addBook(const string &title, const string &author){
        books.push_back({title, author});
    }

    const vector<Book> &getBooks() const{
        return books;
    }

    unique_ptr<Iterator> createIterator() const override{
        return make_unique<BookshelfIterator>(*this);
    }
};

bool BookshelfIterator::hasNext() const{
    return index < bookshelf.getBooks().size();
}

Book BookshelfIterator::next(){
    if(!hasNext()){
        throw out_of_range("No more books in the shelf.");
    }
    return bookshelf.getBooks()[index++];
}

// the client
int main(){
    Bookshelf shelf;
    shelf.addBook("The Great Gatsby", "F. Scott Fitzgerald");
    shelf.addBook("To Kill a Mockingbird", "Harper Lee");
    shelf.addBook("1984", "George Orwell");
    unique_ptr<Iterator> it = shelf.createIterator();
    cout<<"Books in the shelf:"<<endl;
    while(it->hasNext()){
        Book book = it->next();
        cout<<"- "<<book.title<<" by "<<book.author<<endl;
    }
    return 0;
}