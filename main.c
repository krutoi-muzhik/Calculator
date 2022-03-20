#include "calc.h"

int main () {
	tree_t tree;
	TreeConstruct (&tree);
	Input ("input.txt", &tree);
	Calculate (&tree);
	GVDump ("graph/graph.gv", &tree);

	exit (EXIT_SUCCESS);
}