#define _CRT_SECURE_NO_WARNINGS
//保留三位小数
//c->0.01~5.20
#include<iostream>

using namespace std;
const double eps = 1e-4; //no int, is double can get float point

int solve(float num, double ans, int cnt)
{
    if (ans >= num) return cnt;
    return solve(num, ans + 1.0 / (cnt + 1), cnt + 1);
}
int main()
{
    float c;
    while (scanf("%f", &c) && c != 0.00)
    {
        double ans = 0.0;
        printf("%d card(s)\n", solve(c, ans, 1) - 1);
    }
    return 0;
}
