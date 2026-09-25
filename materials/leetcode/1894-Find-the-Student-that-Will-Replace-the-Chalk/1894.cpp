class Solution {
public:
    int chalkReplacer(vector<int>& chalk, int k) 
    {
        long long turn = 0;
        for (int i = 0; i < chalk.size(); i++)
        {
            turn += chalk[i];
        }    

        k %= turn;

        if (k == 0)
        {
            return 0;
        }
        for (int j = 0; j < chalk.size(); j++)
        {
            k -= chalk[j];
            if (k < 0)
            {
                return j;
            }
        }
        return -1;
    }
    
};