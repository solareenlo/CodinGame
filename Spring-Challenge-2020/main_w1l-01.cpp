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
constexpr int INF_INT = numeric_limits<int>::infinity();
// typedef vector<vector<int> > Matrix;
// Matrix d; // グラフの距離を格納した2次元配列（隣接行列）
          // d[u][v] は辺 e=(u,v) のコスト（辺が存在しない場合はINF，ただし d[i][i]=0）

// inline void warshallFloyd(int n) {
//     REP(k, n) REP(i, n) REP(j, n) {
//         d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
//     }
// }

inline double calDist(P a, P b) {
    double dist;
    dist = sqrt(pow(a.first - b.first, 2) + pow(a.second - b.second, 2));
    return dist;
}

/**
 * Grab the pellets as fast as you can!
 **/

int main()
{
    int w; // size of the grid
    int h; // top left corner is (x=0, y=0)
    cin >> w >> h; cin.ignore();

    int map[h][w][2];
    REP(i, h) {
        string row;
        getline(cin, row); // one line of the grid: space " " is floor, pound "#" is wall
        REP(j, w) {
            if (row[j] == ' ') map[i][j][0] = 1;
            else if (row[j] == '#') map[i][j][0] = 0;
        }
    }
    cerr << "Debug messages: 001" << endl;

    // REP(i, h) {
    //     REP(j, w) {
    //         cout << map[i][j] << ' ';
    //     }
    //     cout << '-';
    // }
    // cout << endl;

    // 床の枚数を数える
    // 全ての床に対する2点間の最短距離を求めるために
    // int countFloor = 0;
    // REP(i, h) REP(j, w) {
    //     countFloor += map[i][j][0];
    //     map[i][j][1] = countFloor - 1;
    // }

    // ワーシャルフロイド法のための初期化
    // d = Matrix(count_floor, vector<int>(count_floor, INF_INT));
    // REP(i, count_floor) d[i][i] = 0;

    // 2点間のコストを設定する
    // for (int i = 1; i < h - 1; i++) {
    //     for (int j = 1; j < w - 1; j++) {
    //         if (map[i][j][0] == 1) {
    //             if (map[i - 1][j][0] == 1) d[map[i][j][1]][map[i - 1][j][1]] = 1;
    //             if (map[i + 1][j][0] == 1) d[map[i][j][1]][map[i + 1][j][1]] = 1;
    //             if (map[i][j - 1][0] == 1) d[map[i][j][1]][map[i][j - 1][1]] = 1;
    //             if (map[i][j + 1][0] == 1) d[map[i][j][1]][map[i][j + 1][1]] = 1;
    //         }
    //     }
    // }

    // 全ての床に対して2点間の最短距離をワーシャルフロイド法で設定
    // warshallFloyd(countFloor);

    std::map<P, int> pellet;
    cerr << "Debug messages: 002" << endl;

    // game loop
    while (1) {
        int myScore;
        int opponentScore;
        cin >> myScore >> opponentScore; cin.ignore();
        int visiblePacCount; // all your pacs and enemy pacs in sight
        cin >> visiblePacCount; cin.ignore();
        int countMyPac = 0;
        vector<P> myPac;
        cerr << "Debug messages: 003" << endl;
        REP(i, visiblePacCount) {
            int pacId; // pac number (unique within a team)
            bool mine; // true if this pac is yours
            int x, y; // position in the grid
            string typeId; // unused in wood leagues
            int speedTurnsLeft; // unused in wood leagues
            int abilityCooldown; // unused in wood leagues
            cin >> pacId >> mine >> x >> y >> typeId >> speedTurnsLeft >> abilityCooldown; cin.ignore();
            cerr << "Debug messages: 004" << endl;
            cerr << pacId << ' ' << mine << ' ' << x << ' ' << y << endl;
            if (mine) {
                // myPac[pacId] = make_pair(x, y);
                // myPac[pacId].first = x;
                // myPac[pacId].second = y;
                countMyPac++;
            }
            cerr << "Debug messages: 005" << endl;
        }
        cerr << "Debug messages: 006" << endl;

        pellet.clear();
        int visiblePelletCount; // all pellets in sight
        cin >> visiblePelletCount; cin.ignore();
        REP(i, visiblePelletCount) {
            int x, y, v; // v is amount of points this pellet is worth
            cin >> x >> y >> v; cin.ignore();
            pellet.insert(make_pair(make_pair(x, y), v));
        }

        vector<P> target;
        double tmp = INF_DOUBLE;
        int count10pellet = 0;
        for (auto itr = pellet.begin(); itr != pellet.end(); ++itr) {
            if (itr->second == 10) {
                REP(i, countMyPac) {
                    double dist = calDist(itr->first, myPac[i]);
                    if (dist < tmp) {
                        target[i] = itr->first;
                        tmp = dist;
                    }
                }
                count10pellet++;
            }
        }

        if (!(count10pellet)) {
            for (auto itr = pellet.begin(); itr != pellet.end(); ++itr) {
                REP(i, countMyPac) {
                    double dist = calDist(itr->first, myPac[i]);
                    if (dist < tmp) {
                        target[i] = itr->first;
                        tmp = dist;
                    }
                }
            }
        }

        // Write an action using cout. DON'T FORGET THE "<< endl"
        // To debug: cerr << "Debug messages..." << endl;

        REP(i, countMyPac) {
            cout << "MOVE" << ' ' << i << ' ' << target[i].first << ' ' << target[i].second; // MOVE <pacId> <x> <y>
            if (i == countMyPac - 1) cout << endl;
            else cout << " | ";
        }
    }
}
