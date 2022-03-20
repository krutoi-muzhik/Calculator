#include "Tree/tree.h"
#include "calc.h"

#define skipspace while (isspace (buf[len])) len++;

size_t GetNum (char *buf, branch_t *branch) {
	size_t len = 0;
	branch->type = NUM;
	int num = 0;
	if (buf[len] == '-') {
		len++;
		while (isdigit (buf[len])) {
			num = num * 10 - buf[len] + 48;
			len++;
		}
	} else {
		while (isdigit (buf[len])) {
			num = num * 10 + buf[len] - 48;
			len++;
		}
	}
	branch->data = num;
	while (isspace (buf[len])) len++;
	return len;
}

size_t GetMulDiv (char *buf, branch_t **current) {
	size_t len = 0;
	skipspace
	len += GetNum (buf + len, *current);
	skipspace

	while ((buf[len] == '*') || (buf[len] == '/')) {
		(*current)->parent = Branch_ (NULL, buf[len], BINAR);
		(*current)->parent->left = (*current);
		(*current) = (*current)->parent;

		len++;
		skipspace
		(*current)->right = Branch_ (*current, POISON, NUM);
		len += GetNum (buf + len, (*current)->right);

		if ((*current)->left->type == BINAR) {
			printf ("%c ", (*current)->left->data);
		} else if ((*current)->left->type == NUM) {
			printf ("%d ", (*current)->left->data);
		}
		printf ("%c %d\n", (*current)->data, (*current)->right->data);

		skipspace
	}
	return len;
}

size_t GetPlusMinus (char *buf, branch_t **current) {
	size_t len = 0;
	skipspace
	len += GetMulDiv (buf + len, current);
	skipspace

	while ((buf[len] == '+') || (buf[len] == '-')) {
		(*current)->parent = Branch_ (NULL, buf[len], BINAR);
		(*current)->parent->left = (*current);
		(*current) = (*current)->parent;

		len++;
		skipspace
		(*current)->right = Branch_ (*current, POISON, NUM);
		len += GetMulDiv (buf + len, &((*current)->right));

		if ((*current)->left->type == BINAR) {
			printf ("%c ", (*current)->left->data);
		} else if ((*current)->left->type == NUM) {
			printf ("%d ", (*current)->left->data);
		}
		printf ("%c %d\n", (*current)->data, (*current)->right->data);

		skipspace
	}
 
}

int isoper (char c) {
	if ((c == MINUS) || (c == PLUS) || (c == POW) || (c == DIV) || (c == MUL))
		return 1;
	return 0;
}

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

void Calculate (tree_t *tree) {
	double cnt = Count (tree->root);
	printf ("%lf\n", cnt);
}

void Input (const char *pathname, tree_t *tree) {
	FILE *inp = fopen (pathname, "r+");
	char buf[BUF_SIZE];
	size_t len = 0;
	size_t nread = fread (buf, sizeof (char), BUF_SIZE, inp);
	fclose (inp);

	branch_t *tmp = Branch (NULL, POISON);

	len = GetPlusMinus (buf, &tmp);
	tree->root = tmp;
	printf ("nread = %ld, len = %ld\n", nread, len);
}

void WriteBase (FILE *out, branch_t *branch) {
	if (branch->type == NUM) {
		fprintf (out, "%d ", branch->data);
		return;
	}
	if (branch->type == BINAR) {
		WriteBase (out, branch->left);
		fprintf (out, "%c ", branch->data);
		WriteBase (out, branch->right);
		return;
	}
	printf ("unknown branch type\n");
	return;
}

void SaveBase (const char *pathname, tree_t* tree) {
	FILE *out = fopen (pathname, "w");
	fprintf (out, "CALCULATOR by krutoi_muzhik crated this base\n\n");
	WriteBase (out, tree->root);
	fclose (out);
	return;
}
