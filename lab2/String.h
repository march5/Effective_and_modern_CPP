#include <iostream>
#include <algorithm>
#include "MyString.h"
using namespace std;

class String{
   using string = emcpp::MyString;
   //using string = std::string;

   shared_ptr<string> ptr = nullptr;

/// Store a pointer to dynamically allocated string!

public:
    String() {
        ptr.reset(new string());
    }/// creates an empty string
    String(const char* str) {
        ptr.reset(new string(str));
    }           /// copy C-string
    String(const String& s) {
        ptr = s.ptr;
    }            /// no copy
    String operator=(const String& s) {
        ptr = s.ptr;
        return *this;
    } /// no copy
    /// makes a copy of a string if it has more than one reference.
    void set(int index, char ch) {
        if (ptr.unique()) {
            ptr->at(index) = ch;
        }
        else {
            if (ptr != nullptr) {
                ptr.reset(new string(*ptr));
                ptr->at(index) = ch;
            }
            else {
                ptr.reset(new string());
                *ptr += ch;
            }
        }
    }
    /// no copy
    char get(int index) const {
        if(ptr != nullptr)
        return ptr->at(index);
    }
    /// creates a new string only if both strings are non empty
    friend String operator+(String a, String b) {
        if (a.ptr == nullptr || a.ptr->empty()) {
            a.ptr = b.ptr;
            return a;
        }
        else if (b.ptr == nullptr || b.ptr->empty()) {
            b.ptr = a.ptr;
            return b;
        }
        else {
            char* c = const_cast<char*>(a.ptr->c_str());
            String s(c);
            s.ptr->append(*b.ptr);
            return s;
        }
    }
    friend std::ostream& operator<< (std::ostream& out, String s) {
        if (s.ptr != nullptr) {
            int size = s.ptr->size();
            for (int i = 0; i < size; i++) {
                out << s.ptr->at(i);
            }
        }

        return out;
    }
};
