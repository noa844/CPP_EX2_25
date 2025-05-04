// noa.honigstein@gmail.com

#include <iostream>
#include "SquareMat.hpp"

using namespace matrix;
using namespace std;

int main() {
    SquareMat A(2);
    A[0][0] = 1.0;  A[0][1] = 2.0;
    A[1][0] = 3.0;  A[1][1] = 4.0;
   
    SquareMat B(2);
    B[0][0] = 5.0;  B[0][1] = 6.0;
    B[1][0] = 7.0;  B[1][1] = 8.0;
  

    cout << "Matrix A:\n" << A;
    cout << "Matrix B:\n" << B;

    cout << "A + B:\n" << (A + B);
    cout << "A - B:\n" << (A - B);
    cout << "-A:\n" << (-A);
    cout << "A * B:\n" << (A * B);

    cout << "A * 2.5:\n" << (A * 2.5);
    cout << "2.5 * B:\n" << (2.5 * B);

    cout << "A % B (element-wise multiplication):\n" << (A % B);
    cout << "A % 3 (modulo with int):\n" << (A % 3);

    cout << "A / 2.0:\n" << (A / 2.0);
    cout << "A^2:\n" << (A ^ 2);
    cout << "Transpose of A (~A):\n" << (~A);

    cout << "++A (pre-increment):\n" << (++A);
    cout << "A++ (post-increment):\n" << (A++); 
    cout << "After A++:\n" << A;

    cout << "--B (pre-decrement):\n" << (--B);
    cout << "B-- (post-decrement):\n" << (B--);
    cout << "After B--:\n" << B;

    cout << "Determinant of A (!A): " << !A << endl;

    SquareMat C = A;
    cout << "C == A ? " << (C == A) << endl;
    cout << "C != B ? " << (C != B) << endl;
    cout << "C < B ?  " << (C < B) << endl;

    cout << "C += B:\n" << (C += B);
    cout << "C -= B:\n" << (C -= B);
    cout << "C *= B:\n" << (C *= B);
    cout << "C /= 2:\n" << (C /= 2.0);
    cout << "C %= 5:\n" << (C %= 5);

    return 0;
}
