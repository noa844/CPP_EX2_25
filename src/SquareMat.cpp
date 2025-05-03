#include "SquareMat.hpp"
#include <cmath>  
using std::cout;
using std::endl;
using std::runtime_error;

namespace matrix {

    // constructor
    SquareMat::SquareMat(int size) : size(size) {
        if (size <= 0) {
            throw runtime_error("Invalid argument");
        }
        int n = size*size;
        data = new double[n];

        for (int i = 0; i < n; ++i) {
            data[i] = 0.0; 
        }
    }



    //copy constructor
    SquareMat::SquareMat(const SquareMat& other) : size(other.size) {
        int n = size*size;
        data = new double[n];
        for (int i = 0; i < n; ++i) {
            data[i] = other.data[i];
        }
    }

    
    SquareMat& SquareMat::operator=(const SquareMat& other) {
        if (this == &other) return *this; 

        delete[] data; 
        size = other.size;
        int n = size*size;
        data = new double[n];
        for (int i = 0; i < n; ++i) {
            data[i] = other.data[i];
        }
        return *this;
    }

    // Destructor
    SquareMat::~SquareMat() {
        delete[] data;
    }

    SquareMat::RowAccessor SquareMat::operator[](int i) {
        if (i < 0 || i >= size)
            throw runtime_error("Row index out of bounds");

        return RowAccessor(&data[i * size], size);
    }
    
    const SquareMat::RowAccessor SquareMat::operator[](int i) const {
        if (i < 0 || i >= size)
            throw runtime_error("Row index out of bounds");

        return RowAccessor(&data[i * size], size);
    }

    SquareMat SquareMat::operator+(const SquareMat &other) const {
        if (size != other.size) {
            throw runtime_error("Must be the same size for addition.");
        }
    
        SquareMat result(size);
        
        for (int i = 0; i < size * size; ++i) {
            result.data[i] = data[i] + other.data[i];
        }

        return result;
    }
    
    
    

}
 

