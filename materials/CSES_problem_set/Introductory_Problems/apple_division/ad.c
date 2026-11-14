#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

void pick(long long n, long long lst[n], long long i, long long sum, long long* ans, long long* ssum)
{
    if (i == n)
    {
        if (llabs((*ssum) - sum * 2) < *ans)
        {
            *ans = llabs((*ssum) - sum * 2);
        }
        return;
    }

    pick(n,lst,i+1,sum,ans,ssum);
    pick(n,lst,i+1,sum+lst[i],ans,ssum);
    
}



long long main()
{
    long long n;
    scanf("%lld", &n);
    long long lst[n];
    long long ssum = 0;
    for (long long i = 0; i < n; i++)
    {
        scanf("%lld", &lst[i]);
        ssum+=lst[i];
    }

    long long ans = LLONG_MAX;

    long long used[n];
    for (long long i = 0; i < n; i++)
    {
        used[i] = 0;
    }

    pick(n, lst, 0, 0, &ans, &ssum);
    printf("%lld", ans);
}