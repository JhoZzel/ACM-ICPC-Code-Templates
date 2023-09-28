#include <iostream>
using namespace std;
int main(){
    float Ax,Ay,Bx,By,Cx,Cy;

    cin>>Ax>>Ay;
    cin>>Bx>>By;
    cin>>Cx>>Cy;

    float p1x = (Ax+Bx)/2;
    float p1y = (Ay+By)/2;
    float v1x = By-Ay;
    float v1y = Ax-Bx;
    
    float a1 = v1y, b1 = -v1x, c1 = p1x*v1y - p1y*v1x;  

    float p2x = (Ax+Cx)/2;
    float p2y = (Ay+Cy)/2;
    float v2x = Cy-Ay;
    float v2y = Ax-Cx;

    float a2 = v2y, b2 = -v2x, c2 = p2x*v2y - p2y*v2x;

    float dS = a1*b2 - a2*b1;
    float dx = c1*b2 - c2*b1;
    float dy = a1*c2 - a2*c1;
    
    cout<<"x: "<<dx/dS<<endl;
    cout<<"y: "<<dy/dS<<endl;   

    return 0;
}