#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>

using namespace std;
class Printer{
	
	int str;
	ostream* str_o;
	ofstream* str_of;
	string left;
	string right;

public:
	Printer(ofstream& instr, string l, string r) {
		str = 1;
		str_of = &instr;
		left = l;
		right = r;
	}

	Printer(ostream& instr, string l, string r) {
		str = 0;
		str_o = &instr;
		left = l;
		right = r;
	}

	template<typename T>
	void operator() (T item) const {
		if (str == 0)
			*str_o << left << item << right;
		else
			*str_of << left << item << right;
	}
};

int main(){
  /// Creates unary functor that takes one argument x (of any type)
  /// and outputs to given stream x surrounded by given prefix na postfix
  /// e.g. in the following  [ x ]
  /// Hint: define function template.
  Printer printer(std::cout,  "[ ", " ] " );
  printer("hello");    // [ hello ]
  std::cout << "\nv = ";
  std::vector<int> v = {1, 2, 3, 4};
  std::for_each(v.begin(), v.end(), printer);  // v = [ 1 ] [ 2 ] [ 3 ] [ 4 ]

  std::ofstream file("myFile.txt");
  Printer filePrinter(file, "- ", "\n");
  filePrinter(5);
  filePrinter("My text");	
	return 0;
}
/** myFile.txt
- 5
- My text
*/
