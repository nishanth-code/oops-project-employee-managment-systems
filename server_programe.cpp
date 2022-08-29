//employee mangament system software design by b2 batch
//header file section
#include<iostream>
#include<conio.h>
#include<stdlib.h>
#include<math.h>
using namespace std;
struct date_
{
    int day;
    int month;
    int year;
};

//your code begins here add comment lines befor each section and explain any complex logic if u r using

//primaray base class for creating database for employees inherit this class for further needs

class read_display//genral class for reading and displaying info may be we can replace it with operator overloading also
{
    protected:
    virtual void read() =0;
    virtual void display() =0;
    

};

class data_base: public read_display//database class inherithing read
{
     private:
         static int employee_code;
         char name[20];
         char posting[5];
         struct date_ d_o_b;
         struct date_ d_o_j;
         char qualification[10];
         float salary;
         float attendance;

};

