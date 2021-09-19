// https://www.spoj.com/problems/ACQUIRE/
// http://wcipeg.com/wiki/Convex_hull_trick

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef long long ftype;
typedef complex<ftype> point;
typedef pair<ll, ll> pii;

#define x real
#define y imag



struct env {
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
        auto it = lower_bound(vecs.begin(), vecs.end(), query, [this](point a, point b) {
            return cross(a, b) > 0;
        });
        return dot(query, hull[it - vecs.begin()]);
    }

public:
    vector<point> hull, vecs;
};

void solve () 
{
    env hull;
    int n;
    cin >> n;
    vector<pii> plots;

    int w, l;
    for (int i = 0; i < n; i++) {
        cin >> w >> l;
        plots.emplace_back(w, l);
    }

    sort(plots.begin(), plots.end());

    auto comp = [] (const pii& a, const pii& b) {
        // if (a.first == b.first && a.second > b.second) return -1;
        if (b.second >= a.second) return true;
        return false;
    };
    
    stack<pii> unq;
    unq.push(plots[0]);

    for (uint i = 1; i < plots.size(); i++) {
        while (!unq.empty() && comp(unq.top(), plots[i])) unq.pop();

        unq.push(plots[i]);
    }
    plots.resize(0);
    while (!unq.empty()) {
        plots.push_back(unq.top());
        unq.pop();
    }
    reverse(plots.begin(), plots.end());
    n = plots.size();

    hull.add_line(plots[0].second, 0);

    ll cost = 0;
    for (int i = 0; i < n; i++) {

        cost = hull.get(plots[i].first);
		if (i < n-1) hull.add_line(plots[i+1].second, cost);
	}

    cout << cost << endl;

    // greedy solution
    // It fails on (10, 25), (15, 12), (20, 5), (25, 4) - answer is 500
    // the problem is DP 
    /*
    auto merge = [] (pii& a, const pii& b) {
        ll mw = max(a.first, b.first);
        ll mh = max(a.second, b.second);

        if (mw*mh < ((a.first * a.second) + (b.first * b.second)) ) {
            a.first = mw;
            a.second = mh;
            return true;
        }
        return false;
    };
    
    while (!unq.empty()) {
        auto curr = unq.top(); unq.pop();

        while (!unq.empty() && merge(curr, unq.top())) unq.pop();

        cout << curr.first << " " << curr.second << endl;
        cost += curr.first * curr.second;
    }
    */
}


int main () 
{
    solve();
}