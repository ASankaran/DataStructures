#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
	int key;
	struct Node *rightChild;
	struct Node *leftChild;
	struct Node *parent;
} Node;

typedef struct BinarySearchTree {
	Node *root;
} BinarySearchTree;

void btree_insert(BinarySearchTree *tree, int key);
void btree_insertnode(Node *root, int key);
void btree_preorder(BinarySearchTree *root);
void btree_inorder(BinarySearchTree *root);
void btree_postorder(BinarySearchTree *root);
void btree_preordernode(Node *root);
void btree_inordernode(Node *root);
void btree_postordernode(Node *root);
Node * btree_find(BinarySearchTree *tree, int key);
Node * btree_findnode(Node *root, int key);
Node * btree_findminnode(Node *node);
void btree_remove(BinarySearchTree *tree, int key);
void btree_removenode(Node *node, BinarySearchTree *tree);

void btree_preorder(BinarySearchTree *tree) {
	btree_preordernode(tree->root);
}

void btree_preordernode(Node *root) {
	printf("%i\n", root->key);
	if (root->leftChild != NULL) {
		btree_preordernode(root->leftChild);
	}
	if (root->rightChild != NULL) {
		btree_preordernode(root->rightChild);
	}
}


void btree_inorder(BinarySearchTree *tree) {
	btree_inordernode(tree->root);
}

void btree_inordernode(Node *root) {
	if (root->leftChild != NULL) {
		btree_inordernode(root->leftChild);
	}
	printf("%i\n", root->key);
	if (root->rightChild != NULL) {
		btree_inordernode(root->rightChild);
	}
}


void btree_postorder(BinarySearchTree *tree) {
	btree_postordernode(tree->root);
}

void btree_postordernode(Node *root) {
	if (root->leftChild != NULL) {
		btree_postordernode(root->leftChild);
	}
	if (root->rightChild != NULL) {
		btree_postordernode(root->rightChild);
	}
	printf("%i\n", root->key);
}

void btree_insert(BinarySearchTree *tree, int key) {
	if (tree->root == NULL) {
		Node *node = malloc(sizeof(Node));
		node->parent = NULL;
		node->rightChild = NULL;
		node->leftChild = NULL;
		node->key = key;
		tree->root = node;
	} else {
		btree_insertnode(tree->root, key);
	}
}

void btree_insertnode(Node *root, int key) {
	Node *node = malloc(sizeof(Node));
	if (key < root->key) {
		if (root->leftChild == NULL) {
			node->key = key;
			node->parent = root;
			node->rightChild = NULL;
			node->leftChild = NULL;
			root->leftChild = node;
			return; 
		} else {
			btree_insertnode(root->leftChild, key);
		}
	} else {
		if (root->rightChild == NULL) {
			node->key = key;
			node->parent = root;
			node->rightChild = NULL;
			node->leftChild = NULL;
			root->rightChild = node;
			return;
		} else {
			btree_insertnode(root->rightChild, key);
		}
	}
}

Node * btree_find(BinarySearchTree *tree, int key) {
	return btree_findnode(tree->root, key);
}

Node * btree_findnode(Node *root, int key) {
	if (root->key > key) {
		return btree_findnode(root->leftChild ,key);
	} else if (root->key < key) {
		return btree_findnode(root->rightChild ,key);
	} else {
		return root;
	}
}

void btree_remove(BinarySearchTree *tree, int key) {
	btree_removenode(btree_find(tree, key), tree);
}

void btree_removenode(Node *node, BinarySearchTree *tree) {
	if (node->leftChild == NULL && node->rightChild == NULL) {
		if (node == tree->root) {
			tree->root = NULL;
			return;
		}
		if (node == node->parent->leftChild) {
			node->parent->leftChild = NULL;
		} else {
			node->parent->rightChild = NULL;
		}
	} else if (node->leftChild == NULL || node->rightChild == NULL) {
		if (node == tree->root) {
			tree->root = (node->leftChild == NULL ? node->rightChild : node->leftChild);
			return;
		}
		if (node == node->parent->leftChild) {
			node->parent->leftChild = (node->leftChild == NULL ? node->rightChild : node->leftChild);
		} else {
			node->parent->rightChild = (node->leftChild == NULL ? node->rightChild : node->leftChild);
		}
	} else {
		Node *minnode = btree_findminnode(node->rightChild);
		node->key = minnode->key;
		btree_removenode(minnode, tree);
	}
}

Node * btree_findminnode(Node *node) {
	if (node->leftChild == NULL) {
		return node;
	} else {
		return btree_findminnode(node->leftChild);
	}
}

int main() {
	BinarySearchTree *btree = malloc(sizeof(BinarySearchTree));
	btree->root = NULL;
	btree_insert(btree, 50);
	btree_insert(btree, 40);
	btree_insert(btree, 75);
	btree_insert(btree, 25);
	btree_insert(btree, 45);
	btree_insert(btree, 47);
	btree_insert(btree, 77);
	btree_insert(btree, 46);
	
	btree_preorder(btree);
	printf("-----\n");
	btree_inorder(btree);
	printf("-----\n");
	btree_postorder(btree);
	printf("-----\n");

	btree_remove(btree, 40);

	btree_preorder(btree);
	printf("-----\n");
	btree_inorder(btree);
	printf("-----\n");
	btree_postorder(btree);	
	printf("-----\n");
}
