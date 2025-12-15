#include <stdio.h>

void merge_sort(int array[], int size);

void _merge_sort_recursion(int array[], int start, int end);

void _merge_sorted_arrays(int array[], int start, int middle, int end);

int main(int argc, char const *argv[])
{

    int array[7] = {1, 9, 3, 2, 1 , 2, 5};

    for(int i = 0; i< 7; i++){
        printf("element %d, %d \n",i, array[i]);
    }

    merge_sort(array, 7);

    for(int i = 0; i< 7; i++){
        printf("element %d, %d \n",i, array[i]);
    }

    return 0;
}

void merge_sort(int array[], int size)
{
    _merge_sort_recursion(array, 0, size - 1);
}

void _merge_sort_recursion(int array[], int start, int end)
{
    if (start < end)
    {
        int middle = start + (end - start) / 2;
        _merge_sort_recursion(array, start, middle);
        _merge_sort_recursion(array, middle + 1, end);
        _merge_sorted_arrays(array, start, middle, end);
    }
}

void _merge_sorted_arrays(int array[], int start, int middle, int end)
{
    int left_lenght = middle - start + 1;
    int right_lenght = end - middle;
    int temp_left[left_lenght];
    int temp_right[right_lenght];
    int i,j,k;
    for (int i = 0; i < left_lenght; i++)
    {
        temp_left[i] = array[start + i];
    }
    for (int i = 0; i < right_lenght; i++)
    {
        temp_right[i] = array[middle + 1 + i];
    }
    for (int i = 0, j = 0, k = start; k <= end; k++)
    {
        if ((i < left_lenght) && ((j >= right_lenght) || (temp_left[i] <= temp_right[j])))
        {
            array[k] = temp_left[i];
            i++;
        }
        else
        {
            array[k] = temp_right[j];
            j++;
        }
    }
}
