# [Codinggame Spring Challenge 2020](https://www.codingame.com/contests/spring-challenge-2020)
- 自分なりの解答コード．

## 最短経路探索の種類
- V: 頂点数
- E: 辺数

| 使用する時                 | 名称                  | 計算量                           |
|----------------------------|-----------------------|----------------------------------|
| 辺の重みが全て同一の非負数 | 幅優先探索            | O(V+E)                        |
| 辺の重みが非負数           | ダイクストラ法        | O(V^2), O((E+V)logV), O(E+VlogV) |
| 辺の重みに負数を含む       | ベルマン-フォード法   | O(abs(V)\*abs(E))                |
| 全ての2点間を求める        | ワーシャル-フロイド法 | O(V^3)                           |

## References
### ゲーム木探索
- [ゲーム木探索技術とコンピュータ将棋への応用](https://www.slideshare.net/shogotakeuchi/ss-62415546)
- [5分で覚えるAI Minimax（ミニマックス）法とalpha-beta法](https://www.webcyou.com/?p=6997)
- [強化学習入門 Part3 － AlphaGoZeroでも重要な技術要素！ モンテカルロ木探索の入門 －](https://blog.brainpad.co.jp/entry/2018/04/05/163000)
- [モンテカルロで二人ゲーム](http://ustimaw.hatenablog.com/entry/2014/12/14/081423)
- [競技プログラミングにおけるゲーム木探索の面白さ](https://qiita.com/tsukammo/items/02e8ad2469c5441d2956)

### 幅優先探索
- [幅優先探索(Breadth First Search)の基本](https://algo-logic.info/bfs/)
- [最短経路問題総特集！！！～BFSから拡張ダイクストラまで～](https://qiita.com/ageprocpp/items/cdf67e828e1b09316f6e)
- [最短経路問題の解法まとめ](https://qiita.com/ta-ka/items/a023a11efe17ab097433)
- [競プロとかに使うアルゴリズム実装メモ（最短経路探索系）](https://yamagensakam.hatenablog.com/entry/2018/08/19/234224)
- [最短経路問題(ダイクストラ法)](http://nocotan.github.io/%E3%82%A2%E3%83%AB%E3%82%B4%E3%83%AA%E3%82%BA%E3%83%A0/2017/01/26/dijkstra-copy.html)
- [ダイクストラ法アルゴリズムで最短ルートを求める](http://www.sousakuba.com/Programming/algo_root.html)
- [ベルマンフォード法とワーシャルフロイド法の解説](https://dai1741.github.io/maximum-algo-2012/docs/shortest-path/)
- [C++ 高速化 処理時間の計測](http://www.sanko-shoko.net/note.php?id=rnfd)
