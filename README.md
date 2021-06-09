# Barebones programming language
This is my repo for CS111 - Spring 2021, University of Information Technology, VNU HCM. In this repo,I try to create a barebones compiler using C++.
Barebones programming language is a low level language which includes only basic statements to execute a simple program.

## Introduction 

![version](https://img.shields.io/badge/version%20-1.0.0-brightgreen%20)

## How syntax tree of barebones look like?
Syntax trees are data structures widely used in compilers to represent the structure of program code. ... It often serves as an intermediate representation of the program through several stages that the compiler requires, and has a strong impact on the final output of the compiler

![alt text](https://github.com/BTrDung/Complex/blob/master/BBLang/198661149_968732063958275_4394586345187106564_n.png)
## How to run program
Clone my git:

> ```git clone https://github.com/BTrDung/barebones-language.git```

Run command in your terminal: 

> ```g++ barebones.cpp -o bb;```

Run barebones by using ```./bb``` and link to your file ```*.bb```

> ```./bb ./examples/test.bb```

## Examples barebones program
Two simple sample barebones programs are provided in the "examples" subdirectory. ```test1.bb``` will compute A + B. For example, to compute A + B:

> ```./bb ./examples/test1.bb```

### Requirements
`g++ 9.3.0` or later


## Installation
```g++```: [Download](https://gcc.gnu.org/)
