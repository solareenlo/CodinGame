#pragma GCC optimize("-O3")
#pragma GCC optimize("inline")
#pragma GCC optimize("omit-frame-pointer")
#pragma GCC optimize("unroll-loops")

#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <queue>
#include <algorithm>
#include <limits>
#include <cmath>
#include <iomanip>
#include <chrono>
#define REP(i, n) for (int i = 0; i <(n); i++)
using namespace std;
using P = pair<int, int>;
using VP = vector<P>;
using QP = queue<P>;
using VI = vector<int>;
using VVI = vector<vector<int> >;
constexpr double INF_DOUBLE = numeric_limits<double>::infinity();
constexpr double INF_INT = numeric_limits<int>::infinity();
constexpr int DX[4] = {1, 0, -1, 0};
constexpr int DY[4] = {0, 1, 0, -1};

inline VVI calDist(P from, P to, VVI map) {
    int height = map.size();
    int width = map[0].size();

    /* 幅優先探索の初期設定 */
    VVI dist(height, VI(width, -1)); // 各セルの最短距離 (訪れていないところは -1 としておく)
    dist[from.second][from.first] = 0; // スタートを 0 に設定
    QP que; // 「一度見た頂点」のうち「まだ訪れていない頂点」を表すキュー
    que.push(make_pair(from.first, from.second)); // スタートを push

    /* キューが空になるまで */
    while (!que.empty()) {
        P currentPos = que.front(); // キューの先頭を見る
        int x = currentPos.first;
        int y = currentPos.second;
        que.pop(); // キューから先頭を pop する

        // 隣接頂点を探索
        REP(direction, 4) {
            int nextX = x + DX[direction];
            int nextY = y + DY[direction];
            if (nextX < 0 || nextX >= width || nextY < 0 || nextY >= height)
                continue; // 場外アウトはだめ
            if (map[nextY][nextX] == 0)
                continue; // 壁はだめ
            // まだ見ていない頂点なら push
            if (dist[nextY][nextX] == -1) {
                que.push(make_pair(nextX, nextY));
                dist[nextY][nextX] = dist[y][x] + 1; // next の距離も更新
            }
        }
    }
    return dist;
}

inline void mapTranslation(VVI &from, VVI &to, P ori, char c) {
    int height = from.size();
    int width = from[0].size();
    int diffX = 0;
    if (c == 'R') { // ori を右端に持っていく
        for (int j = ori.first + 1; j < width; j++)
            REP(i, height)
                to.at(i).at(j - (ori.first + 1)) = from.at(i).at(j);
        for (int j = 0; j < ori.first + 1; j++)
            REP(i, height)
                to.at(i).at(j + (width - ori.first - 1)) = from.at(i).at(j);
    }
    else if (c == 'L') { // ori を左端に持っていく
        for (int j = ori.first; j < width; j++)
            REP(i, height)
                to.at(i).at(j - ori.first) = from.at(i).at(j);
        for (int j = 0; j < ori.first; j++)
            REP(i, height)
                to.at(i).at(j + (width - ori.first)) = from.at(i).at(j);
    }
}

inline void mapTranslation2Center(VVI &from, VVI &to, P ori) {
    int height = from.size();
    int width = from[0].size();
    int diffX = diffX =  ori.first - (width / 2); // ori を中心に持っていく
    if (diffX <= 0) {
        for (int j = ori.first; j < width + diffX; j++)
            REP(i, height)
                to.at(i).at(j - diffX) = from.at(i).at(j);
        for (int j = 0; j < ori.first; j++)
            REP(i, height)
                to.at(i).at(j - diffX) = from.at(i).at(j);
        for (int j = width + diffX; j < width; j++)
            REP(i, height)
                to.at(i).at(j - width - diffX) = from.at(i).at(j);
    } else {
        for (int j = ori.first; j < width; j++)
            REP(i, height)
                to.at(i).at(j - diffX) = from.at(i).at(j);
        for (int j = diffX; j < ori.first; j++)
            REP(i, height)
                to.at(i).at(j - diffX) = from.at(i).at(j);
        for (int j = 0; j < diffX; j++)
            REP(i, height)
                to.at(i).at(width - diffX + j) = from.at(i).at(j);
    }
}

