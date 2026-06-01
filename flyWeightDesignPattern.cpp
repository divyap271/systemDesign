// it is a structural design pattern that lets you fit millions of objects into available RAM by sharing common parts of their state between multiple objects. rather than keeping identical data in each individual object. It seprates data into intrinsic state and extrinsic state.

#include <iostream>
#include <string>
#include <memory>
#include <unordered_map>
#include <vector>

using namespace std;

// this heavy data is read-only and shared across thousands of objects.
class TreeModel{
private:
    string name;
    string color;
    string textureData;

public:
    TreeModel(string name, string color, string texture): name(std::move(name)), color(std::move(color)), textureData(std::move(texture)) {
        cout<<"[TreeModel] Loading heavy texture data for "<<this->name<<" tree..."<<endl;
    }

    void draw(int x, int y) const{
        cout<<"Drawing "<<color<<" "<<name<<" tree at ("<<x<<","<<y<<") using shared texture data."<<endl;
    }
};

// the flyweight factory that manages the shared TreeModel instances
class TreeFactory{
private:
    unordered_map<string, shared_ptr<TreeModel>> treeModels;

public:
    shared_ptr<TreeModel> getTreeModel(const string &name, const string &color, const string &texture){
        string key = name + "_" + color;

        if(treeModels.find(key) == treeModels.end()){
            treeModels[key] = make_shared<TreeModel>(name, color, texture);
        }
        else{
            cout<<"[TreeFactory] Reusing existing TreeModel for "<<key<<"."<<endl;
        }
        return treeModels[key];
    }
};

class Tree{
private:
    int x;
    int y;
    shared_ptr<TreeModel> model;
public:
    Tree(int x, int y, shared_ptr<TreeModel> model): x(x), y(y), model(std::move(model)) {}
    void draw() const{
        model->draw(x, y);
    }
};

int main(){
    cout<<"---Forest Simulation Started---"<<endl;
    TreeFactory factory;

    vector<Tree> forest;
    forest.emplace_back(10, 20, factory.getTreeModel("Oak", "Green", "OakTextureData"));
    forest.emplace_back(15, 25, factory.getTreeModel("Pine", "Dark Green", "PineTextureData"));
    forest.emplace_back(20, 30, factory.getTreeModel("Oak", "Green", "OakTextureData")); // Reuses the same Oak model

    for(const auto& tree : forest){
        tree.draw();
    }

    cout<<"---Forest Simulation Ended---"<<endl;
    return 0;
}