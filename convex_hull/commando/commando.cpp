// https://www.spoj.com/problems/APIO10A/
// http://wcipeg.com/wiki/Convex_hull_trick

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef long long ftype;
typedef complex<ftype> point;
typedef pair<ll, ll> pii;

#define x real
#define y imag

struct env 
{
    ftype dot(point a, point b)   { return (conj(a) * b).x(); }
    ftype cross(point a, point b) { return (conj(a) * b).y(); }

    void add_line(ftype k, ftype b) {
        point nw = {k, b};
        
        // sign of the dot product matters if ur going clockwise or counterclockwise
        while(!vecs.empty() && dot(vecs.back(), nw - hull.back()) > 0) {
            hull.pop_back();
            vecs.pop_back();
        }

        if(!hull.empty()) {
            vecs.push_back(complex<ll>{0, 1} * (nw - hull.back()));
        }
        hull.push_back(nw);
    }

    ftype get(ftype x) {
        point query = {x, 1};
        auto it = lower_bound(vecs.begin(), vecs.end(), query, [this] (point a, point b) {
            return cross(a, b) < 0;
        });
        return dot(query, hull[it - vecs.begin()]);
    }

private:
    // int pos = 0;

public:
    vector<point> hull, vecs;
};

void solve () 
{
    ll n, a, b, c;
    cin >> n;
    cin >> a >> b >> c;

    env hull;
    vector<ll> dp(n+1);

    vector<ll> pre(n+1); // prefix sum array
    for (int i = 1; i <= n; i++) {
        cin >> pre[i];
        pre[i] += pre[i-1];
    }

    auto func = [a, b, c, pre] (ll x) {
        return a*pre[x]*pre[x] + b*pre[x] + c;
    };

    auto get_m = [a, pre] (ll x) {
        return -2 * a * pre[x];
    };

    // lambdas don't capture by reference unless told to!
    auto get_b = [a, b, pre, &dp] (int x) {
        return dp[x] + (a*pre[x]*pre[x]) - (b*pre[x]);
    };

    dp[1] = func(1);
    hull.add_line(get_m(1), get_b(1));


    for(int i = 2; i <= n; i++) {
        dp[i] = func(i);
        dp[i] = max(dp[i], dp[i] + hull.get(pre[i]));

        hull.add_line( get_m(i) , get_b(i) );
    }

    cout << dp[n] << endl;

}


int main () 
{
    int k;
    cin >> k;

    while (k--) solve();
}