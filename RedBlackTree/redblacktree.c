#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

typedef enum Color {
	RED,
	BLACK
} Color;

typedef struct Node {
	int key;
	Color color;
	struct Node *rightChild;
	struct Node *leftChild;
	struct Node *parent;
} Node;

typedef struct RedBlackTree {
	Node *root;
} RedBlackTree;

void rbtree_insert(RedBlackTree *tree, int key);
void rbtree_insertnode(Node *root, int key, RedBlackTree *tree);
void rbtree_insertfix(Node *node, RedBlackTree *tree);
void rbtree_preorder(RedBlackTree *root);
void rbtree_inorder(RedBlackTree *root);
void rbtree_postorder(RedBlackTree *root);
void rbtree_preordernode(Node *root);
void rbtree_inordernode(Node *root);
void rbtree_postordernode(Node *root);
void rbtree_rotateright(Node *node, RedBlackTree *tree);
void rbtree_rotateleft(Node *node, RedBlackTree *tree);
Node * rbtree_find(RedBlackTree *tree, int key);
Node * rbtree_findnode(Node *root, int key);
Node * rbtree_findminnode(Node *node);
void rbtree_remove(RedBlackTree *tree, int key);
void rbtree_removenode(Node *node, RedBlackTree *tree, Node *sibling);
void rbtree_removefix(Node *node, Node *sibling, RedBlackTree *tree);

void rbtree_preorder(RedBlackTree *tree) {
	rbtree_preordernode(tree->root);
}

void rbtree_preordernode(Node *root) {
	printf("%i\n", root->key);
	if (root->leftChild != NULL) {
		rbtree_preordernode(root->leftChild);
	}
	if (root->rightChild != NULL) {
		rbtree_preordernode(root->rightChild);
	}
}


void rbtree_inorder(RedBlackTree *tree) {
	rbtree_inordernode(tree->root);
}

void rbtree_inordernode(Node *root) {
	if (root->leftChild != NULL) {
		rbtree_inordernode(root->leftChild);
	}
	printf("%i\n", root->key);
	if (root->rightChild != NULL) {
		rbtree_inordernode(root->rightChild);
	}
}


void rbtree_postorder(RedBlackTree *tree) {
	rbtree_postordernode(tree->root);
}

void rbtree_postordernode(Node *root) {
	if (root->leftChild != NULL) {
		rbtree_postordernode(root->leftChild);
	}
	if (root->rightChild != NULL) {
		rbtree_postordernode(root->rightChild);
	}
	printf("%i\n", root->key);
}

void rbtree_insert(RedBlackTree *tree, int key) {
	if (tree->root == NULL) {
		Node *node = malloc(sizeof(Node));
		node->parent = NULL;
		node->rightChild = NULL;
		node->leftChild = NULL;
		node->key = key;
		node->color = BLACK;
		tree->root = node;
	} else {
		rbtree_insertnode(tree->root, key, tree);
	}
}

void rbtree_insertnode(Node *root, int key, RedBlackTree *tree) {
	Node *node = malloc(sizeof(Node));
	if (key < root->key) {
		if (root->leftChild == NULL) {
			node->key = key;
			node->parent = root;
			node->color = RED;
			node->rightChild = NULL;
			node->leftChild = NULL;
			root->leftChild = node;
			rbtree_insertfix(node, tree);
			return; 
		} else {
			rbtree_insertnode(root->leftChild, key, tree);
		}
	} else {
		if (root->rightChild == NULL) {
			node->key = key;
			node->parent = root;
			node->color = RED;
			node->rightChild = NULL;
			node->leftChild = NULL;
			root->rightChild = node;
			rbtree_insertfix(node, tree);
			return;
		} else {
			rbtree_insertnode(root->rightChild, key, tree);
		}
	}
}

void rbtree_insertfix(Node *node, RedBlackTree *tree) {
	if (node->parent == NULL) {
		node->color = BLACK;
		return;
	}
	if (node->parent->color == BLACK) {
		return;
	}
	if (node->parent->color == RED && (node->parent->parent->leftChild == node->parent ? node->parent->parent->rightChild : node->parent->parent->leftChild) != NULL &&
		                          (node->parent->parent->leftChild == node->parent ? node->parent->parent->rightChild : node->parent->parent->leftChild)->color == RED) {
		node->parent->color = BLACK;
		(node->parent->parent->leftChild == node->parent ? node->parent->parent->rightChild : node->parent->parent->leftChild)->color = BLACK;
		node->parent->parent->color = RED;
		rbtree_insertfix(node->parent->parent, tree);
		return;
	}
	if (node == node->parent->rightChild && node->parent == node->parent->parent->leftChild) {
		rbtree_rotateleft(node->parent, tree);
		node = node->leftChild;
	} else if (node == node->parent->leftChild && node->parent == node->parent->parent->rightChild) {
		rbtree_rotateright(node->parent, tree);
		node = node->rightChild;
	}
	node->parent->color = BLACK;
	node->parent->parent->color = RED;
	if (node == node->parent->leftChild) {
		rbtree_rotateright(node->parent->parent, tree);
	} else {
		rbtree_rotateleft(node->parent->parent, tree);
	}
}

