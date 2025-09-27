# Computor v1
  Polynomial equation solver (degree <= 2).
## steps
-> 
## leak tests
- pull nd run valgrind ```bash docker run -tiv $PWD:/valgrind karek/valgrind:latest ```
- run ```valgrind ./computor "args..." ```

## notes
- since math.h is not allowed , use **Newton’s Method** to calculate the square root
- my parser is sloppy and i have to do a lot of patching and handling of edge cases, i'm looking into implementing a proper lexer and parser using  **Recursive Descent Parsing** 
- it is worth it to spend as mush time as possible on RDP since i will be using it on other projects
- for printing fraction we multiply the double by 1e6 for example to preserve 6 degrees of percision then find the gcd

## resources
- [Square Roots via Newton’s Method](https://math.mit.edu/~stevenj/18.335/newton-sqrt.pdf)
- [Recursive Descent Parsing](https://www.youtube.com/watch?v=SToUyjAsaFk&ab_channel=hhp3)
- [the best article i've read about parsing](https://craftinginterpreters.com/scanning.html)
- [LL Parsing and Recursive Descent ](https://blog.jeffsmits.net/ll-parsing-recursive-descent/)
- [Grammars, parsing, and recursive descent - good video](https://www.youtube.com/watch?v=ENKT0Z3gldE&ab_channel=KayLack)
- [Automata Theory](https://cs.stanford.edu/people/eroberts/courses/soco/projects/2004-05/automata-theory/basics.html)