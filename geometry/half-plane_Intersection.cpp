#include "geometry.cpp"
#define hp halfplane
vector<point> hp_intersect(vector<hp> &h){
  point box[4] = {
    point(inf, inf),
    point(-inf, inf),
    point(-inf, -inf),
    point(inf, -inf)
  };
  for(int i = 0; i<4; i++){
    hp aux(box[i], box[(i+1)%4]);
    h.push_back(aux);
  }
  sort(h.begin(), h.end());
  deque<hp> dq;
  int len = 0;
  for(int i = 0; i < h.size(); i++){
    while(len > 1 && h[i].out(intersection(dq[len-1], dq[len-2]))){
      dq.pop_back(); 
      --len;
    }
    while(len > 1 && h[i].out(intersection(dq[0], dq[1]))){
      dq.pop_front();
      --len;
    }
    if(len > 0 && fabsl(cross(h[i].pq, dq[len-1].pq)) < eps){
      if(dot(h[i].pq, dq[len-1].pq) < 0.0) 
        return vector<point>();
      if (h[i].out(dq[len-1].p)) {
        dq.pop_back();
        --len;
      }
      else continue;
    }

    dq.push_back(h[i]);
    ++len;
  }
  while (len > 2 && dq[0].out(intersection(dq[len-1], dq[len-2]))) {
    dq.pop_back();
    --len;
  }
  while (len > 2 && dq[len-1].out(intersection(dq[0], dq[1]))) {
    dq.pop_front();
    --len;
  }
  if (len < 3) return vector<point>();

  vector<point> ret(len);
  for(int i = 0; i+1 < len; i++) {
    ret[i] = intersection(dq[i], dq[i+1]);
  }
  ret.back() = intersection(dq[len-1], dq[0]);
  return ret;
}