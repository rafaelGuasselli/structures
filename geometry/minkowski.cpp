// AKA ConvexHull sum, the set of points A, B, and C where C = {a+b | a e A, b e B}
#include "geometry.cpp"

void reorder_polygon(vector<point> & p){
  int pos = 0;
  for(int i = 1; i < p.size(); i++){
    if(p[i].y < p[pos].y || (p[i].y == p[pos].y && p[i].x < p[pos].x))
      pos = i;
  }
  rotate(p.begin(), p.begin() + pos, p.end());
}

vector<point> minkowski(vector<point> p, vector<point> q){
  reorder_polygon(p);
  reorder_polygon(q);
  p.push_back(p[0]);
  p.push_back(p[1]);
  q.push_back(q[0]);
  q.push_back(q[1]);
  vector<point> result;
  int i = 0, j = 0;
  while(i < p.size() - 2 || j < q.size() - 2){
    result.push_back(p[i] + q[j]);
    auto c = cross(p[i+1] - p[i], q[j+1] - q[j]);
    if(c >= 0 && i < p.size() - 2)
      ++i;
    if(c <= 0 && j < q.size() - 2)
      ++j;
  }
  return result;
}