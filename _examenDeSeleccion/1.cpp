#include<iostream>
#include<vector>
using namespace std;

#define ll long long

int main(){
    ll n,x,answer=-1; 
    cin>>n;
    vector<ll> v(n);
    for (ll i=0; i<n; i++){
        cin>>x;
        v[x-1]++;
        if (v[x-1]>=3){
            answer=x;
            break;
        }
    }
    cout<<answer<<endl;
    return 0;
}