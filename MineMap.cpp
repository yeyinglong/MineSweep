#include "MineMap.h"
#include <stdlib.h>
#include <time.h>

CMineMap::CMineMap()
    : nMime(0)
    , winf(0)
    , rMine(0)
{
    mx = 20; my = 15;
    nMime = 50;
    Map=NULL;
}


CMineMap::~CMineMap()
{
}
//重新布雷
void CMineMap::Restart()
{
    int i,j;
    for (i = 0; i < mx; i++)
        for (j = 0; j < my; j++)
            Map[i][j] = 100;
    srand(time(NULL));
    for (i = 0; i < nMime; i++)
    {
        int m = rand() % mx;
        int n = rand() % my;
        if (Map[m][n] != 99)
            Map[m][n] = 99;
        else
            i--;
    }
    for (i = 0; i < mx; i++)
        for (j = 0; j < my; j++)
        {
            if (Map[i][j] == 99)
            {
                int m, n;
                for (m = -1; m < 2; m++)
                    for (n = -1; n < 2; n++)
                    {
                        if ((i + m >= mx) || (j + n >= my) || (i + m<0) || (j + n<0) || (Map[i + m][j + n] == 99))
                            continue;
                        Map[i + m][j + n]++;
                    }
            }
        }
    winf = 1;
    rMine = nMime;
    first = 1;
    timer = 0;
}
//动态数组分配内存并布雷
void CMineMap::Create()
{
    int i;
    if(Map!=NULL)
    {
        for(i=0;i<mx;i++)
        {
            delete Map[i];
        }
        delete Map;
        Map=NULL;
    }
    Map = new int*[mx];
    for (i = 0; i < mx; i++)
    {
        Map[i] = new int[my];
    }
    Restart();
}
//动态数组分配内存并布雷，传入参数：　列数　行数　雷数
void CMineMap::Create(int cx,int cy,int ms)
{
    int i;
    if(Map!=NULL)
    {
        for(i=0;i<mx;i++)
        {
            delete Map[i];
        }
        delete Map;
        Map=NULL;
        mx=cx;
        my=cy;
        nMime=ms;
    }
    Map = new int*[mx];
    for (i = 0; i < mx; i++)
    {
        Map[i] = new int[my];
    }
    Restart();
}

bool CMineMap::Onlbtup(int m, int n)
{
    if(winf==0||winf==2)
        return false;
    if (m >= mx || n >= my || m < 0 || n < 0 || Map[m][n] <= 90)
        return false;
    if (Map[m][n] >= 101 && Map[m][n] <= 108)
    {
        Map[m][n] -= 100;
        first = 0;
        iswin();
        return true;
    }
    if (Map[m][n] == 100)
    {   //点击的地放周围都没雷，则递归点击周围８个
        Map[m][n] -= 100;
        Onlbtup(m - 1, n);
        Onlbtup(m + 1, n);
        Onlbtup(m, n - 1);
        Onlbtup(m, n + 1);
        Onlbtup(m - 1, n - 1);
        Onlbtup(m + 1, n - 1);
        Onlbtup(m - 1, n + 1);
        Onlbtup(m + 1, n + 1);
    }
    if (Map[m][n] == 99)
    {   //中雷了
        if (first)
        {
            rMine--;
            int a, b, t = 0;
            for (a = -1; a < 2; a++)
                for (b = -1; b < 2; b++)
                {
                    if ((a + m < mx) && (b + n < my) && (a + m >= 0) && (b + n >= 0) && (a || b))
                    {
                        if (Map[a + m][b + n] > 99)
                            Map[a + m][b + n]--;
                        if (Map[a + m][b + n] == 99)
                            t++;
                    }
                }
            first = 0;
            Map[m][n] = 100 + t;
            Onlbtup(m, n);
            return true;
        }
        int i, j;
        for (i = 0; i < mx; i++)
            for (j = 0; j < my; j++)
            {
                if (Map[i][j] == 99)
                    Map[i][j] = -1;
                if (Map[i][j]>49 && Map[i][j] < 60)
                    Map[i][j] = -2;
            }
        winf = 0;
    }
    return true;
}
//右键插小红旗
bool CMineMap::Onrbtdown(int m, int n)
{
    if(winf==0||winf==2)
        return false;
    if (m >= mx || m < 0 || n >= my || n < 0||Map[m][n]<40)
        return false;
    if (Map[m][n]>90)
    {
        Map[m][n] -= 50;
        rMine--;
    }
    else if (Map[m][n] > 40 && Map[m][n] < 60)
    {
        rMine++;
        Map[m][n] += 50;
    }
    return true;
}


bool CMineMap::Onlrbtdown(int m, int n)
{
    if (m >= mx || m < 0 || n >= my || n < 0||Map[m][n]>40)
        return false;
    if (Map[m][n] == ctnflag(m, n))
    {
        Onlbtup(m - 1, n);
        Onlbtup(m + 1, n);
        Onlbtup(m, n - 1);
        Onlbtup(m, n + 1);
        Onlbtup(m - 1, n - 1);
        Onlbtup(m + 1, n - 1);
        Onlbtup(m - 1, n + 1);
        Onlbtup(m + 1, n + 1);
    }
    return true;
}

int CMineMap::ctnflag(int m, int n)
{
    int t = 0;
    if (m >= mx || m < 0 || n >= my || n < 0)
        return -1;
    int a, b;
    for (a = -1; a < 2; a++)
        for (b = -1; b < 2; b++)
        {
            if ((m + a >= mx) || (n + b >= my) || (m + a<0) || (n + b<0) || (Map[m + a][n + b] > 60) || (Map[m + a][n + b] < 40))
                continue;
            t++;
        }
    return t;
}
//判断是否赢了
bool CMineMap::iswin()
{
    int i, j;
    for (i = 0; i < mx; i++)
    {
        for (j = 0; j < my; j++)
        {
            if (Map[i][j]>99)
                return false;
            if (Map[i][j]>49 && Map[i][j] < 59)
                return false;
        }
    }
    winf = 2;
    return true;
}
