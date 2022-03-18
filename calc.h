#include "Tree/tree.h"
#include <ctype.h>
#include <math.h>

enum SIZES {
	BUF_SIZE = 1024
};

enum OPERS {
	PLUS = '+',
	MINUS = '-',
	POW = '^',
	MUL = '*',
	DIV = '/'
};

enum FUNCS {
	SIN = 1,
	COS = 2,
	TAN = 3,
	CAT = 4,
	ASIN = 5,
	ACOS = 6,
	ATAN = 7,
	ACOT = 8,
	SINH = 9,
	COSH = 10,
	TANH = 11,
	COTH = 12,
	ASINH = 13,
	ACOSH = 14,
	ATANH = 15,
	ACOTH = 16,
	EXP = 17,
	SQRT = 18,
	LOG = 19,
	LN = 20,
	LG = 21,
	FACT = 22,
	ABS = 23
};