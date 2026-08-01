# CT174 — Algorithms Analysis and Design

> Tài liệu học tập và mã nguồn minh họa cho học phần \\\*\\\*CT174 – Phân tích và Thiết kế thuật toán\\\*\\\*.

!\[Language](https://img.shields.io/badge/Language-C%2B%2B-00599C?logo=c%2B%2B\&logoColor=white)
!\[License](https://img.shields.io/badge/License-MIT-green.svg)
!\[Status](https://img.shields.io/badge/Status-In%20Progress-orange)

## Giới thiệu

Repository này được xây dựng nhằm hệ thống hóa kiến thức, mã nguồn và ví dụ minh họa trong học phần **CT174 – Phân tích và Thiết kế thuật toán**. Nội dung hướng đến các bạn đang học hoặc muốn ôn tập học phần.

Mỗi thuật toán được trình bày theo cùng một quy trình:

1. Giới thiệu bài toán và mục tiêu.
2. Trình bày ý tưởng của thuật toán.
3. Mô phỏng từng bước bằng dữ liệu mẫu.
4. Cài đặt bằng C++.
5. Phân tích độ đúng và độ phức tạp.
6. Đưa ra bài tập gợi ý để tự luyện tập.

> \\\*\\\*Lưu ý:\\\*\\\* Repository này là tài liệu học tập tham khảo, không thay thế bài giảng, giáo trình hoặc hướng dẫn chính thức của giảng viên.

## Mục tiêu học tập

Sau khi nghiên cứu và thực hành các nội dung trong repository, người học có thể:

* Hiểu nguyên lý hoạt động của các thuật toán cơ bản.
* Mô phỏng thuật toán bằng tay trên một bộ dữ liệu cụ thể.
* Cài đặt thuật toán bằng ngôn ngữ C++.
* Phân tích độ phức tạp thời gian và không gian.
* So sánh ưu điểm, hạn chế và trường hợp sử dụng của từng thuật toán.
* Lựa chọn phương pháp thiết kế thuật toán phù hợp với bài toán.

## Nội dung hiện tại: Sorting Algorithms

Giai đoạn đầu của repository tập trung vào các thuật toán sắp xếp.

|Thuật toán|Tốt nhất|Trung bình|Xấu nhất|Bộ nhớ phụ|Ổn định|Tại chỗ|
|-|-:|-:|-:|-:|:-:|:-:|
|Selection Sort|`O(n²)`|`O(n²)`|`O(n²)`|`O(1)`|Không|Có|
|Bubble Sort|`O(n)`<sup>1</sup>|`O(n²)`|`O(n²)`|`O(1)`|Có|Có|
|Insertion Sort|`O(n)`|`O(n²)`|`O(n²)`|`O(1)`|Có|Có|
|Quick Sort|`O(n log n)`|`O(n log n)`|`O(n²)`|`O(log n)`<sup>2</sup>|Không|Có<sup>3</sup>|
|Heap Sort|`O(n log n)`|`O(n log n)`|`O(n log n)`|`O(1)`|Không|Có|
|Merge Sort|`O(n log n)`|`O(n log n)`|`O(n log n)`|`O(n)`|Có|Không|

1. Bubble Sort chỉ đạt `O(n)` trong trường hợp tốt nhất khi có biến kiểm tra để dừng sớm.
2. Quick Sort cần trung bình `O(log n)` bộ nhớ cho ngăn xếp đệ quy; trường hợp xấu nhất có thể cần `O(n)`.
3. Quick Sort thường được xem là sắp xếp tại chỗ vì không tạo mảng phụ, nhưng vẫn sử dụng bộ nhớ cho các lời gọi đệ quy.

### Một số khái niệm cần phân biệt

* **Ổn định (stable):** các phần tử có khóa bằng nhau vẫn giữ nguyên thứ tự tương đối sau khi sắp xếp.
* **Tại chỗ (in-place):** thuật toán chỉ cần một lượng nhỏ bộ nhớ phụ và chủ yếu sắp xếp trực tiếp trên mảng ban đầu.
* **Thích nghi (adaptive):** thuật toán chạy nhanh hơn khi dữ liệu đã được sắp xếp một phần.

## Những điểm cần lưu ý đối với từng thuật toán

### 1\. Selection Sort – Sắp xếp chọn

#### Nguyên lý

Với phiên bản tăng dần, ở mỗi lượt, thuật toán tìm phần tử nhỏ nhất trong đoạn chưa được sắp xếp rồi đưa phần tử đó về đầu đoạn.

```text
Đã sắp xếp | Chưa sắp xếp
            ↑
        tìm phần tử nhỏ nhất
```

#### Điểm cần nhớ

* Vòng lặp ngoài thường chạy từ `i = 0` đến `n - 2`.
* Vòng lặp trong tìm phần tử nhỏ nhất từ `j = i + 1` đến `n - 1`.
* Chỉ đổi chỗ một lần sau khi vòng lặp trong kết thúc.
* Phải đổi `a\\\[i]` với `a\\\[lowindex]`, không đổi với `a\\\[j]` sau vòng lặp.
* Thuật toán luôn thực hiện khoảng `n(n - 1) / 2` phép so sánh, dù mảng đã có thứ tự.
* Số lần đổi chỗ ít, tối đa khoảng `n - 1` lần.
* Phiên bản thông thường không ổn định nhưng sắp xếp tại chỗ.

#### Lỗi thường gặp

```cpp
// Sai: j đã chạy hết vòng lặp tìm kiếm.
Swap(\\\&a\\\[i], \\\&a\\\[j]);

// Đúng:
Swap(\\\&a\\\[i], \\\&a\\\[lowindex]);
```

#### Khi nên sử dụng

Selection Sort phù hợp với mảng nhỏ hoặc trường hợp cần hạn chế số lần ghi và đổi chỗ dữ liệu. Thuật toán không phù hợp với dữ liệu lớn vì có độ phức tạp `O(n²)`.

\---

### 2\. Bubble Sort – Sắp xếp nổi bọt

#### Nguyên lý

Thuật toán so sánh hai phần tử kề nhau và đổi chỗ nếu chúng chưa đúng thứ tự.

Có hai hướng duyệt thường gặp:

* Duyệt từ trái sang phải: phần tử lớn nhất dần nổi về cuối mảng.
* Duyệt từ phải sang trái: phần tử nhỏ nhất dần được đẩy về đầu mảng.

Cả hai cách đều đúng nếu điều kiện so sánh và giới hạn vòng lặp được viết thống nhất.

#### Điểm cần nhớ

* Bubble Sort chỉ so sánh các phần tử kề nhau.
* Sau mỗi lượt, ít nhất một phần tử được đưa về đúng vị trí cuối cùng.
* Nếu sắp xếp tăng dần và duyệt trái sang phải, đổi chỗ khi phần tử bên trái lớn hơn phần tử bên phải.
* Nếu chỉ đổi khi khóa bên trái `>` khóa bên phải, thuật toán có tính ổn định.
* Có thể sử dụng biến `swapped` để dừng khi không còn lần đổi chỗ nào.
* Có cơ chế dừng sớm, trường hợp tốt nhất là `O(n)`; nếu không có, vẫn là `O(n²)`.

#### Lỗi thường gặp

* Nhầm hướng duyệt nhưng không đổi điều kiện so sánh.
* Cho `j` chạy quá giới hạn rồi truy cập `a\\\[j + 1]` hoặc `a\\\[j - 1]` ngoài mảng.
* Dùng `>=` thay vì `>` khiến các phần tử bằng nhau có thể bị đổi thứ tự.
* Quên thu hẹp phần mảng chưa được sắp xếp sau mỗi lượt.

#### Khi nên sử dụng

Bubble Sort dễ học và phù hợp để minh họa thao tác đổi chỗ. Trong thực tế, thuật toán chủ yếu chỉ phù hợp với dữ liệu nhỏ hoặc dữ liệu gần có thứ tự khi có cơ chế dừng sớm.

\---

### 3\. Insertion Sort – Sắp xếp xen

#### Nguyên lý

Thuật toán xem phần đầu của mảng là đoạn đã được sắp xếp. Mỗi lượt lấy phần tử tiếp theo và đưa nó về đúng vị trí trong đoạn đã sắp xếp.

```text
Đã sắp xếp | Phần tử đang xét | Chưa xét
```

#### Điểm cần nhớ

* Vòng lặp ngoài thường bắt đầu từ `i = 1` vì một phần tử đầu tiên được xem là đã có thứ tự.
* Gán `j = i` để theo dõi vị trí hiện tại của phần tử đang được chèn.
* Sau mỗi lần đổi chỗ với phần tử đứng trước, phải có `j--` để tiếp tục đưa phần tử sang trái.
* Điều kiện `j > 0` phải được kiểm tra trước khi truy cập `a\\\[j - 1]`.
* Thuật toán ổn định nếu chỉ dịch chuyển hoặc đổi chỗ khi khóa bên trái lớn hơn khóa đang xét.
* Insertion Sort có tính thích nghi và hoạt động tốt với mảng nhỏ hoặc gần có thứ tự.

Ví dụ điều kiện an toàn:

```cpp
while ((j > 0) \\\&\\\& (a\\\[j].key < a\\\[j - 1].key)) {
    Swap(\\\&a\\\[j], \\\&a\\\[j - 1]);
    j--;
}
```

#### Lỗi thường gặp

* Quên `j--`, khiến phần tử chỉ di chuyển được một vị trí hoặc vòng lặp không hoạt động đúng.
* Viết điều kiện truy cập `a\\\[j - 1]` trước `j > 0`, có thể truy cập `a\\\[-1]`.
* Bắt đầu vòng lặp ngoài từ `i = 0` dù chưa cần chèn phần tử đầu tiên.
* Dùng điều kiện `<=` làm thay đổi thứ tự của các phần tử có khóa bằng nhau.

#### Khi nên sử dụng

Insertion Sort phù hợp với dữ liệu nhỏ, gần có thứ tự hoặc dùng để xử lý các đoạn nhỏ bên trong những thuật toán sắp xếp nâng cao.

\---

### 4\. Quick Sort – Sắp xếp nhanh

#### Nguyên lý

Quick Sort chọn một giá trị làm `pivot`, phân hoạch mảng thành hai phần rồi gọi đệ quy để tiếp tục sắp xếp từng phần.

Với cách cài đặt tăng dần đang sử dụng trong học phần:

```text
Các phần tử < pivot | Các phần tử >= pivot
```

#### Ba hàm quan trọng

1. `FindPivot()` tìm một pivot phù hợp.
2. `Partition()` chia mảng thành hai phần và trả về điểm phân hoạch `k`.
3. `QuickSort()` gọi đệ quy trên hai đoạn `\\\[i, k - 1]` và `\\\[k, j]`.

#### Điểm cần nhớ

* Trong phiên bản gốc, `FindPivot()` tìm hai khóa khác nhau đầu tiên và chọn khóa lớn hơn làm pivot.
* Nếu mọi khóa trong đoạn đều bằng nhau, `FindPivot()` phải trả về `-1` để dừng đệ quy.
* Con trỏ `L` đi từ trái sang phải; con trỏ `R` đi từ phải sang trái.
* Với phiên bản tăng dần gốc, `L` dừng ở phần tử `>= pivot`, còn `R` dừng ở phần tử `< pivot`.
* `Partition()` trả về điểm phân hoạch, không nhất thiết là vị trí cuối cùng của chính pivot.
* Hai lời gọi đệ quy phải khớp với cách phân hoạch: `\\\[i, k - 1]` và `\\\[k, j]`.
* Khi gọi cho toàn bộ mảng, phải dùng `QuickSort(a, 0, n - 1)`.
* Quick Sort thường nhanh trong thực tế nhưng không ổn định.

#### Biến thể cần phân biệt

* Phân hoạch `< pivot | >= pivot` cho kết quả tăng dần.
* Phân hoạch `<= pivot | > pivot` vẫn có thể cho kết quả tăng dần; đây chỉ là một biến thể phân hoạch.
* Muốn sắp xếp giảm dần, cần đổi thống nhất cách chọn pivot và các dấu so sánh trong hàm phân hoạch.
* Không nên chỉ đổi một dấu so sánh riêng lẻ vì có thể làm con trỏ không dừng hoặc đệ quy không thu nhỏ đoạn mảng.

#### Lỗi thường gặp

* Truyền `n` thay vì `n - 1`, dẫn đến truy cập ngoài mảng.
* Không xử lý trường hợp các phần tử trong đoạn đều bằng nhau.
* Nhầm `pivotindex` là giá trị pivot; giá trị đúng phải lấy bằng `a\\\[pivotindex].key`.
* Gọi đệ quy sai đoạn, gây bỏ sót phần tử hoặc lặp vô hạn.
* Viết điều kiện phân hoạch không đồng bộ với cách chọn pivot.

#### Khi nên sử dụng

Quick Sort phù hợp với việc sắp xếp mảng trong bộ nhớ và thường có hiệu năng trung bình rất tốt. Cần thận trọng khi dữ liệu hoặc cách chọn pivot có thể tạo các phân hoạch quá lệch.

\---

### 5\. Heap Sort – Sắp xếp vun đống

#### Nguyên lý

Đối với sắp xếp tăng dần, Heap Sort xây dựng một **max-heap**, đưa phần tử lớn nhất ở gốc về cuối mảng, giảm kích thước heap rồi tiếp tục vun đống.

#### Điểm cần nhớ

Với mảng đánh số từ `0`, các vị trí liên quan đến nút `i` là:

```text
Con trái:  2 \\\* i + 1
Con phải:  2 \\\* i + 2
Nút cha:   (i - 1) / 2
```

* Dùng max-heap để sắp xếp tăng dần và min-heap để sắp xếp giảm dần.
* Giai đoạn xây dựng heap có độ phức tạp `O(n)`.
* Sau mỗi lần đổi gốc với phần tử cuối heap, phải giảm kích thước heap.
* Phần cuối mảng đã có thứ tự không được đưa trở lại quá trình vun đống.
* Heap Sort có độ phức tạp `O(n log n)` trong mọi trường hợp.
* Thuật toán sắp xếp tại chỗ nhưng không ổn định.

#### Lỗi thường gặp

* Nhầm công thức vị trí con khi mảng bắt đầu từ chỉ số `0`.
* Không kiểm tra con trái hoặc con phải có nằm trong heap hay không.
* Vun đống trên toàn bộ mảng thay vì chỉ trên phần heap chưa sắp xếp.
* Dùng min-heap nhưng vẫn mong nhận kết quả tăng dần theo quy trình của max-heap.

#### Khi nên sử dụng

Heap Sort phù hợp khi cần bảo đảm độ phức tạp `O(n log n)` và không muốn sử dụng mảng phụ lớn.

\---

### 6\. Merge Sort – Sắp xếp trộn

#### Nguyên lý

Merge Sort sử dụng phương pháp chia để trị:

1. Chia mảng thành hai nửa.
2. Sắp xếp đệ quy từng nửa.
3. Trộn hai nửa đã có thứ tự thành một đoạn hoàn chỉnh.

#### Điểm cần nhớ

* Điều kiện dừng thường là khi đoạn có không quá một phần tử.
* Nên tính vị trí giữa bằng `mid = left + (right - left) / 2`.
* Khi trộn, phải sao chép đầy đủ các phần tử còn dư của cả hai nửa.
* Muốn giữ tính ổn định, khi hai khóa bằng nhau nên lấy phần tử ở nửa trái trước.
* Merge Sort luôn có độ phức tạp `O(n log n)`.
* Phiên bản chuẩn dành cho mảng cần `O(n)` bộ nhớ phụ.
* Thuật toán ổn định nhưng thường không phải là sắp xếp tại chỗ.

#### Lỗi thường gặp

* Chia sai giới hạn của hai đoạn con.
* Quên sao chép phần tử còn dư sau vòng lặp trộn chính.
* Ghi đè dữ liệu trong mảng ban đầu trước khi hoàn thành việc so sánh.
* Dùng điều kiện `<` thay vì `<=` khi chọn phần tử từ nửa trái, làm mất tính ổn định.

#### Khi nên sử dụng

Merge Sort phù hợp khi cần tính ổn định, cần thời gian `O(n log n)` có thể dự đoán được, hoặc khi xử lý danh sách liên kết và dữ liệu ngoài bộ nhớ.

## So sánh nhanh: nên chọn thuật toán nào?

|Tình huống|Thuật toán phù hợp|
|-|-|
|Mảng nhỏ và cần cách cài đặt đơn giản|Selection Sort hoặc Insertion Sort|
|Mảng gần có thứ tự|Insertion Sort hoặc Bubble Sort có dừng sớm|
|Muốn hạn chế số lần đổi chỗ|Selection Sort|
|Muốn tốc độ trung bình tốt trên mảng|Quick Sort|
|Cần bảo đảm `O(n log n)` và ít bộ nhớ phụ|Heap Sort|
|Cần sắp xếp ổn định với `O(n log n)`|Merge Sort|

## Định dạng dữ liệu

Các chương trình sắp xếp có thể sử dụng kiểu bản ghi gồm hai trường:

```cpp
typedef int keytype;
typedef float othertype;

typedef struct {
    keytype key;
    othertype otherfields;
} recordtype;
```

Trong đó:

* `key` là khóa được dùng để so sánh và sắp xếp.
* `otherfields` là dữ liệu đi kèm với khóa.

Ví dụ file `data.txt`:

```text
50 5.50
10 2.00
143 8.50
0 1.50
90 6.00
```

## Yêu cầu môi trường

Bạn có thể sử dụng một trong các công cụ sau:

* Dev-C++ trên Windows.
* Visual Studio Code kết hợp với trình biên dịch GCC/G++.
* Một trình biên dịch C++ tương thích với C++11 trở lên.
* Git để tải mã nguồn và đồng bộ thay đổi với GitHub.

Kiểm tra Git và trình biên dịch:

```bash
git --version
g++ --version
```

## Giấy phép

Repository được phát hành theo [MIT License](LICENSE). Bạn có thể sử dụng và chỉnh sửa mã nguồn theo các điều khoản của giấy phép này.



