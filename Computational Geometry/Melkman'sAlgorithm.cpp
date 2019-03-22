#include <bits/stdc++.h>
using namespace std;

struct point{
    int x;
    int y;

    point(){x=0;y=0;}
    point(int a,int b){x=a;y=b;}
    void set(int a,int b){x=a;y=b;}
};

int orientation(point a,point b,point c){
    int slope_difference=(b.y-a.y)*(c.x-b.x)-(c.y-b.y)*(b.x-a.x);

    if (slope_difference==0)
        return 0;
    return (slope_difference>0)? 1:2;
}

point beforeFront(deque<point> &D)
{
    point p = D.front();
    D.pop_front();
    point ans = D.front();
    D.push_front(p);
    return ans;
}

point beforeBack(deque<point> &D)
{
    point p = D.back();
    D.pop_back();
    point ans = D.back();
    D.push_back(p);
    return ans;
}

void melkmanHull(point p[],int n){
    deque <point> D;

    if (orientation(p[0],p[1],p[2])==2) {///Counterclockwise 0 1 2
        D.push_back(p[0]);
        D.push_front(p[1]);
    }
    else {///Counterclockwise order is 1 0 2
        D.push_back(p[1]);
        D.push_front(p[0]);
    }
    D.push_back(p[2]);
    D.push_front(p[2]);

    for (int i=3; i < n; i++) {
        if (orientation(D.back(), beforeBack(D), p[i])==2 && orientation(beforeFront(D), D.front(), p[i])==2)
            continue;           ///internal vertex

        while (orientation(D.back(), beforeBack(D), p[i])!=2)
            D.pop_back();
        D.push_back(p[i]);

        while (orientation(beforeFront(D), D.front(), p[i])!=2)
            D.pop_front();
        D.push_front(p[i]);
    }

    cout<<"\nConvex Hull"<<endl;
    deque <point>::iterator it;
    for (it=D.begin();it!=D.end();it++){
        point q=*it;
        cout<<q.x<<" "<<q.y<<endl;
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
        if (i>1)
            melkmanHull(points,n);
    }

    return 0;
}
