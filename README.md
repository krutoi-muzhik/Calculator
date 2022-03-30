# Introduction
As you can guess from the repository's name, this programm works as a simple calculator. It reads the math expression and parses it to a binar tree. The realisation of tree is descripted in my repository [Tree](https://github.com/krutoi-muzhik/Tree).

# Run
Clone the repo and use "make calc" to compile the programm

To run write the math expression you want to calculate in file "input.txt" and use "make run". The unswer will be written in the terminal.

You can use "make clean" to delete all object and executable files.

# Implementation
The structure of programm contains 2 parts - building a binar tree, basing on syntax analysis and then counting the result of the tree.

## Reading the expression
The programm is building the, while reading the input file from the beginning.

Here is the priority of reading different operations in EBNF scheme:

```EBNF
GetPlusMinus ::= GetMulDiv{[+-]GetMulDiv}*
GetMulDiv ::= GetLog{[*/]GetLog}*
GetLog ::= GetPow{[log]GetPow}*
GetPow ::= GetNF{[^]GetNF}
GetNF ::= GetFunc | GetNum
GetFunc ::= func(GetPlusMinus)
GetNum := ['0'-'9']+
```

Example of tree:

![tree](https://github.com/krutoi-muzhik/Calculator/blob/Main/graph/expression.png)

## Counting

The programm counts it from the root. Here is the main counting function:

```C
double Count (branch_t *branch) {
	if (branch->type == BINAR) {
		#define DEF_BINAR(oper_num, oper, priority, performance) {	\
			if (branch->data == oper_num) {							\
				performance											\
			}														\
		}															// end of define
																	// return is containeed in performance
		#include "cmd/oper_binar.h"
		#undef DEF_BINAR

	} else if (branch->type == UNAR) {
		#define DEF_UNAR(oper_num, oper, performance) {		\
			if (branch->data == oper_num) {					\
				performance									\
			}												\
		}													// end of define
															// return is containeed in performance
		#include "cmd/oper_unar.h"
		#undef DEF_UNAR
	} else if (branch->type == NUM) {
		return branch->data;
	}
}
```

As you can see, this function uses DSL so as not to clog the code with extra "if" or "switch - case" instructions.

DEF_UNAR or DEF_BINAR is contained in includable files "oper_binar.h" and "oper_unar.h" and facing the needed operation, when the 
```C
(branch->data == oper_num) 
```
the block of code called "performance" is being executed.

Here is an example from "oper_binar.h":

```C
DEF_BINAR (DIV, '/', 2, {
	return Count (branch->left) / Count (branch->right);
})
```

The block of code, that is named "performance" in function "Count" just returns the values counted according to the branches operation.
