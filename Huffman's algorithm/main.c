typedef struct tree {
	int item;
	struct tree *left;
	struct tree *right;

	//int height;
} tree;

tree *create(int x) {
	tree *p;
	p = (tree*)malloc(sizeof(tree));
	p->item = x;
	p->left = p->right = NULL;
	//p->height = 1;
	return p;
}

void deleteNode(tree *node) {
	free(node);
}

void insert_element(tree **l, int x) {
	if (*l == NULL) {
		*l = create(x);
		return;
	}
	if (x < (*l)->item)
		insert_element(&((*l)->left), x);
	else
		insert_element(&((*l)->right), x);
	balance(*l);
	//(*l)->height = 1 + get_max(*l);
}

void inorder(tree *l, FILE *output_file) {
	if (l != NULL) {
		inorder(l->left, output_file);
		fprintf(output_file, "%d ", l->item);
		inorder(l->right, output_file);
	}
}
int createTableFrequency(char *word, int *table) { //не забыть про пробелы
	
}

int main() {
	//fin 
	assert(fin != NULL) {
		puts("error openning file");
		getch();
		exit(ERROR_FILE_OPEN);
	}
	
	char command;
	scanf("%c", &command);
	// чтение всего файла binary до конца //  size_t fread ( void * ptr, size_t size, size_t count, FILE * stream );
	
	int *table = (int *)malloc(sizeof(int) * 
	
	if((int)command == 'c') { //сжатие 
		coding();
	} else if ((int)command == 'd') { //разархивация
		decoding();
	} else {
		puts("Invalid command");
		exit(0);
	}
	
	return 0;	
}
				
// https://habr.com/ru/post/144200/
// https://learnc.info/c/binary_files.html
