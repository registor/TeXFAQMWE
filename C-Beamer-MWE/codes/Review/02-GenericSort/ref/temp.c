#include <stdio.h>
#include <malloc.h>
#define SIZE 10
int cmp(void* elm1, void* elm2);
void insertionSort(void* arr, int size);

int main()
{
    int arr[] = {5, 8, 2, 3, 15, 7, 4, 9, 20, 13};
    int arr2[] =  {1};
    int i;
    for (i = 0; i < SIZE; i++)
        printf("%d ", arr[i]);
    printf("\n");
    insertionSort(&arr, SIZE);
    for (i = 0; i < SIZE; i++)
        printf("%d ", arr[i]);
    return 0;
}

void insertionSort(void** arr, int size)
{
    int i = 1;
    int j;
    void* temp;
    while (i < size)
    {
        if (cmp(arr[i], arr[i-1]) == -1)
        {
            temp = arr[i];
            j = i - 1;
            while (j >= 0 && cmp(arr[j], temp) == 1)
            {
                arr[j + 1] = arr[j];
                j--;
            }
            arr[j + 1] = temp;
        }
        i++;
    }
}

int cmp(void* elm1, void* elm2)
{
    if ((int)elm1 == (int)elm2)
        return 0;
    else if ((int)elm1 > (int)elm2)
        return 1;
    else 
        return -1;
}


#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "inssort.h"
 
void inssort (void *base, size_t nelem, size_t size,
               int (*compar) (void *, void *))
{
   //int i, j;
 
    
   for ( size_t i = 1 ; i <= nelem; i++ )
   {
      //size_t offset = size * i;
      void *element = (char *) base + i * size;
      //void *element2 = (char *) base + (i-1) * size;
    
      //(void) printf("element: %c  element2: %c\n", *(char*)element, *(char*)element2); 
       
      //double *value = (double *) element;
      //double *value2 = (double *) element2;
      //printf("e1: %s  e2: %s\n", element, element2);
        
      int slot = i;
      //void *key = malloc ( 200);
      //memcpy( key, element, ((i+1)*size) - (i*size) );
       
      void *key =  element;
       
      //Move all values smaller than key up one position
      for ( ; slot > 0; --slot )
      {
         void *ele1 = (char *) base + slot * size;
         void *ele2 = (char *) base + (slot-1) * size;
       
         int cmp = (*compar)(ele1, ele2);
          
         if ( cmp > 0)
            break;
             
         ele1 = ele2;
 
      }
       
      element = key;
   }
   //free ( key);
}   
 
int numcmp( void *s1, void *s2)
{
   double *no1 = (double *) s1;
   double *no2 = (double *) s2;
    
   //(void) printf("v1: %lg   v2: %lg
", *no1, *no2);
    
   if ( *no1 < *no2 )
      return -1;
   else if ( *no1 > *no2 )
      return 1;
   else
      return 0;
}


/* C implementation QuickSort */

#include<stdio.h>

int cmp(const void *c1, const void *c2)

{

int a = *(const int*)c1;

int b = *(const int*)c2;

if (a > b) return 1;

if (a < b) return -1;

return 0;

}

 

void swap(void *c1, void *c2)

{

int c = *(int*)c1;

*(int*)c1 = *(int*)c2;

*(int*)c2 = c;

}

 

 

/* This function takes last element as pivot, places

the pivot element at its correct position in sorted

array, and places all smaller (smaller than pivot)

to left of pivot and all greater elements to right

of pivot */

int partition (void * arr,int size , int low, int high)

{

int pivot = high; // pivot

int i = (low – 1); // Index of smaller element

 

for (int j = low; j <= high- 1; j++)

{

// If current element is smaller than or

// equal to pivot

//if (arr[j] <= pivot)

if (cmp((char*)arr + pivot * size, (char*)arr + j * size) > 0)

{

i++; // increment index of smaller element

//swap(&arr[i], &arr[j]);

swap((char*)arr + i * size, (char*)arr + j * size);

}

}

//swap(&arr[i + 1], &arr[high]);

swap((char*)arr + (i+1) * size, (char*)arr + high * size);

return (i + 1);

}

 

/* The main function that implements QuickSort

arr[] –> Array to be sorted,

low –> Starting index,

high –> Ending index */

void quickSort(void * arr,int size , int low, int high)

{

if (low < high)

{

/* pi is partitioning index, arr[p] is now

at right place */

int pi = partition(arr, size, low, high);

 

// Separately sort elements before

// partition and after partition

quickSort(arr, size,low, pi – 1);

quickSort(arr, size ,pi + 1, high);

}

}

 

/* Function to print an array */

void printArray(int arr[], int size)

{

int i;

for (i=0; i < size; i++)

printf(“%d “, arr[i]);

printf(“\n”);

}

 

// Driver program to test above functions

int main()

{

int arr[] = {10, 7, 8, 9, 1, 5};

int n = sizeof(arr)/sizeof(arr[0]);

quickSort(arr, 4,0, n-1);

printf(“Sorted array: \n”);

printArray(arr, n);

return 0;

}
