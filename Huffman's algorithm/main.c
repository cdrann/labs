typedef struct tree {
	int item;
	struct tree *left;
	struct tree *right;

	int height;
} tree;


int get_height(tree *node) {
	if (node == NULL)
		return 0;
	return node->height;
}

int get_max(tree *p) {
	if (get_height(p->left) > get_height(p->right))
		return get_height(p->left);
	return get_height(p->right);
}

void LR(tree* top) {
	tree *r = top->right;
	tree *c = top->left->right;
	tree *l = top->left->left;
	top->right = top->left;
	top->left = l;
	top->right->right = r;
	top->right->left = c;
	int temp = top->item;
	top->item = top->right->item;
	top->right->item = temp;
	top->right->height = 1 + get_max(top->right);
	top->height = 1 + get_max(top);
}

void LL(tree* top) {
	tree *r = top->left;
	tree *c = top->right->left;
	tree *l = top->right->right;
	top->left = top->right;
	top->right = l;
	top->left->left = r;
	top->left->right = c;
	int temp = top->item;
	top->item = top->left->item;
	top->left->item = temp;
	top->left->height = 1 + get_max(top->left);
	top->height = 1 + get_max(top);
}

void BL(tree* top) {
	LR(top->right);
	LL(top);
}

void BR(tree* top) {
	LL(top->left);
	LR(top);
}

tree * create(int x) {
	tree *p;
	p = (tree*)malloc(sizeof(tree));
	p->item = x;
	p->left = p->right = NULL;
	p->height = 1;
	return p;
}

void deleteNode(tree *node) {
	free(node);
}

void balance(tree *l) {
	tree *p = l;
	if (get_height(p->right) - get_height(p->left) == 2)
		if (get_height(p->right->left) > get_height(p->right->right))
			BL(p);
		else
			LL(p);
	if (get_height(p->left) - get_height(p->right) == 2)
		if (get_height(p->left->left) < get_height(p->left->right))
			BR(p);
		else
			LR(p);
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
	(*l)->height = 1 + get_max(*l);
}

void inorder(tree *l, FILE *output_file) {
	if (l != NULL) {
		inorder(l->left, output_file);
		fprintf(output_file, "%d ", l->item);
		inorder(l->right, output_file);
	}
}
