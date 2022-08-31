//employee mangament system software design by b2 batch
//header file section
#include<iostream>
#include<conio.h>
#include<stdlib.h>
#include<math.h>
#include<ctime>
#include<fstream>
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
    // virtual void read() =0;
    virtual void display() =0;
    

};

class data_base: public read_display//database class inherithing read
{
      protected:
         char name[20];
         char posting[5];
         struct date_ d_o_b;
         struct date_ d_o_j;
         char qualification[10];
         float salary;
         float attendance;
         
    public:
         static int employee_id;

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
       employee_id+=1;
       cout<<"\nyour employee id is : "<<employee_id;

    }
    void display()
    {
      cout<<"name : "<<name<<endl;
      cout<<"date of birth : "<<d_o_b.day<<"/"<<d_o_b.month<<"/"<<d_o_b.year<<endl;
      cout<<"date of joining : "<<d_o_j.day<<"/"<<d_o_b.month<<"/"<<d_o_j.year<<endl;
      cout<<"qualification : "<<qualification<<endl;
      cout<<"posting : "<<posting; 
         
    }

};
int data_base:: employee_id=132456;
class attendance:public virtual data_base
{  
    protected:
        int attendance_matrix[150][13][32];
        ofstream outfile;
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
                    percentage=(total_attendance/(days(m,y)-4))*100;
                
                return percentage;          
            }
            
            void display(int m,int y)
            {  
                char att='a';
                int d=1;
                cout<<"\t"<<m<<"-"<<y<<endl;
                cout<<"Sun\tMon\tTue\tWed\tThur\tFri\tSat\n";
                for(int i=1;i<=days(m,y);i+=7)
                {   cout<<"-\t";
                    d++;
                    for(int j=1;j<7 && d<=days(m,y);j++)
                    {
                            if(attendance_matrix[y][m][d]==0)
                            att='p';
                            cout<<att<<"\t";
                            d++;
                    }
                    cout<<"\n";
                }
            }
            void mark_attendance()
            {
               int year,month,day,day_of_week;
               time_t now= time(0);
               tm *cur = localtime(&now);
               char* log = ctime(&now);
               year=1900+cur->tm_year;
               month=1+cur->tm_mon;
               day=cur->tm_mday;
               day_of_week=cur->tm_wday;
               if(day_of_week == 0)
               {
                attendance_matrix[year][month][day]= 0;
                return ;
               }
               attendance_matrix[year][month][day]=1;
               outfile.open("check_in.txt");
               outfile<<employee_id<<" checked in at :"<<log<<endl;
               outfile.close();
               cout<<"\nentered log details sucessfully";

               


            }
            void checkout()
            {
               time_t now= time(0);
               char* log = ctime(&now);
               outfile.open("check_out.txt");
               outfile<<employee_id<<" checked out at :"<<log<<endl;
               outfile.close();
               cout<<"\nentered log details sucessfully";
               
             }
};


class salary:public attendance, virtual data_base

{
    
    
    float basic,da,hra,lta,pf,esi,gross_sal,tax,salary,atd,newsalary;
    public:void read_emp_details()
    {
        // cout<<"Employee id:\n" ;
        // cin>>emp_id;
        cout<<"Enter basic salary:\n" ;
        cin>>basic;
    }
    void find_net_salary()
    {
        da=(0.5*basic);
        hra=(0.4*basic)+da;
        lta=(0.1*basic);
        pf=(0.12*basic)+da;
        esi=(0.0075*basic);
        gross_sal=basic+da+hra+lta;
        if(gross_sal<=250000)
            tax=0;
        else if(gross_sal>250000 && gross_sal<=500000)
            tax=12500;
        else if(gross_sal>500000 && gross_sal<=750000)
            tax=25000;
        else if(gross_sal>750000 && gross_sal<=1000000)
            tax=37500;
        else if(gross_sal>1000000 && gross_sal<=1250000)
            tax=50000;
        else if(gross_sal>1250000 && gross_sal<=1500000)
            tax=62500;
        else 
            tax=122400;
        salary=gross_sal-(pf+esi+tax);
        // atd=compute(m,y);
        // if(atd<=100 && atd>=95)
        //     newsalary=salary;
        // else if(atd<95 && atd>=85)
        //     newsalary=salary-(0.1*salary);
        // else if(atd<85 && atd>=75)
        //     newsalary=salary-(0.2*salary);
        // else
        //     newsalary=salary-(0.3*salary);  
        // salary=newsalary;      
    }

    void display_sal()
    {
        cout<<"The Basic saalry is : "<<basic;
        cout<<"PF is : "<<pf;
        cout<<"Home Rent Allowance is : "<<hra;
        cout<<"Gross Salary : "<<gross_sal;
        cout<<"Tax on your salary : "<<tax;
        cout<<"Take home salary : "<<newsalary;
    }
};

class menu:public salary
{
     public:
          void add_new_employee()
          {
            data_base::read();
            read_emp_details();
            find_net_salary();

          } 
          void display_employee_details()
          {
            data_base::display();

          }
          void display_attendance(){
            int month,year;
            cout<<"\n enter the month and year : ";
            cin>>month>>year;
            attendance::display(month,year);
            cout<<"\n percentage : "<<compute(month,year);

          }
};
int main()
{
   menu employees[100];
   int key=34567,choice,i=1,j,id;
   while(choice!=key)
   {
    
    cout<<"================================================================================================================================================\n";
    cout<<"---------------------------------------------------employee managment system--------------------------------------------------------------------"<<endl;
    cout<<"================================================================================================================================================="<<endl;

    cout<<"\n1.add new employee"<<endl;
    cout<<"2.veiw employee details"<<endl;
    cout<<"3.mark your attendance"<<endl;
    cout<<"4.know your detailed salary"<<endl;
    cout<<"5.know your attendance"<<endl;
    cout<<"6.checkout"<<endl;
    while(choice<1 || choice>5)
    {
    cout<<"\nenter your choice : ";
    cin>>choice;
    }
    switch(choice)
    {
        case 1:
            employees[i].add_new_employee();
            i+=1;
            break;
        case 2:
             cout<<"\nenter employee id : ";
             cin>>id;
             for(j=0;j<i;j++)
             {
                if(employees[j].employee_id==id)
                {
                    employees[j].display_employee_details();
                    break;
                }
             }
             cout<<"\ninvalid employee id";
             break;
        case 3:
             cout<<"\nenter employee id : ";
             cin>>id;
             for(j=0;j<i;j++)
             {
                if(employees[j].employee_id==id)
                {
                    employees[j].mark_attendance();
                    break;
                }
             }
             cout<<"\ninvalid employee id";
             break;
        case 4:
             cout<<"\nenter employee id : ";
             cin>>id;
             for(j=0;j<i;j++)
             {
                if(employees[j].employee_id==id)
                {
                    employees[j].display_sal();
                    break;
                }
             }
             cout<<"\ninvalid employee id";
             break;
        case 5:
             cout<<"\nenter employee id : ";
             cin>>id;
             for(j=0;j<i;j++)
             {
                if(employees[j].employee_id==id)
                {
                    employees[j].display_attendance();
                    break;
                }
             }
             cout<<"\ninvalid employee id";
             break;
        case 6:
             cout<<"\nenter employee id : ";
             cin>>id;
             for(j=0;j<i;j++)
             {
                if(employees[j].employee_id==id)
                {
                    employees[j].checkout();
                    break;
                }
             }
             cout<<"\ninvalid employee id";
             break;

        default:
              break;
         


             
    }


   }
   return 0;

}