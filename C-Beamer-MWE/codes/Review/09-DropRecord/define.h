#ifndef DEFINE_H_INCLUDED
#define DEFINE_H_INCLUDED

#define NAMELEN 20
#define NGRADE 3

typedef struct
{
    unsigned int ID;
    char name[NAMELEN];
    double grade[NGRADE];
    double average;
    unsigned int rank;
} Student;


#endif // DEFINE_H_INCLUDED
