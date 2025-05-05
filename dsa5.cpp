#include <iostream>
using namespace std;

struct Node {
int data;
Node* left;
Node* right;
bool rightThread;

Node(int val) {
data = val;
left = right = nullptr;
rightThread = false;
}
};

Node* insert(Node* root, int key) {
if (!root) return new Node(key);
Node* curr = root;
while (true) {
if (key < curr->data) {
if (!curr->left) {
curr->left = new Node(key);
break;
}
curr = curr->left;
} else {
if (!curr->right) {
curr->right = new Node(key);
break;
}
curr = curr->right;
}
}
return root;
}

void convertToThreadedBinaryTree(Node* root, Node*& prev) {
if (!root) return;
convertToThreadedBinaryTree(root->left, prev);
if (prev && !prev->right) {
prev->right = root;
prev->rightThread = true;
}
prev = root;
convertToThreadedBinaryTree(root->right, prev);
}

void convertToThreadedBinaryTree(Node* root) {
Node* prev = nullptr;
convertToThreadedBinaryTree(root, prev);
}

void inorder(Node* root) {
Node* curr = root;
while (curr && curr->left)
curr = curr->left;
while (curr) {
cout << curr->data << " ";
if (curr->rightThread) {
curr = curr->right;
} else {
curr = curr->right;
while (curr && curr->left)
curr = curr->left;
}
}
cout << endl;
}

int main() {
Node* root = nullptr;
root = insert(root, 45);
root = insert(root, 20);
root = insert(root, 65);
root = insert(root, 15);
root = insert(root, 35);
root = insert(root, 50);
root = insert(root, 85);
convertToThreadedBinaryTree(root);
cout << "Inorder Traversal of Threaded Binary Tree: ";
inorder(root);
return 0;
}
