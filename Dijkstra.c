/******************* インクルード *******************/
#include<stdio.h>
#include<stdlib.h>      // for exit
#include<stdbool.h>     // for boolean

/*********************** 定数 ***********************/
#define INFINITE 1000000    // 無限
#define MAX_NODE 1000       // 最大地点数

/*********************** 変数 ***********************/
int dist[MAX_NODE][MAX_NODE];   // 距離テーブル
int cost[MAX_NODE];             // 最小コスト
int via[MAX_NODE];              // 
bool flag[MAX_NODE];            // 確定フラグ
int node_num;                   // ノード数
int path_num;                   // パス数

/******************* ダイクストラ *******************/
int dijkstra(int start, int goal) {
    int min, target;     // 作業用変数

    cost[start] = 0;    // スタートの距離は0

    while(true) {
        /*--- 未確定の中から距離が最も小さい地点を探索 ---*/
        min = INFINITE;     // 初期化
        for (int i = 0; i < node_num; i++) {
            if (!flag[i] && min > cost[i]) {
                min = cost[i];
                target = i;
            }
        }

        /*--- すべての地点が確定 ---*/
        if (target == goal) {
            return cost[goal];;
        }

        /*--- 確定した場所から「つながっている」or「未確定」の地点に関して ---*/
        /*--- 確定した場所を経由した場合の距離を再計算                   ---*/
        for (int neigh = 0; neigh < node_num; neigh++) {
            if (cost[neigh] > dist[target][neigh] + cost[target]) {
                cost[neigh] = dist[target][neigh] + cost[target];       //更新
                via[neigh] = target;
            }
        }

        flag[target] = true;
    }
}

void init() {
    for (int i = 0; i < MAX_NODE; i++) {
        cost[i] = INFINITE;
        flag[i] = false;
        via[i] = -1;

        for(int j = 0; j < MAX_NODE; j++) {
            dist[i][j] = INFINITE;
        }
    }
}

void read_file() {
    /*** 変数 ***/
    FILE *fp;                   // ファイルポインタ
    char *file_name;            // ファイル名
    int begin, end, cost;       // 作業用変数

    file_name = "example_NodePath.txt"; // ファイル名指定

    /*** ファイルオープン ***/
    fp = fopen(file_name, "r");         // ファイルオープン
    if (fp == NULL) {                   // エラー処理 
        printf("%s file not open.\n", file_name);
        exit(0);
    }

    /*** パス数，ノード数読み込み ***/
    fscanf(fp, "%d %d", &path_num, &node_num);

    /*** 距離テーブル読み込み ***/
    while (fscanf(fp, "%d%d%d", &begin, &end, &cost) != EOF) {
        dist[begin][end] = cost;
        dist[end][begin] = cost;
    }

    fclose(fp); // ファイルクローズ
}

int main() {
    int start, goal, node;        // 作業用変数

    init();
    read_file();

    printf("Input start and goal\n");
    scanf("%d", &start);
    scanf("%d", &goal);

    dijkstra(start, goal);

    node = goal;
    printf("%d", node);
    while (node != start) {
        node = via[node];
        printf(" -> %d", node);
    }

    return 0;
}