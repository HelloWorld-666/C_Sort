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

/*******************************ð��*******************************/
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

/*******************************�ݹ����*******************************/
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


/*******************************�ǵݹ����*******************************/
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
               while(array[right] >= temp&&left<right)
               {
                  right--;
               }
               if(left<right)
               {
                   array[left]=array[right];	// �Ҳ������б�temp��׼С�ķ�����ߣ���ǰarray[left]�Ѿ�������temp�У�
               }
               while(array[left] <= temp&&left<right)
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

 /*******************************����*******************************/
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
	 array[i] = temp;								// �����ձȽϺ��С��ֵ�ŵ����ʵ�λ��
 }
 
 void  heap_sort(int * array, int len)
 {
	 int i;
	 for (i = len/2 - 1; i>=0; i--)					// i:�����������һ�����ڵ��±�(���µ���)  i--��������϶ѵ���������i--���Ƶ������ڶ������ڵ�
	 {
		create_heap(array, i, len);
	 }
	
	 for (int i = len - 1; i > 0; i--)				// i > 0 (��1����Ϊ�����±��Ǵ�0��ʼ)
	 {
		swap_fun(array, 0, i);
		create_heap(array, 0, i);					// ���¹����ѵ�ʱ�򣬵ڶ���������0��������������Զ�ͶѶ�Ԫ�ؽ���λ�ã��� �±�0
	 }

	 //for (i = 0; i < len; i++)						// �Ѵ󶥶Ѹ��ڵ�(�±�Ϊ0)�ϵ����ֵ������ĩβ���û�����. 
	 //{
		// swap_fun(array, 0, len-i-1);				
		// create_heap(array, 0, len - i-1);			// �������˴���Ϊlen-i-1����������i+1<=len�����ַ�ʽ������.
	 //}
 }


 /*******************************�鲢*******************************/
 void merge_sort(int* array1, int len1, int* array2, int len2)
 {
	 int i = 0;
	 int j = 0;
	 int k = 0;
	 //int tmp[10];						// ��ʱ���� ����Ҫ�Ż������̶ܹ�Ϊ10
	 int* tmp = new int[10];
	 // 1.�ֱ������������н�Сһ����ֵ����С˳���ƶ�����ʱ����tmp��
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
	 // 2.�϶�����һ�����������ƶ��꣬������Ҫ����һ��δ�ƶ��������������ʣ�µ�Ԫ�ؼ����ƶ���tmp��
	 while (i < len1)
	 {
		 tmp[k++] = array1[i++];
	 }
	 while (j < len2)
	 {
		 tmp[k++] = array2[j++];
	 }

	 // 3.���ϲ�����ֵ����ԭʼ����
	 for (int q = 0; q < len1 + len2; q++)
	 {
		 array1[q] =  tmp[q];			// int* subArray1 = array; subArray1�а���ԭ���������Ԫ��
	 }
 }

 // ��ֺ���
 void merge(int* array, int len)
 {
	 if (len > 1)						// ������ÿ��������ֻ��һ��Ԫ��
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
	int right = len - 1; // �±��0��ʼ

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
