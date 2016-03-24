//
//  main.cpp
//  QuickSort
//

#include <iostream>

void split(int * A, int i0, int i1) {
    if (i0 < i1) {
        int pivot = A[i1];
        int wall = i0; // everyone to the left is <= pivot
        for (int j = i0; j < i1; j++) {
            if (A[j] <= pivot) {
                int vWall = A[wall];
                A[wall] = A[j];
                A[j] = vWall;
                wall++;
            }
        }
        int vWall = A[wall];
        A[wall] = pivot;
        A[i1] = vWall;
        split(A,i0,wall-1);
        split(A,wall+1,i1);
    }
}

static void quickSort(int * A, int lengthA) {
    split(A, 0, lengthA-1);
}

int main(int argc, const char * argv[]) {

    int A[8] = {3, 2, 8, 9, 0, 1, 2, 2};
    
    quickSort(A, 8);
    
    for (int i : A) {
        printf("%d\t", i);
    }
    printf("\n");
    
    return 0;
}
