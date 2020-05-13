#pragma GCC optimize("-O3")
#pragma GCC optimize("inline")
#pragma GCC optimize("omit-frame-pointer")
#pragma GCC optimize("unroll-loops")

#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <limits>
#include <cmath>
#define REP(i, n) for (int i = 0; i <(n); i++)
using namespace std;
using P = pair<int, int>;
constexpr double INF_DOUBLE = numeric_limits<double>::infinity();
constexpr double INF_INT = numeric_limits<int>::infinity();
typedef vector<vector<int> > Matrix;
Matrix d; // グラフの距離を格納した2次元配列（隣接行列）
          // d[u][v] は辺 e=(u,v) のコスト（辺が存在しない場合はINF，ただし d[i][i]=0）

inline void warshallFloyd(int n) {
    REP(k, n) REP(i, n) REP(j, n) {
        d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
    }
}

inline double calDist(P a, P b) {
    double dist;
    dist = sqrt(pow(a.first - b.first, 2) + pow(a.second - b.second, 2));
    return dist;
}

/**
 * Grab the pellets as fast as you can!
 **/

int main() {
    int width, height; // top left corner is (x=0, y=0)
    cin >> width >> height; cin.ignore();

    int map[height][width][2];
    REP(i, height) REP(j, width) REP(k, 2) map[i][j][k] = 0;
    REP(i, height) {
        string row;
        getline(cin, row); // one line of the grid: space " " is floor, pound "#" is wall
        REP(j, width) {
            if (row[j] == ' ') map[i][j][0] = 1;
            else if (row[j] == '#') map[i][j][0] = 0;
        }
    }
    // REP(i, height) {
    //     REP(j, width) cerr << map[i][j][0] << ' ';
    //     cerr << endl;
    // }
    // cerr << endl;

    // 床の枚数を数える
    // 全ての床に対する2点間の最短距離を求めるために
    int countFloor = 0;
    REP(i, height) REP(j, width) {
        countFloor += map[i][j][0];
        if (map[i][j][0] == 1) map[i][j][1] = countFloor - 1;
    }
    cerr << "countFloor: " << countFloor << endl;
    REP(i, height) {
        REP(j, width) cerr << map[i][j][1] << ' ';
        cerr << endl;
    }
    cerr << endl;

    // ワーシャルフロイド法のための初期化
    d = Matrix(countFloor, vector<int>(countFloor, 9));
    REP(i, countFloor) d[i][i] = 0;

    // 2点間のコストを設定する
    for (int i = 1; i < height - 1; i++) {
        for (int j = 1; j < width - 1; j++) {
            if (map[i][j][0] == 1) {
                if (map[i - 1][j][0] == 1) d[map[i][j][1]][map[i - 1][j][1]] = 1;
                if (map[i + 1][j][0] == 1) d[map[i][j][1]][map[i + 1][j][1]] = 1;
                if (map[i][j - 1][0] == 1) d[map[i][j][1]][map[i][j - 1][1]] = 1;
                if (map[i][j + 1][0] == 1) d[map[i][j][1]][map[i][j + 1][1]] = 1;
            }
        }
    }
    // REP(i, countFloor) {
    //     REP(j, countFloor) cerr << d[i][j] << ' ' ;
    //     cerr << endl;
    // }

    REP(j, height) {
        if (map[0][j][0] == 1) {
            d[map[0][j][1]][map[1][j][1]] = 1;
            d[map[1][j][1]][map[0][j][1]] = 1;
            d[map[0][j][1]][map[width - 1][j][1]] = 1;
            d[map[width - 1][j][1]][map[0][j][1]] = 1;
        }
    }
    // REP(i, countFloor) {
    //     REP(j, countFloor) cerr << d[i][j] << ' ' ;
    //     cerr << '\n';
    // }

    vector<P> myPac;
    vector<P> opponentPac;
    std::map<P, int> pellet;
    // game loop
    while (1) {
        int myScore;
        int opponentScore;
        cin >> myScore >> opponentScore; cin.ignore();

        int visiblePacCount; // all your pacs and enemy pacs in sight
        cin >> visiblePacCount; cin.ignore();
        myPac.clear();
        opponentPac.clear();
        REP(i, visiblePacCount) {
            int pacId; // pac number (unique within a team)
            bool mine; // true if this pac is yours
            int x, y; // position in the grid
            string typeId; // unused in wood leagues
            int speedTurnsLeft; // unused in wood leagues
            int abilityCooldown; // unused in wood leagues
            cin >> pacId >> mine >> x >> y >> typeId >> speedTurnsLeft >> abilityCooldown; cin.ignore();
            if (mine) myPac.push_back(make_pair(x, y));
            else opponentPac.push_back(make_pair(x, y));
            // ワーシャルフロイド法のために pacs がいるところはコストを無限大にする
            d[x][y] = 0;
        }

        // 全ての床に対して2点間の最短距離をワーシャルフロイド法で設定
        warshallFloyd(countFloor);
        REP(i, countFloor) {
            REP(j, countFloor) cerr << d[i][j] << ' ' ;
            cerr << '\n';
        }

        int visiblePelletCount; // all pellets in sight
        cin >> visiblePelletCount; cin.ignore();
        pellet.clear();
        REP(i, visiblePelletCount) {
            int x, y, v; // v is amount of points this pellet is worth
            cin >> x >> y >> v; cin.ignore();
            pellet.insert(make_pair(make_pair(x, y), v));
        }

        vector<P> target;
        int tmpI[myPac.size()];
        REP(i, myPac.size()) tmpI[i] = INF_INT;
        int count10pellet = 0;
        int cost = INF_INT;
        for (auto itr = pellet.begin(); itr != pellet.end(); ++itr) {
            if (itr->second == 10) {
                REP(i, myPac.size()) {
                    int cost = d[map[myPac[i].first][myPac[i].second][1]][map[itr->first.first][itr->first.second][1]];
                    if (cost < tmpI[i]) {
                        target.insert(target.begin() + i, itr->first);
                        tmpI[i] = cost;
                    }
                }
                count10pellet++;
            }
        }

        if (!(count10pellet)) {
            for (auto itr = pellet.begin(); itr != pellet.end(); ++itr) {
                REP(i, myPac.size()) {
                    int cost = d[map[myPac[i].first][myPac[i].second][1]][map[itr->first.first][itr->first.second][1]];
                    if (cost < tmpI[i]) {
                        target.insert(target.begin() + i, itr->first);
                        tmpI[i] = cost;
                    }
                }
            }
        }

        // Write an action using cout. DON'T FORGET THE "<< endl"
        // To debug: cerr << "Debug messages..." << endl;

        REP(i, myPac.size()) {
            cout << "MOVE" << ' ' << i << ' ' << target[i].first << ' ' << target[i].second; // MOVE <pacId> <x> <y>
            if (i == myPac.size() - 1) cout << endl;
            else cout << " | ";
        }
    }
}
