//employee mangament system software design by b2 batch
//header file section
#include<iostream>
#include<conio.h>
#include<stdlib.h>
#include<math.h>
#include<ctime>
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
    public:
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
    protected:
         float salary;
         float attendance;
    public:
    void read()
    {
       cout<<"\nenter the name of the employee : ";
       cin>>name;
       cout<<"\nenter the date of birth of the employee in the formate(dd/mm/yyyy) : ";
       cin>>d_o_b.day>>d_o_b.month>>d_o_b.year;
       cout<<"\nenter the date of joining of the employee in the formate(dd/mm/yyyy) : ";
       cin>>d_o_j.day>>d_o_j.month>>d_o_j.year;
       cout<<"\nenter the qualification of the employee : ";
       cin>>qualification;
       cout<<"\nenter the posting of the employee : ";
       cin>>posting;

    }
    void display()
    {
        //function body
    }

};

