#include <iostream>
#include <stack>
#include <string>
using namespace std;
int main(){
    stack<char> suma;
    string a,b; cin>>a; cin>>b;

    // Completar ceros
    if (a.size()<b.size()){
        string ceros(b.size()-a.size(),'0');
        a = ceros + a;
    }
    else{
        string ceros(a.size()-b.size(),'0');
        b = ceros + b;
    }

    // Suma
    int s1,s2,s,acumulado=0;
    for (int i=a.size()-1; i>=0; i--){
        s1 = a[i]-'0';
        s2 = b[i]-'0';
        s = s1 + s2 + acumulado;
        acumulado = s/10;
        suma.push( (char) (s%10+'0') );
    }
    if (acumulado>0) suma.push( (char) (acumulado+'0') );
    
    // Impresion
    while(!suma.empty()){
        cout<<suma.top();
        suma.pop();
    }

    return 0;
}