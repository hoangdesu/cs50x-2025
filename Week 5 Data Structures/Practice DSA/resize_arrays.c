#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int *nums = malloc(sizeof(int) * 3);

    // nums is the pointer to the first element of the array, not the whole array itself
    printf("sizeof nums: %lu\n", sizeof(nums)); // size of pointer is 8 bytes
    printf("Address of nums: %p\n", nums);

    if (nums == NULL)
    {
        printf("Error allocating memory for nums list\n");
        return 1;
    }

    nums[0] = 1;
    nums[1] = 2;
    nums[2] = 3;

    // Suppose we want to grow the list's size to 4 elements
    int *tmp = malloc(sizeof(int) * 4);
    if (tmp == NULL)
    {
        printf("Error allocating memory for tmp list\n");
        free(nums); // very subtle, but we ALWAYS have to free memory created by ourselves to avoid memory leak
        return 1;
    }

    printf("Address of tmp: %p\n", tmp);

    // Copy over the values
    for (int i = 0; i < 3; i++)
    {
        tmp[i] = nums[i];
    }

    // Add new value 
    tmp[3] = 4;

    // Free up the memory blocks that nums points at
    free(nums);

    // We dont wanna use tmp for the list name, instead it's better to refer to the new list as nums
    // - essentially these 2 pointers are pointing to the same list
    nums = tmp;

    // Potentially also remove tmp pointer to avoid confusion
    tmp = NULL;

    for (int i = 0; i < 4; i++)
    {
        printf("nums[%d] = %d\n", i, nums[i]);
    }
    

    // Using realloc to resize the nums list to be of size 5
    int *tmp2 = realloc(nums, sizeof(int) * 5);
    if (tmp2 == NULL)
    {
        printf("Error allocating memory for tmp2 list\n");
        free(nums); 
        return 1;
    }

    
    // - notice that the new memory address of tmp2 could be the same as nums
    // - realloc will try to keep the array at the same place if possible => optimized performance
    printf("&nums = %p | &tmp2: %p\n", nums, tmp2);

    // Address is not guaranteed to always be the same
    // Point the nums to the tmp2
    nums = tmp2;
    nums[4] = 5;

    for (int i = 0; i < 5; i++)
    {
        printf("nums[%d] = %d\n", i, nums[i]);
    }

    // Free up all memory that is dynamically allocated
    free(nums);

    return 0;
}