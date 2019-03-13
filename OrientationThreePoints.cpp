#include <iostream>
using namespace std;

struct point{
    int x;
    int y;
};

/**
For any three ordered points a,b,c, we can calculate the slopes by:
slope_ab=(b.y-a.y)/(b.x-a.x)
slope_bc=(c.y-b.y)/(c.x-b.x)

If the two slopes are equal, then orientation is collinear.(0)
If slope_ab > slope_bc, then orientation is clockwise.(1)
If slope_ab < slope_bc, then orientation is counterclockwise.(2)


That is, orientation depends on the sign of the expression:
(b.y-a.y)*(c.x-b.x)-(c.y-b.y)*(b.x-a.x)

**/

int orientation(point a,point b,point c){
    int slope_difference=(b.y-a.y)*(c.x-b.x)-(c.y-b.y)*(b.x-a.x);

    if (slope_difference==0)
        return 0;
    return (slope_difference>0)? 1:2;
}

int main(){
    point a={1,1},b={5,5},c={4,9};
    int orient=orientation(a,b,c);

    if (!orient)
        cout<<"Collinear.";
    else{
        cout<<((orient==1)?"Clockwise":"Counterclockwise");
    }
}
