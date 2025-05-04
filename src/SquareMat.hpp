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
                        int size; // Row size/Column count.
                public:
                    RowAccessor(double* row, int size) : row(row), size(size) {}

                        double& operator[](int j) {
                            if (j < 0 || j >= size)
                                throw runtime_error("Column index is out of bounds");
                            return row[j];
                        }

                        const double& operator[](int j) const {
                            if (j < 0 || j >= size)
                                throw runtime_error("Column index is out of bounds");
                            return row[j];
                        }
                    };

    public:
        // Constructeurs
        SquareMat(int size);
        SquareMat(const SquareMat& other);
        SquareMat& operator=(const SquareMat& other);
        ~SquareMat();

        RowAccessor operator[](int i);
        const RowAccessor operator[](int i) const;

        // Opérateurs
        SquareMat operator+(const SquareMat& other) const;
        SquareMat operator-(const SquareMat& other) const;
        SquareMat operator-() const;
        SquareMat operator*(const SquareMat& other) const;
        SquareMat operator*(double scalar) const;
        
        SquareMat operator%(const SquareMat& other) const;
        SquareMat operator%(int scalar) const;
        SquareMat operator/(double scalar) const;
        SquareMat operator^(int power) const;

        SquareMat& operator++();   // prefix operator
        SquareMat operator++(int); // postfix operator
        SquareMat& operator--(); // prefix operator
        SquareMat operator--(int); // postfix operator

        SquareMat operator~() const; 

        SquareMat& operator+=(const SquareMat& other);
        SquareMat& operator-=(const SquareMat& other);
        SquareMat& operator*=(const SquareMat& other);
        SquareMat& operator*=(double scalar);
        SquareMat& operator%=(const SquareMat& other);
        SquareMat& operator%=(int scalar);
        SquareMat& operator/=(double scalar);

       
        bool operator==(const SquareMat& other) const;
        bool operator!=(const SquareMat& other) const;
        bool operator<(const SquareMat& other) const;
        bool operator<=(const SquareMat& other) const;
        bool operator>(const SquareMat& other) const;
        bool operator>=(const SquareMat& other) const;

        double operator!() const; // déterminant

        friend std::ostream& operator<<(std::ostream& os, const SquareMat& mat);

    };

     SquareMat operator*(double scalar, const SquareMat& mat);
    
}
