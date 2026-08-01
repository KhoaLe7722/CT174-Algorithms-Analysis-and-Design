# CT174 — Algorithms Analysis and Design

Tài liệu học tập và mã nguồn minh họa cho học phần **CT174 – Phân tích và Thiết kế thuật toán**.

Repository được xây dựng để giúp sinh viên:

* Hiểu nguyên lý hoạt động của từng thuật toán.
* Biết cách mô phỏng thuật toán bằng tay.
* Cài đặt thuật toán bằng C/C++.
* Phân biệt cách sắp xếp tăng dần và giảm dần.
* Phân tích độ phức tạp thời gian và bộ nhớ.

> Đây là tài liệu tham khảo, không thay thế bài giảng hoặc hướng dẫn chính thức của giảng viên.

## Các thuật toán hiện có

|Thuật toán|Tốt nhất|Trung bình|Xấu nhất|Ghi chú|
|-|-:|-:|-:|-|
|Selection Sort|`O(n²)`|`O(n²)`|`O(n²)`|Tìm phần tử nhỏ nhất hoặc lớn nhất|
|Bubble Sort|`O(n²)`|`O(n²)`|`O(n²)`|Phiên bản hiện tại chưa có dừng sớm|
|Insertion Sort|`O(n)`|`O(n²)`|`O(n²)`|Hiệu quả với mảng gần có thứ tự|
|Quick Sort|`O(n log n)`|`O(n log n)`|`O(n²)`|Sử dụng pivot và phân hoạch|
|Heap Sort|`O(n log n)`|`O(n log n)`|`O(n log n)`|Sử dụng min-heap hoặc max-heap|

## 1\. Selection Sort – Sắp xếp chọn

### Nguyên lý

Mỗi lượt tìm một phần tử trong đoạn chưa sắp xếp rồi đưa phần tử đó về vị trí `a\\\[i]`.

* Tìm phần tử nhỏ nhất và đưa về đầu: sắp xếp tăng dần.
* Tìm phần tử lớn nhất và đưa về đầu: sắp xếp giảm dần.

### Điều kiện so sánh

Tăng dần:

```c
if (a\\\[j].key < lowkey)
```

Giảm dần:

```c
if (a\\\[j].key > lowkey)
```

### Điểm cần nhớ

* Vòng ngoài chạy từ `i = 0` đến `n - 2`.
* Vòng trong chạy từ `j = i + 1` đến `n - 1`.
* `lowindex` lưu vị trí của phần tử được chọn.
* Sau vòng lặp trong, phải đổi `a\\\[i]` với `a\\\[lowindex]`.

```c
Swap(\\\&a\\\[i], \\\&a\\\[lowindex]);
```

Không được đổi với `a\\\[j]` vì khi vòng lặp kết thúc, `j` đã vượt khỏi phạm vi mảng.

## 2\. Bubble Sort – Sắp xếp nổi bọt

### Nguyên lý

Thuật toán so sánh hai phần tử kề nhau và đổi chỗ nếu chúng chưa đúng thứ tự.

Trong phiên bản duyệt từ phải sang trái, mỗi lượt sẽ đưa một phần tử về đầu đoạn chưa sắp xếp.

### Điều kiện so sánh

Tăng dần – đưa phần tử nhỏ hơn về bên trái:

```c
if (a\\\[j].key < a\\\[j - 1].key)
```

Giảm dần – đưa phần tử lớn hơn về bên trái:

```c
if (a\\\[j].key > a\\\[j - 1].key)
```

### Điểm cần nhớ

* Bubble Sort chỉ so sánh các phần tử kề nhau.
* Vòng trong duyệt từ `j = n - 1` về `j = i + 1`.
* Hai phần tử được so sánh là `a\\\[j]` và `a\\\[j - 1]`.
* Phiên bản hiện tại không có biến dừng sớm nên trường hợp tốt nhất vẫn là `O(n²)`.

## 3\. Insertion Sort – Sắp xếp xen

### Nguyên lý

Thuật toán xem phần đầu mảng là đoạn đã có thứ tự. Mỗi lượt đưa phần tử `a\\\[i]` về đúng vị trí trong đoạn đã sắp xếp.

### Điều kiện so sánh

Tăng dần:

```c
while ((j > 0) \\\&\\\& (a\\\[j].key < a\\\[j - 1].key))
```

Giảm dần:

```c
while ((j > 0) \\\&\\\& (a\\\[j].key > a\\\[j - 1].key))
```

### Điểm cần nhớ

* Vòng ngoài bắt đầu từ `i = 1`.
* Gán `j = i` trước khi đưa phần tử sang trái.
* Phải kiểm tra `j > 0` trước khi truy cập `a\\\[j - 1]`.
* Sau mỗi lần đổi chỗ phải có `j--`.

```c
Swap(\\\&a\\\[j], \\\&a\\\[j - 1]);
j--;
```

Nếu thiếu `j--`, phần tử đang xét không thể tiếp tục di chuyển về đúng vị trí.

## 4\. Quick Sort – Sắp xếp nhanh

### Nguyên lý

Quick Sort chọn một giá trị làm `pivot`, phân hoạch mảng thành hai phần rồi tiếp tục sắp xếp hai phần bằng đệ quy.

Code trong repository gồm ba nhóm hàm:

