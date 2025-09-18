#include<iostream>
#include<vector>
#include<algorithm>
#include"Sort.h"
using namespace std;
//ʱ�临�Ӷȣ�n?
//ð����������
void bubbleSort(vector<int>& arr) {
	int n = arr.size();
	//ֻ�����n-1����ѭ��
	for (int i = 0; i < n; i++) {
		//����n-i-i����ѭ����ÿ��ѭ������������ŵ����ұ�
		for (int j = 0; j < n - 1 - i; j++) {
			//�Ƚ�
			if (arr[j] > arr[j + 1]) {
				//����
				swap(arr[j], arr[j + 1]);
			}
		}
	}
}

//ѡ������ÿ�δ�δ������������ҳ���С�����뿪ͷ����λ��
void selectionSort(vector<int>& arr) {
	//��ȡ����Ԫ�ظ���
	int n = arr.size();
	for (int i = 0; i < n - 1; i++) {
		int min = i;
		for (int j = i + 1; j < n; j++) {
			if (arr[j] < arr[i]) {
				min = j;//������Сֵ������
			}
		}
		//���ҵ�����СԪ����δ���򲿷ֵĵ�һ��Ԫ�ؽ���λ��
		if (min != i) {
			swap(arr[i], arr[min]);
		}
	}
}
//�������򣺽������Ϊ�������δ�������飬ÿ�δ�δ������ѡһ�����뵽�������������ȷλ��
void insertionSort(vector<int>& arr) {
	int n = arr.size();
	//��һ��Ԫ��Ĭ����������ѭ��ֻ��n-1��
	for (int i = 1; i < n; i++) {
		int key = arr[i];//���浱ǰҪ�����Ԫ��
		int j = i - 1;//�����򲿷ֵ����һ��Ԫ������
		//�Ӻ���ǰ��
		while (j >= 0 && arr[j] > key) {
			//����
			arr[j + 1] = arr[j];
			j--;
		}
		//����Ԫ��С��keyʱ����ѭ��
		arr[j + 1] = key;
	}
}
//ϣ������
void shellSort(vector<int>& arr) {
	int n = arr.size();
	//gapָÿ���������е�����Ԫ����ԭ���������������gap��Ԫ�أ����ÿһ��gap�ܽ�ԭ����ָ��n/gap���飬ÿ������в�������
	/*for (int gap = n / 2; gap > 0; gap /= 2) {//��ʼgapΪn/2��ÿ��ѭ��gap���룬ֱ��gap=1
		//���з�����ÿ��Ĳ�������
		//��Ӧÿһ��gap��һ���ᱻ��Ϊgap����,ѭ��gap��
		for (int j = 0; j < gap; j++) {
			//����ÿһ����Ĳ�������
			for (int k = 0; k < n / gap - 1; k++) {
				//�Һ���λ��
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
		//��ѭ������ÿ�������н��д���
		for (int i = gap; i < n; i++) {
			int key = arr[i];//��¼Ҫ�����Ԫ��
			int j;
			for (j = i; j >= gap && arr[j-gap] > key; j -= gap) {
				//����λ��
				arr[j] = arr[j - gap];
			}
			//�ҵ������λ�ú󣬲���key
			arr[j] = key;
		}
	}
}

//ʱ�临�Ӷȣ�nlogn
//�鲢�����Ȳ��ֱ��ÿ����ֻ�е���Ԫ�أ���Ϊ����Ԫ������Ȼ����ģ�Ȼ��ӵ���Ԫ�ؿ�ʼ����ϲ�
//�����ṩ������ӿ�
void merge(vector<int>& arr, int left, int mid, int right, vector<int>& temp) {
	//�ú�����Ҫ����ϲ�������ʵҲ˳��������
	int t = 0;//temp������
	int i = left;//���������ʼ
	int j = mid + 1;//���������ʼ
	while (i <= mid && j <= right) {
		if (arr[i] <= arr[j]) {
			temp[t++] = arr[i++];//�ѽ�С���ȷŽ�temp
		}
		else {
			temp[t++] = arr[j++];
		}
	}
	//�������ʣ�µ�Ԫ��
	while (i <= mid) {
		temp[t++] = arr[i++];
	}
	//����������ʣ��Ԫ��
	while (j <= right) {
		temp[t++] = arr[j++];
	}
	//��temp���Ƹ�ԭ����
	t = 0;
	while (left <= right) {
		arr[left++] = temp[t++];
	}
}
void mergeSort(vector<int>& arr, int left, int right, vector<int>& temp) {
	//���������Ҫͨ���ݹ�һ�δεط��飬����ٵ��úϲ�����ʵ�ֺϲ�
	if (left < right) {//���������֤�˵�����Ϊ����Ԫ��ʱleft=right���������ÿ�ʼ�ع�
		int mid = (left + right) / 2;
		mergeSort(arr, left, mid, temp);//�����߽��з�������
		mergeSort(arr, mid + 1, right, temp);//���Ұ�߽��з�������
		merge(arr, left, mid,right, temp);
	}
}
//�����ṩ������ӿ�
void sort(vector<int>& arr) {
	if (arr.empty() || arr.size() <= 1)return;
	vector<int>temp(arr.size());//������ʱ����������ʱװ�ź����Ԫ��
	mergeSort(arr, 0, arr.size() - 1, temp);
}
//��������
int partition(vector<int>&arr,int low,int high) {//�˺����������鰴��׼���Ȼ�׼��ͱȻ�׼С�ķֵ����࣬�������ػ�׼����ȷλ��
	//����׼��Ϊ�����
	int pivot = arr[high];
	//����һ����ָ����ʵ�ֽ���
	int i =low-1;
	//��ʼ��low�����pivot�Ƚ�
	for (int j = low; j <=high-1; j++) {
		if (arr[j] <= pivot) {//��ʱ˵��������Ҫ��ʼ��ֵ
			//����
			i++;
			swap(arr[i], arr[j]);
		}
	}
	//ѭ��֮���������ڵ���i��ֵ���Ȼ�׼��С�ڵ���i-2��ֵ���Ȼ�׼С����˽�����Ϊi-1��ֵ���׼����λ��
	swap(arr[high], arr[i+1]);
	return i+1;
}
void quickSort(vector<int>& arr, int low, int high) {
	//���������ݹ������
	if (low < high) {//��low>=highʱ����Ԫ��Ϊ1��0����������
		//�õ���׼ֵ
		int pi = partition(arr, low, high);
		//�ݹ�Ի�׼ֵ���ߵ������ٴν�������
		quickSort(arr, low, pi - 1);
		quickSort(arr, pi + 1, high);
	}
}
//������
void heapSort(vector<int>& arr) {
	//���γ�����
	make_heap(arr.begin(), arr.end());
	//ʹ��sort_heap������������
	//sort_heap(arr.begin(), arr.end());
	int n = arr.size();
	//ÿ�ν��Ѷ�Ԫ�ط��ڶ�ĩβ��Ȼ���ٶ�ʣ�µ�Ԫ���γɶ�
	for (int i = n; i > 1; i--) {
		//���Ѷ�Ԫ���Ƶ���ǰĩβ��Ȼ���ʣ�µ�Ԫ���ٴγɶ�
		pop_heap(arr.begin(), arr.begin() + i);
	}
}