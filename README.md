# CPP_EX2_25

probleme de securiter dians [] alor on a cree une sous classe{idee proposer par gpt}
dans la class de matrix elle meme pour pas permetre a lutilisateur de cree une instance de row
on peut pas faire data[i * size + j];

In C++, when overloading a binary operator like "*", the function must take exactly two operands.

To allow expressions like "scalar * matrix", we need to define a non-member function, because the left-hand side is a built-in type (e.g., double), which cannot be the implicit object of a member function.

If we tried to make it a member function, it would implicitly add a third parameter (the "this" pointer), resulting in three operands, which is invalid for a binary operator.

Therefore, the correct approach is to define a non-member operator function for "scalar * matrix".
Since we don't access any private members directly (we just delegate to the already-defined "matrix * scalar" operator), we don't even need to declare it as a friend. But if we ever need direct access to private members, declaring it as a `friend` inside the class is also valid.
