#include <iostream>
//-------------------------------------------
/// ADD FORWARD DECLARATIONS HERE

//-------------------------------------------
// DO NOT CHANGE CLASS Pair
template <typename T, typename S>
class Pair {
    const T first;
    const S second;
    static int numberOfPair;
public:
    Pair(T first, S second);                // Constructor, increases numberOfPairs
    //template <typename P, typename R>
    //explicit Pair(const Pair<P, R>& pair);  // Converting constructor, increases numberOfPairs
    //~Pair();                                // Destructor, decreases numberOfPair
    constexpr T getFirst() const;           // returns first, mark it inline
    constexpr S getSecond() const;          // returns second, mark it inline
    //constexpr Pair<S, T> reverse() const;    // returns a reversed Pair
    constexpr static int getNumberOfPairs();// return the number of existing objects of Pair<T,S>
    // friend declaration with single template function operator<<(std::ostream, const Pair<T,S> &)
    //friend std::ostream& operator<< <>(std::ostream& out, const Pair& pair);
    // friend declaration with class template (any Pair<P,R>)
    //template <typename, typename>
    //friend class Pair;
};
//-------------------------------------------
/// IMPLEMENTATION SECTION: Implement methods here

template<typename T, typename S>
int Pair<T,S>::numberOfPair = 0;

template<typename T, typename S>
Pair<T, S>::Pair(T first, S second) : first(first), second(second){
    numberOfPair++;
}

template<typename T, typename S>
constexpr T Pair<T, S>::getFirst() const {
    return this->first;
}

template<typename T, typename S>
constexpr S Pair<T, S>::getSecond() const {
    return this->second;
}

template<typename T, typename S>
constexpr int Pair<T,S>::getNumberOfPairs() {
    return numberOfPair;
}

//-------------------------------------------
using namespace std;
int main() {

    Pair<int, double> p{ 1, 3.1415 };
    cout << p.getFirst() << " " << p.getSecond() << endl;
    /*cout << p << endl;
    auto p2 = p.reverse();
    cout << p2 << endl;
    {
        Pair<int, int> p3(p)
            cout << p3 << endl;
        cout << Pair<int, int>::getNumberOfPairs() << endl; 
    }
    cout << Pair<int, int>::getNumberOfPairs() << endl;*/
}
/** Expected output
1 3.1415
(1, 3.1415)
(3.1415, 1)
(1, 3)
1
0
 */