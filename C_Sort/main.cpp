#include <iostream>

using namespace std;

void  printf_array(int *array, int len)
{
	int i;
	for (i = 0; i<len; i++)
	{
		printf("%d\t", array[i]);
	}
	printf("\n");
}

/*******************************冒泡*******************************/
void maopao_sort(int *array, int len)
{
	int i, j, tmp;
	for (i = 0; i < len; i++)
	{
		for (j = i + 1; j < len; j++)
		{
			if (array[i] > array[j])
			{
				tmp = array[i];
				array[i] = array[j];
				array[j] = tmp;
			}
		}
	}
}

/*******************************递归快排*******************************/
// 1.recursion quick sort：
int quick_sorting(int* array, int left, int right)
{
	int tmp = array[right];						// 基准值   （基准值从数组左侧下标0开始，则从基准值右侧往左遍历数据；基准值从数组右侧下标righht开始，则从基准值左侧往右遍历数据）
	while (left < right)
	{
		//while (array[right] >= tmp  && left < right)
		//{
		//	right--;
		//}
		//if (left < right)
		//{
		//	array[left] = array[right]; // array[right] < tmp
		//}
		while (array[left] <= tmp && left < right)	// 等于！
		{
			left++;
		}
		if (left < right)
		{
			array[right] = array[left];			// array[left] > tmp
		}
		while (array[right] >= tmp  && left < right)
		{
			right--;
		}
		if (left < right)
		{
			array[left] = array[right];			// array[right] < tmp
		}
	}
	array[left] = tmp;

	return left;
}

void quick_sort(int* array, int left, int right)
{
	if (left < right)
	{
		int mid = quick_sorting(array, left, right);
		quick_sort(array, left, mid-1);			// 左递归
		quick_sort(array, mid+1, right);		// 右递归
	}
}


/*******************************非递归快排*******************************/
// 2.no recursion quick sort：
 void quick_sroting_not_by_recursion(int *array,int left,int right)
 {
     int temp;
     int left_bc=left;
     int right_bc=right;
     while(left_bc<right_bc)
     {
            while(left<right)					// 比到自己比自己就退出。
            {
               temp=array[left_bc]; 
               while(array[right] >= temp&&left<right)
               {
                  right--;
               }
               if(left<right)
               {
                   array[left]=array[right];	// 右侧数据中比temp基准小的放在左边（此前array[left]已经备份在temp中）
               }
               while(array[left] <= temp&&left<right)
               {
                   left++;
               }
               if(left<right)
               {
                   array[right]=array[left];	// 左侧数据中比temp基准大的放在右边
               }
               array[left]=temp; 
               left=left_bc;					// 每一次保证比temp即array[left_bc]大的在右边。小的在左边。
            }
            left=left_bc+1;						// 更新基准值
			left_bc++;
            right=right_bc;
     }          
 }

 /*******************************堆排*******************************/
 //交换元素
 void swap_fun(int *array, int i, int j)
 {
	 int temp = array[i];
	 array[i] = array[j];
	 array[j] = temp;
 }
 
 void create_heap(int *array, int i, int len)
 {
	 int temp = array[i];							// 备份父节点A基准值
	 int j;
	 for (j = 2*i+1; j < len; j = 2*j+1)			// j=2i+1:A的左孩子下标			j = 2* j + 1:以当前叶子节点为新的根节点，这个根节点的下一层叶子节点左孩子下标
	 {
		 if (j+1 < len && array[j] < array[j+1])	// 从左孩子(j)和右孩子(j+1)中选出一个较大的值.  j+1<len:右孩子(j+1)不能超出len长度范围
		 {
			 ++j;
		 }
		 if (temp > array[j])						// 用两个孩子中较大的值与它们的父节点进行比较，temp>array[j]:父节点大于孩子中较大的一个节点值(上面j已经自增过了) -> break
		 {
			 break;
		 }
		 array[i] = array[j];						// temp<array[j]时:用孩子中较大的一个节点值替换掉父节点的基准值
		 i = j;										// 将孩子节点看作下一个父节点，不断往下遍历
	 }
	 array[i] = temp;								// 将最终比较后较小的值放到合适的位置
 }
 
 void  heap_sort(int * array, int len)
 {
	 int i;
	 for (i = len/2 - 1; i>=0; i--)					// i:二叉树的最后一个父节点下标(从下到上)  i--：如果符合堆的条件，则i--，移到倒数第二个父节点
	 {
		create_heap(array, i, len);
	 }
	
	 for (int i = len - 1; i > 0; i--)				// i > 0 (减1：因为数组下标是从0开始)
	 {
		swap_fun(array, 0, i);
		create_heap(array, 0, i);					// 重新构建堆的时候，第二个参数是0？？？？？：永远和堆顶元素交换位置，即 下标0
	 }

	 //for (i = 0; i < len; i++)						// 把大顶堆根节点(下标为0)上的最大值交换到末尾，置换出来. 
	 //{
		// swap_fun(array, 0, len-i-1);				
		// create_heap(array, 0, len - i-1);			// ！！！此处若为len-i-1，则上面是i+1<=len；两种方式都可以.
	 //}
 }


 /*******************************归并*******************************/
 void merge_sort(int* array1, int len1, int* array2, int len2)
 {
	 int i = 0;
	 int j = 0;
	 int k = 0;
	 //int tmp[10];						// 临时数组 后续要优化，不能固定为10
	 int* tmp = new int[10];
	 // 1.分别将两个子数组中较小一方的值按大小顺序移动到临时数组tmp中
	 while (i < len1 && j < len2)
	 {
		 if (array1[i] < array2[j])
		 {
			 tmp[k++] = array1[i++];
		 }
		 else
		 {
			 tmp[k++] = array2[j++];
		 }
	 }
	 // 2.肯定存在一个子数组先移动完，所以需要将另一个未移动完的有序子数组剩下的元素继续移动到tmp中
	 while (i < len1)
	 {
		 tmp[k++] = array1[i++];
	 }
	 while (j < len2)
	 {
		 tmp[k++] = array2[j++];
	 }

	 // 3.将合并数组值赋给原始数组
	 for (int q = 0; q < len1 + len2; q++)
	 {
		 array1[q] =  tmp[q];			// int* subArray1 = array; subArray1中包含原数组的所有元素
	 }
 }

 // 拆分函数
 void merge(int* array, int len)
 {
	 if (len > 1)						// 最后拆至每个子数组只有一个元素
	 {
		 int len1 = len / 2;
		 int len2 = len - len1;
		 int* subArray1 = array;
		 int* subArray2 = array + len1;
		 merge(subArray1, len1);
		 merge(subArray2, len2);
		 merge_sort(subArray1, len1, subArray2, len2);
	 }
 }

 int main()
 {
	int test_array[7] = { 5, 28, 73, 19, 6, 0, 5 };
	int len = sizeof(test_array) / sizeof(int);
	int right = len - 1; // 下标从0开始

	//maopao_sort(test_array, len);
	//quick_sort(test_array, 0, right); // ok
	//quick_sroting_not_by_recursion(test_array, 0, right); // ok
	//heap_sort(test_array, len);
	merge(test_array, len);

	printf("result:\t");
	printf_array(test_array, len);
	getchar();

	return 0;
}
