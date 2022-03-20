#include "calc.h"

int main () {
	tree_t tree;
	TreeConstruct (&tree);
	Input ("input.txt", &tree);
	// if (tree.root->type == BINAR) {
	// 	printf ("oper\n");
	// } else if (tree.root->type == NUM) {
	// 	printf ("num\n");
	// } else {
	// 	printf ("unknown type\n");87
	// }
	// printf ("%d\n", tree.root->data);
	SaveBase ("output.txt", &tree);
	Calculate (&tree);
	GVDump ("graph/graph.gv", &tree);

	exit (EXIT_SUCCESS);
}