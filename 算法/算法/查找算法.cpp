#include<iostream>
#include<vector>
#include"Sort.h"
using namespace std;
//时间复杂度log2n
//二分查找：默认是已经排好序的，否则需要重新排序
int binarySearch(vector<int>& arr, int target) {
    int left = 0;
    int right = arr.size() - 1;
    while (left <=right) {//当left和right指向同一个元素时就找完了
        int mid = left + (right-left) / 2;
        if (arr[mid] == target) {
            return mid;
        }
        else if (arr[mid] > target) {
            //目标值比中间值小，从左边查找
            right = mid - 1;
        }
        else {
            //目标值比中间值大,从右边查找
            left =mid+1;
        }
    }
    return -1;//没找到
}
int main() {
    vector<int> arr= {2, 1, 3, 6, 4, 78, 1};
    quickSort(arr, 0, arr.size() - 1);
    int target = 4;
    int res = binarySearch(arr, 4);
    if (res == -1) {
        cout << "没找到该值" << endl;
    }else{
        cout << "找到该值，索引为：" << res << endl;
    }
    return 0;
}