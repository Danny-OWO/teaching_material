
class Solution {
public:
    vector<int> answerQueries(vector<int>& nums, vector<int>& queries) {
        sort(nums.begin(), nums.end());

        vector<int> prefix;
        int temp = 0;

        for (int i = 0; i < nums.size(); i++) {   
            temp += nums[i];
            prefix.push_back(temp);
        }

        vector<int> ans;

        for (int j = 0; j < queries.size(); j++) {
            int need = queries[j];

            int count = upper_bound(prefix.begin(), prefix.end(), need)
                        - prefix.begin();

            ans.push_back(count);
        }

        return ans;
    }
};