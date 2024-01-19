#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using ld = long double;
const ld PI = acos(-1.0);

int sgn(ll a) {
    if (a < 0) {
        return -1;
    } else if (a > 0) {
        return 1;
    } else {
        return 0;
    }
}

template <typename T>
struct point {
    T x, y;
    explicit point() {
        x = 0;
        y = 0;
    }
    explicit point(T _x, T _y) {
        x = _x;
        y = _y;
    }

    const point<T> operator+(const point<T> &other) { return point<T>(x + other.x, y + other.y); }
    const point<T> operator-(const point<T> &other) { return point<T>(x - other.x, y - other.y); }

    bool operator==(const point<T> &other) { return (x == other.x) && (y == other.y); }
    bool operator<(const point<T> &other) {
        if (x == other.x) {
            return y < other.y;
        }
        return x < other.x;
    }

    ll operator*(point<T> &other) { return 1ll * x * other.x + 1ll * y * other.y; }  // dot product - |a||b|cos(alpha)

    ll operator%(point<T> &other) { return 1ll * x * other.y - 1ll * y * other.x; }  // cross product - |a||b|sin(alpha)

    ld get_vector_length() { return sqrtl(1ll * x * x + 1ll * y * y); }

    point<ld> normalize_vector() {
        ld len = get_vector_length();
        return point<ld>(x / len, y / len);
    }

    point<ld> vector_to_len(T length) {
        point<ld> norm_vector = normalize_vector();
        return point<ld>(norm_vector.x * length, norm_vector.y * length);
    }

    ld polar_angle() {
        ld angle = atan2(y, x);
        if (angle < 0) angle += 2 * PI;
        return angle;
    }

    ld angle_between_points(point<T> &other) { return atan2(operator%(other), operator*(other)); }  // angle - [-pi, +pi]

    ld angle_between_points_normal(point<T> &other) {  // angle - [0, 2 * pi]
        ld angle = angle_between_points(other);
        if (angle < 0) angle += 2 * PI;
        return angle;
    }

    point<T> rotate_vector_ninety_degrees_clockwise() { return point<T>(y, -x); }

    point<T> rotate_vector_ninety_degrees_counterclockwise() { return point<T>(-y, x); }

    point<ld> rotate_vector_counterclockwise(ld angle) {
        return point<ld>(cos(angle) * x - sin(angle) * y, sin(angle) * x + cos(angle) * y);
    }
};
template <typename T>
istream &operator>>(istream &in, point<T> &pt) {
    in >> pt.x >> pt.y;
    return in;
}
template <typename T>
ostream &operator<<(ostream &out, point<T> &pt) {
    out << pt.x << " " << pt.y;
    return out;
}

template <typename T>
bool turning_counter_clockwize(point<T> &a, point<T> &b) {
    return sgn(a % b) > 0;
}

template <typename T>
bool turning_clockwize(point<T> &a, point<T> &b) {
    return sgn(a % b) < 0;
}

template <typename T>
ld area_of_triangle(point<T> p1, point<T> p2, point<T> p3) {
    return abs(p1 % p2 + p2 % p3 + p3 % p1) / 2.0;
}
template <typename T>
ll area_of_triangle2(point<T> p1, point<T> p2, point<T> p3) {
    return p1 % p2 + p2 % p3 + p3 % p1;
}

template <typename T>
struct sequence {
    point<T> a, b;
    explicit sequence() {
        a.x = 0;
        a.y = 0;
        b.x = 0;
        b.y = 0;
    }
    explicit sequence(point<T> _a, point<T> _b) {
        a = _a;
        b = _b;
    }

    bool bounding_box(point<T> pt) {
        return (min(a.x, b.x) <= pt.x && pt.x <= max(a.x, b.x) && min(a.y, b.y) <= pt.y && pt.y <= max(a.y, b.y));
    }

    bool points_on_diff_sides(point<T> pt1, point<T> pt2) {
        point<T> AB = this->b - this->a;
        point<T> AP1 = pt1 - this->a;
        point<T> AP2 = pt2 - this->b;
        return sgn(AB % AP1) != sgn(AB % AP2);
    }
};
template <typename T>
istream &operator>>(istream &in, sequence<T> &seq) {
    in >> seq.a >> seq.b;
    return in;
}

template <typename T>
ostream &operator<<(ostream &out, sequence<T> &seq) {
    out << seq.a << seq.b;
    return out;
}

template <typename T>
struct line {
    T A, B, C;
    point<T> pt1, pt2;
    explicit line() {
        A = 0;
        B = 0;
        C = 0;
    }
    explicit line(T _A, T _B, T _C) {
        A = _A;
        B = _B;
        C = _C;
    }
    explicit line(point<T> a, point<T> b) {
        pt1 = a;
        pt2 = b;
        A = b.y - a.y;
        B = a.x - b.x;
        C = -1 * (A * a.x + B * a.y);
    }
    explicit line(sequence<T> s) {
        pt1 = s.a;
        pt2 = s.b;
        A = s.b.y - s.a.y;
        B = s.a.x - s.b.x;
        C = -1 * (A * s.a.x + B * s.a.y);
    }

