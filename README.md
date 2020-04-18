# Simple Compiler

A simple implementation for lexical and parsing/syntax phases of a compiler 


## Lexical Phase 
The language consists of keywords, identifiers, constants, operators and symbols. While others are invalid.

 <p align="center">
  <img  src="../media/lexicalSeq.png?raw=true" widht="400" height="300">
</p>

The output of lexical phase for the following code should be as follow
```
int main  () {
int a,b,0c=0;
c = a+b;
&
return;	
}
```
 <p align="center">
  <img  src="../media/lexicalOp.png?raw=true" widht="500" height="400">
</p>

**InputFile:** lexical prog.txt

## Parsing Phase
Parsing phase depends on the output of the lexical phase.  

The grammar is:

 <p align="center">
  <img  src="../media/parsingGM.png?raw=true" widht="400" height="150">
</p>
 
 
The output of parsing phase for the following code should be as follow
```
int * int * int   
```
<p align="center">
  <img  src="../media/parsingOp.PNG?raw=true" widht="100" height="50">
</p>

**InputFile:** syntax prog.txt
