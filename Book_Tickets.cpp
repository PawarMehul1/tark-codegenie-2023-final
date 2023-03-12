#include<iostream>
#include<vector>
#include<string>
#include<bits/stdc++.h>

using namespace std;

long long PNR=10000000;

class Seats
{
    public:
    string name;
    vector<vector<string>> slots;

    Seats(string s,int n)
    {
        this->name=s;
        vector<vector<string>> all(n);
        slots=all;
    }

    int getsize()
    {
        return slots.size();
    }
    string getName()
    {
        return name;
    }

};

class detail
{
    public:
    long long pnr;
    vector<string> sits;

    detail(long long p,vector<string> sit)
    {
        this->pnr=pnr;
        this->sits=sit;
    }
};

class Train
{
    public:
    int No;
    int distanc;
    string station1;
    string station2;
    vector<Seats> all;

    Train(int no, string s1,string s2,int d)
    {

        this->No=no;
        this->station1=s1;
        this->station2=s2;
        this->distanc=d;
    }

    int getNo()
    {
        return No; 
    }

    string gets1()
    {
        return station1;
    }

    string gets2()
    {
        return station2;
    }

    void addseats(string type,int size)
    {
        Seats s(type,size);
        this->all.push_back(s);
    }

    void display()
    {
        for(int i=0; i<all.size(); i++)
        {
            cout<<all[i].getName()<<" "<<all[i].getsize()<<endl;
        }    
    }
    vector<Seats> giveset()
    {
        return this->all;
    }

};


vector<string> split(string str)
{
    vector<string> ans;
    int index=0;
    int n=str.length();


    while(index<n)
    {
        string current="";
        while(index<n && str[index]!=' ')
        {
            current+=str[index++];
        }
        index++;
        ans.push_back(current);
    }

    return ans;
}

string inttostr(int n)
{
    if(n==0)
        return "0";

    string ans="";
    while(n>0)
    {
        ans=(char)(48+(n%10))+ans;
        n/=10;
    }

    return ans;
}

int strtoint(string s)
{
    int ans=0;

    for(int i=0; i<s.length(); i++)
    {
        ans*=10;
        ans+=(int)(s[i])-48;
    }

    return ans;
}

void allocate(string str,vector<Train>& alltrain)
{
    vector<string> tocken=split(str);
    int n=alltrain.size();

            for(int j=1; j<tocken.size(); j++)
            {
                string tmp=tocken[j];
                int index=0;
                int len=tmp.length();

                for(; index<len; index++)
                {
                    if(tmp[index]=='-')
                        break;
                }

                string s1=tmp.substr(0,index);
                string s2=tmp.substr(index+1,len-index-1);

                int size=strtoint(s2);

                alltrain[n-1].addseats(s1,size);
    
            }

}
vector<detail> book(string details,vector<Train>& alltrain,vector<detail>& info)
{
    // Input: Rajkot Mumbai 2023-03-15 SL 6
    vector<string> tocken=split(details);
    int n=strtoint(tocken[4]);

    if(tocken[3]=="SL")
        tocken[3]="S";
    else if(tocken[3]=="3A")
        tocken[3]="B";
    else if(tocken[3]=="2A")
        tocken[3]="A";
    else
        tocken[3]="H";   

    int count=0; 
    int price=n;       
    vector<string> seats; 
    for(int i=0; i<alltrain.size(); i++)
    {
        if((count<n)&&(tocken[0]==alltrain[i].station1 && tocken[1]==alltrain[i].station2)||(tocken[0]==alltrain[i].station2 && tocken[1]==alltrain[i].station1))
        {
            price*=alltrain[i].distanc;
            //alltrain[i]
            for(int j=0; j<alltrain[i].all.size() && count<n; j++)
            {
                if(tocken[3][0]==alltrain[i].all[j].name[0])
                {
                    for(int k=0; k<alltrain[i].all[j].slots.size() && (count<n); k++)
                    {
                        if(alltrain[i].all[j].slots[k].size()==0)
                        {
                            alltrain[i].all[j].slots[k].push_back(tocken[2]);
                            count++;
                            string sit=tocken[3];
                            sit+='-';
                            sit+=inttostr(k+1);
                            seats.push_back(sit);
                        }
                        else
                        {
                            bool flag=true;
                            for(int m=0; m<alltrain[i].all[j].slots[k].size(); m++)
                            {
                                if(alltrain[i].all[j].slots[k][m]==tocken[2])
                                    flag=false;

                            }

                            if(flag)
                            {
                                alltrain[i].all[j].slots[k].push_back(tocken[2]);
                            count++;
                            string sit=tocken[3];
                            sit+='-';
                            sit+=inttostr(k+1);
                            seats.push_back(sit);
                            }


                        }
                    }
                }
            }
            break;
        }
    }
    if(count==n)
    {
        if(tocken[3]=="B")
            price*=2;
        else if(tocken[3]=="A")
            price*=3;
        else if(tocken[3]=="H")  
            price*=4;      
        
        cout<<PNR<<" "<<price<<endl;
        PNR++;
        detail d(PNR,seats);
        info.push_back(d);

    }
    else
    {
        cout<<"NO SEATS ARE VAILABLE"<<endl;
    }



    return info;
}
int main()
{

    // 1
    // 17726 Rajkot-0 Mumbai-750
    // 17226 S1-72 S2-72 B1-72 A1-48 H1-24
    // 37392 Ahmedabad-0 Surat-300
    // 37392 S1-15 S2-20 S3-50 B1-36 B2-48

    int n;
    cin>>n;

    string input;
    vector<string> details;
    vector<Train> alltrain;
    
    for(int i=0; i<=(n*2); i++)
    {
        getline(cin,input);
        details.push_back(input);
    }


    for(int i=1; i<=(2*n); i+=2)
    {
        vector<string> tocken=split(details[i]);

        string s1=tocken[1];
        int index=0;

        for(; index<s1.length(); index++)
            if(s1[index]=='-')
                break;

        string tmp1=s1.substr(0,index);
        string tmp2=s1.substr(index+1,s1.length()-index-1);

        
        string s2=tocken[2];

        for(index=0; index<s2.length(); index++)
            if(s1[index]=='-')
                break;

        string tmp3=s2.substr(0,index);
        string tmp4=s2.substr(index+1,s2.length()-index-1);


        Train T(strtoint(tocken[0]),tmp1,tmp3,strtoint(tmp4)-strtoint(tmp2));

        alltrain.push_back(T);

        allocate(details[i+1],alltrain);
    }

    vector<detail> info;
    while(true)
    {
        getline(cin,input);
        if(input=="EXIT")
            break;

        info=book(input,alltrain,info);
    }
    return 0;
}