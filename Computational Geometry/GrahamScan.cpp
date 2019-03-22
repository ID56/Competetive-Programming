#include <bits/stdc++.h>
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

point p0; ///global minimum point

point nextToTop(stack<point> &S)
{
    point p = S.top();
    S.pop();
    point next_to_top = S.top();
    S.push(p);
    return next_to_top;
}

int squareDistance(point a, point b){
    return (a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y);
}

int orientation(point a,point b,point c){
    int slope_difference=(b.y-a.y)*(c.x-b.x)-(c.y-b.y)*(b.x-a.x);

    if (slope_difference==0)
        return 0;
    return (slope_difference>0)? 1:2;
}

///In order to sort our points by polar angle with respect to p0.
int polar_angle_compare(const void *a, const void *b)
{
    point *p1 = (point *)a;
    point *p2 = (point *)b;

    int orient = orientation(p0, *p1, *p2);
    if (orient == 0){
        if (squareDistance(p0,*p1)<squareDistance(p0,*p2))///p1 is closer
            return -1;
        else
            return 1;
   }

    ///If counterclockwise, p1 goes before p2
    return (orient == 2)? -1: 1;
}

bool smaller(point a,point b){
    if (a.y<b.y || (a.y==b.y && a.x<b.x))
        return true;
    else
        return false;
}

void convexHull(point points[], int n){

    int min = 0;
    for (int i = 1; i < n; i++) {
        if (smaller(points[i],points[min])){
            min=i;
        }
    }

    swap(points[0],points[min]);
    p0=points[0];

    ///qsort(base pointer,number of elements,size of each element,compare function)

    qsort(&points[1],n-1,sizeof(point),polar_angle_compare);

    int i,j;
    for (i=1,j=1; i<n; i++) {
       while (i<n-1 && orientation(p0, points[i], points[i+1]) == 0)
          i++;
       points[j] = points[i];
       j++;  // Update size of modified array
    }

    int m=j;
    if (m<3){
        cout<<"Convex Hull not possible";
        return;
    }

    stack <point> S;
    S.push(points[0]);
    S.push(points[1]);
    S.push(points[2]);

    for (i=3;i<m;i++){
        ///keep popping till getting counterclockwise
        while (orientation(nextToTop(S), S.top(), points[i]) != 2)
            S.pop();
        S.push(points[i]);
    }

    cout<<"Convex Hull: "<<endl;
    while (!S.empty()) {
       point p = S.top();
       cout<<p.x<<" "<<p.y<<endl;
       S.pop();
   }
}

int main(){
    int n,i;
    cin>>n;
    point points[n];
    for (i=0;i<n;i++){
        int a,b;
        cin>>a>>b;
        points[i].set(a,b);
    }

    convexHull(points, n);
    return 0;
}

/**
0 0
0 1
3 0
5 5
7 2
2 9
8 4
6 3
**/
