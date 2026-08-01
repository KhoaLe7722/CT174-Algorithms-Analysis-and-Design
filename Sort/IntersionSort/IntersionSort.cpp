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
		printf("Loi doc file");
	fclose(f);
	*n = i;
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

// INSERTION SORT TĂNG DẦN
void InsertionSort(recordtype a[], int n)
{
	int i, j;

	/*
		Bắt đầu từ a[1] vì a[0] được xem
		là đoạn đã có thứ tự gồm một phần tử.
	*/
	for (i = 1; i <= n - 1; i++)
	{
		j = i;
		while (
			(j > 0) &&
			(a[j].key < a[j - 1].key) // GIẢM DẦN: a[j].key > a[j - 1].key
		)
		{
			Swap(&a[j], &a[j - 1]);

			// Đưa phần tử đang xét sang trái.
			j--;
		}
	}
}

// HÀM MAIN
int main(void)
{
	recordtype a[100];
	int n;

	printf("THUAT TOAN INSERTION SORT TANG DAN\n\n");

	Read_Data(a, &n);

	printf("Du lieu truoc khi sap xep:\n");
	Print_Data(a, n);

	InsertionSort(a, n);

	printf("\nDu lieu sau khi sap xep tang dan:\n");
	Print_Data(a, n);

	return 0;
}