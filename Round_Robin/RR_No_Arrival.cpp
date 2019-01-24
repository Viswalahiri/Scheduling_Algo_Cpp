#include<iostream>
using namespace std;
class Round
{
        public:

                int i,j,k;
                float atat=0.0,awt=0.0;
                int elapsed_time=0;
                int burst_sum=0;
                int n,t_q;
                int *pno;
                int *at;
                int *bt;
                int *cbt;
                int *ct;
                int *tat;
                int *wt;
        void getdata();
        void calculator();
        void tat_wt();
        void atat_awt();
        void putdata();
};
void Round::getdata()
{
        cout<<"Enter the number of processes."<<endl;
        cin>>n;
        cout<<"Enter the time quantum."<<endl;
        cin>>t_q;
        pno=new int[n+1];
        at=new int[n+1];
        bt=new int[n+1];
        cbt=new int[n+1];
        ct=new int[n+1];
        tat=new int[n+1];
        wt=new int[n+1];
        cout<<"Enter the burst times of "<<n<<" processes."<<endl;

        for (i=0;i<n;i++)
        {
        cin>>bt[i];
        burst_sum+=bt[i];
		cbt[i]=bt[i];
        }
        for (i=0;i<n;i++)
        {
        at[i]=0;
        }
        for (i=0;i<n;i++)
        {
        ct[i]=0;
        }
}
void Round::calculator()
{
        while(burst_sum>0)
        {
        for(i=0;i<n;i++)
        {
                if(bt[i]<=t_q)
                {
                        elapsed_time+=bt[i];
                        bt[i]=0;
                        if(ct[i]==0)
                        {
                        ct[i]=elapsed_time;
                        }
                }
                else
                {
                bt[i]-=t_q;
                elapsed_time+=t_q;
                }
        }
        burst_sum=0;
        for (i=0;i<n;i++)
        {
                burst_sum+=bt[i];
        }

        }
}
void Round::tat_wt()
{
        for(i=0;i<n;i++)
        { 
				tat[i]=ct[i];
                wt[i]=tat[i]-cbt[i];
        }
}

void Round::atat_awt()
{
        int sumatat=0;
        int sumawt=0;
        for(i=0;i<n;i++)
        {
                sumatat+=tat[i];
                sumawt+=wt[i];
        }
        atat=sumatat/float(n);
        awt=sumawt/float(n);
}
void Round::putdata()
{
    cout<<"Process\t"<<"Arrival\t"<<"Burst\t"<<"Completion\t"<<"Turn Around\t"<<"Waiting\t"<<endl;
    for(int i=0;i<n;i++)
    cout<<"P"<<"["<<i+1<<"]\t"<<at[i]<<"\t"<<cbt[i]<<"\t"<<ct[i]<<"\t\t"<<tat[i]<<"\t\t"<<wt[i]<<endl;
    cout<<endl;
    cout<<"Average Waiting Time is "<<awt<<"ms."<<endl;
    cout<<"Average Turn Around is "<<atat<<"ms."<<endl;
}

int main()
{
        Round obj;
        obj.getdata();
        obj.calculator();
        obj.tat_wt();
        obj.atat_awt();
        obj.putdata();
        return 0;
}
                            
