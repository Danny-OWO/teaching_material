#include <vector>
using namespace std;

class Solution {
public:
    int search(vector<int>& nums, int target) {
        int left = 0;
        int right = static_cast<int>(nums.size()) - 1;

        while (left <= right) {
            const int middle = left + (right - left) / 2;
            if (nums[middle] == target) {
                return middle;
            }
            if (nums[middle] < target) {
                left = middle + 1;
            } else {
                right = middle - 1;
            }
        }

        return -1;
    }
};
