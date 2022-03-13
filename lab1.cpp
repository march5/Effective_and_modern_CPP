#include <iostream>

using namespace std;

class Matrix {
public:
    int N;
    int M;

    double* data;

    Matrix() {
        N = M = 0;
        data = NULL;

        cout << "Empty constructor" << endl;
    }

    Matrix(int n, int m) {
        N = n;
        M = m;

        data = new double[M * N];

        fillZeros();

        cout << "Constructor of " << N << "x" << M << " matrix filled with 0.0" << endl;
    }

    Matrix(const Matrix& m) {

        N = m.N;
        M = m.M;
        data = new double[N * M];

        copy(m.data, m.data + (m.M * m.N), data);

        cout << "Copy constructor" << endl;
    }

    Matrix(Matrix&& m) noexcept {

        N = m.N;
        M = m.M;
        data = m.data;

        m.data = NULL;
        m.N = 0;
        m.M = 0;

        cout << "Move constructor" << endl;
    }

    Matrix(initializer_list<initializer_list<double>> list) {
        N = list.size();
        int minSize = N;
        auto temp = list.begin();
        for (int i = 0; i < N; i++) {
            if (minSize < temp->size()) minSize = temp->size();
            temp++;
        }
        M = minSize;
        data = new double[M * N];
        fillZeros();

        auto ptr = list.begin();
        auto ptr2 = ptr->begin();
        int i = 0;

        do {
            for (int x = 0; x < ptr->size(); x++) {
                data[i + x] = *ptr2;
                ptr2++;
            }
            ptr++;
            i += M;
            ptr2 = ptr->begin();
        } while (ptr != list.end());

        cout << "Constructor of " << N << "x" << M << " matrix from initializer list" << endl;

    }
    
    friend ostream& operator<<(ostream& os, const Matrix& m);

    double& operator()(int n, int m) {
        return data[(n - 1) * M + m - 1];
    }

    //Copy Assignment constructor
    Matrix& operator=(const Matrix& m) {
        if (this == &m) return *this;

        N = m.N;
        M = m.M;
        data = new double[N * M];

        copy(m.data, m.data + (m.M * m.N), data);

        cout << "Constructor of " << N <<"x" << M << " matrix" << endl;
        return *this;
    }

    //Move assignment operator
    Matrix& operator=(Matrix&& m) noexcept{

        if (this != &m) {
            N = m.N;
            M = m.M;
            data = m.data;

            m.data = NULL;
            m.N = 0;
            m.M = 0;
        }
        cout << "Move assignment operator" << endl;
        return *this;
    }

    // - unary operator 
    Matrix& operator-() {
        for(int i = 0; i < N*M; i++){
            data[i] = -data[i];
        }
        return *this;
    }

    ~Matrix() {
        delete[] data;

        cout << "Destructor" << endl;
    }

protected:
    void fillZeros() {
        for (int i = 0; i < M * N; i++)
            data[i] = 0.0;
    }

};

ostream& operator<<(ostream& os, const Matrix& m) {
    for (int i = 0; i < m.N; i++) {
        os << "{";
        for (int j = 0; j < m.M; j++) {
            if (j < m.M - 1) os << m.data[i * m.M + j] << ", ";
            else os << m.data[i * m.M + j] << "}" << endl;
        }
    }
    return os;
}

class MatrixWithLabel : public Matrix {

    using Matrix::Matrix;

    string label = "A";
public: 
    MatrixWithLabel(string l, int n, int m) : Matrix(n,m) {
        label = l;
    }

    MatrixWithLabel(string l, initializer_list<initializer_list<double>> list) : Matrix(list) {
        label = l;
    }

    string getLabel() {
        return label;
    }

    void setLabel(string l) {
        label = l;
    }

    /*explicit MatrixWithLabel(MatrixWithLabel&& m) : Matrix(m) {
        label = m.label;
        m.label = "A";
    }
    explicit MatrixWithLabel(MatrixWithLabel& m) : Matrix(m) {
        label = m.label;
    }*/
};

int main()
{
    Matrix m1;
    Matrix m2(3, 4);
    Matrix m3({ {1,2,3},{32, 23, 22},{3,234,23,44} });
    cout << m2(1, 1) << endl;  // 0
    cout << m3(2, 2) << endl;  // 23
    cout << m3;

    cout << "Copy semantics \n";
    Matrix m4 = m2;
    m4 = m3;

    cout << "Move semantics \n";
    Matrix m7 = std::move(m2);
    m4 = -m3;

    cout << "Copy elision \n";
    Matrix m6 = -m4;
    Matrix* pm = new Matrix(-m4);
    cout << m6(2, 1) << endl; // 32

    cout << "Inheritance \n";
    MatrixWithLabel l0("B", 3, 4);
    MatrixWithLabel l1({ {1,2},{4,5} });
    l1.setLabel("A");
    MatrixWithLabel l2 = l1;
    MatrixWithLabel l3 = std::move(l1);
    cout << l2.getLabel() << " " << l3.getLabel() << endl;
    cout << l1.getLabel() << endl;

    return 0;
}