    bool point_on_line(point<T> a) { return (A * a.x + B * a.y + C) == 0; }

    int line_intersection(line<T> &other) {
        if (1ll * A * B == 1ll * other.A * B && 1ll * B * other.C == 1ll * other.B * C && 1ll * A * other.C == 1ll * C * other.A) {
            return 2;  // lines - equal
        }
        if (1ll * A * other.B == 1ll * other.A * B) {
            return 0;  // lines - parallel
        }
        return 1;  // lines - intersect
    }

    point<ld> point_of_intersection(line<T> &other) {
        point<ld> ans;
        ans.x = (ld)(other.C * B - C * other.B) / (other.B * A - other.A * B);
        ans.y = (ld)(C * other.A - A * other.C) / (other.B * A - other.A * B);
        return ans;
    }
};
template <typename T>
istream &operator>>(istream &in, line<T> &l) {
    in >> l.A >> l.B >> l.C;
    return in;
}
template <typename T>
ostream &operator<<(ostream &out, line<T> &l) {
    out << l.A << " " << l.B << " " << l.C;
    return out;
}

template <typename T>
struct ray {
    point<T> start, finish;
    explicit ray() {
        start.x = 0;
        start.y = 0;
        finish.x = 0;
        finish.y = 0;
    }
    explicit ray(T x1, T y1, T x2, T y2) {
        start.x = x1;
        start.y = y1;
        finish.x = x2;
        finish.y = y2;
    }

    explicit ray(point<T> a, point<T> b) {
        start = a;
        finish = b;
    }

    explicit ray(sequence<T> s) {
        start = s.a;
        finish = s.b;
    }

    bool point_on_ray(point<T> &other) {
        line<T> line_of_ray(start, finish);
        point<T> start_finish = finish - start;
        point<T> start_other = other - start;
        return (line_of_ray.point_on_line(other) && sgn(start_finish * start_other) >= 0);
    }
};

template <typename T>
istream &operator>>(istream &in, ray<T> &r) {
    in >> r.start >> r.finish;
    return in;
}

template <typename T>
ostream &operator<<(ostream &out, ray<T> &r) {
    out << r.start << r.finish;
    return out;
}

template <typename T>
struct circle {
    point<T> center;
    T r;
    explicit circle() {
        center.x = 0;
        center.y = 0;
        r = 0;
    }
    explicit circle(point<T> pt, T _r) {
        center = pt;
        r = _r;
    }
};

template <typename T>
istream &operator>>(istream &in, circle<T> &c) {
    in >> c.center >> c.r;
    return in;
}

template <typename T>
ostream &operator<<(ostream &out, circle<T> &c) {
    out << c.center << c.r;
    return out;
}

template <typename T>
int sequence_intersection(sequence<T> s1, sequence<T> s2) {
    line<T> l1(s1), l2(s2);
    int type_of_intersection = l1.line_intersection(l2);
    if (type_of_intersection == 0) {
        return 0;
    }
    if (type_of_intersection == 2) {
        if (s1.bounding_box(s2.a) || s1.bounding_box(s2.b) || s2.bounding_box(s1.a) || s2.bounding_box(s1.b)) {
            return 2;
        }
        return 0;
    }
    if (s1.points_on_diff_sides(s2.a, s2.b) && s2.points_on_diff_sides(s1.a, s1.b)) {
        return 1;
    }
    return 0;
}

template <typename T>
ld get_distance(point<T> &pt1, point<T> &pt2) {
    return sqrtl((pt1.x - pt2.x) * 1ll * (pt1.x - pt2.x) + (pt1.y - pt2.y) * 1ll * (pt1.y - pt2.y));
}

template <typename T>
ld get_distance(point<T> &pt, sequence<T> &seq) {
    line<T> l(seq);
    if (l.point_on_line(pt)) {
        return (seq.bounding_box(pt) ? 0 : min(get_distance(pt, seq.a), get_distance(pt, seq.b)));
    }
    point<T> BA = pt - seq.a, BC = seq.b - seq.a;
    if (sgn(BA * BC) < 0) {
        return get_distance(pt, seq.a);
    }
    point<T> CA = pt - seq.b, CB = seq.a - seq.b;
    if (sgn(CA * CB) < 0) {
        return get_distance(pt, seq.b);
    }
    return area_of_triangle(pt, seq.a, seq.b) / get_distance(seq.a, seq.b) * 2;
}

template <typename T>
ld get_distance(point<T> &pt, line<T> &l) {
    return abs(1ll * l.A * pt.x + 1ll * l.B * pt.y + l.C) / sqrtl(1ll * l.A * l.A + 1ll * l.B * l.B);
}

