typedef struct A
{
    unsigned short a0: 1;
    unsigned short a1: 1;
    unsigned short a2: 1;
    unsigned short a3: 1;
    unsigned short a4: 1;
    unsigned short a5: 1;
    unsigned short a6: 1;
    unsigned short a7: 1;

    unsigned short a8: 1;
    unsigned short a9: 1;
    unsigned short a10: 1;
    unsigned short a11: 1;
    unsigned short a12: 1;
    unsigned short a13: 1;
    unsigned short a14: 1;
    unsigned short a15: 1;
} DATATYPE;

int main(int argc, char** argv)
{
    DATATYPE p;

    unsigned short b = 234;
    memcpy(&p, &b, sizeof(short));
    printbit(p);
    sumbites1(p);

    return 0;
}
