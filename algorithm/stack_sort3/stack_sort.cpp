#include<vector>
#include<iostream>

using namespace std;

void printArr(vector<int> &nums) {
    cout << "printArr:";
    for (auto const &x: nums) {
        cout << x << " ";
    }
    cout << endl;
}

// 构建最小堆
void FF(vector<int> &nums, int start, int end) {
    int i = start, j = 2 * i + 1;
    int tmp = nums[i];
    while (j <= end) {
        if (j < end && nums[j] > nums[j + 1]) {//有右孩子并且左孩子小于右孩子
            j += 1;
        }
        if (tmp <= nums[j])
            break;
        nums[i] = nums[j];
        i = j;
        j = i * 2 + 1;
    }
    nums[i] = tmp;
}

void SortFF(vector<int> &nums, int n) {
    int pos = ((n - 1) - 1) / 2;
    while (pos >= 0) {//从下往上局部，最后整体去调整成小顶堆
        FF(nums, pos, n - 1);
        pos -= 1;
        printArr(nums);
    }
    //调整完了此时这个二叉堆最上面就是最小的数
    //在数组里就是一顿调整之后，第一个元素是最小的
    pos = n - 1;
    while (pos > 0) {
        swap(nums[0], nums[pos]);
        pos -= 1;
        FF(nums, 0, pos);
//        printArr(nums);
    }
}
// 6 2 1 4

int main() {
//    int a[]={53, 17, 78, 9, 45, 65, 87, 23};
    int a[]={6, 2, 1, 4};
    vector<int> vv(a,a+sizeof(a)/sizeof(a[0]));
    printArr(vv);

    SortFF(vv, vv.size());
    for (auto const &x: vv) {
        cout << x << " ";
    }
    return 0;
}



// 降序：87 78 65 53 45 23 17 9