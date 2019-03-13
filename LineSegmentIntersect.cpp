#include <iostream>
using namespace std;

struct point{
    int x;
    int y;

    point(){
        x=0;y=0;
    }
    point(int a,int b){
        x=a;y=b;
    }
    void set(int a,int b){
        x=a;y=b;
    }
};

/** For any three collinear points a,b,c, to check if the point c lies on the line segment ab.**/

bool collinear_coincide(point a,point b,point c){
    int x_high=max(a.x,b.x);
    int x_low=min(a.x,b.x);
    int y_high=max(a.y,b.y);
    int y_low=min(a.y,b.y);

    if (c.x<=x_high && c.x>=x_low && c.y<=y_high && c.y>=y_low)
        return true;
    else
        return false;
}

int orientation(point a,point b,point c){
    int slope_difference=(b.y-a.y)*(c.x-b.x)-(c.y-b.y)*(b.x-a.x);

    if (slope_difference==0)
        return 0;
    return (slope_difference>0)? 1:2;
}

bool intersect(point p1,point q1,point p2,point q2){
    int o1=orientation(p1,q1,p2);
    int o2=orientation(p1,q1,q2);
    int o3=orientation(p2,q2,p1);
    int o4=orientation(p2,q2,q1);

    if (o1!=o2 && o3!=o4)
        return true;

    /**Special cases for collinear orientations**/

    if (o1==0 && collinear_coincide(p1,q1,p2))
        return true;
    if (o2==0 && collinear_coincide(p1,q1,q2))
        return true;
    if (o3==0 && collinear_coincide(p2,q2,p1))
        return true;
    if (o4==0 && collinear_coincide(p2,q2,q1))
        return true;

    return false;
}

int main(){
    point p1(1,1),q1(5,5),p2(5,1),q2(1,5); ///An x shaped intersection
    cout<<((intersect(p1,q1,p2,q2)==true)? "Intersects":"Nope")<<endl;

    q2.set(6,1);
    cout<<((intersect(p1,q1,p2,q2)==true)? "Intersects":"Nope")<<endl;
}

