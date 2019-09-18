#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct StuNode
{
    char ch;
    double dfv;
    int iv;
};

//struct StuNode
//{
//    char ch;
//    int iv;
//    double dfv;
//};
//
//
//struct StuNode
//{
//    char ch;
//    int iv;
//    double dfv;
//};



int main(void)
{
    struct StuNode st;

    printf("%c %d %f\n", st.ch, st.iv, st.dfv);

    return 0;
}
