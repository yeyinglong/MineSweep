#pragma once

class CMineMap
{
public:
    CMineMap();
    ~CMineMap();
    void Create();
    void Create(int,int,int);
    void Restart();
private:
    int ctnflag(int m, int n);

public:
    int **Map;
    int nMime;//雷数
    int mx;  //行数
    int my;   //列数
    bool Onrbtdown(int m, int n);
    bool Onlrbtdown(int m, int n);
    bool Onlbtup(int m, int n);
    bool iswin();
    int winf;
    int rMine;
    bool first;
    int timer;
};

