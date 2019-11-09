#include "array_operations.hh"



int greatest_v1(int* itemptr, int size) {
    int greatest = *itemptr;
    itemptr++;
    for (int i = 1; i < size; i++) {
        if (*(itemptr) > greatest) {
            greatest = *(itemptr);
        }

        itemptr++;
    }

    return greatest;
}

int greatest_v2(int* itemptr, int* endptr) {

    int greatest = *itemptr;
    while (itemptr < endptr) {
        if (*itemptr > greatest) {
            greatest = *itemptr;

        }
        itemptr++;
    }

    return greatest;
}

void copy(int* itemptr, int* endptr, int* targetptr) {
    int i = 0;
    while (itemptr < endptr) {
        *(targetptr+i) = *itemptr;

        i++;
        itemptr++;
    }
}

void reverse(int* leftptr, int* rightptr) {

    while(leftptr < rightptr) {
        int temp = *leftptr;
        *leftptr = *(rightptr-1);
        *(rightptr-1) = temp;

        leftptr++;
        rightptr--;
    }
}
