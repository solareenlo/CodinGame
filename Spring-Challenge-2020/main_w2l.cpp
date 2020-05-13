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
constexpr double INF = numeric_limits<double>::infinity();

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

    string map[h];
    REP(i, h) {
        string row;
        getline(cin, row); // one line of the grid: space " " is floor, pound "#" is wall
        map[i] = row;
    }
    // REP (i, h) {
    //     cout << map[i] << '-';
    // }

    std::map<P, int> pallet;
    P myPac;

    // game loop
    while (1) {
        int myScore;
        int opponentScore;
        cin >> myScore >> opponentScore; cin.ignore();
        int visiblePacCount; // all your pacs and enemy pacs in sight
        cin >> visiblePacCount; cin.ignore();
        REP(i, visiblePacCount) {
            int pacId; // pac number (unique within a team)
            bool mine; // true if this pac is yours
            int x; // position in the grid
            int y; // position in the grid
            string typeId; // unused in wood leagues
            int speedTurnsLeft; // unused in wood leagues
            int abilityCooldown; // unused in wood leagues
            cin >> pacId >> mine >> x >> y >> typeId >> speedTurnsLeft >> abilityCooldown; cin.ignore();
            if (mine) {
                myPac.first = x;
                myPac.second = y;
            }
        }
        int visiblePelletCount; // all pellets in sight
        cin >> visiblePelletCount; cin.ignore();
        pallet.clear();
        REP(i, visiblePelletCount) {
            int x;
            int y;
            int v; // amount of points this pellet is worth
            cin >> x >> y >> v; cin.ignore();
            pallet.insert(make_pair(make_pair(x, y), v));
        }

        P target;
        double tmp = INF;
        int count_10pallet = 0;
        for (auto itr = pallet.begin(); itr != pallet.end(); ++itr) {
            if (itr->second == 10) {
                // cout << itr->first.first << ' ' << itr->first.second << ' ' <<  myPac.first << ' ' << myPac.second << endl;
                double dist = calDist(itr->first, myPac);
                if (dist < tmp) {
                    target = itr->first;
                    tmp = dist;
                }
                count_10pallet++;
            }
        }

        if (!(count_10pallet)) {
            for (auto itr = pallet.begin(); itr != pallet.end(); ++itr) {
                double dist = calDist(itr->first, myPac);
                if (dist < tmp) {
                    target = itr->first;
                    tmp = dist;
                }
            }
        }

        // Write an action using cout. DON'T FORGET THE "<< endl"
        // To debug: cerr << "Debug messages..." << endl;

        cout << "MOVE 0 " << target.first << ' ' << target.second << endl; // MOVE <pacId> <x> <y>
    }
}
