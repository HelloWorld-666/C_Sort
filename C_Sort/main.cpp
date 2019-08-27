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

// 1.recursion quick sort��
int quick_sorting(int* array, int left, int right)
{
	int tmp = array[right];						// ��׼ֵ   ����׼ֵ����������±�0��ʼ����ӻ�׼ֵ�Ҳ�����������ݣ���׼ֵ�������Ҳ��±�righht��ʼ����ӻ�׼ֵ������ұ������ݣ�
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
		while (array[left] <= tmp && left < right)	// ���ڣ�
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
		quick_sort(array, left, mid-1);			// ��ݹ�
		quick_sort(array, mid+1, right);		// �ҵݹ�
	}
}

// 2.no recursion quick sort��
 void quick_sroting_not_by_recursion(int *array,int left,int right)
 {
     int temp;
     int left_bc=left;
     int right_bc=right;
     while(left_bc<right_bc)
     {
            while(left<right)					// �ȵ��Լ����Լ����˳���
            {
               temp=array[left_bc]; 
               while(array[right]>temp&&left<right)
               {
                  right--;
               }
               if(left<right)
               {
                   array[left]=array[right];	// �Ҳ������б�temp��׼С�ķ�����ߣ���ǰarray[left]�Ѿ�������temp�У�
               }
               while(array[left]<temp&&left<right)
               {
                   left++;
               }
               if(left<right)
               {
                   array[right]=array[left];	// ��������б�temp��׼��ķ����ұ�
               }
               array[left]=temp; 
               left=left_bc;					// ÿһ�α�֤��temp��array[left_bc]������ұߡ�С������ߡ�
            }
            left=left_bc+1;						// ���»�׼ֵ
			left_bc++;
            right=right_bc;
     }          
 }

 void maopao_sort(int *array, int len)
 {
	 int i, j, tmp;
	 for (i = 0; i < len; i++)
	 {
		 for (  j = i+1; j < len; j++)
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

 //����Ԫ��
 void swap_fun(int *array, int i, int j)
 {
	 int temp = array[i];
	 array[i] = array[j];
	 array[j] = temp;
 }
 
 void create_heap(int *array, int i, int len)
 {
	 int temp = array[i];							// ���ݸ��ڵ�A��׼ֵ
	 int j;
	 for (j = 2*i+1; j < len; j = 2*j+1)			// j=2i+1:A�������±�			j = 2* j + 1:�Ե�ǰҶ�ӽڵ�Ϊ�µĸ��ڵ㣬������ڵ����һ��Ҷ�ӽڵ������±�
	 {
		 if (j+1 < len && array[j] < array[j+1])	// ������(j)���Һ���(j+1)��ѡ��һ���ϴ��ֵ.  j+1<len:�Һ���(j+1)���ܳ���len���ȷ�Χ
		 {
			 ++j;
		 }
		 if (temp > array[j])						// �����������нϴ��ֵ�����ǵĸ��ڵ���бȽϣ�temp>array[j]:���ڵ���ں����нϴ��һ���ڵ�ֵ(����j�Ѿ���������) -> break
		 {
			 break;
		 }
		 array[i] = array[j];						// temp<array[j]ʱ:�ú����нϴ��һ���ڵ�ֵ�滻�����ڵ�Ļ�׼ֵ
		 i = j;										// �����ӽڵ㿴����һ�����ڵ㣬�������±���
	 }
	 array[i] = temp;
 }
 
 void  heap_sort(int * array, int len)
 {
	 int i;
	 for (i = len/2 - 1; i>=0; i--)					// i:�����������һ�����ڵ��±�(���µ���)  i--��������϶ѵ���������i--���Ƶ������ڶ������ڵ�
	 {
		 create_heap(array, i, len);
	 }
	
	 for (i = 1; i < len; i++)						// �Ѵ󶥶Ѹ��ڵ�(�±�Ϊ0)�ϵ����ֵ������ĩβ���û�����.
	 {
		 swap_fun(array, 0, len-i);	 // 0 <-> 
		 create_heap(array, 0, len - i);			// �������˴���Ϊlen-i-1����������i+1<=len�����ַ�ʽ������.
	 }

	 //for (int i = len - 1; i > 0; i--)				// i > 0
	 //{
		// swap_fun(array, 0, i);
		// create_heap(array, 0, i);					// ���¹����ѵ�ʱ�򣬵ڶ���������0��������������Զ�ͶѶ�Ԫ�ؽ���λ�ã��� �±�0
	 //}
 }

int main()
{
	int test_array[7] = { 5, 28, 73, 19, 6, 0, 5 };
	int len = sizeof(test_array) / sizeof(int);

	//maopao_sort(test_array, len);
	//quick_sort(test_array, 0, len);
	//quick_sroting_not_by_recursion(test_array, 0, len);
	heap_sort(test_array, len);

	printf("result:\t");
	printf_array(test_array, len);
	getchar();

	return 0;
}
