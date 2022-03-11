#include "Tree/tree.h"
#include "calc.h"

size_t GetNum (char *buf, int *num);

int main () {
	FILE *inp = fopen ("input.txt", "r+");
	char buf[BUF_SIZE];
	size_t len = 0;
	int num;
	size_t nread = fread (buf, sizeof (char), BUF_SIZE, inp);
	printf ("nread = %ld\n", nread);
	len = GetNum (buf, &num);
	printf ("%ld %d\n", len, num);

	exit (EXIT_SUCCESS);
}

branch_t *Input (char *buf) {
	branch_t *tmp;
	size_t len = 0;
	while (buf[len] == '(') {
		len++;
	}
	while ()
}

size_t GetNum (char *buf, branch_t *branch) {
	size_t len = 0;
	int num = 0;
	while (isdigit (buf[len])) {
		num = num * 10 + buf[len] - 48;
		len++;
	}
	branch->data = num;
	while (isspace (buf[len])) {
		len++;
	}
	return len;
}

size_t GetOper (char *buf, branch_t *branch) {
	size_t len = 0;
	while (buf[len] != '=') {
		if (isdigit (buf[len])) {
			branch = Branch_ ()
		}
	}

}

int isoper (char c) {
	if ((c == MINUS) || (c == PLUS) || (c == POW) || (c == DIVIDE) || (c == MULTY))
		return 1;
	return 0;
}

int GetPriority (char c) {
	switch (c) {
		case POW:		return 2;
		case MULTY:		return 1;
		case DIVIDE:	return 1;
		case PLUS:		return 0;
		case MINUS:		return 0;
		default:		return -1;
	}
	return -1;
}
