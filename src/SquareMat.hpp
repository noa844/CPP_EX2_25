// noa.honigstein@gmail.com
#pragma once
#include <iostream>
#include <stdexcept>
using std::runtime_error;

namespace matrix {

    class SquareMat {
    private:
        double* data;
        int size; 

        // This class represents a reference to a row of the matrix.
        // It allows accessing matrix elements via double indexing, like mat[i][j],
        // while still performing bounds checking on both i (row) and j (column).
        // This is necessary because C++ only allows the first [] to be overloaded,
        // so the second [] must be handled manually through this helper class.
        class RowAccessor {
            double* row; // Pointer to the beginning of line i.
            int size;    // Row size / Column count.

        public:
            RowAccessor(double* row, int size) : row(row), size(size) {}

            // Overload for writable access 
            double& operator[](int j) {
                if (j < 0 || j >= size)
                    throw runtime_error("Column index is out of bounds");
                return row[j];
            }

            // Overload for read-only access 
            const double& operator[](int j) const {
                if (j < 0 || j >= size)
                    throw runtime_error("Column index is out of bounds");
                return row[j];
            }
        };

    public:
        // Constructors and destructor
        SquareMat(int size);
        SquareMat(const SquareMat& other);
        SquareMat& operator=(const SquareMat& other);
        ~SquareMat();

        // Row access
        RowAccessor operator[](int i);
        const RowAccessor operator[](int i) const;

        // Arithmetic operators
        SquareMat operator+(const SquareMat& other) const;
        SquareMat operator-(const SquareMat& other) const;
        SquareMat operator-() const;
        SquareMat operator*(const SquareMat& other) const;
        SquareMat operator*(double scalar) const;
        SquareMat operator%(const SquareMat& other) const; // Element-wise multiplication
        SquareMat operator%(int scalar) const;             // Modulo with scalar
        SquareMat operator/(double scalar) const;
        SquareMat operator^(int power) const;              // Matrix exponentiation

        // Increment / Decrement operators
        SquareMat& operator++();   // Prefix increment (++mat)
        SquareMat operator++(int); // Postfix increment (mat++)
        SquareMat& operator--();   // Prefix decrement (--mat)
        SquareMat operator--(int); // Postfix decrement (mat--)

        // Transpose
        SquareMat operator~() const;

        // Sum of all elements in matrix
        double sumMat() const;

        // Comparison operators (based on sum of elements)
        bool operator==(const SquareMat& other) const;
        bool operator!=(const SquareMat& other) const;
        bool operator<(const SquareMat& other) const;
        bool operator<=(const SquareMat& other) const;
        bool operator>(const SquareMat& other) const;
        bool operator>=(const SquareMat& other) const;

        // Determinant operator (!mat)
        double operator!() const;

        // Compound assignment operators
        SquareMat& operator+=(const SquareMat& other);
        SquareMat& operator-=(const SquareMat& other);
        SquareMat& operator*=(const SquareMat& other);
        SquareMat& operator*=(double scalar);
        SquareMat& operator%=(const SquareMat& other);
        SquareMat& operator%=(int scalar);
        SquareMat& operator/=(double scalar);

        // Output stream operator for printing the matrix
        friend std::ostream& operator<<(std::ostream& os, const SquareMat& mat);
    };

    // Non-member operator for scalar * matrix (required since the scalar is on the left)
    SquareMat operator*(double scalar, const SquareMat& mat);

}
