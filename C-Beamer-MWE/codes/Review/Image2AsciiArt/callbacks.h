#ifndef CALLBACKS_H_INCLUDED
#define CALLBACKS_H_INCLUDED

// 对区块数据求平均值
double GetAverage(unsigned char *pdata, int pixW, int pixH);
// 取区块数据的中值
double GetMedian(unsigned char *pdata, int pixW, int pixH);
// 对区块数据用LOG算子进行处理
double GetLoG(unsigned char *pdata, int pixW, int pixH);
#endif // CALLBACKS_H_INCLUDED
