//
//  main.cpp
//  BinaryHeap
//

#include <iostream>
#include <vector>

using namespace std;

class BinaryHeap {
public:
    vector<int> heap;
    
    void insert(int element) {
        heap.push_back(element);
        if (heap.size() > 1) {
            // up-heap
            int index = (int)heap.size()-1;
            int parentIndex = (index-1)/2;
            while (parentIndex < index && heap.at(index) > heap.at(parentIndex)) {
                int t = heap.at(index);
                heap.at(index) = heap.at(parentIndex);
                heap.at(parentIndex) = t;
                index = parentIndex;
                parentIndex = (index-1)/2;
            }
        }
    }
    
    int remove() { // removes root
        if (heap.size() == 0)
            throw "empty heap";
        
        if (heap.size() == 1) { // no need to heap-down
            int value = heap.at(0);
            heap.erase(heap.begin());
            return value;
        }
        
        int r = heap.at(0); // to be returned after heap-down
        
        // heap-down
        int last = heap.at(heap.size()-1);
        heap.at(0) = last;
        heap.pop_back(); // heap shrinks
        
        int index = 0;
        int indexLeft = 2*index+1; // index of left child
        int indexRight = 2*index+2; // index of right child
        int indexMax = indexLeft; // if we get here, root has at least one left child
        if (indexRight < heap.size() && heap.at(indexRight) > heap.at(indexLeft))
            indexMax = indexRight;
        
        while (indexLeft < heap.size() && heap.at(index) < heap.at(indexMax)) {
            // swap
            int t = heap.at(indexMax);
            heap.at(indexMax) = heap.at(index);
            heap.at(index) = t;
            
            index = indexMax;
            indexLeft = 2*index+1;
            indexRight = 2*index+2;
            indexMax = indexLeft;
            if (indexRight < heap.size() && heap.at(indexRight) > heap.at(indexLeft))
                indexMax = indexRight;
        }
        
        return r;
    }
};

int main(int argc, const char * argv[]) {
    
    int numbers[13] = {2, 1, 3, 5, 7, 7, 9, 2, 4, 6, 8, 0, 0};

    BinaryHeap * bh = new BinaryHeap();
    
    for (int n : numbers) {
        bh->insert(n);
    }
    
    cout << "breadth-first traversal" << endl;
    for (int n : bh->heap) {
        cout << n << " ";
    }
    cout << endl;
    
    cout << "removing all elements, one by one" << endl;
    for (int i = 0; i < 15; i++) {
        try {
            cout << bh->remove() << " ";
        } catch (const char * msg) {
            cout << "_" << " ";
        }
    }
    cout << endl;
    
    delete bh;
    
    return 0;
}
