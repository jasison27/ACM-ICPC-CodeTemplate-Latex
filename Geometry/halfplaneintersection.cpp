const double eps = 1e-6;
// intersection of areas (leftside of lines)
vector<Point> HalfplaneIntersection(vector<Line> L) {
  int n = L.size();
  sort(L.begin(), L.end());
  int first, last;
  vector<Point> p(n);
  vector<Line> q(n);
  vector<Point> ans;
  q[first=last=0] = L[0];
  for(int i = 1; i < n; i++) {
    while(first < last && !OnLeft(L[i], p[last-1])) last--;
    while(first < last && !OnLeft(L[i], p[first])) first++;
    q[++last] = L[i];
    if(fabs(Cross(q[last].v, q[last-1].v)) < eps) {
      last--;
      if(OnLeft(q[last], L[i].P)) q[last] = L[i];
    }
    if(first < last) p[last-1] = GetLineIntersection(q[last-1], q[last]);
  }
  while(first < last && !OnLeft(q[first], p[last-1])) last--;
  if(last - first <= 1) return ans;
  p[last] = GetLineIntersection(q[last], q[first]);
  for(int i = first; i <= last; i++) ans.push_back(p[i]);
  return ans;
}