//
//  main.cpp
//  BinarySearchTree
//
//  non-duplicate keys
//  any left-child subtree node < parent < any right-child subtree node
//

#include <iostream>

using namespace std;

typedef struct BinaryNode {
    int key;
    BinaryNode * left = NULL;
    BinaryNode * right = NULL;
    BinaryNode * parent = NULL;
    BinaryNode(int theKey) {
        key = theKey;
    }
} BinaryNode;

class BinarySearchTree {
public:
    BinaryNode * root = NULL;
    
    ~BinarySearchTree() {
        while (root != NULL) {
            remove(root->key);
        }
    }
    
    // out = null if the tree is empty
    // out = node if key matches
    // out = potential parent if key doesn't match (convenient for insertion)
    BinaryNode * search(int k) {
        if (root == NULL) {
            return NULL;
        }
        BinaryNode * u = root;
        while (k != u->key) {
            if (k < u->key) {
                if (u->left == NULL) {
                    return u;
                } else {
                    u = u->left;
                }
            } else {
                if (u->right == NULL) {
                    return u;
                } else {
                    u = u->right;
                }
            }
        }
        return u;
    }
    
    // adds a new key to the tree (if possible)
    // returns success of failure
    bool add(int k){
        if (root == NULL) {
            root = new BinaryNode(k);
            return true;
        }
        BinaryNode * u = search(k);
        if (k == u->key) { // element exists; do not add
            return false;
        }
        if (k < u->key) {
            BinaryNode * v = new BinaryNode(k);
            v->parent = u;
            u->left = v;
        } else {
            BinaryNode * v = new BinaryNode(k);
            v->parent = u;
            u->right = v;
        }
        return true;
    }
    
    // deletes leaf node, or node that has one child
    // used in general remove() method
    void cut(BinaryNode * v) {
        BinaryNode * childOfV = NULL;
        
        if (v->left != NULL) childOfV = v->left;
        if (v->right != NULL) childOfV = v->right;
        if (v->parent != NULL) {
            if (v->parent->left == v) { // v is a left child
                v->parent->left = childOfV;
            } else { // v is right child
                v->parent->right = childOfV;
            }
            if (childOfV != NULL) {
                childOfV->parent = v->parent;
            }
            delete v;
        } else { // deleting root
            if (childOfV == NULL) {
                delete root;
                root = NULL;
            } else {
                BinaryNode * tmp = root;
                root = childOfV;
                root->parent = NULL;
                delete tmp;
            }
        }
    }
    
    // out = node of minimum key in subtree
    // used in general remove() method
    BinaryNode * min(BinaryNode * node) {
        BinaryNode * out = node;
        while (out->left != NULL) {
            out = out->left;
        }
        return out;
    }
    
    // removes node from tree (if possible)
    // returns success of failure
    bool remove(int k) {
        BinaryNode * u = search(k);
        if (u == NULL || u->key != k) return false;
        BinaryNode * nodeToCut = u;
        if (u->left != NULL && u->right != NULL) { // tricky case
            nodeToCut = min(u->right);
            u->key = nodeToCut->key; // save nodeToCut's key in u
        }
        cut(nodeToCut);
        return true;
    }
    
    void inorder(BinaryNode * u){
        if (u == NULL) return;
        inorder(u->left);
        printf(" %d", u->key);
        inorder(u->right);
    }
    
    void preorder(BinaryNode * u){
        if (u == NULL) return;
        printf(" %d", u->key);
        preorder(u->left);
        preorder(u->right);
    }
    
    void postorder(BinaryNode * u){
        if (u == NULL) return;
        postorder(u->left);
        postorder(u->right);
        printf(" %d", u->key);
    }
    
    // in-order traversal
    void inorder(){
        inorder(root);
        printf("\n");
    }
    
    // pre-order traversal
    void preorder(){
        preorder(root);
        printf("\n");
    }
    
    // post-order traversal
    void postorder(){
        postorder(root);
        printf("\n");
    }
};

int main(int argc, const char * argv[]) {
    int keys[13] = {5, 3, 7, 2, 4, 6, 8, 1, 9, 0, 0, 0, 5};
    
    BinarySearchTree * bst = new BinarySearchTree();
    for (int n : keys)
        bst->add(n);
    
    printf("in-order traversal:\n");
    bst->inorder();
    
    printf("pre-order traversal:\n");
    bst->preorder();
    
    printf("post-order traversal:\n");
    bst->postorder();
    
    printf("removing 3, 2, 6, 1...\n");
    bst->remove(3);
    bst->remove(2);
    bst->remove(6);
    bst->remove(1);
    
    printf("new in-order traversal:\n");
    bst->inorder();
    
    delete bst;
    
    return 0;
}
