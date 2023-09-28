#include<iostream>
#include<vector>
using namespace std;

class Rectangulo{
    public:
        int x1;
        int x2;
        int y1;
        int y2;
        Rectangulo(){}
        Rectangulo(int _x1, int _x2, int _y1, int _y2){
            x1 = _x1;
            x2 = _x2;
            y1 = _y1;
            y2 = _y2;
        }
        int area(){
            return (y2-y1)*(x2-x1); 
        }
};

int main(){
    int n,answer=0; 
    Rectangulo r_res;
    vector<Rectangulo> r;
    cin>>n;
    for (int i=0; i<n; i++){
        int x1,x2,y1,y2;
        cin>>x1>>x2>>y1>>y2;
        Rectangulo aux(x1,x2,y1,y2);
        r.push_back(aux);
    }
    
    r_res = r[0];
    
    for (int i=1; i<n; i++){
        if (r_res.x1>=r[i].x2 || r_res.x2<=r[i].x1 || r_res.y2<=r[i].y1 || r_res.y1>=r[i].y2){
            answer=0;
            break;
        }
        // analizar los 4 casos de interseccion, reconocer el caso y guardar la inters en (r_res) 
        // hacer lo mismo con los demas rect almacenados en el vector r.
    }
    
    return 0;
}