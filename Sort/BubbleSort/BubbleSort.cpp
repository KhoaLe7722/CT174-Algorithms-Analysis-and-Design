#include <stdio.h>

typedef int keytype;
typedef float othertype;

typedef struct
{
	keytype key;
	othertype otherdata;
} recordtype;

// HÀM ĐỔI CHỖ
void Swap(recordtype *x, recordtype *y)
{
	recordtype temp;

	temp = *x;
	*x = *y;
	*y = temp;
}

// HÀM READ_DATA
void Read_Data(recordtype a[], int *n)
{
	FILE *f;
	int i = 0;

	f = fopen("data.txt", "r");

	if (f != NULL)
	{
		while (!feof(f))
		{
			fscanf(
				f,
				"%d%f",
				&a[i].key,
				&a[i].otherdata);

			i++;
		}
	}
	else
	{
		printf("Loi doc file");
	}
	fclose(f);
	*n = i; // Trả số lượng bản ghi đã đọc được qua con trỏ n.
}

// HÀM IN DỮ LIỆU
void Print_Data(recordtype a[], int n)
{
	int i;

	for (i = 0; i < n; i++)
	{
		printf(
			"%3d %5d %8.3f\n",
			i + 1,
			a[i].key,
			a[i].otherdata);
	}
}

// BUBBLE SORT
void BubbleSort(recordtype a[], int n)
{
	int i, j;

	for (i = 0; i <= n - 2; i++)
	{
		for (j = n - 1; j >= i + 1; j--)
		{
			if (a[j].key < a[j - 1].key)
			{ // GIẢM DẦN: if (a[j].key > a[j - 1].key)
				Swap(&a[j], &a[j - 1]);
			}
		}
	}
}

// HÀM MAIN
int main(void)
{
	recordtype a[100];
	int n;

	printf("THUAT TOAN BUBBLE SORT GIAM DAN\n\n");

	Read_Data(a, &n);

	printf("Du lieu truoc khi sap xep:\n");
	Print_Data(a, n);

	BubbleSort(a, n);

	printf("\nDu lieu sau khi sap xep giam dan:\n");
	Print_Data(a, n);

	return 0;
}