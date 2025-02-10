#pragma optimize("O3")

#include <bits/stdc++.h>
using namespace std;

#define all(x) begin(x), end(x)
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<ll> vll;
typedef vector<vll> vvll;

struct edge {
    char type;
    string company;
    string dest;

    string stringify() {
        return "type=" + to_string(type) + " "
               "company=" + company + " "
               "dest=" + dest;
    }
};

struct state {
    int dist;
    string location;
    int tickets_left;
    string last_company;

    string stringify() {
        return "dist=" + to_string(dist) + " " + 
               "company=" + last_company + " " +
               "tix=" + to_string(tickets_left) + " " +
               "location=" + location;
    }
};

bool operator<(const state x, const state y) {
    return x.dist < y.dist;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n;
    string start, end;
    int k;
    cin >> n >> start >> end >> k;

    map<string, vector<edge>> edges;
    while (n--) {
        char type;
        string company, x, y;
        cin >> type >> company >> x >> y;
        edges[x].push_back(edge{type, company, y});
        edges[y].push_back(edge{type, company, x});
    }

    map<pair<string, int>, int> dist; // location, tickets
    priority_queue<state> pq;
    pq.push(state{0, start, k, ""});

    while (!pq.empty()) {
        state cur = pq.top();
        pq.pop();

        /*cout << "bsfing!!! " << cur.stringify() << endl;*/

        for (edge e : edges[cur.location]) {
            /*cout << "checking edge... " << e.stringify() << endl;*/
            int new_dist = cur.dist + (e.company != cur.last_company);
            int new_tickets_left = cur.tickets_left - (e.type == 'P');
            if (new_tickets_left < 0) {
                continue;
            }

            auto dist_id = make_pair(e.dest, new_tickets_left);
            if (!dist.count(dist_id) || new_dist < dist[dist_id]) {
                dist[dist_id] = new_dist;
                pq.push(state{new_dist, e.dest, new_tickets_left, e.company});
            }
        }
    }

    int ans = INT_MAX;
    for (int i = 0; i <= k; i++) {
        if (dist.count(make_pair(end, i))) {
            ans = min(ans, dist[make_pair(end, i)]);
        }
    }
    cout << ans << endl;
}
