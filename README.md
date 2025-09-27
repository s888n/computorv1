# Computor v1
  Polynomial equation solver (0 < degree <= 2) using a [Recursive Descent Parser](https://en.wikipedia.org/wiki/Recursive_descent_parser).

## How to run
> You will need ```Make``` and the Standard C library
```bash
# clone the repo
git clone https://github.com/s888n/computorv1.git
# go the cloned directory
cd computorv1
# and just run make
make
```

## How to use
```bash
./computor -[ts] "<equation>"
-t   Print the Abstract Syntax Tree
-s   Show detailed solution steps

# example
 ./computor -ts "8 * X^0 - 6 * X^1 + 0 * X^2 - 5.6 * X^3 = 3 * X^0"
 ./computor -s "5 + 4 * X + X^2 = X^2"
```

## Backus–Naur form
```ebnf
Equation := Expression "=" Expression
Expression := Term {( "-" | "+" ) Term}*
Term := Factor { "*" Factor}*
Factor := NUMBER | VAR | "(" Expression ")"
NUMBER := "0" | "1" | "2" | "3" | "4" | "5" | "6" | "7" | "8" | "9" | "."
VAR := "x" | "X"
```

## Demo

## resources
- [the best article i've read about parsing](https://craftinginterpreters.com/scanning.html)
- [Square Roots via Newton’s Method](https://math.mit.edu/~stevenj/18.335/newton-sqrt.pdf)
- [Recursive Descent Parsing](https://www.youtube.com/watch?v=SToUyjAsaFk&ab_channel=hhp3)
- [LL Parsing and Recursive Descent ](https://blog.jeffsmits.net/ll-parsing-recursive-descent/)
- [Grammars, parsing, and recursive descent - good video](https://www.youtube.com/watch?v=ENKT0Z3gldE&ab_channel=KayLack)
- [Automata Theory](https://cs.stanford.edu/people/eroberts/courses/soco/projects/2004-05/automata-theory/basics.html)

<!-- ## notes -->
<!-- - since math.h is not allowed , use **Newton’s Method** to calculate the square root -->
<!-- - my parser is sloppy and i have to do a lot of patching and handling of edge cases, i'm looking into implementing a proper lexer and parser using  **Recursive Descent Parsing**  -->
<!-- - it is worth it to spend as much time as possible on RDP since i will be using it on other projects -->
<!-- - for printing fraction we multiply the double by 1e6 for example to preserve 6 degrees of percision then find the gcd -->

> Since using the math library is forbidden, i implemented all the math functions i needed.