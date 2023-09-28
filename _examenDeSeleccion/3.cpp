#include<iostream>
#include<vector>
using namespace std;

#define ll long long

int main(){
    ll x,i=2,answer=0;
    cin>>x;
    while(x!=1){
        if (x%i==0){
            x/=i;
            answer++;
        }
        else i++;
    }
    cout<<answer<<endl;
    return 0;
}