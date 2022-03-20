#include "tree.h"
#include "../calc.h"

// const data_t POISON = 0xBEEBA;

branch_t *Branch (branch_t *parent, data_t data) {
	branch_t *branch = calloc (1, sizeof (branch_t));
	branch->data = data;
	branch->parent = parent;
	branch->left = NULL;
	branch->right = NULL;
	return branch;
}

branch_t *Branch_ (branch_t *parent, data_t data, branch_type_t type) {
	branch_t *branch = Branch (parent, data);
	branch->type = type;
	return branch;
}

void RecursiveDestruct (branch_t *branch) {
	if (branch->left != NULL) {
		RecursiveDestruct (branch->left);
		branch->left = NULL;
		// if (branch->left == NULL)
		// 	printf ("\n%d left -> null\n\n", branch->data);
	}
	if (branch->right != NULL) {
		RecursiveDestruct (branch->right);
		branch->right = NULL;
		// if (branch->right == NULL)
		// 	printf ("\n%d right -> null\n\n", branch->data);
	}
	#ifdef DINAMIC_DATA
	free (branch->data);
	#endif

	free (branch);
	return;
}

void TreeConstruct (tree_t *tree) {
	tree->root = Branch (NULL, POISON);
	tree->size = 0;
}

void TreeDestruct (tree_t *tree) {
	RecursiveDestruct (tree->root);
	tree->root = NULL;
	tree->size = 0;
}

#define Out(func) fprintf (graph, "\tpeak%p [label = \"%s\"];\n", branch, func); break;

void Graph (FILE *graph, branch_t *branch) {
	switch (branch->type) {
		case BINAR:
			switch (branch->data) {
				case PLUS:	Out("+")
				case MINUS:	Out("-")
				case MUL:	Out("*")
				case DIV:	Out("/")
				case POW:	Out("^")
				case LOG:	Out("log")
			}
			break;
		case UNAR:
			switch (branch->data) {
				case SIN:	Out("sin")
				case COS:	Out("cos")
				case TAN:	Out("tan")
				case COT:	Out("cot")
				case ASIN:	Out("asin")
				case ACOS:	Out("acos")
				case ATAN:	Out("atan")
				case ACOT:	Out("acot")
				case SH:	Out("sh")
				case CH:	Out("ch")
				case TANH:	Out("tanh")
				case COTH:	Out("coth")
				case ASH:	Out("ash")
				case ACH:	Out("ach")
				case ATANH:	Out("atanh")
				case ACOTH:	Out("acoth")
				case EXP:	Out("exp")
				case SQRT:	Out("sqrt")
				case LN:	Out("ln")
				case LG:	Out("lg")
				case FACT:	Out("fact")
				case ABS:	Out("abs")
			}
			break;
		case NUM:
			fprintf (graph, "\tpeak%p [label = \"%d\"];\n", branch, branch->data);
			break;
	}

	if (branch->left != NULL) {
		fprintf (graph, "\t\tpeak%p -> peak%p\n", branch, branch->left);
		Graph (graph, branch->left);
	}
	if (branch->right != NULL) {
		fprintf (graph, "\t\tpeak%p -> peak%p\n", branch, branch->right);
		Graph (graph, branch->right);
	}
	return;
}

void GVDump (const char *pathname, tree_t *tree) {
	FILE *graph = fopen (pathname, "w");
	branch_t *branch = tree->root;
	fprintf (graph, "digraph TREE {\n");
	fprintf (graph, "	node [shape = box]\n\n");
	Graph (graph, branch);
	fprintf (graph, "}\n");
	fclose (graph);
	return;
}

void InsertBranch (branch_t *parent, size_t dir, data_t data) {
	branch_t *tmp;
	if (dir) {
		tmp = parent->right;
		parent->right = Branch (parent, data);
		parent->right->left = tmp;
	}
	else {
		tmp = parent->left;
		parent->left = Branch (parent, data);
		parent->left->left = tmp;
	}
	return;
}
