struct PointToPolygonProjector {
  vector<Point> CH; // convex-hull clockwise
  Point center;
  PointToPolygonProjector(vector<Point> _CH) : CH(_CH), center(0, 0) {
    for (Point &p : CH) {
      center = center + p;
    }
    center = center.scale(1.0 / CH.size());
  }
  pair<int, int> getWindow(Point p) {
    int ff = lowerBoundAngle(p, 0);
    int fs = lowerBoundAngle(p, M_PI) - 1;
    if (fs < 0) fs += CH.size();
    int sf = (CH.size() + ff - 1) % CH.size();
    int ss = (fs + 1) % CH.size();
    return make_pair(bestAngle(p, ss, sf, -1), bestAngle(p, ff, fs, 1));
  }
  int bestAngle(Point p, int lo, int hi, int sig = 1) {
//      int sig = (center - p).getSide(CH[lo] - p) < 0 ? -1 : 1;
    int N = CH.size();
    if (hi < lo) hi += N;
    while (hi - lo > 2) {
      int mi1 = lo + 1 * (hi - lo) / 3;
      int mi2 = lo + 2 * (hi - lo) / 3;
      if ((CH[mi1%N] - p).getSide(CH[mi2%N] - p) * sig > 0) {
        lo = mi1;
      } else {
        hi = mi2;
      }
    }
    int b = lo;
    for (int i = lo; i <= hi; ++i) {
        if ((CH[b%N] - p).getSide(CH[i%N] - p) * sig > 0) {
        b = i;
      }
    }
    return b % N;
  }
  Double getAngle(Point f, Point s) {
    return (f - center).angle(s - center);
  }
  int lowerBoundAngle(Point p, Double target) {
    Double ang = getAngle(CH[0], p);
    //    Double ang = getAngle(AN[0], ref);
    if (target < ang) target += 2 * M_PI;
    int N = CH.size();
    int lo = 0, hi = N;
    while (lo < hi) {
      int mi = (lo + hi) / 2;
      Double e = getAngle(CH[mi], p);
      if (e < ang) e += 2 * M_PI;
      if (e < target)
        lo = mi + 1;
      else
        hi = mi;
    }
    lo %= N;
    return lo;
  }
};