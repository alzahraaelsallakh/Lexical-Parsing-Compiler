# simple_compiler-C
a simple lexical and parsing phases of a compiler.

**lexixal Phase**

The language consists of keywords, identifiers, constants, operators and symbols. Others are invalid.

**Syntax Phase**

The Grammar:
    S >> int T
    T >> * int T | + int T | epsilon
    
The code works on the tokens that results out of the lexical phase.
