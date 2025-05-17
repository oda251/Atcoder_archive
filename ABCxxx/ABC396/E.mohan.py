from collections import deque

n, m = map(int, input().split())  # n: 頂点数, m: 辺数
g = [
    [] for _ in range(n)
]  # g[i]: 頂点iに隣接する頂点のリスト (y, z)のタプルで格納。yは隣接頂点、zは辺の重み
for _ in range(m):
    x, y, z = map(int, input().split())  # x, y: 辺の両端の頂点, z: 辺の重み
    x, y = x - 1, y - 1  # 0-indexedに変換
    g[x].append((y, z))  # 頂点xに(頂点y, 重みz)を追加
    g[y].append((x, z))  # 頂点yに(頂点x, 重みz)を追加

visited = [False] * n  # visited[i]: 頂点iが訪問済みかどうか
val = [-1] * n  # val[i]: 頂点iのグループ内での値。初期値は-1


def bfs(start):
    """
    BFSで連結成分を探索し、各頂点の値を決定する。
    矛盾がある場合は"-1"を出力して終了する。
    """
    dq = deque([start])  # dequeに開始頂点を入れる
    visited[start] = True  # 開始頂点を訪問済みにする
    comp = [start]  # 連結成分の頂点リスト。開始頂点を入れる
    while dq:
        v = dq.popleft()  # dequeから頂点を取り出す
        for u, w in g[v]:  # 頂点vに隣接する頂点を探索
            if not visited[u]:  # 頂点uが未訪問の場合
                visited[u] = True  # 頂点uを訪問済みにする
                val[u] = val[v] ^ w  # 頂点uの値を、頂点vの値とのXORで決定
                comp.append(u)  # 連結成分に頂点uを追加
                dq.append(u)  # dequeに頂点uを追加
            else:  # 頂点uが訪問済みの場合
                if val[u] != val[v] ^ w:  # 頂点uの値が、頂点vの値とのXORと異なる場合
                    print("-1")  # 矛盾があるので"-1"を出力
                    exit()  # プログラムを終了
    return comp  # 連結成分の頂点リストを返す


ans = [0] * n  # ans[i]: 頂点iの最終的な値
for st in range(n):  # 全ての頂点に対して
    if visited[st]:  # 頂点stが訪問済みの場合
        continue  # 次の頂点へ

    val[st] = 0  # 頂点stの値を0に初期化
    comp = bfs(st)  # 頂点stからBFSを開始し、連結成分を取得
    for i in range(30):  # 各bitに対して
        cnt = 0  # 連結成分内でi番目のbitが立っている頂点の数をカウント
        for j in comp:  # 連結成分内の全ての頂点に対して
            if val[j] & (1 << i):  # 頂点jのi番目のbitが立っている場合
                cnt += 1  # カウントを増やす
        if (
            cnt < len(comp) - cnt
        ):  # i番目のbitが立っている頂点の数が、立っていない頂点の数より少ない場合
            for j in comp:  # 連結成分内の全ての頂点に対して
                if val[j] & (1 << i):  # 頂点jのi番目のbitが立っている場合
                    ans[j] |= 1 << i  # 頂点jのansのi番目のbitを立てる
        else:  # i番目のbitが立っている頂点の数が、立っていない頂点の数以上の場合
            for j in comp:  # 連結成分内の全ての頂点に対して
                if not (val[j] & (1 << i)):  # 頂点jのi番目のbitが立っていない場合
                    ans[j] |= 1 << i  # 頂点jのansのi番目のbitを立てる
print(*ans)  # 結果を出力
