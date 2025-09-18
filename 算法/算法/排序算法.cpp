#include<iostream>
#include<vector>
#include<algorithm>
#include"Sort.h"
using namespace std;
//时间复杂度：n?
//冒泡排序：升序
void bubbleSort(vector<int>& arr) {
	int n = arr.size();
	//只需进行n-1次外循环
	for (int i = 0; i < n; i++) {
		//进行n-i-i次内循环，每次循环会把最大的数放到最右边
		for (int j = 0; j < n - 1 - i; j++) {
			//比较
			if (arr[j] > arr[j + 1]) {
				//交换
				swap(arr[j], arr[j + 1]);
			}
		}
	}
}

//选择排序：每次从未排序的数组中找出最小的数与开头交换位置
void selectionSort(vector<int>& arr) {
	//获取数组元素个数
	int n = arr.size();
	for (int i = 0; i < n - 1; i++) {
		int min = i;
		for (int j = i + 1; j < n; j++) {
			if (arr[j] < arr[i]) {
				min = j;//更新最小值的索引
			}
		}
		//将找到的最小元素与未排序部分的第一个元素交换位置
		if (min != i) {
			swap(arr[i], arr[min]);
		}
	}
}
//插入排序：将数组分为已排序和未排序两组，每次从未排序中选一个插入到已排序数组的正确位置
void insertionSort(vector<int>& arr) {
	int n = arr.size();
	//第一个元素默认已排序，外循环只需n-1次
	for (int i = 1; i < n; i++) {
		int key = arr[i];//保存当前要插入的元素
		int j = i - 1;//已排序部分的最后一个元素索引
		//从后往前找
		while (j >= 0 && arr[j] > key) {
			//后移
			arr[j + 1] = arr[j];
			j--;
		}
		//当有元素小于key时跳出循环
		arr[j + 1] = key;
	}
}
//希尔排序
void shellSort(vector<int>& arr) {
	int n = arr.size();
	//gap指每个子数组中的相邻元素在原来的数组中相隔了gap个元素，因此每一个gap能将原数组分割成n/gap个组，每个组进行插入排序
	/*for (int gap = n / 2; gap > 0; gap /= 2) {//初始gap为n/2，每次循环gap减半，直到gap=1
		//进行分组后的每组的插入排序
		//对应每一个gap，一共会被分为gap个组,循环gap次
		for (int j = 0; j < gap; j++) {
			//处理每一个组的插入排序
			for (int k = 0; k < n / gap - 1; k++) {
				//找合适位置
				if (arr[gap + j] < arr[j]) {
					int temp = arr[gap+j];
					arr[gap+j] = arr[j];
					arr[j] = temp;
				}
			}
		}

	}*/
	/*for (int gap = n / 2; gap > 0; gap /= 2) {
		for (int i = gap; i < n; i++) {
			int key = arr[i];
			int j;
			for (j = i; j >= gap && arr[j - gap] > key; j -= gap) {
				arr[j]=arr[j - gap];
			}
			arr[j] = key;
		}
	}*/
	for (int gap = n / 2; gap > 0; gap /= 2) {
		//中循环：对每个子序列进行处理
		for (int i = gap; i < n; i++) {
			int key = arr[i];//记录要插入的元素
			int j;
			for (j = i; j >= gap && arr[j-gap] > key; j -= gap) {
				//后移位置
				arr[j] = arr[j - gap];
			}
			//找到放入的位置后，插入key
			arr[j] = key;
		}
	}
}

//时间复杂度：nlogn
//归并排序：先拆分直至每个组只有单个元素，因为单个元素是天然有序的，然后从单个元素开始排序合并
//对外提供的排序接口
void merge(vector<int>& arr, int left, int mid, int right, vector<int>& temp) {
	//该函数主要处理合并，但其实也顺便排了序
	int t = 0;//temp的索引
	int i = left;//左数组的起始
	int j = mid + 1;//右数组的起始
	while (i <= mid && j <= right) {
		if (arr[i] <= arr[j]) {
			temp[t++] = arr[i++];//把较小的先放进temp
		}
		else {
			temp[t++] = arr[j++];
		}
	}
	//处理左边剩下的元素
	while (i <= mid) {
		temp[t++] = arr[i++];
	}
	//处理右数组剩余元素
	while (j <= right) {
		temp[t++] = arr[j++];
	}
	//将temp复制给原数组
	t = 0;
	while (left <= right) {
		arr[left++] = temp[t++];
	}
}
void mergeSort(vector<int>& arr, int left, int right, vector<int>& temp) {
	//这个函数主要通过递归一次次地分组，最后再调用合并函数实现合并
	if (left < right) {//这个条件保证了当被分为单个元素时left=right会跳出调用开始回归
		int mid = (left + right) / 2;
		mergeSort(arr, left, mid, temp);//对左半边进行分组排序
		mergeSort(arr, mid + 1, right, temp);//对右半边进行分组排序
		merge(arr, left, mid,right, temp);
	}
}
//对外提供的排序接口
void sort(vector<int>& arr) {
	if (arr.empty() || arr.size() <= 1)return;
	vector<int>temp(arr.size());//创建临时数组用于暂时装排好序的元素
	mergeSort(arr, 0, arr.size() - 1, temp);
}
//快速排序
int partition(vector<int>&arr,int low,int high) {//此函数负责将数组按基准将比基准大和比基准小的分到两侧，并将返回基准的正确位置
	//将基准设为最左边
	int pivot = arr[high];
	//设置一个慢指针来实现交换
	int i =low-1;
	//开始从low逐个与pivot比较
	for (int j = low; j <=high-1; j++) {
		if (arr[j] <= pivot) {//此时说明新数组要开始放值
			//交换
			i++;
			swap(arr[i], arr[j]);
		}
	}
	//循环之后，索引大于等于i的值都比基准大，小于等于i-2的值都比基准小，因此将索引为i-1的值与基准互换位置
	swap(arr[high], arr[i+1]);
	return i+1;
}
void quickSort(vector<int>& arr, int low, int high) {
	//控制跳出递归的条件
	if (low < high) {//当low>=high时组内元素为1或0，即可跳出
		//得到基准值
		int pi = partition(arr, low, high);
		//递归对基准值两边的数组再次进行排序
		quickSort(arr, low, pi - 1);
		quickSort(arr, pi + 1, high);
	}
}
//堆排序
void heapSort(vector<int>& arr) {
	//先形成最大堆
	make_heap(arr.begin(), arr.end());
	//使用sort_heap将堆升序排列
	//sort_heap(arr.begin(), arr.end());
	int n = arr.size();
	//每次将堆顶元素放在堆末尾，然后再对剩下的元素形成堆
	for (int i = n; i > 1; i--) {
		//将堆顶元素移到当前末尾，然后对剩下的元素再次成堆
		pop_heap(arr.begin(), arr.begin() + i);
	}
}