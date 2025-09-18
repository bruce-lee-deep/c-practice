#include<iostream>
#include<vector>
#include"Sort.h"
using namespace std;
//ʱ�临�Ӷ�log2n
//���ֲ��ң�Ĭ�����Ѿ��ź���ģ�������Ҫ��������
int binarySearch(vector<int>& arr, int target) {
    int left = 0;
    int right = arr.size() - 1;
    while (left <=right) {//��left��rightָ��ͬһ��Ԫ��ʱ��������
        int mid = left + (right-left) / 2;
        if (arr[mid] == target) {
            return mid;
        }
        else if (arr[mid] > target) {
            //Ŀ��ֵ���м�ֵС������߲���
            right = mid - 1;
        }
        else {
            //Ŀ��ֵ���м�ֵ��,���ұ߲���
            left =mid+1;
        }
    }
    return -1;//û�ҵ�
}
int main() {
    vector<int> arr= {2, 1, 3, 6, 4, 78, 1};
    quickSort(arr, 0, arr.size() - 1);
    int target = 4;
    int res = binarySearch(arr, 4);
    if (res == -1) {
        cout << "û�ҵ���ֵ" << endl;
    }else{
        cout << "�ҵ���ֵ������Ϊ��" << res << endl;
    }
    return 0;
}