void rbtree_rotateright(Node *node, RedBlackTree *tree) {
	Node *child = node->leftChild;
	node->leftChild = child->rightChild;
	if (child->rightChild != NULL) {
		child->rightChild->parent = node;
	}
	child->parent = node->parent;
	if (node->parent == NULL) {
		tree->root = child;
	} else if (node == node->parent->rightChild) {
		node->parent->rightChild = child;
	} else {
		node->parent->leftChild = child;
	}
	child->rightChild = node;
	node->parent = child;
}

void rbtree_rotateleft(Node *node, RedBlackTree *tree) {
	Node *child = node->rightChild;
	node->rightChild = child->leftChild;
	if (child->leftChild != NULL) {
		child->leftChild->parent = node;
	}
	child->parent = node->parent;
	if (node->parent == NULL) {
		tree->root = child;
	} else if (node == node->parent->leftChild) {
		node->parent->leftChild = child;
	} else {
		node->parent->rightChild = child;
	}
	child->leftChild = node;
	node->parent = child;
}

Node * rbtree_find(RedBlackTree *tree, int key) {
	return rbtree_findnode(tree->root, key);
}

Node * rbtree_findnode(Node *root, int key) {
	if (root->key > key) {
		return rbtree_findnode(root->leftChild ,key);
	} else if (root->key < key) {
		return rbtree_findnode(root->rightChild ,key);
	} else {
		return root;
	}
}

void rbtree_remove(RedBlackTree *tree, int key) {
	rbtree_removenode(rbtree_find(tree, key), tree, NULL);
}

void rbtree_removenode(Node *node, RedBlackTree *tree, Node *sibling) {
	if (sibling == NULL) {
		sibling = (node == node->parent->leftChild ? node->parent->rightChild : node->parent->leftChild);
	}
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
		rbtree_removefix(node, sibling, tree);
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
		rbtree_removefix(node, sibling, tree);
	} else {
		Node *minnode = rbtree_findminnode(node->rightChild);
		node->key = minnode->key;
		rbtree_removenode(minnode, tree, sibling);
	}
}

void rbtree_removefix(Node *node, Node *sibling, RedBlackTree *tree) {
	if ((node->leftChild != NULL && node->leftChild->color == RED) || (node->rightChild != NULL && node->rightChild->color == RED)) {
		(node->leftChild == NULL ? node->rightChild : node->leftChild)->color = BLACK;
	} else {
		if (sibling->color == BLACK) {
			if ((sibling->leftChild != NULL && sibling->leftChild->color == RED) || (sibling->rightChild != NULL && sibling->rightChild->color == RED)) {
				if (sibling == sibling->parent->leftChild) {
					if (sibling->leftChild != NULL && sibling->leftChild->color == RED) {
						rbtree_rotateright(sibling->parent, tree);
					} else {
						Node *parent = sibling->parent;
						rbtree_rotateleft(sibling, tree);
						rbtree_rotateright(parent, tree);
					}
				} else {
					if (sibling->rightChild != NULL && sibling->rightChild->color == RED) {
						rbtree_rotateleft(sibling->parent, tree);
					} else {
						Node *parent = sibling->parent;
						rbtree_rotateright(sibling, tree);
						rbtree_rotateleft(parent, tree);
					}
				}
			} else {
				sibling->color == RED;
				if (sibling->parent->color == BLACK) {
					rbtree_removefix(sibling->parent, sibling == sibling->parent->leftChild ? sibling->parent->rightChild : sibling->parent->leftChild, tree);
				}
			}
		} else {
			sibling->color = BLACK;
			sibling->parent->color = RED;
			Node *parent = sibling->parent;
			Node *sucessor = (sibling == sibling->parent->leftChild ? sibling->parent->rightChild : sibling->parent->leftChild);
			if (sibling == sibling->parent->leftChild) {
				rbtree_rotateright(sibling->parent, tree);
			} else {
				rbtree_rotateleft(sibling->parent, tree);
			}
			rbtree_preorder(tree);
			rbtree_removefix(node, sucessor == parent->leftChild ? parent->rightChild : parent->leftChild, tree);
		}
	}
}

Node * rbtree_findminnode(Node *node) {
	if (node->leftChild == NULL) {
		return node;
	} else {
		return rbtree_findminnode(node->leftChild);
	}
}

int main() {
	RedBlackTree *rbtree = malloc(sizeof(RedBlackTree));
	rbtree->root = NULL;
	rbtree_insert(rbtree, 50);
	rbtree_insert(rbtree, 40);
	rbtree_insert(rbtree, 75);
	rbtree_insert(rbtree, 25);
	rbtree_insert(rbtree, 45);
	rbtree_insert(rbtree, 47);
	rbtree_insert(rbtree, 77);
	rbtree_insert(rbtree, 46);
	
	rbtree_preorder(rbtree);
	printf("-----\n");
	rbtree_inorder(rbtree);
	printf("-----\n");
	rbtree_postorder(rbtree);
	printf("-----\n");

	rbtree_remove(rbtree, 46);

	rbtree_preorder(rbtree);
	printf("-----\n");
	rbtree_inorder(rbtree);
	printf("-----\n");
	rbtree_postorder(rbtree);	
	printf("-----\n");
}
