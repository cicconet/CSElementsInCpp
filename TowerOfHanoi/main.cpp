//
//  main.cpp
//  TowerOfHanoi
//

#include <iostream>

typedef struct Node {
    Node * next = NULL;
    int data;
    Node(int theData) { data = theData; }
} Node;

class Stack {
public:
    Node * top;
    
    ~Stack () {
        Node * n = pop();
        while (n != NULL) {
            delete n;
            n = pop();
        }
    }
    
    void print() {
        Node * n = top;
        while (n != NULL) {
            printf("%d\t", n->data);
            n = n->next;
        }
        printf("\n");
    }
    
    Node * pop() { // returned node must be deleted outside
        Node * r = NULL;
        if (top != NULL) {
            r = top;
            top = top->next;
        }
        return r;
    }
    
    void push(int theData) {
        Node * n = new Node(theData);
        n->next = top;
        top = n;
    }
};

class TowerOfHanoi {
public:
    Stack * s1 = new Stack();
    Stack * s2 = new Stack();
    Stack * s3 = new Stack();
    Stack * ss[3] = {s1, s2, s3};
    
    ~TowerOfHanoi() {
        for (int i = 0; i < 3; i++) {
            delete ss[i];
        }
    }
    
    void move1(int iOrig, int iDest) {
        Node * topOrig = ss[iOrig]->pop();
        ss[iDest]->push(topOrig->data);
        delete topOrig;
    }
    
    void move2(int iOrig, int iDest, int iTemp) {
        Node * topOrig = ss[iOrig]->pop();
        ss[iTemp]->push(topOrig->data);
        delete topOrig;
        topOrig = ss[iOrig]->pop();
        ss[iDest]->push(topOrig->data);
        delete topOrig;
        Node * topTemp = ss[iTemp]->pop();
        ss[iDest]->push(topTemp->data);
        delete topTemp;
    }
    
    void moveN(int n) {
        moveN(n, 0, 2, 1);
    }
    
    void moveN(int n, int iOrig, int iDest, int iTemp) {
        if (n == 1) {
            move1(iOrig,iDest);
        } else if (n == 2) {
            move2(iOrig,iDest,iTemp);
        } else {
            moveN(n-1, iOrig, iTemp, iDest);
            Node * topOrig = ss[iOrig]->pop();
            ss[iDest]->push(topOrig->data);
            delete topOrig;
            moveN(n-1, iTemp, iDest, iOrig);
        }
    }
};

int main(int argc, const char * argv[]) {

    TowerOfHanoi * TN = new TowerOfHanoi();
    
    int n = 25; // number of discs initially at first tower
    for (int i = 0; i < n; i++) {
        TN->ss[0]->push(n-i);
    }
    
    printf("before\n");
    printf("s1:\t"); TN->ss[0]->print();
    printf("s2:\t"); TN->ss[1]->print();
    printf("s3:\t"); TN->ss[2]->print();
    
    TN->moveN(n);
    
    printf("after\n");
    printf("s1:\t"); TN->ss[0]->print();
    printf("s2:\t"); TN->ss[1]->print();
    printf("s3:\t"); TN->ss[2]->print();
    
    delete TN;
    
    return 0;
}
