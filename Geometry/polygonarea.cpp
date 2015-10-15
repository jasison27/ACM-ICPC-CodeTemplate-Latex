double PolygonArea(vector<Point> p) {
  int n = p.size();
  double area = 0;
  for(int i = 1; i < n-1; i++)
    area += Cross(p[i]-p[0], p[i+1]-p[0]);
  return area/2;
}
