int i = 0;
float fCGrade[90];          /*声明数组*/
float * pArray;               /*声明指针，注意是浮点型地址类型的指针*/
pArray = fCGrade;           /*将数组首地址赋给指针*/
*pArray = 80.0;              /*相当于fCGrade[0]*/
*(pArray + 5 + 6) = 80.0; /*相当于fCGrade[11]*/
pArray[4] = 87.0;            /*相当于fCGrade[4]*/
pArray = &fCGrade[5];     /*将fCGrade[5]的地址赋给指针*/
pArray[4] = 79.0;            /*相当于fCGrade[9]*/
