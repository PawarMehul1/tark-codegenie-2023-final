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

};

class Train
{
    public:
    int No;
    string station1;
    string station2;
    vector<Seats> all;

    Train(int no, string s1,string s2)
    {
        this->No=no;
        this->station1=s1;
        this->station2=s2;
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

        all.push_back(s);
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
    int no=strtoint(tocken[0]);

    for(int i=alltrain.size()-1; i>=0; i--)
    {
        cout<<alltrain[i].getNo()<<endl;
    }

}
int main()
{

    // 2
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
        Train T(strtoint(tocken[0]),tocken[1],tocken[2]);

        alltrain.push_back(T);

        allocate(details[i+1],alltrain);
        
    }

    
    return 0;
}