// 函数原型
int SumArray(int n, int a[n]);    /*version1*/

int SumArray(int n, int a[*]);    /*version2a*/
int SumArray(int, int a[*]);      /*version2b*/

int SumArray(int n, int a[]);     /*version3a*/
int SumArray(int, int []);        /*version3b*/
