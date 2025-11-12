#include<iostream>
#include<iomanip>
#include<fstream>
#include<set>
#include<map>
using namespace std;
class account
{
private:
    string first_name;
    string last_name;
    int amount;
    int account_number;
    static int counter;
    static set<int> s;
public:
    static set<int> &getset(){return s;}
    bool check()
    {
        return s.count(account_number);
    }
    void closea()
    {
            cout<<first_name<<" your account has been closed"<<endl;
            cout<<"Collect your balance: "<<amount<<" rupees at the nearest branch"<<endl;
            string name = "Closed_Account_Owner's_name_:_";
            name.append(first_name);
            first_name = name;
            string lname = "Last_Name_:_";
            lname.append(last_name);
            last_name = lname;
            amount = 0;
            s.insert(account_number);
    }
    void deposit(int d){amount+=d;}
    void withdraw(int w){amount-=w;}
    int getbalance(){return amount;}
    int getaccount_number(){return account_number;}
    static int getcounter(){return counter;}
    static void setcounter(int x){counter=x;}
    string getfirstname(){return first_name;}
    account(string first_name="", string last_name="",int amount=0,int an=0):first_name(first_name),last_name(last_name),amount(amount),account_number(an){}
    friend bool operator<(const account &ref1, const account &ref2);
    friend ifstream &operator>>(ifstream &ifs,account &ref);
    friend ostream &operator<<(ostream &o,const account &ref);
    friend ofstream &operator<<(ofstream &ofs,const account &ref);
    
};
ofstream &operator<<(ofstream &ofs,const account &ref)
{
    ofs<<ref.account_number<<endl;
    ofs<<ref.first_name<<endl;
    ofs<<ref.last_name<<endl;
    ofs<<ref.amount<<endl;
    return ofs;
}
ostream &operator<<(ostream &o,const account &ref)
{
    o<<"Account number:    "<<ref.account_number<<endl;
    o<<"First name:        "<<ref.first_name<<endl;
    o<<"Last name:         "<<ref.last_name<<endl;
    o<<"Account balance:   "<<ref.amount<<endl;
    return o;
}
ifstream &operator>>(ifstream &ifs,account &ref)
{
    ifs>>ref.account_number;
    ifs>>ref.first_name;
    ifs>>ref.last_name;
    ifs>>ref.amount;
    return ifs;
}
bool operator<(const account &ref1, const account &ref2)
{
    return ref1.account_number < ref2.account_number?ref1.account_number:ref2.account_number;
}
int account::counter;
set<int> account::s;
int main()
{
    ifstream fcan("closed.txt");
    while(!(fcan.eof()))
    {
        int temp;
        fcan>>temp;
        account::getset().insert(temp);
    }
    fcan.close();
    ifstream an("account_number.txt"); //an account number
    int assist;
    an>>assist;
    account::setcounter(assist);
    an.close();
    int quit=1;
    map<int, account> m;
    ifstream ifs;
    ifs.open("account_list.txt");
    if(!ifs)
    {
        cout<<"No Previous account found";
    }
    else
    {
        int last = account::getcounter();
        for(int i=0;i<=last;i++)
        {
            account insta;
            ifs>>insta;
            int anfm = insta.getaccount_number();//anfm account number for map
            m.insert({anfm,insta});
        }
    }
    ifs.close();
    while(quit!=7)
    {

        cout<<endl<<endl;
        cout<<"***Banking System***"<<endl<<endl;
        cout<<"         Select an option";
        cout<<endl<<"         "<<"1. Open an Account";
        cout<<endl<<"         "<<"2. Balance Enquiry";
        cout<<endl<<"         "<<"3. Deposit";
        cout<<endl<<"         "<<"4. Withdrawl";
        cout<<endl<<"         "<<"5. Close an Account";
        cout<<endl<<"         "<<"6. Show all Accounts";
        cout<<endl<<"         "<<"7. Quit"<<endl;
        cout<<"Select: ";
        cin>>quit;
        switch(quit)
        {
            case 1:
                {
                    cout<<"Fill the details below: "<<endl;
                    string first_name;
                    string last_name;
                    int amount;
                    cout<<"Enter first name: ";
                    cin>>first_name;
                    cout<<"Enter last name: ";
                    cin>>last_name;
                    cout<<"Enter the amount: ";
                    cin>>amount;
                    int tempan = account::getcounter(); //tempan: temprary account number
                    tempan++;
                    account::setcounter(tempan);
                    account a(first_name,last_name,amount,tempan);
                    m[tempan]={a};
                    cout<<"Congratulations your account is created"<<endl;
                    cout<<"Account detailes"<<endl;
                    cout<<m[tempan]<<endl;
                    break;
                }
            case 2: 
                {
                    cout<<"Account number: ";
                    int bean;//beac balance enquiry account number
                    cin>>bean;
                    account beb; //balance enquiry balance
                    beb = m[bean];
                    if(bean>account::getcounter())
                    {
                        cout<<"Account number does not exist"<<endl;
                    }
                    else if(beb.check())
                    {
                        cout<<"This account was closed"<<endl;
                    }
                    else
                    {
                        cout<<beb.getfirstname()<<" your account balance is "<<beb.getbalance()<<endl;
                    }
                    break;
                }
            case 3:
                {
                    int dan; //deposit account number
                    int amtd;//amount to deposit
                    cout<<"Account number: ";
                    cin>>dan;
                    account &ada = m[dan]; //ada account deposit account
                    if(dan>account::getcounter())
                    {
                        cout<<"Account number does not exist"<<endl;
                    }
                    else if(ada.check())
                    {
                        cout<<"This account was closed"<<endl;  
                    }
                    else
                    {
                        cout<<"Enter amount: ";
                        cin>>amtd;
                        ada.deposit(amtd);
                        cout<<ada.getfirstname()<<" your new balance is "<<ada.getbalance()<<endl;
                    }
                    break;
                }
            case 4:
                {
                    int wan; //account withdraw
                    int amtw; //amount to withdraw
                    cout<<"Account number: ";
                    cin>>wan;
                    account &awa = m[wan]; //account withdraw account
                    if(wan>account::getcounter())
                    {
                        cout<<"Account number does not exist"<<endl;
                    }
                    else if(awa.check())
                    {
                        cout<<"This account was closed"<<endl;
                    }
                    else
                    {
                        cout<<"Enter amount: ";
                        cin>>amtw;
                        if(amtw>awa.getbalance())
                        {
                            cout<<"Insufficent balance"<<endl;
                        }
                        else
                        {
                            awa.withdraw(amtw);
                            cout<<awa.getfirstname()<<" your new balance is "<<awa.getbalance()<<endl;
                        }
                    }
                    break;
                }
            case 5:
                {
                    int can; //closing account number
                    cout<<"Account number: ";
                    cin>>can;
                    account &aca = m[can]; //aca account closing account
                    if(can>account::getcounter())
                    {
                        cout<<"Accound number does not exist"<<endl;
                    }
                    else if(aca.check())
                    {
                        cout<<"This account is already closed"<<endl;
                    }
                    else
                    {
                        aca.closea();
                    }
                    break;  
                }
            case 6:
                {
                    for(int i=1;i<=account::getcounter();i++)
                    {
                        if(m[i].check())
                        {
                            
                        }
                        else
                        {
                            cout<<m[i]<<endl;
                        }
                    }
                    break;
                }
        }
    }
    ofstream ofs("account_number.txt",ios::trunc);
    ofs<<account::getcounter();    
    ofstream ual("account_list.txt",ios::trunc);
    for(int i=1;i<=account::getcounter();i++)
    {
        ual<<m[i];
    }
    ual.close();
    ofstream cal("closed.txt",ios::trunc);
    for(auto x:account::getset())
    {
        cal<<x<<endl;
    }
    return 0;
}