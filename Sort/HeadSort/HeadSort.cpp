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
// HEAP SORT GỐC – SẮP XẾP GIẢM DẦN
// ==================================================

// HÀM PUSH DOWN TẠO MIN-HEAP
void PushDown(recordtype a[], int first, int last)
{
    int r;

    // Bắt đầu từ nút cần đẩy xuống.
    r = first;

    /*
        r còn nằm trong nhóm các nút có con.

        Con trái của r:  2 * r + 1
        Con phải của r: 2 * r + 2
    */
    while (r <= (last - 1) / 2)
    {
        /*
            Trường hợp r chỉ có một con trái.

            Khi:
                last == 2 * r + 1

            thì nút con trái chính là phần tử cuối.
        */
        if (last == 2 * r + 1)
        {
            /*
                Nếu nút cha lớn hơn nút con,
                đổi chỗ để phần tử nhỏ hơn nằm trên.
            */
            if (a[r].key > a[last].key)
            {
                Swap(&a[r], &a[last]);
            }

            // Kết thúc quá trình đẩy xuống.
            r = last;
        }

        /*
            Trường hợp r có đủ hai nút con.

            Nếu nút cha lớn hơn con trái và
            con trái nhỏ hơn hoặc bằng con phải,
            đổi nút cha với con trái.
        */
        else if (
            (a[r].key > a[2 * r + 1].key) &&
            (a[2 * r + 1].key <= a[2 * r + 2].key))
        {
            Swap(&a[r], &a[2 * r + 1]);

            // Tiếp tục xét tại vị trí con trái.
            r = 2 * r + 1;
        }

        /*
            Nếu nút cha lớn hơn con phải và
            con phải nhỏ hơn con trái,
            đổi nút cha với con phải.
        */
        else if (
            (a[r].key > a[2 * r + 2].key) &&
            (a[2 * r + 2].key < a[2 * r + 1].key))
        {
            Swap(&a[r], &a[2 * r + 2]);

            // Tiếp tục xét tại vị trí con phải.
            r = 2 * r + 2;
        }

        /*
            Nếu nút cha đã nhỏ hơn hoặc bằng
            các nút con thì không cần đổi chỗ.
        */
        else
        {
            r = last;
        }
    }
}

// HEAP SORT GIẢM DẦN
void HeapSort(recordtype a[], int n)
{
    int i;

    // Mảng có không quá một phần tử thì không cần sắp xếp.
    if (n <= 1)
    {
        return;
    }

    /*
        GIAI ĐOẠN 1: TẠO MIN-HEAP

        (n - 2) / 2 là vị trí nút cha cuối cùng.
        Các phần tử đứng sau vị trí này là nút lá.
    */
    for (i = (n - 2) / 2; i >= 0; i--)
    {
        PushDown(a, i, n - 1);
    }

    /*
        GIAI ĐOẠN 2: SẮP XẾP

        Phần tử nhỏ nhất nằm tại a[0].
        Đưa phần tử nhỏ nhất về cuối đoạn đang xét.
    */
    for (i = n - 1; i >= 2; i--)
    {
        Swap(&a[0], &a[i]);

        /*
            Sau khi đổi chỗ, vun đống lại
            trong đoạn từ a[0] đến a[i - 1].
        */
        PushDown(a, 0, i - 1);
    }

    /*
        Sau vòng lặp còn hai phần tử a[0] và a[1].
        Đổi chỗ để hoàn thành thứ tự giảm dần.
    */
    Swap(&a[0], &a[1]);
}

// ==================================================
// HEAP SORT BIẾN THỂ – SẮP XẾP TĂNG DẦN
// ==================================================

// HÀM PUSH DOWN TẠO MAX-HEAP
void PushDown_up(recordtype a[], int first, int last)
{
    int r;

    r = first;

    while (r <= (last - 1) / 2)
    {
        // Trường hợp r chỉ có một con trái.
        if (last == 2 * r + 1)
        {
            /*
                Nếu nút cha nhỏ hơn nút con,
                đổi chỗ để phần tử lớn hơn nằm trên.
            */
            if (a[r].key < a[last].key)
            {
                Swap(&a[r], &a[last]);
            }

            r = last;
        }

        /*
            Nếu nút cha nhỏ hơn con trái và
            con trái lớn hơn hoặc bằng con phải,
            đổi nút cha với con trái.
        */
        else if (
            (a[r].key < a[2 * r + 1].key) &&
            (a[2 * r + 1].key >= a[2 * r + 2].key))
        {
            Swap(&a[r], &a[2 * r + 1]);

            r = 2 * r + 1;
        }

        /*
            Nếu nút cha nhỏ hơn con phải và
            con phải lớn hơn con trái,
            đổi nút cha với con phải.
        */
        else if (
            (a[r].key < a[2 * r + 2].key) &&
            (a[2 * r + 2].key > a[2 * r + 1].key))
        {
            Swap(&a[r], &a[2 * r + 2]);

            r = 2 * r + 2;
        }

        // Nút cha đã lớn hơn hoặc bằng các nút con.
        else
        {
            r = last;
        }
    }
}

// HEAP SORT TĂNG DẦN
void HeapSort_up(recordtype a[], int n)
{
    int i;

    // Mảng có không quá một phần tử thì không cần sắp xếp.
    if (n <= 1)
    {
        return;
    }

    /*
        GIAI ĐOẠN 1: TẠO MAX-HEAP
    */
    for (i = (n - 2) / 2; i >= 0; i--)
    {
        PushDown_up(a, i, n - 1);
    }

    /*
        GIAI ĐOẠN 2: SẮP XẾP

        Phần tử lớn nhất nằm tại a[0].
        Đưa phần tử lớn nhất về cuối đoạn đang xét.
    */
    for (i = n - 1; i >= 2; i--)
    {
        Swap(&a[0], &a[i]);

        // Vun đống lại phần chưa được sắp xếp.
        PushDown_up(a, 0, i - 1);
    }

    // Đổi chỗ hai phần tử cuối cùng còn lại.
    Swap(&a[0], &a[1]);
}

// HÀM MAIN
int main(void)
{
    recordtype a[100];
    int n;

    printf("THUAT TOAN HEAP SORT\n\n");

    Read_Data(a, &n);

    printf("Du lieu truoc khi sap xep:\n");
    Print_Data(a, n);

    /*
        Chỉ sử dụng một trong hai hàm:

        HeapSort:    sắp xếp giảm dần.
        HeapSort_up: sắp xếp tăng dần.
    */

    HeapSort(a, n);

    // HeapSort_up(a, n);

    printf("\nDu lieu sau khi sap xep giam dan:\n");
    Print_Data(a, n);

    return 0;
}