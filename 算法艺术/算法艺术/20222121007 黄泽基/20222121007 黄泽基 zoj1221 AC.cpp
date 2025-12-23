#include<iostream>

using namespace std;
const int N = 51, INF = 0x3f3f3f;
int dis[N][N];
int cas; //test case

int main()
{
    int n; //ÖÕÖ¹·ûºÅ
    while(scanf("%d", &n)!=EOF)
    {
        int cnt = 1;
        for(int i = 1; i <= N; i ++)
            for(int j = 1; j <= N; j ++)
                if(i == j) dis[i][j] = 0;
                else dis[i][j] = INF;

        for(int i = 0; i < n; i++)
        {
            int neb;//ÁÚ¾Ó
            scanf("%d", &neb);
            dis[cnt][neb] = 1;
            dis[neb][cnt] = 1;
        }
        cnt++;
        //ÓàÏÂ½Úµã
        for(int i = 0 ; i < 18; i++)
        {
            int num; //number
            scanf("%d",&num);
            while(num--)
            {
                int neb;
                scanf("%d", &neb);
                dis[cnt][neb] = 1;
                dis[neb][cnt] = 1;
            }
            cnt++;
        }

        for(int k = 1; k <= 20; k++)
            for(int i = 1; i <= 20; i++)
                for(int j = 1; j <= 20; j++)
                    dis[i][j] = min(dis[i][j], dis[i][k]+dis[k][j]);
        int ans_t;
        scanf("%d", &ans_t);
        cas++;
        printf("Test Set #%d\n", cas);
        for(int i = 0; i < ans_t; i++)
        {
            int a, b;
            scanf("%d%d", &a, &b);
            printf("%d to %d: %d\n", a, b, dis[a][b]);
        }
        printf("\n");  
    }
    return 0;
}
