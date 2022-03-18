#include "Tree/tree.h"
#include "calc.h"

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

size_t GetPlus (char *buf, branch_t *current) {
	size_t len = 0;
	while (isspace (buf[len])) len++;
	len += GetNum (buf + len, current);
	while (isspace (buf[len])) len++;

	while ((buf[len] == '-') || (buf[len] == '+')) {
		current->parent = Branch_ (NULL, buf[len], OPER);
		current->parent->left = current;
		current = current->parent;

		len++;
		while (isspace (buf[len])) len++;
		current->right = Branch_ (current, POISON, NUM);
		len += GetNum (buf + len, current->right);

		if (current->left->type == OPER) {
			printf ("%c ", current->left->data);
		} else if (current->left->type == NUM) {
			printf ("%d ", current->left->data);
		}
		printf ("%c %d\n", current->data, current->right->data);

		while (isspace (buf[len])) len++;
	}
	return len;
}

int isoper (char c) {
	if ((c == MINUS) || (c == PLUS) || (c == POW) || (c == DIV) || (c == MUL))
		return 1;
	return 0;
}

int GetPriority (char c) {
	switch (c) {
		case POW:		return 2;
		case MUL:		return 1;
		case DIV:		return 1;
		case PLUS:		return 0;
		case MINUS:		return 0;
		default:		return -1;
	}
	return -1;
}

void Input (const char *pathname, tree_t *tree) {
	FILE *inp = fopen (pathname, "r+");
	char buf[BUF_SIZE];
	size_t len = 0;
	size_t nread = fread (buf, sizeof (char), BUF_SIZE, inp);
	fclose (inp);

	len = GetPlus (buf, tree->root);
	printf ("nread = %ld, len = %ld\n", nread, len);

}

void WriteBase (FILE *out, branch_t *branch) {
	if (branch->type == NUM) {
		fprintf (out, "%d ", branch->data);
		return;
	}
	if (branch->type == OPER) {
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

int main () {
	tree_t tree;
	TreeConstruct (&tree);
	Input ("input.txt", &tree);
	// if (tree.root->type == OPER) {
	// 	printf ("oper\n");
	// } else if (tree.root->type == NUM) {
	// 	printf ("num\n");
	// } else {
	// 	printf ("unknown type\n");
	// }
	printf ("%d\n", tree.root->data);
	// SaveBase ("output.txt", &tree);

	exit (EXIT_SUCCESS);
}