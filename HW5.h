起泡排序
void bubbleSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}


插入排序
void insertionSort(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}



选择排序
void selectionSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }
        int temp = arr[i];
        arr[i] = arr[minIndex];
        arr[minIndex] = temp;
    }
}


归并排序
void merge(int arr[], int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;

    int L[n1], R[n2];
    for (int i = 0; i < n1; i++) {
        L[i] = arr[l + i];
    }
    for (int j = 0; j < n2; j++) {
        R[j] = arr[m + 1 + j];
    }

    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(int arr[], int l, int r) {
    if (l >= r) {
        return;
    }

    int m = l + (r - l) / 2;
    mergeSort(arr, l, m);
    mergeSort(arr, m + 1, r);
    merge(arr, l, m, r);
}


快速排序
void quickSort(int arr[], int left, int right) {
    int i = left, j = right;
    int tmp, pivot = arr[(left + right) / 2];

    /* partition */
    while (i <= j) {
        while (arr[i] < pivot)
            i++;
        while (arr[j] > pivot)
            j--;
        if (i <= j) {
            tmp = arr[i];
            arr[i] = arr[j];
            arr[j] = tmp;
            i++;
            j--;
        }
    };

    /* recursion */
    if (left < j)
        quickSort(arr, left, j);
    if (i < right)
        quickSort(arr, i, right);
}




冒泡排序（Bubble Sort）
冒泡排序是一种基础的排序算法，属于交换排序。它重复地遍历要排序的数列，一次比较两个元素，如果它们的顺序错误就交换过来。最差的时间复杂度是O(n^2)。

插入排序（Insertion Sort）
插入排序也是一种基础的排序算法，属于插入排序。其基本操作是将一个记录插入到已经排好序的有序表中，从而得到一个新的、记录数增1的有序表。插入排序的最坏复杂度也是O(n^2)。

选择排序（Selection Sort）
选择排序也是一种基础的排序算法，属于选择排序。选择排序的基本思想是：每一次从待排序的数据元素中选出最小（或最大）的一个元素，存放在序列的起始位置，直到全部待排序的数据元素排完为止。时间复杂度是O(n^2)。

归并排序（Merge Sort）
归并排序是一种稳定的排序算法，采用分治法策略。它的基本思想是先将待排序的序列分组，每组之间进行排序，再将组内元素进行排序，最后再合并。时间复杂度是O(nlog n)。归并排序可以实现外部排序，即可以对大文件进行排序。

快速排序（Quick Sort）
快速排序是一种基于分治的排序算法，时间复杂度为O(nlogn)，在平均情况下是最优秀的排序算法之一。它的基本思想是选取一个基准元素，将序列中小于等于基准元素的元素放到基准元素前面，将大于等于基准元素的元素放到基准元素后面，再分别对基准元素前面的序列和后面的序列递归地进行排序。

综合考虑时间复杂度和实际运行效率，快速排序的性能比其他四种算法都要优秀一些。
