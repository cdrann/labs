#include "something.h"

int main() {
	FILE *input_file = fopen("in.txt", "r");
	FILE *output_file = fopen("out.txt", "a");

	if (input_file == NULL) {
		fputs("no such file", output_file);
		return 0;
	}

	int n;
	fscanf(input_file, "%d", &n);

	tree *head = NULL;

	int tmp;
	for (int i = 0; i < n; i++) {
		fscanf(input_file, "%d", &tmp);
		insert_element(&head, tmp);
	}

	inorder(head, output_file);

	fclose(input_file);
	fclose(output_file);

	return 0;
}