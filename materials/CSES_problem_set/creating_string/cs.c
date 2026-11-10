#include <stdio.h>
#include <string.h>

void per(int used_char[26], int max_char[26], char ans[9], int ans_length, int end)
{
    if (ans_length == end)
    {
        for (int i = 0; i < end; i++)
        {
            printf("%c", ans[i]);
        }
        printf("\n");
        return;
    }

    for (int i = 0; i < 26; i++)
    {
        if (used_char[i] < max_char[i])
        {
            ans[ans_length] = (char) ('a'+i); ans_length++;
            used_char[i]+=1;
            per(used_char, max_char, ans, ans_length, end);
            ans_length--;
            used_char[i]-=1;
        }
    }
}





int main()
{
    char s[9];
    scanf("%s", s);
    int used_char[26] = {0};
    int max_char[26] = {0};
    long long x = 1;
    for (int i = 0 ; i < strlen(s); i++)
    {
        max_char[s[i] - 'a'] += 1;
        x *= (long long) (i+1);
    }
    for (int i = 0 ; i < 26; i++)
    {
        if (max_char[i] != 0)
        {
            for (int j = 1; j <= max_char[i]; j++)
            {
                x /= (long long) j;
            }
        }        
    }



    printf("%lld\n", x);
    char ans[9] = {};
    int ans_length = 0;
    per(used_char, max_char, ans, ans_length, strlen(s));
}