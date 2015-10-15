struct Point {
  double x, y;
  Point(double x=0, double y=0):x(x),y(y){}
};

typedef Point Vector;

Vector operator + (const Vector &A, const Vector &B) { return Vector(A.x+B.x, A.y+B.y); }
Vector operator - (const Point &A, const Point &B) { return Vector(A.x-B.x, A.y-B.y); }
Vector operator * (const Vector &A, double p) { return Vector(A.x*p, A.y*p); }
double Dot(const Vector &A, const Vector &B) { return A.x*B.x + A.y*B.y; }
double Cross(const Vector &A, const Vector &B) { return A.x*B.y - A.y*B.x; }
double Length(const Vector &A) { return sqrt(Dot(A, A)); }
Vector Normal(const Vector &A) { double L = Length(A); return Vector(-A.y/L, A.x/L); }

struct Line {
  Point P;
  Vector v;
  double ang;
  Line() {}
  Line(Point P, Vector v):P(P),v(v){ ang = atan2(v.y, v.x); }
  bool operator < (const Line &L) const {
    return ang < L.ang;
  }
};

// if $p$ is on the left side of $L$
bool OnLeft(const Line &L, const Point &p) {
  return Cross(L.v, p-L.P) > 0;
}

// intersection of line $a$ and $b$
Point GetLineIntersection(const Line &a, const Line &b) {
  Vector u = a.P-b.P;
  double t = Cross(b.v, u) / Cross(a.v, b.v);
  return a.P+a.v*t;
}
