//employee mangament system software design by b2 batch
//header file section
#include<iostream>
#include<conio.h>
#include<stdlib.h>
#include<math.h>
#include<ctime>
#include<fstream>
#include<string.h>
#include<cctype>
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
         char posting[10];
         struct date_ d_o_b;
         struct date_ d_o_j;
         char qualification[10];
         float salary;
         float attendance;
         int age;
         
    public:
        int employee_code;
        static int employee_id;

    void read()
    {
        label2:
       cout<<"\nenter the name of the employee : ";
       cin>>name;
      
       cout<<"\nenter the date of birth of the employee in the format (dd/mm/yyyy) : ";
       cin>>d_o_b.day>>d_o_b.month>>d_o_b.year;
       cout<<"\nenter the date of joining of the employee in the format (dd/mm/yyyy) : ";
       cin>>d_o_j.day>>d_o_j.month>>d_o_j.year;
       age=d_o_j.year-d_o_b.year;
       if(age<17)
       {
          cout<<"\n employee age not valid to work";
          return;
       }
       cout<<"\nenter the qualification of the employee : ";
       cin>>qualification;
       cout<<"\nenter the posting of the employee : ";
       cin>>posting;
       employee_code=employee_id;
       employee_id+=1;
       cout<<"\nyour employee id is : "<<employee_code;

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
        time_t log_in,log_out;
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
                    total_attendance+=attendance_matrix[y-1900][m][i];
                }
                    percentage=(total_attendance/(days(m,y)-4))*100;
                
                return percentage;          
            }
            
            void display(int m,int y)
            {  
                char att;
                int d=1;
                cout<<"\t"<<m<<"-"<<y<<endl;
                cout<<"Sun\tMon\tTue\tWed\tThur\tFri\tSat\n";
                for(int i=1;i<=days(m,y);i+=7)
                {   cout<<"-\t";
                    d++;
                    for(int j=1;j<7 && d<=days(m,y);j++)
                    {
                             att='p';
                            if(attendance_matrix[y-1900][m][d]==0)
                            att='a';
                            cout<<att<<"\t";
                            d++;
                    }
                    cout<<"\n";
                }
            }
            void mark_attendance()
            {
              int day_of_week,month,year,day;
                log_in= time(0);
               tm *in = localtime(&log_in);
               char* log = ctime(&log_in);
               year=in->tm_year;
               month=1+in->tm_mon;
               day=in->tm_mday;
              day_of_week=in->tm_wday;
               if(day_of_week == 0)
               {
                attendance_matrix[year-1900][month][day]= 0;
                return ;
               }
            //    attendance_matrix[year][month][day]=1;
               outfile.open("check_in.txt");
               outfile<<employee_id<<"   "<<name<<" checked in at :"<<log<<endl;
               outfile.close();
               cout<<"\nentered log details sucessfully";

               


            }
            void checkout()
            {
                int month,year,day;
               log_out= time(0);
               char* log = ctime(&log_out);
                tm *out = localtime(&log_in);
               outfile.open("check_out.txt");
               outfile<<employee_id<<"   "<<name<<" checked out at :"<<log<<endl;
               outfile.close();
               year=out->tm_year;
               month=1+out->tm_mon;
               day=out->tm_mday;
               
            //    tm*in=localtime(&log_in);
            //    tm*out=localtime(&log_out);
               double hours= difftime(log_out,log_in);
               if(hours>=7.5)
               {
                 attendance_matrix[year][month][day]=1;
               }
               else{
                cout<<"insufficient working hour fr the day attendance not valid";
               }

               cout<<"\nentered log details sucessfully";
               
             }
            
             
};


class salary:public attendance, virtual data_base

{
    
    
    float basic,da,hra,lta,pf,esi,rent,gross_sal,tax,salary,atd,newsalary;
    char choice;
    public:void read_emp_details()
    {
        // cout<<"Employee id:\n" ;
        // cin>>emp_id;
        cout<<"\nEnter basic salary :" ;
        cin>>basic;
        cout<<"If you live in rented house type YES else NO\n";
        cin>>choice;
        if(choice=="yes" || choice=="YES")
        {
            hra=(hra+(0.5*basic))/12;
        }
        else 
        {
            exit(0);
        }
    }
    void find_net_salary()
    {
        da=(0.12*basic);        
        pf=(0.12*basic)+da;
        esi=(0.0075*basic);
        gross_sal=basic+da+hra;
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
        cout<<"\nThe Basic saalry is : "<<basic;
        cout<<"\nPF is : "<<pf;
        cout<<"\nHome Rent Allowance is : "<<hra;
        cout<<"\nGross Salary : "<<gross_sal;
        cout<<"\nTax on your salary : "<<tax;
        cout<<"\nTake home salary : "<<salary;
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
   menu employees[15];
   int key=34567,choice,i=1,j,id;
   label1:
   while(choice!=key)
   {
    
    cout<<"\n================================================================================================================================================\n";
    cout<<"---------------------------------------------------employee managment system--------------------------------------------------------------------"<<endl;
    cout<<"================================================================================================================================================="<<endl;

    cout<<"\n1.add new employee"<<endl;
    cout<<"2.veiw employee details"<<endl;
    cout<<"3.mark your attendance"<<endl;
    cout<<"4.know your detailed salary"<<endl;
    cout<<"5.know your attendance"<<endl;
    cout<<"6.checkout"<<endl;
   
    cout<<"\nenter your choice : ";
    cin>>choice;
    
    switch(choice)
    {
        case 1:
            system("CLS");
            employees[i].add_new_employee();
            i+=1;
            goto label1;
        case 2:
             cout<<"\nenter employee id : ";
             cin>>id;
             for(j=0;j<i;j++)
             {
                if(employees[j].employee_code==id)
                {
                    employees[j].display_employee_details();
                    goto label1;
                }
             }
             cout<<"\ninvalid employee id";
             break;
        case 3:
             cout<<"\nenter employee id : ";
             cin>>id;
             for(j=0;j<i;j++)
             {
                if(employees[j].employee_code==id)
                {
                    system("CLS");
                    employees[j].mark_attendance();
                    goto label1;
                }
             }
             cout<<"\ninvalid employee id";
             break;
        case 4:
             cout<<"\nenter employee id : ";
             cin>>id;
             for(j=0;j<i;j++)
             {
                if(employees[j].employee_code==id)
                {
                    system("CLS");
                    employees[j].display_sal();
                    goto label1;
                }
             }
             cout<<"\ninvalid employee id";
             break;
        case 5:
             cout<<"\nenter employee id : ";
             cin>>id;
             for(j=0;j<i;j++)
             {
                if(employees[j].employee_code==id)
                {
                    system("CLS");
                    employees[j].display_attendance();
                    goto label1;
                }
             }
             cout<<"\ninvalid employee id";
             break;
        case 6:
             cout<<"\nenter employee id : ";
             cin>>id;
             for(j=0;j<i;j++)
             {
                if(employees[j].employee_code==id)
                {
                    system("CLS");
                    employees[j].checkout();
                    goto label1;
                }
             }
             cout<<"\ninvalid employee id";
             break;

        default:
             cout<<"\ninvalid choice :-( \n";
              break;
         


             
    }


   }
   return 0;

}