inline int calShortestDist(P from, P to, VVI map) {
    int height = map.size();
    int width = map[0].size();
    int diffX =  from.first - (width / 2);
    VVI fieldCenter(height, VI(width, 0)); // from が中央に持っていく
    VVI fieldLeft(height, VI(width, 0)); // from が左端に持っていく
    VVI fieldRight(height, VI(width, 0)); // from を右端に持っていく
    int x = 0, y = 0;

    bool loop = false;
    REP(i, height)
        if (map[i][0] == 1)
            loop = true;
    if (loop) {
        mapTranslation(map, fieldRight, from, 'R');
        P fromRight = make_pair(width - 1, from.second);
        VVI distRight = calDist(fromRight, to, fieldRight);

        mapTranslation(map, fieldLeft, from, 'L');
        P fromLeft = make_pair(0, from.second);
        VVI distLeft = calDist(fromLeft, to, fieldLeft);

        mapTranslation2Center(map, fieldCenter, from);
        P fromCenter = make_pair(from.first - diffX, from.second);
        VVI distCenter = calDist(fromCenter, to, fieldCenter);
        VVI tmp(height, VI(width, -1));
        P inverse = make_pair(width - 1 - from.first, y);
        mapTranslation2Center(distCenter, tmp, inverse);
    } else {
        VVI sidt = calDist(from, to, map);
    }
    return 0;
}

/**
 * Grab the pellets as fast as you can!
 **/

int main() {
    chrono::system_clock::time_point start, end;
    int width, height; // top left corner is (x=0, y=0)
    cin >> width >> height; cin.ignore();

    VVI map(height, VI(width, 0));
    REP(i, height) {
        string row;
        getline(cin, row); // one line of the grid: space " " is floor, pound "#" is wall
        REP(j, width) {
            if (row[j] == ' ') map[i][j] = 1;
            else if (row[j] == '#') map[i][j] = 0;
        }
    }

    // 床の枚数を数える
    int countFloor = 0;
    REP(i, height) REP(j, width) {
        countFloor += map[i][j];
    }

    VP myPac;
    VP opponentPac;
    std::map<P, int> pellet;
    double time = static_cast<double>(chrono::duration_cast<chrono::microseconds>(end - start).count() / 1000.0);
    cerr << "time: " << time << endl;
    // printf("time %lf[ms]\n", time);
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
            map[y][x] = 0;
        }

        int visiblePelletCount; // all pellets in sight
        cin >> visiblePelletCount; cin.ignore();
        pellet.clear();
        REP(i, visiblePelletCount) {
            int x, y, v; // v is amount of points this pellet is worth
            cin >> x >> y >> v; cin.ignore();
            pellet.insert(make_pair(make_pair(x, y), v));
        }

        start = chrono::system_clock::now();
        VP target;
        VP pellet10;
        for (auto itr = pellet.begin(); itr != pellet.end(); itr++) {
            if (itr->second == 10) pellet10.push_back(itr->first);
        }
        // for (auto itr = pellet10.begin(); itr != pellet10.end(); itr++) {
        //     cerr << itr->first << ' ' << itr->second << endl;
        // }
        int tmp = calShortestDist(myPac[0], pellet.begin()->first, map);
        end = chrono::system_clock::now();

        // Write an action using cout. DON'T FORGET THE "<< endl"
        // To debug: cerr << "Debug messages..." << endl;

        REP(i, myPac.size()) {
            cout << "MOVE" << ' ' << i << ' ' << target[i].first << ' ' << target[i].second; // MOVE <pacId> <x> <y>
            if (i == myPac.size() - 1) cout << endl;
            else cout << " | ";
        }
    }
}
