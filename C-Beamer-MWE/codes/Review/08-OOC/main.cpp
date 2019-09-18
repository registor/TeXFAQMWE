#include <iostream>

using namespace std;
class Base
{
protected:
    int x;
public:
    virtual void Print()
    {
        cout<<"Base:"<<x<<endl;
    }
    virtual void ShowParameter(string par)
    {
        cout<<"Base:"<<par<<endl;
    }
};
class Derive1:public Base
{
private:
    int y;
public:
    Derive1(int x,int y)
    {
        this->x=x;
        this->y=y;
    }
    virtual void Print()
    {
        cout<<"Derive1"<<x<<" "<<y<<endl;
    }
    virtual void ShowParameter(string par)
    {
        cout<<"Derive1:"<<par<<endl;
    }
};

class Derive2:public Base
{
private:
    int z;
public:
    Derive2(int x, int z)
    {
        this->x=x;
        this->z=z;
    }
    virtual void Print()
    {
        cout<<"Derive2"<<x<<" "<<z<<endl;
    }
    virtual void ShowParameter(string par)
    {
        cout<<"Derive2:"<<par<<endl;
    }
};

//每个类：一个结构体定义；一组函数定义
//结构体定义中包含指向虚函数表的指针和对应类中的成员
//函数与类中定义的成员函数
struct base
{
    void (**vtable)(base* const);
    int x;
};

void Print0(base* const this0)
{
    cout<<"Base:"<<this0->x<<endl;
}

void ShowParameter0(base* const this0,string par)
{
    cout<<"Base:"<<par<<endl;
}

struct derive1
{
    void (**vtable)(derive1* const);
    int x;
    int y;
};

void Print1(derive1* const this0)
{
    cout<<"Derive1:"<<this0->x<<" "<<this0->y<<endl;
}

void ShowParameter1(derive1* const this0,string par)
{
    cout<<"Derive1:"<<par<<endl;
}

struct derive2
{
    void (**vtable)(derive2* const);
    int x;
    int z;
};

void Print2(derive2* const this0)
{
    cout<<"Derive2:"<<this0->x<<" "<<this0->z<<endl;
}

void ShowParameter2(derive2* const this0,string par)
{
    cout<<"Derive2:"<<par<<endl;
}

//每个类一个虚函数表
void (*bv[])(base* const)={Print0,(void (*)(base* const))ShowParameter0};
void (*dv1[])(derive1* const)={Print1,(void(*)(derive1* const))ShowParameter1};
void (*dv2[])(derive2* const)={Print2,(void(*)(derive2* const))ShowParameter2};

void Construct(base* this0)
{
    this0->vtable=bv;
    this0->x=0;
}

void Construct(derive1* this0)
{
    this0->vtable=dv1;
    this0->x=0;
    this0->y=1;
}
void Construct(derive2* this0)
{
    this0->vtable=dv2;
    this0->x=0;
    this0->z=2;
}

int main()
{
    Base *bs[10];
    for(int i=0;i<10;i+=2)
    {
        bs[i]=new Derive1(0,1);
        bs[i+1]=new Derive2(0,2);
    }
    for(int i=0;i<10;i++)
    {
        bs[i]->Print();
        bs[i]->ShowParameter("hello");
        cout<<endl;
    }

    cout<<"------------------------"<<endl;
    base* b[10];
    for(int i=0;i<10;i+=2)
    {
        derive1* d1=new derive1;
        Construct(d1);
        b[i]=(base*)d1;
        derive2* d2=new derive2;
        Construct(d2);
        b[i+1]=(base*)d2;
    }
    for(int i=0;i<10;i++)
    {
        b[i]->vtable[0](b[i]);
        ((void (*)(base* const,string))b[i]->vtable[1])(b[i],"test");
        cout<<endl;
    }
    return 0;
}
