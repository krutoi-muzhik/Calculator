#include "../calc.h"

DEF_OPER (PLUS, '+', 1, {
	return Count (branch->left) + Count (branch->right);
})

DEF_OPER (MINUS, '-', 1, {
	return Count (branch->left) - Count (branch->right);
})

DEF_OPER (MUL, '*', 2, {
	return Count (branch->left) * Count (branch->right);
})

DEF_OPER (DIV, '/', 2, {
	return Count (branch->left) / Count (branch->right);
})

DEF_OPER (POW, '^', 3, {
	return powf (Count (branch->left), Count (branch->right));
})