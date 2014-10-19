const int MAXN = 500;
const double EPS = 1e-10;
inline int sgn(const double &a) { return a > EPS ? 1 : (a < -EPS ? -1 : 0); }
struct Polynomial {
    double data[MAXN];
    int n;
    Polynomial() {}
    Polynomial(int _n) : n(_n) {
        memset(data, 0, sizeof(data));
    }
    Polynomial(double *_data, int _n) {
        memset(data, 0, sizeof(data));
        n = _n;
        for (int i = n; i >= 0; i--) data[i] = _data[i];
    }
    Polynomial operator + (const Polynomial &a) {
        Polynomial c(max(n, a.n));
        for (int i = c.n; i >= 0; i--) c.data[i] = data[i] + a.data[i];
        while (sgn(c.data[c.n]) == 0 && c.n) c.n--;
        return c;
    }
    Polynomial operator - (const Polynomial &a) {
        Polynomial c(max(n, a.n));
        for (int i = c.n; i >= 0; i--) c.data[i] = data[i] - a.data[i];
        while (sgn(c.data[c.n]) == 0 && c.n) c.n--;
        return c;
    }
    Polynomial operator * (const Polynomial &a) {
        Polynomial c(n + a.n);
        for (int i = n; i >= 0; i--) for (int j = a.n; j >= 0; j--) c.data[i + j] += data[i] * a.data[j];
        return c;
    }
    Polynomial operator / (const Polynomial &a) {
        if (n < a.n) return *this;
        else {
            Polynomial c(n - a.n);
            for (int i = c.n; i >= 0; i--) c.data[i] = data[i + a.n];
            for (int i = c.n; i >= 0; i--) {
                c.data[i] /= a.data[a.n];
                for (int j = i - 1; a.n - i + j >= 0 && j >= 0; j--) c.data[j] -= c.data[i] * a.data[a.n - i + j];
            }
            return c;
        }
    }
    Polynomial operator % (const Polynomial &a) {
        Polynomial c = *this - *this / a * a;
        while (sgn(c.data[c.n]) == 0 && c.n) c.n--;
        return c;
    }
    bool iszero() {
        return n == 0 && sgn(data[0]) == 0;
    }
    bool isconst() {
        return n > 0;
    }
    Polynomial derivative() {
        Polynomial a(n - 1);
        for (int i = n - 1; i >= 0; i--) a.data[i] = data[i + 1] * (double)(i + 1);
        return a;
    }
    Polynomial integral() {
        Polynomial a(n + 1);
        for (int i = n + 1; i >= 1; i--) a.data[i] = data[i - 1] / (double)i;
        return a;
    }
    void show() {
        for (int i = n; i >= 0; i--) {
            printf("%.6f", data[i], i);
            if (i != 0) printf(" x");
            if (i != 1 && i != 0) printf(" ^ %d", i);
            if (i != 0) printf(" + ");
            else printf("\n");
        }
    }
};
Polynomial gcd(Polynomial a , Polynomial b) {
    if (b.iszero()) return a;
    else return gcd(b, a % b);
}
