#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

void swap(int *x, int *y)
{
    int temp = *x;
    *x = *y;
    *y = temp;
}

int parent(int i)
{
    return (i-1)/2;
}

int left(int i)
{
    return (2*i + 1);
}

int right(int i)
{
    return (2*i + 2);
}

void insertKey(int *heap, int k, int *heap_size, int capacity)
{
    if (*heap_size == capacity)
    {
        printf("\nOverflow: Could not insertKey\n");
        return;
    }

    *heap_size += 1;
    int i = *heap_size - 1;
    heap[i] = k;

    while (i != 0 && heap[parent(i)] > heap[i])
    {
       swap(&heap[i], &heap[parent(i)]);
       i = parent(i);
    }
}

void MinHeapify(int *heap, int i, int *heap_size)
{
    int l = left(i);
    int r = right(i);
    int smallest = i;
    if (l < *heap_size && heap[l] < heap[i])
        smallest = l;
    if (r < *heap_size && heap[r] < heap[smallest])
        smallest = r;
    if (smallest != i)
    {
        swap(&heap[i], &heap[smallest]);
        MinHeapify(heap, smallest, heap_size);
    }
}

int verifyValue(int val, int *heap, int heap_size, int *position)
{
    int i;
    for(i = 0; i < heap_size; i++)
    {
        if(val == heap[i])
        {
            *position = i;
            return 1;
        }
    }
    return 0;
}

int extractMin(int *heap, int *heap_size)
{
    int root;
    if (*heap_size <= 0)
        return INT_MAX;
    if (*heap_size == 1)
    {
        *heap_size -= 1;
        return heap[0];
    }

    root = heap[0];
    heap[0] = heap[*heap_size - 1];
    *heap_size -= 1;
    MinHeapify(heap, 0, heap_size);

    return root;
}

void decreaseKey(int *heap, int i, int new_val)
{
    heap[i] = new_val;
    while (i != 0 && heap[parent(i)] > heap[i])
    {
       swap(&heap[i], &heap[parent(i)]);
       i = parent(i);
    }
}

void deleteKey(int *heap, int i, int *heap_size)
{
    decreaseKey(heap, i, INT_MIN);
    extractMin(heap, heap_size);
}

int main()
{
    int *heap;
    int heap_size = 0;
    int capacity;
    int i;
    int j;
    int val;
    int position = -1;
    int del;
    printf("Insert the capacity of the heap: ");
    scanf("%d", &capacity);

    heap =(int *) malloc(capacity * sizeof(int));


    for(i = 0; i < capacity; i++)
    {
        printf("Insert a value: ");
        scanf("%d", &j);
        insertKey(heap, j, &heap_size, capacity);
    }

    printf("Insert the value you want to search: ");
    scanf("%d", &val);
    if(verifyValue(val, heap, heap_size, &position))
    {
        printf("Yes, the value is in min heap!\n");
    }
    else
    {
        printf("No, the value isn't in min heap!\n");
    }
    for(i = 0; i < heap_size; i++)
    {
        printf("%d ", heap[i]);
    }
    printf("\nInsert the value you want to delete: ");
    scanf("%d", &del);
    if(verifyValue(del, heap, heap_size, &position))
    {
        deleteKey(heap, position, &heap_size);
    }
    else
    {
        printf("The value isn't in min heap!\n");
    }

    for(i = 0; i < heap_size; i++)
    {
        printf("%d ", heap[i]);
    }
    return 0;
}
