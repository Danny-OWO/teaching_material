#include <algorithm>
#include <numeric>
#include <vector>
using namespace std;

class Solution {
public:
    int splitArray(vector<int>& nums, int k) {
        long long left = *max_element(nums.begin(), nums.end());
        long long right = accumulate(nums.begin(), nums.end(), 0LL);

        while (left < right) {
            const long long middle = left + (right - left) / 2;
            if (canSplitWithin(nums, k, middle)) {
                right = middle;
            } else {
                left = middle + 1;
            }
        }

        return static_cast<int>(left);
    }

private:
    static bool canSplitWithin(const vector<int>& nums, int k, long long limit) {
        int groups = 1;
        long long currentSum = 0;

        for (int value : nums) {
            if (currentSum + value > limit) {
                ++groups;
                currentSum = value;
                if (groups > k) return false;
            } else {
                currentSum += value;
            }
        }

        return true;
    }
};
