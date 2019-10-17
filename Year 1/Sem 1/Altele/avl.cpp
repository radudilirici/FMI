#include <stdio.h>
#include <stdlib.h>


struct node
{
	int value;
	node *left, *right;
};

void print_tree(node *p, FILE *g)
{
	if (p == NULL)
		return;
	fprintf(g, "%d ", p->value);
	print_tree(p->left, g);
	print_tree(p->right, g);
}

int height(node *p)
{
	if (p == NULL)
		return 0;
	int l = height(p->left);
	int r = height(p->right);
	if (l > r)
		return l + 1;
	else
		return r + 1;
}

int balance(node *p)
{
	return (height(p->right) - height(p->left));
}

node *parent(node *father, node *p)
{
	if (father == p)
		return NULL;
	if (father->left == p || father->right == p)
		return father;
	if (p->value < father->value)
		return parent(father->left, p);
	else
		return parent(father->right, p);
}

node *rotate_left(node *p, node *r)
{
	p->right = r->left;
	r->left = p;
	return r;
}

node *rotate_right(node *p, node *l)
{
	p->left = l->right;
	l->right = p;
	return l;
}

node *rotate_rightleft(node *p, node *r, node *rl)
{
	r->left = rl->right;
	rl->right = r;
	p->right = rl->left;
	rl->left = p;
	return rl;
}

node *rotate_leftright(node *p, node *l, node *lr)
{
	l->right = lr->left;
	lr->left = l;
	p->left = lr->right;
	lr->right = p;
	return lr;
}

void AVL(node *&father, node *&p)
{
	if (p == NULL)
		return;
	int balance_value = balance(p);
	node *parent_of_p = parent(father, p);
	if (balance_value >= -1 && balance_value <= 1)
	{
		AVL(father, parent_of_p);
		return;
	}

	node *new_p;
	if (balance_value >= 2) //p is right heavy
	{
		if (balance(p->right) >= 1) //rotate left case
			new_p = rotate_left(p, p->right);
		else
			new_p = rotate_rightleft(p, p->right, p->right->left);
	}
	else
	{
		if (balance(p->left) <= -1)
			new_p = rotate_right(p, p->left);
		else
			new_p = rotate_leftright(p, p->left, p->left->right);
	}

	if (parent_of_p == NULL)
	{
		father = new_p;
		return;
	}
	if (balance_value >= 2)
	{
		parent_of_p->right = new_p;
		return;
	}
	parent_of_p->left = new_p;
	return;
}

void add_in_tree(node *&father, node *&p, int value_to_add)
{
	if (p == NULL)
	{
		p = new node;
		p->value = value_to_add;
		p->left = NULL;
		p->right = NULL;
		return;
	}

	if (value_to_add < p->value)
	{
		if (p->left == NULL)
		{
			node *aux = new node;
			aux->value = value_to_add;
			aux->left = NULL;
			aux->right = NULL;
			p->left = aux;
			AVL(father, aux);
			return;
		}
		add_in_tree(father, p->left, value_to_add);
	}
	else if (value_to_add > p->value)
	{
		if (p->right == NULL)
		{
			node *aux = new node;
			aux->value = value_to_add;
			aux->left = NULL;
			aux->right = NULL;
			p->right = aux;
			AVL(father, aux);
			return;
		}
		add_in_tree(father, p->right, value_to_add);
	}
}

int main()
{
	FILE *f, *g;
	f = fopen("avl.in", "r");
	g = fopen("avl.out", "w");

	int n, i, value_to_add;
	node *father=NULL;

	fscanf(f, "%d", &n);
	for (i=1; i<=n; i++)
	{
		fscanf(f, "%d", &value_to_add);
		add_in_tree(father, father, value_to_add);
	}

	print_tree(father, g);

	printf("%d", father->value);
	//nod *p = (nod*) malloc(sizeof(nod));
	fclose(f);
	fclose(g);
	return 0;
}
