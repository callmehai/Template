
struct Point {
    int x, y;
    
    bool equal(const Point &o) {
        return x == o.x && y == o.y;
    }
};

long long cross(const Point &A, const Point &B, const Point &C) {
    return 1LL * (B.x - A.x) * (C.y - A.y) - 1LL * (C.x - A.x) * (B.y - A.y);
}
long long dot(const Point &A, const Point &B, const Point &C) {
    return 1LL * (B.x - A.x) * (C.x - A.x) + 1LL * (B.y - A.y) * (C.y - A.y);
}

bool onSegment(const Point &A, const Point &B, const Point &C) {
    return cross(A, B, C) == 0 && dot(C, A, B) <= 0;
}


int ccw(const Point &A, const Point &B, const Point &C) {
    long long S = cross(A, B, C);
    if (S < 0) return -1; // right
    if (S == 0) return 0; // mid
    return 1; // left
}


vector<Point> convexHull(vector<Point> p, int n) {

    for (int i = 1; i < n; ++i) {
        if (p[0].y > p[i].y || (p[0].y == p[i].y && p[0].x > p[i].x)) {
            swap(p[0], p[i]);
        }
    }


    sort(p.begin() + 1, p.end(), [&p](const Point &A, const Point &B) {
        int c = ccw(p[0], A, B);
        if (c > 0) return true;
        if (c < 0) return false;
        return A.x < B.x || (A.x == B.x && A.y < B.y);
    });
    

    vector<Point> hull;
    hull.push_back(p[0]);

    for (int i = 1; i < n; ++i) {
//        for(auto &[x,y]:hull) cout<<x<<' '<<y<<'\n';
//        cout<<"***\n";
        while (hull.size() >= 2 && 
               ccw(hull[hull.size() - 2], hull.back(), p[i]) <= 0) {
            hull.pop_back();
        }
        hull.push_back(p[i]);
    }
    //reverse to have clockwise hull
    if(hull.size()>2) reverse(hull.begin()+1,hull.end());
  
    return hull;
}

bool checkInHull(vector<Point> &hull, Point P) {
    int n = (int)hull.size();

    if (n == 1) return P.equal(hull[0]) ;
    if (n == 2) return onSegment(hull[0], hull[1], P);


    if (ccw(hull[0], hull[1], P)==1) return 0;
    
    
    if (ccw(hull[n - 1], hull[0], P)!=-1) {
        return onSegment(hull[n - 1], hull[0], P);
    }



    

    int lo = 2, hi = n - 1, x = -1;
    while (lo <= hi) {
        int mid = (lo + hi) >> 1;

        if (ccw(hull[0], hull[mid], P)==1) {
            x  = mid;
            hi = mid - 1;
        }
        else lo = mid + 1;
    }

    return (ccw(hull[x - 1], hull[x], P)!=1);
}