template <typename T>
ld get_distance(point<T> &pt, ray<T> &r) {
    line<T> l(r.start, r.finish);
    if (l.point_on_line(pt)) {
        point<T> start_pt = pt - r.start, start_finish = r.finish - r.start;
        if (sgn(start_pt * start_finish) < 0) {
            return get_distance(pt, r.start);
        }
        return 0;
    }
    point<T> BA = pt - r.start, BC = r.finish - r.start;
    if (sgn(BA * BC) < 0) {
        return get_distance(pt, r.start);
    }
    return area_of_triangle(pt, r.start, r.finish) / get_distance(r.start, r.finish) * 2;
}

template <typename T>
ld get_distance(sequence<T> &seq1, sequence<T> &seq2) {
    if (sequence_intersection(seq1, seq2) != 0) {
        return 0;
    }
    return min({get_distance(seq1.a, seq2), get_distance(seq1.b, seq2), get_distance(seq2.a, seq1), get_distance(seq2.b, seq1)});
}

template <typename T>
ld get_distance(sequence<T> &seq, ray<T> &r) {
    line<T> l1(seq), l2(r.start, r.finish);
    int type_of_intersection = line_intersection(l1, l2);
    if (type_of_intersection == 2) {
        point<T> start_finish = r.finish - r.start, start_a = seq.a - r.start, start_b = seq.b - r.start;
        if (sgn(start_finish * start_a) >= 0 || sgn(start_finish * start_b) >= 0) {
            return 0;
        }
        return min(get_distance(seq.a, r.start), get_distance(seq.b, r.start));
    }
    if (type_of_intersection == 1) {
        point<T> start_finish = r.finish - r.start, start_a = seq.a - r.start, start_b = seq.b - r.start;
        if (sgn(start_finish % start_a) != sgn(start_finish % start_b)) {
            point<T> a_b = seq.b - seq.a, a_start = r.start - seq.a;
            if (sgn(a_b % a_start) != sgn(a_b % start_finish)) {
                return 0;
            }
        }
    }
    return min({get_distance(seq.a, r), get_distance(seq.b, r), get_distance(r.start, seq)});
}

template <typename T>
ld get_distance(sequence<T> &seq, line<T> &l) {
    line<T> l_seq(seq);
    if (line_intersection(l_seq, l) == 2) {
        return 0;
    }
    point<T> pt1_pt2 = l.pt2 - l.pt1, pt1_a = seq.a - l.pt1, pt1_b = seq.b - l.pt1;
    if (sgn(pt1_pt2 % pt1_a) != sgn(pt1_pt2 % pt1_b)) {
        return 0;
    }
    return min(get_distance(seq.a, l), get_distance(seq.b, l));
}

template <typename T>
ld get_distance(ray<T> &r1, ray<T> &r2) {
    line<T> l1(r1.start, r1.finish), l2(r2.start, r2.finish);
    int type_of_intersection = line_intersection(l1, l2);
    if (type_of_intersection == 2) {
        point<T> st_fin1 = r1.finish - r1.start, st_fin2 = r2.finish - r2.start, st1_st2 = r2.start - r1.start,
                st2_st1 = r1.start - r2.start;
        if (sgn(st_fin1 * st1_st2) >= 0 || sgn(st_fin2 * st2_st1) >= 0) {
            return 0;
        }
    }
    if (type_of_intersection == 1) {
        point<T> st_fin1 = r1.finish - r1.start, st_fin2 = r2.finish - r2.start, st1_st2 = r2.start - r1.start,
                st2_st1 = r1.start - r2.start;
        if (sgn(st_fin1 % st1_st2) != sgn(st_fin1 % st_fin2) && sgn(st_fin2 % st2_st1) != sgn(st_fin2 % st_fin1)) {
            return 0;
        }
    }
    return min(get_distance(r2.start, r1), get_distance(r1.start, r2));
}

template <typename T>
ld get_distance(ray<T> &r, line<T> l) {
    line<T> lr(r.start, r.finish);
    int type_of_intersection = line_intersection(lr, l);
    if (type_of_intersection == 2) {
        return 0;
    }
    if (type_of_intersection == 1) {
        point<T> pt1_pt2 = l.pt2 - l.pt1, pt1_start = r.start - l.pt1, start_finish = r.finish - r.start;
        if (sgn(pt1_pt2 % pt1_start) != sgn(pt1_pt2 % start_finish)) {
            return 0;
        }
    }
    return get_distance(r.start, l);
}

template <typename T>
ld get_distance(line<T> &l1, line<T> &l2) {
    if (line_intersection(l1, l2) != 0) {
        return 0;
    }
    return min({get_distance(l1.pt1, l2), get_distance(l1.pt2, l2), get_distance(l2.pt1, l1), get_distance(l2.pt2, l1)});
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    return 0;
}