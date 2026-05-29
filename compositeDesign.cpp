// the composite design pattern pattern is a structural design pattern that allows you to compose objects into three structures to represent part whole hierarchies.

#include <iostream>
#include <string>
#include <vector>
#include <memory>

// The Component interface
class FileSystemItem {
protected:
    std::string name;
public:
    explicit FileSystemItem(std::string name) : name(std::move(name)) {}
    virtual ~FileSystemItem() = default;

    virtual void display(const std::string& indentation = "") const = 0;
    virtual int getSize() const = 0;
};

// Leaf node
class File : public FileSystemItem {
private:
    int size;
public:
    File(std::string name, int size) : FileSystemItem(std::move(name)), size(size) {}

    void display(const std::string& indentation) const override {
        std::cout << indentation << "- File: " << name << " (" << size << " KB)\n";
    }

    int getSize() const override {
        return size;
    }
};

// Composite node
class Folder : public FileSystemItem {
private:
    std::vector<std::unique_ptr<FileSystemItem>> children; // Can hold any FileSystemItem

public:
    using FileSystemItem::FileSystemItem;

    void add(std::unique_ptr<FileSystemItem> item) {
        children.push_back(std::move(item));
    }

    void display(const std::string& indentation = "") const override {
        std::cout << indentation << "+ Folder: " << name << "\n";
        for (const auto& child : children) {
            child->display(indentation + "  "); // Recursive print
        }
    }

    int getSize() const override {
        int totalSize = 0;
        for (const auto& child : children) {
            totalSize += child->getSize(); // Recursive calculation
        }
        return totalSize;
    }
};

int main() {
    // 1. Create root folder
    auto root = std::make_unique<Folder>("Root_Directory");

    // 2. Add some standalone files to root
    root->add(std::make_unique<File>("boot.ini", 4));
    root->add(std::make_unique<File>("system.log", 102));

    // 3. Create a subfolder and add files to it
    auto subFolder1 = std::make_unique<Folder>("Documents");
    subFolder1->add(std::make_unique<File>("resume.pdf", 250));
    subFolder1->add(std::make_unique<File>("budget.xlsx", 1200));

    // 4. Create a deeply nested sub-subfolder
    auto nestedFolder = std::make_unique<Folder>("Holiday_Photos");
    nestedFolder->add(std::make_unique<File>("beach.png", 4500));
    nestedFolder->add(std::make_unique<File>("mountain.png", 5200));
    
    // Nest the nested folder inside Documents
    subFolder1->add(std::move(nestedFolder));

    // Add Documents folder to root
    root->add(std::move(subFolder1));

    // 5. Treat the entire structure uniformly!
    std::cout << "--- File System Architecture Tree ---\n";
    root->display();

    std::cout << "\nTotal Directory Size: " << root->getSize() << " KB\n";

    return 0;
};