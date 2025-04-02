#include <stdio.h>
#include <stdlib.h>

void swap (int *a,int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}
//これがクイックソートの本体
//pivotよりも小さい値を左側に、大きい値を右側に分ける  
//再帰的に呼び出すことでソートを完成させる
void quick_sort(int a[],int left,int right)
{
    int pl = left;
    int pr = right;
    int pivot = a[(pl + pr) / 2];
    int i;

    printf("a[%d] ~ a[%d]\n",left,right);
    for(i = left; i <= right; i++)
        printf("%d ",a[i]);
    printf("\n");

    do
    {
        while(a[pl] < pivot) pl++;
        while(a[pr] > pivot) pr--;
        if(pl <= pr)
        {
            swap(&a[pl],&a[pr]);
            pl++;
            pr--;
        }
    }while(pl <= pr);
    if(left < pr) quick_sort(a,left,pr);
    if(pl < right) quick_sort(a,pl,right);
}

int main ()
{
    int a[] = {5, 2, 9, 1, 5, 6};
    int n = sizeof(a) / sizeof(a[0]);
    printf("Before quick sort:\n");  
    for(int i = 0; i < n; i++)
        printf("%d ",a[i]); 
    printf("\n");
    printf("\n");
    quick_sort(a,0,n-1);
    printf("\nAfter quick sort:\n");
    for(int i = 0; i < n; i++)
        printf("%d ",a[i]);
    return 0;
}
