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

    SquareMat SquareMat::operator+(const SquareMat &toAdd) const {
        if (size != toAdd.size) {
            throw runtime_error("Must be the same size for addition.");
        }
    
        SquareMat result(size);
        
        for (int i = 0; i < size * size; ++i) {
            result.data[i] = data[i] + toAdd.data[i];
        }

        return result;
    }

    SquareMat SquareMat::operator-(const SquareMat &toReduce) const {
        if (size != toReduce.size) {
            throw runtime_error("Must be the same size for addition.");
        }
    
        SquareMat result(size);
        
        for (int i = 0; i < size * size; ++i) {
            result.data[i] = data[i] - toReduce.data[i];
        }

        return result;
    }

    SquareMat SquareMat::operator-() const {
    
        SquareMat result(size);
        
        for (int i = 0; i < size * size; ++i) {
            result.data[i] = data[i] * (-1);
        }

        return result;
    }
    
    SquareMat SquareMat::operator*(const  SquareMat &other) const {
        if (size != other.size) {
            throw runtime_error("Must be the same size for addition.");
        }

        SquareMat result(size);
        for (int i = 0; i < size; i++) { // size==this.rows
            for (int j = 0; j < size; j++) { // size==other.colomns
                for (int k = 0; k < size; k++) { // size==this.colomns
                    result[i][j] += (*this)[i][k] * other[k][j];
                }
            }
        }
        return result;
    }

    SquareMat SquareMat::operator*(double scalar) const {

        SquareMat result(size);
        
        for (int i = 0; i < size * size; ++i) {
            result.data[i] = data[i] * scalar;
        }

        return result;

    }
    
    //Function allowing scalar * matrix, since it is not a member function and thus doesn't operate directly on this
    SquareMat operator*(double scalar, const SquareMat &other) {
        return other*scalar;
    }

    SquareMat SquareMat::operator%(const SquareMat &toMultiply) const {
        if (size != toMultiply.size) {
            throw runtime_error("Must be the same size for addition.");
        }
    
        SquareMat result(size);
        
        for (int i = 0; i < size * size; ++i) {
            result.data[i] = data[i] * toMultiply.data[i];
        }

        return result;
    }

    SquareMat SquareMat::operator%(int scalar) const {
        if (scalar == 0) {
            throw runtime_error("error! division by 0.");
        }
        SquareMat result(size);
        
        for (int i = 0; i < size * size; ++i) {
            result.data[i] = fmod(data[i], static_cast<double>(scalar));
        }

        return result;

    }

    SquareMat SquareMat::operator/(double scalar) const {

        SquareMat result(size);
        
        for (int i = 0; i < size * size; ++i) {
            result.data[i] = data[i]/scalar;
        }

        return result;

    }

    SquareMat SquareMat::operator^(int scalar) const {
        if (scalar < 0) {
            throw runtime_error("Power must be positive.");
        }
        
        SquareMat result(size);

        if(scalar == 0){
            for (int i = 0; i < size; ++i) {
                for (int j = 0; j < size; ++j) {
                    if(i==j){
                        result[i][j] = 1.0;
                    }else{
                        result[i][j] = 0.0;
                    }
                    
                }
            }
        }else{

        result = (*this);
        
        for (int i = 1; i < scalar; ++i) {
            result = result*(*this);
        }
    }

        return result;

    }









    
    

}
 

