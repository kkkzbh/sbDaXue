

#ifdef P1719

#include<iostream>

#define max(A,B) ((A) > B ? (A) : (B))
constexpr int size = 120 + 10;

int matrix[size][size];
int prefix[size][size];
int arr[size];
int dp[size];
int ans;

void packarr(int a,int b,int n)
{
    for(int i = 1;i<n;++i)
    {
        arr[i] = prefix[i][b] - prefix[i][a];
    }
}

int solve(int n)
{
    ans = 0;
    for(int i = 1;i<=n;++i)
    {
        dp[i] = max(arr[i],dp[i-1] + arr[i]);
        ans = max(ans,dp[i]);
    }
    return ans;
}

int main()
{
    int n;
    std::cin >> n;
    for(int i = 1;i <= n;++i)
    {
        for(int j = 1;j <= n;++j)
        {
            std::cin >> matrix[i][j];
        }
    }
    for(int i = 1;i<=n;++i)
    {
        for(int j = 1;j<=n;++j)
        {
            prefix[i][j] = matrix[j][i] + prefix[i][j-1];
        }
    }
    int ans = 0;
    for(int i = 1;i<=n;++i)
    {
        for(int j = i+1;j<=n;++j)
        {
            packarr(i,j,n);
            ans = max(ans,solve(n));
        }
    }
    std::cout << ans;

    return 0;
}


#endif

