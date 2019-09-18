int i = 0;
float fCGrade[90];        /*声明数组*/
fCGrade[0] = 80.0;        /*下标访问*/
fCGrade[5 + 6] = 90.0;   /*表达式访问*/
fCGrade[i + 80] = 78.0;
*(fCGrade + 4) = 87.0;    /*相当于fCGrade[4], 注意求内容运算符*/
(&fCGrade[5])[4] = 79.0; /*相当于fCGrade[9],
                                        取得fCGrade[5]的地址，再偏移4个元素*/
