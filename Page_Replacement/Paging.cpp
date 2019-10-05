#include<iostream>
using namespace std;
int main()
{
  int size,n,pgno,pagetable[10],i,j,frameno,max,choice;
  double m;
  int la=0,ofs,phy;
  cout<<"Enter memory size (in KB) : ";
  cin>>size;  
  max=size/4;
  cout<<"Max. pages u can map: "<<max<<"\n";
  cout<<"Enter no. of pages u want to map: ";
  cin>>n;
  if(n<=max)
  {
	cout<<"Enter the frame no. in the page table : ";
	for(i=0;i<n;i++)
	cin>>pagetable[i];
  }
  cout<<"Total No. of pages:"<<n<<"\n";
  cout<<"page table :\n";
  cout<<"pg no.\tframe no.";
  for(i=0;i<n;i++)
  cout<<"\n  "<<i<<"        ["<<pagetable[i]<<"]";
  do
  {
  cout<<"\nEnter logical address :";
  cin>>la;
  pgno=la/4;      
  ofs=la%4;
  phy=(pagetable[pgno]*4)+ofs;  
  cout<<"\nEquivalent physical address : "<<phy;
  
  cout<<"\nIf u want to continue   Press 1 otherwise 0 :";
  cin>>choice;
  }
  while(choice==1);    
}
