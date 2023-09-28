#include <iostream>
using namespace std;
int main(){
    bool flag;
    int p,n; cin>>n;
    p=n+1; 
    while(true){
        flag=true;
        for (int i=2; i*i<=p; i++)
            if (p%i==0){
                flag=false;
                break;
            }
        if (flag==true) 
            break;
        p++;
    }
    cout<<p<<endl;
    return 0;
}