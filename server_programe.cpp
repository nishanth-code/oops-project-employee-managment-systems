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
       
         
    }

};
class attendance:public data_base
{  
    int attendance_matrix[10000][13][32];
    public: int days(int m,int y)
            {
                if(m==2 && y%4==0)
                return (29);
                if(m==2 && y%4!=0)
                return(28);
                if(m==1 || m==3 || m==5 || m==7|| m==8 || m==10 || m==12)
                return(31);
                return(30);
            }
            float compute(int m, int y)
            {   
                float percentage;
                int total_attendance=0;
                for(int i=1;i<=days(m,y);i++)
                {   
                    total_attendance+=attendance_matrix[y][m][i];
                }
                    percentage=(total_attendance/days(m,y))*100;
                return percentage;          
            }
            void diaplay_attendance()
            {  
                char att="p";
                for(int y=2022;y<10000;y++)
                {
                    for(int m=1;m<13;m++)
                    {
                        for(int i=1;i<=days(m,y);i++)
                        {
                            if(attendance_matrix[y][m][i]==0)
                            att="a";
                            cout<<i<<"/"<<m<<"/"<<y<<" = "<<att<<endl;
                        }
                    }
                }
            }
            void mark_attendance()
            {
               int year,month,day,day_of_week;
               time_t now= time(0);
               tm *cur = localtime(&)          
            }
};

