#include  <stdio.h>

int main()
{
    enum weeks {MON, TUE, WED, THU, FRI, SAT, SUN};
    enum weeks today;
    enum response {no,  yes,  none};
    enum response answer;

    today  = TUE;
    answer = yes;

    if (answer == yes)
        printf("Today is Tuesday.\n");
    else
        printf("Today is NOT Tuesday.\n");


    return 0;
}

