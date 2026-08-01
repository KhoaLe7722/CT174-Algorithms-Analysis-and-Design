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
			"%3d %5d %8.2f\n",
			i + 1,
			a[i].key,
			a[i].otherdata);
	}
}

// SELECTION SORT
void SelectionSort(recordtype a[], int n)
{
	int i, j, lowindex;
	keytype lowkey;

	for (i = 0; i <= n - 2; i++)
	{
		lowkey = a[i].key;
		lowindex = i;

		for (j = i + 1; j <= n - 1; j++)
		{
			if (a[j].key < lowkey) // GIẢM DẦN: a[j].key > lowkey
			{
				lowkey = a[j].key;
				lowindex = j;
			}
		}

		/*
			Đưa phần tử tìm được về vị trí a[i].

			Phải dùng lowindex, không dùng j.
		*/
		Swap(&a[i], &a[lowindex]);
	}
}

// HÀM MAIN
int main(void)
{
	recordtype a[100];
	int n;

	printf("THUAT TOAN SELECTION SORT GIAM DAN\n\n");

	Read_Data(a, &n);

	printf("Du lieu truoc khi sap xep:\n");
	Print_Data(a, n);

	SelectionSort(a, n);

	printf("\nDu lieu sau khi sap xep giam dan:\n");
	Print_Data(a, n);

	return 0;
}