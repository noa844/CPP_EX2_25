// noa.honigstein@gmail.com
#include "SquareMat.hpp"
#include <cmath>  
using std::cout;
using std::endl;
using std::runtime_error;
const char PIPE = '|';

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
            throw runtime_error("Matrices must be the same size");
        }
    
        SquareMat result(size);
        
        for (int i = 0; i < size * size; ++i) {
            result.data[i] = data[i] + toAdd.data[i];
        }

        return result;
    }

    SquareMat SquareMat::operator-(const SquareMat &toReduce) const {
        if (size != toReduce.size) {
            throw runtime_error("Matrices must be the same size");
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
            throw runtime_error("Matrices must be the same size");
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
        if (std::isnan(scalar) || std::isinf(scalar)) {
            throw std::runtime_error("Invalid scalar: NaN, or infinity");
        }

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
            throw runtime_error("Matrices must be the same size");
        }
    
        SquareMat result(size);
        
        for (int i = 0; i < size * size; ++i) {
            result.data[i] = data[i] * toMultiply.data[i];
        }

        return result;
    }

    SquareMat SquareMat::operator%(int scalar) const {
        if (scalar == 0.0 || std::isnan(scalar) || std::isinf(scalar)) {
            throw std::runtime_error("Invalid scalar: division by zero, NaN, or infinity");
        }
        SquareMat result(size);
        
        for (int i = 0; i < size * size; ++i) {
            result.data[i] = fmod(data[i], static_cast<double>(scalar));
        }

        return result;

    }

    SquareMat SquareMat::operator/(double scalar) const {
        if (scalar == 0.0 || std::isnan(scalar) || std::isinf(scalar)) {
            throw std::runtime_error("Invalid scalar: division by zero, NaN, or infinity");
        }

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
        if (std::isnan(scalar)) {
            throw std::runtime_error("Invalid scalar: NaN");
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

    SquareMat& SquareMat::operator++() {
        for (int i = 0; i < size * size; ++i) {
            data[i] += 1;
        }
        return *this;
    }

    SquareMat SquareMat::operator++(int) {
        SquareMat befor = *this;
        ++(*this);
        return befor;
    }

    SquareMat& SquareMat::operator--() {
        for (int i = 0; i < size * size; ++i) {
            data[i] -= 1;
        }
        return *this;
    }

    SquareMat SquareMat::operator--(int) {
        SquareMat befor = *this;
        --(*this);
        return befor;
    }

    SquareMat SquareMat::operator~() const {
        SquareMat result(size);

        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                result[j][i] = (*this)[i][j];
            }
        }
        return result;
    }

    double SquareMat::sumMat() const{
        double sum = 0.0;
        for (int i = 0; i < size * size; ++i) {
            sum += data[i];
        }
        return sum;

    }
    bool SquareMat::operator==(const SquareMat& other) const {

        return (*this).sumMat() == other.sumMat();
    }
    bool SquareMat::operator!=(const SquareMat& other) const {

        return (*this).sumMat() != other.sumMat();
    }
    bool SquareMat::operator<(const SquareMat& other) const {

        return (*this).sumMat() < other.sumMat();
    }
    
    bool SquareMat::operator>(const SquareMat& other) const {

        return (*this).sumMat() > other.sumMat();

    }
    
    bool SquareMat::operator<=(const SquareMat& other) const {

        return (*this).sumMat() <= other.sumMat();

    }
    
    bool SquareMat::operator>=(const SquareMat& other) const {

        return (*this).sumMat() >= other.sumMat();

    }

    double SquareMat::operator!() const {
        // Base case: 1x1 matrix, determinant is the single value
        if (size == 1) {
            return data[0];
        }
    
        // Base case: 2x2 matrix, use the classic determinant formula
        if (size == 2) {
            return (*this)[0][0] * (*this)[1][1] - (*this)[0][1] * (*this)[1][0];
        }
    
        double det = 0.0;
    
        // Loop over the first row, expanding the determinant along this row
        for (int x = 0; x < size; ++x) {
            // Create a sub-matrix that excludes the first row and column x
            SquareMat subMatrix(size - 1);
    
            int subi = 0;  // sub-matrix row index
            for (int i = 1; i < size; ++i) {  // skip the first row
                int subj = 0;  // sub-matrix column index
                for (int j = 0; j < size; ++j) {
                    if (j == x) continue;  // skip the current column
                    // Copy remaining elements into the sub-matrix
                    subMatrix[subi][subj] = (*this)[i][j];
                    ++subj;
                }
                ++subi;
            }
    
            // Add or subtract the determinant of the sub-matrix, depending on position
            det += pow(-1.0, x) * (*this)[0][x] * !subMatrix;
        }
    
        return det;
    }

    SquareMat& SquareMat::operator+=(const SquareMat& other) {
        if (size != other.size)
            throw runtime_error("Matrices must be the same size");
    
        for (int i = 0; i < size * size; ++i) {
            data[i] += other.data[i];
        }
        return *this;
    }

    SquareMat& SquareMat::operator-=(const SquareMat& other) {
        if (size != other.size)
            throw runtime_error("Matrices must be the same size");
    
        for (int i = 0; i < size * size; ++i) {
            data[i] -= other.data[i];
        }
        return *this;
    }

    SquareMat& SquareMat::operator*=(const SquareMat& other) {
        if (size != other.size)
            throw std::runtime_error("Matrices must be the same size");
    
        SquareMat result = (*this) * other;  

        *this = result;  
        return *this;
    }

    SquareMat& SquareMat::operator*=(double scalar) {
        if (std::isnan(scalar) || std::isinf(scalar)) {
            throw std::runtime_error("Invalid scalar: NaN, or infinity");
        }
        for (int i = 0; i < size * size; ++i) {
            data[i] *= scalar;
        }
        return *this;
    }

    SquareMat& SquareMat::operator/=(double scalar) {
        if (scalar == 0.0 || std::isnan(scalar) || std::isinf(scalar)) {
            throw std::runtime_error("Invalid scalar: division by zero, NaN, or infinity");
        }
    
        for (int i = 0; i < size * size; ++i) {
            data[i] /= scalar;
        }
        return *this;
    }
    
    SquareMat& SquareMat::operator%=(const SquareMat& other) {
        if (size != other.size)
            throw runtime_error("Matrices must be the same size");
    
        for (int i = 0; i < size * size; ++i) {
            data[i] *= other.data[i];
        }
        return *this;
    }

    SquareMat& SquareMat::operator%=(int scalar) {
        if (scalar == 0.0 || std::isnan(scalar) || std::isinf(scalar)) {
            throw std::runtime_error("Invalid scalar: division by zero, NaN, or infinity");
        }
    
        for (int i = 0; i < size * size; ++i) {
            data[i] = fmod(data[i], static_cast<double>(scalar));
        }
        return *this;
    }
    
    
    
    
    

    
    
    
    std::ostream &operator<<(std::ostream &os, const SquareMat &matrix) {
    
        for (int i = 0; i < matrix.size; i++) {
            os << PIPE;
            for (int j = 0; j < matrix.size; j++) {
                os << matrix[i][j] << PIPE;
            }
            os << std::endl;
        }
        return os;
    }












    
    

}
 

