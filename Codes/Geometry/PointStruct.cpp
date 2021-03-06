typedef long double Double;
struct Point {
  Double x, y;
  Point(Double x = 0, Double y = 0) : x(x), y(y) {}
  Point round() const { return Point(round(x), round(y)); }
  Point operator-(const Point &P) const { return Point(x - P.x, y - P.y); }
  Point operator+(const Point &P) const { return Point(x + P.x, y + P.y); }
  Double operator^(const Point &P) { return x * P.y - y * P.x; }
  Double operator*(const Point &P) { return x * P.x + y * P.y; }
  Double sqMag() const { return x * x + y * y; }
  Double mag() const { return sqrt(sqMag()); }
  Point unit() const {
    Double m = mag();
    return Point(x / m, y / m);
  }
  Point scale(const Double &d) const { return Point(x * d, y * d); }
  Point rotate90() { return Point(-y, x); }
  Point rotate(const Double &a) const {
    return Point(x * cos(a) - y * sin(a), x * sin(a) + y * cos(a));
  }
  bool operator<(const Point &p) const {
    return (x != p.x ? x < p.x : y < p.y);
  }
  bool operator==(const Point &P) const { return x == P.x && y == P.y; }
  bool similar(const Point &P) {
    Double rex = abs(x - P.x) / max(1.0L, abs(P.x));
    Double rey = abs(y - P.y) / max(1.0L, abs(P.y));
    return rex < 1e-12 && rey < 1e-12;
  }
  Double angle() const {
    Double an = atan2(y, x);
    if (an < 0) an += 2 * acos(-1);
    return an;
  }
  Double angle(const Point &p) const { 
      return p.rotate(-angle()).angle(); 
  }
  Double smallAngle(const Point &p) const {
    Double ang = angle(p);
    if (ang > M_PI) return ang - 2 * M_PI;
    return ang;
  }
  int getSide(const Point &p){ // (< 0):left, (==0):aligned,  (> 0):right
      return (*this)^(p);
  }
  static long long round(Double d) {
    if (d < 0) return (long long)(d - 0.5);
    return (long long)(d + 0.5);
  }
};
ostream& operator<<(ostream& o, const Point &P){
	return o <<"("<< P.x << "," << P.y << ")";
}