// proxy design pattern is a strucural design pattern that lets you provide a substitute or placeholder for another object. A proxy controls access to the original object, allowing you to perform operations either before or after the request gets through to the original object.
// lazy intialization
// access control
// caching

#include <iostream>
#include <string>
#include <memory>

using namespace std;

// suject interface
class Graphic{
public:
    virtual ~Graphic() = default;
    virtual void draw() = 0;
};

// real subject
class HighResImage: public Graphic{
private:
    string filename;
    void loadFromDisk(){
        cout << "[Real object] Loading massive 50MB image file: "<<filename<<"..."<<endl;
    }

public:
    explicit HighResImage(string file): filename(move(file)){
        loadFromDisk();
    }

    void draw() override{
        cout << "[Real object] Drawing High-Res Image: "<<filename<<" to the screen."<<endl;
    }
};

//the proxy
class ImageProxy: public Graphic{
private:
    string filename;
    unique_ptr<HighResImage> realImage;
public:
    explicit ImageProxy(string file): filename(move(file)), realImage(nullptr) {}
    void draw() override{
        if(!realImage){
            cout<<"[Proxy] client requested draw. Instantiating real image now..."<<endl;
            realImage = make_unique<HighResImage>(filename);
        }
        else{
            cout<<"[Proxy] Image already loaded. Skipping disk read."<<endl;
        }
        realImage->draw();
    }
};

// client
int main(){
    cout<<"---App started---"<<endl;
    unique_ptr<Graphic> image1 = make_unique<ImageProxy>("photo1.jpg");
    unique_ptr<Graphic> image2 = make_unique<ImageProxy>("photo2.jpg");
    cout<<"---First draw call for image1---"<<endl;
    image1->draw();
    cout<<"---Second draw call for image1---"<<endl;
    image1->draw();
    cout<<"---First draw call for image2---"<<endl;
    image2->draw();
    cout<<"---App finished---"<<endl;
}