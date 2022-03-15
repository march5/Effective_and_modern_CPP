#pragma once
#include <iostream>
#include "Box.h"

using namespace std;

class Container{
    // Exercise 2: Use smart pointer.
    unique_ptr<Box> pbox = nullptr;
public:
    static bool verbose;
    Container(int content): pbox(new Box(content)){
        if(verbose) cout << "Creating Container" << endl;
        //pbox->setContent(content);
    }
    Container(const Container & container): pbox(new Box{*(container.pbox)}){
        if(verbose) cout << "Creating copy of Container\n";
    }
    Container(Container&& container): pbox(move(container.pbox)) { }
    Container & operator=(const Container &container){
        if(this != &container) {
            if(verbose) cout << "Copying Container\n";
            *pbox = *container.pbox;
        }
        return *this;
    }
    Container& operator=(Container&& container) {
        if (this != &container) {
            pbox = move(container.pbox);
        }
        return *this;
    }
    ~Container(){
        if(verbose) cout << "Destroying Container \n";
    }
    friend int operator+(const Container & p1, const Container & p2);
    friend std::ostream & operator << (std::ostream & out, const Container & p){
        return (out << " [" << p.pbox->getContent() << "] ");
    }
};

bool Container::verbose = false;

inline int operator+(const Container & p1, const Container & p2){
    return p1.pbox->getContent() + p2.pbox->getContent();
}
