#include <stdio.h>

typedef int keytype;
typedef float othertype;

typedef struct recordtype
{
    keytype key;
    othertype otherfields;
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
                &a[i].otherfields);

            i++;
        }   
    }
    else
    {
        printf("Loi mo file");
    }
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
            a[i].otherfields);
    }
}

// ==================================================
// QUICK SORT GỐC – SẮP XẾP TĂNG DẦN
// ==================================================

// HÀM TÌM PIVOT
int FindPivot(recordtype a[], int i, int j)
{
    keytype firstkey;
    int k;

    // Lấy key của phần tử đầu tiên.
    firstkey = a[i].key;

    // Bắt đầu tìm từ phần tử đứng sau a[i].
    k = i + 1;

    /*
        Bỏ qua những phần tử có key
        bằng với firstkey.
    */
    while (
        (k <= j) &&
        (a[k].key == firstkey))
    {
        k++;
    }

    /*
        Nếu k > j thì tất cả phần tử
        trong đoạn đều bằng nhau.
    */
    if (k > j)
    {
        return -1;
    }

    /*
        Chọn phần tử lớn hơn trong hai phần tử
        khác nhau đầu tiên làm pivot.
    */
    if (a[k].key > firstkey)
    {
        return k;
    }
    else
    {
        return i;
    }
}

// HÀM PHÂN HOẠCH TĂNG DẦN
int Partition(
    recordtype a[],
    int i,
    int j,
    keytype pivot)
{
    int L, R;

    L = i;
    R = j;

    while (L <= R)
    {
        /*
            L đi từ trái sang phải.

            Bỏ qua những phần tử nhỏ hơn pivot.
            L dừng khi gặp phần tử >= pivot.
        */
        while (a[L].key < pivot)
        {
            L++;
        }

        /*
            R đi từ phải sang trái.

            Bỏ qua những phần tử >= pivot.
            R dừng khi gặp phần tử < pivot.
        */
        while (a[R].key >= pivot)
        {
            R--;
        }

        /*
            Nếu L vẫn nằm bên trái R,
            đổi chỗ hai phần tử sai vị trí.
        */
        if (L < R)
        {
            Swap(&a[L], &a[R]);
        }
    }

    // Trả về điểm phân hoạch.
    return L;
}

// HÀM QUICK SORT TĂNG DẦN
void QuickSort(recordtype a[], int i, int j)
{
    keytype pivot;
    int pivotindex, k;

    // Tìm vị trí của pivot.
    pivotindex = FindPivot(a, i, j);

    /*
        Nếu pivotindex bằng -1 thì các phần tử
        trong đoạn đều bằng nhau nên không cần sắp xếp.
    */
    if (pivotindex != -1)
    {
        // Lấy giá trị key của pivot.
        pivot = a[pivotindex].key;

        // Phân hoạch và nhận vị trí chia k.
        k = Partition(a, i, j, pivot);

        // Sắp xếp đoạn bên trái.
        QuickSort(a, i, k - 1);

        // Sắp xếp đoạn bên phải.
        QuickSort(a, k, j);
    }
}

// ==================================================
// QUICK SORT BIẾN THỂ – VẪN SẮP XẾP TĂNG DẦN
// ==================================================

// HÀM TÌM PIVOT BIẾN THỂ
int FindPivot2(recordtype a[], int i, int j)
{
    keytype firstkey;
    int k;

    firstkey = a[i].key;
    k = i + 1;

    // Bỏ qua những phần tử bằng firstkey.
    while (
        (k <= j) &&
        (a[k].key == firstkey))
    {
        k++;
    }

    // Tất cả phần tử trong đoạn đều bằng nhau.
    if (k > j)
    {
        return -1;
    }

    /*
        Hàm gốc trả về phần tử lớn hơn.

        Hàm biến thể trả về phần tử nhỏ hơn
        trong hai phần tử khác nhau đầu tiên.
    */
    if (a[k].key > firstkey)
    {
        return i;
    }
    else
    {
        return k;
    }
}

// HÀM PHÂN HOẠCH BIẾN THỂ
int Partition2(
    recordtype a[],
    int i,
    int j,
    keytype pivot)
{
    int L, R;

    L = i;
    R = j;

    while (L <= R)
    {
        /*
            Bên trái chứa các phần tử <= pivot.
            Bên phải chứa các phần tử > pivot.
        */
        while (a[L].key <= pivot)
        {
            L++;
        }

        while (a[R].key > pivot)
        {
            R--;
        }

        if (L < R)
        {
            Swap(&a[L], &a[R]);
        }
    }

    return L;
}

// HÀM QUICK SORT BIẾN THỂ
void QuickSort2(recordtype a[], int i, int j)
{
    keytype pivot;
    int pivotindex, k;

    pivotindex = FindPivot2(a, i, j);

    if (pivotindex != -1)
    {
        pivot = a[pivotindex].key;
        k = Partition2(a, i, j, pivot);

        QuickSort2(a, i, k - 1);
        QuickSort2(a, k, j);
    }
}

// ==================================================
// QUICK SORT GIẢM DẦN
// ==================================================

// HÀM TÌM PIVOT GIẢM DẦN
int FindPivot_down(recordtype a[], int i, int j)
{
    keytype firstkey;
    int k;

    firstkey = a[i].key;
    k = i + 1;

    // Bỏ qua những phần tử bằng firstkey.
    while (
        (k <= j) &&
        (a[k].key == firstkey))
    {
        k++;
    }

    // Tất cả phần tử trong đoạn đều bằng nhau.
    if (k > j)
    {
        return -1;
    }

    /*
        Đối với cách phân hoạch giảm dần này,
        chọn phần tử nhỏ hơn trong hai phần tử
        khác nhau đầu tiên làm pivot.
    */
    if (a[k].key < firstkey)
    {
        return k;
    }
    else
    {
        return i;
    }
}

// HÀM PHÂN HOẠCH GIẢM DẦN
int Partition_down(
    recordtype a[],
    int i,
    int j,
    keytype pivot)
{
    int L, R;

    L = i;
    R = j;

    while (L <= R)
    {
        /*
            Bên trái chứa phần tử > pivot.
            Bên phải chứa phần tử <= pivot.
        */
        while (a[L].key > pivot)
        {
            L++;
        }

        while (a[R].key <= pivot)
        {
            R--;
        }

        if (L < R)
        {
            Swap(&a[L], &a[R]);
        }
    }

    return L;
}

// HÀM QUICK SORT GIẢM DẦN
void QuickSort_down(recordtype a[], int i, int j)
{
    keytype pivot;
    int pivotindex, k;

    pivotindex = FindPivot_down(a, i, j);

    if (pivotindex != -1)
    {
        pivot = a[pivotindex].key;
        k = Partition_down(a, i, j, pivot);

        QuickSort_down(a, i, k - 1);
        QuickSort_down(a, k, j);
    }
}

// HÀM MAIN
int main(void)
{
    recordtype a[100];
    int n;

    printf("THUAT TOAN QUICK SORT\n\n");

    Read_Data(a, &n);

    printf("Du lieu truoc khi sap xep:\n");
    Print_Data(a, n);

    /*
        Chỉ mở một trong ba hàm dưới đây.

        QuickSort:      tăng dần bản gốc.
        QuickSort2:     tăng dần biến thể.
        QuickSort_down: giảm dần.
    */

    // QuickSort(a, 0, n - 1);
    // QuickSort2(a, 0, n - 1);
    QuickSort_down(a, 0, n - 1);

    printf("\nDu lieu sau khi sap xep giam dan:\n");
    Print_Data(a, n);

    return 0;
}