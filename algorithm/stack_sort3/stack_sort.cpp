#include<vector>
#include<iostream>

using namespace std;

// 构建最小堆
void FF(vector<int> &nums, int start, int end) {
    int i = start, j = 2 * i + 1;
    int tmp = nums[i];
    while (j <= end) {
        if (j < end && nums[j] > nums[j + 1]) {
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
    int pos = (((n - 1) - 1) / 2);
    while (pos >= 0) {
        FF(nums, pos, n - 1);
        pos -= 1;
    }

    pos = n - 1;
    while (pos > 0) {
        swap(nums[0], nums[pos]);
        pos -= 1;
        FF(nums, 0, pos);
    }
}

int main() {
    int a[]={53, 17, 78, 9, 45, 65, 87, 23};
    vector<int> vv(a,a+8);

    SortFF(vv, vv.size());
    for (auto const &x: vv) {
        cout << x << " ";
    }
    return 0;
}

// 降序：87 78 65 53 45 23 17 9