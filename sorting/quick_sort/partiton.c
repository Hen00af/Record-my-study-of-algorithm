#include <stdio.h>
#include <stdlib.h>

void swap(int *a,int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

//pivotよりも小さい値を左側に、大きい値を右側に分ける
//これのみではソートは完了しない
void partition(int a[],int n)
{
    int i;
    int pl = 0;
    int pr = n - 1;
    int pivot = a[n / 2];
    while(pl <= pr)
    {
        while(a[pl] < pivot) pl++;
        while(a[pr] > pivot) pr--;
        if(pl <= pr)
        {
            swap(&a[pl],&a[pl]);
            pl++;
            pr--;
        }
    }
    printf("\npovit is %d\n",pivot);

}

int main ()
{
    int a[] = {5, 2, 9, 1, 5, 6};
    int n = sizeof(a) / sizeof(a[0]);
    printf("Before partition:\n");
    for(int i = 0; i < n; i++)
        printf("%d ",a[i]);
    partition(a,n);
    printf("\nAfter partition:\n");
    for(int i = 0; i < n; i++)
        printf("%d ",a[i]);
    return 0;
}