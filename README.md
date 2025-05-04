# Square Matrix – CPP\_EX2\_25

This project implements a class `SquareMat` for performing arithmetic and algebraic operations on square matrices in C++, without using STL containers.

---

## Project Structure

```
CPP_EX2_25/
├── src/
│   └── SquareMat.cpp / .hpp      # Matrix class implementation
├── test/
│   ├── doctest.h
│   └── test.cpp                  # Unit tests for all operators
├── main.cpp                      # Demo of matrix functionality
├── Makefile                      # Build and run instructions
└── README.md
```

---

## How to Run the Project

1. **Build the project**

```bash
make
```

2. **Run the demo**

```bash
./prog
```

Or simply:

```bash
make Main
```

3. **Run unit tests**

```bash
make test
```

4. **Check for memory leaks with Valgrind**

```bash
make valgrind
```

---

## Matrix Class Design (`SquareMat`)

* The matrix is square and its size is fixed at construction.
* Internally, the matrix is represented using a dynamic 1D array (`double* data`).
* Indexing is done via a helper class `RowAccessor` to allow syntax like `mat[i][j]` safely.

### Security Note on Access:

C++ only allows the first `[]` operator to be overloaded. To simulate double bracket access (i.e., `mat[i][j]`), we use a **nested helper class** `RowAccessor`, returned by the outer `operator[]`. This helper allows bounds checking on both `i` and `j`. It is defined *inside* the `SquareMat` class to prevent direct instantiation by the user, ensuring encapsulation and safer usage.

---
 Non-Member Operator `scalar * matrix`

In C++, when overloading a binary operator like `*`, the function must take **exactly two operands**.
To allow `scalar * matrix` (e.g., `2.5 * mat`), the operator cannot be a member of `SquareMat` because `double` (the left-hand operand) is not a class and cannot act as `this`.

So, we define a **non-member function**:

```cpp
SquareMat operator*(double scalar, const SquareMat& mat);
```

This delegates internally to the member function `mat * scalar`. Since it doesn't access any private members directly, it doesn't need to be a `friend`. But if it ever does, making it a `friend` is acceptable and safe.

---

## Author

| Name           | Student ID |
| -------------- | ---------- |
| Noa Honigstein | 329808554  |