* `FindPivot()` tìm pivot.
* `Partition()` thực hiện phân hoạch.
* `QuickSort()` gọi đệ quy cho hai đoạn con.

### Quick Sort tăng dần bản gốc

```c
while (a\\\[L].key < pivot)
    L++;

while (a\\\[R].key >= pivot)
    R--;
```

Sau khi phân hoạch:

```text
Các phần tử < pivot | Các phần tử >= pivot
```

### Quick Sort tăng dần biến thể

```c
while (a\\\[L].key <= pivot)
    L++;

while (a\\\[R].key > pivot)
    R--;
```

Sau khi phân hoạch:

```text
Các phần tử <= pivot | Các phần tử > pivot
```

Đây vẫn là sắp xếp tăng dần, không phải giảm dần.

### Quick Sort giảm dần

```c
while (a\\\[L].key > pivot)
    L++;

while (a\\\[R].key <= pivot)
    R--;
```

Sau khi phân hoạch:

```text
Các phần tử > pivot | Các phần tử <= pivot
```

### Điểm cần nhớ

* `FindPivot()` trả về `-1` nếu tất cả phần tử trong đoạn bằng nhau.
* `Partition()` trả về điểm phân hoạch `k`, không nhất thiết là vị trí cuối cùng của pivot.
* Hai lời gọi đệ quy là `\\\[i, k - 1]` và `\\\[k, j]`.
* Sắp xếp toàn bộ mảng phải gọi với chỉ số `0` và `n - 1`.

```c
QuickSort(a, 0, n - 1);
```

Không được truyền `n` vì chỉ số cuối cùng của mảng là `n - 1`.

## 5\. Heap Sort – Sắp xếp vun đống

### Nguyên lý

Heap Sort xây dựng một cây heap trên mảng, đưa phần tử ở gốc về cuối đoạn đang xét rồi vun đống lại phần còn lại.

Với mảng bắt đầu từ chỉ số `0`:

```text
Con trái  = 2 \\\* r + 1
Con phải  = 2 \\\* r + 2
Nút cha   = (r - 1) / 2
```

### Heap Sort giảm dần

Hàm `PushDown()` tạo min-heap:

* Phần tử nhỏ nhất nằm ở gốc.
* Mỗi lượt đưa phần tử nhỏ nhất về cuối đoạn đang xét.
* Kết quả cuối cùng là thứ tự giảm dần.

Điều kiện chính:

```c
if (a\\\[r].key > a\\\[last].key)
```

### Heap Sort tăng dần

Hàm `PushDown\\\_up()` tạo max-heap:

* Phần tử lớn nhất nằm ở gốc.
* Mỗi lượt đưa phần tử lớn nhất về cuối đoạn đang xét.
* Kết quả cuối cùng là thứ tự tăng dần.

Điều kiện chính:

```c
if (a\\\[r].key < a\\\[last].key)
```

### Điểm cần nhớ

* Nút cha cuối cùng nằm tại vị trí `(n - 2) / 2`.
* Khi đưa phần tử ở gốc về cuối, phải giảm phạm vi heap.
* Min-heap được dùng cho phiên bản giảm dần trong code hiện tại.
* Max-heap được dùng cho phiên bản tăng dần trong code hiện tại.
* Các lời gọi `Swap()` phải truyền địa chỉ phần tử.

```c
Swap(\\\&a\\\[0], \\\&a\\\[i]);
```

## Kiểu dữ liệu sử dụng

Các chương trình sử dụng mảng bản ghi:

```c
typedef int keytype;
typedef float othertype;

typedef struct
{
    keytype key;
    othertype otherdata;
} recordtype;
```

* `key` là khóa dùng để so sánh và sắp xếp.
* `otherdata` là dữ liệu đi kèm với khóa.
* Khi đổi chỗ, toàn bộ bản ghi được đổi nên `otherdata` luôn đi theo `key`.

## Dữ liệu mẫu

File `data.txt` gồm một số nguyên và một số thực trên mỗi dòng:

```text
50 5.50
10 2.00
143 8.50
0 1.50
90 6.00
```

## Lưu ý về Read\_Data

Các code gốc đang sử dụng:

```c
while (!feof(f))
```

Cách này có thể làm chương trình đọc dư một bản ghi ở cuối file. Cách đọc an toàn hơn là kiểm tra kết quả của `fscanf()`:

```c
while (fscanf(f, "%d%f", \\\&a\\\[i].key, \\\&a\\\[i].otherdata) == 2)
{
    i++;
}
```

Nếu muốn giữ nguyên code theo bài giảng, bạn vẫn có thể sử dụng phiên bản cũ nhưng cần lưu ý khả năng xuất hiện bản ghi dư.

## Biên dịch và chạy

Nếu file có đuôi `.c`:

```bash
gcc -std=c99 ten\\\_file.c -o ten\\\_chuong\\\_trinh
```

Nếu file có đuôi `.cpp`:

```bash
g++ ten\\\_file.cpp -o ten\\\_chuong\\\_trinh
```

Trên Dev-C++, mở file nguồn và chọn **Compile \& Run**. File `data.txt` phải nằm trong đúng thư mục làm việc của chương trình.

## Giấy phép

Repository được phát hành theo [MIT License](LICENSE).



