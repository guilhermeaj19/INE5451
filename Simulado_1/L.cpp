#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100005;
double probs[MAXN];

struct Node {
    double left_to_right;
    double right_to_right;
};

Node tree[4 * MAXN];

Node mergeNodes(Node left_block, Node right_block) {
    if (left_block.left_to_right < 0) return right_block;
    if (right_block.left_to_right < 0) return left_block;

    Node res;
    
    double denom = 1.0 - (1.0 - right_block.left_to_right) * left_block.right_to_right;
    
    res.left_to_right = (left_block.left_to_right * right_block.left_to_right) / denom;
    res.right_to_right = right_block.right_to_right + (1.0 - right_block.right_to_right) * left_block.right_to_right * right_block.left_to_right / denom;
    
    return res;
}

void build(int node, int start, int end) {
    if (start == end) {
        tree[node].left_to_right = probs[start];
        tree[node].right_to_right = probs[start];
        return;
    }
    int mid = start + (end - start) / 2;
    build(2 * node, start, mid);
    build(2 * node + 1, mid + 1, end);
    
    tree[node] = mergeNodes(tree[2 * node], tree[2 * node + 1]);
}

void update(int node, int start, int end, int idx, double val) {
    if (start == end) {
        probs[idx] = val;
        tree[node].left_to_right = val;
        tree[node].right_to_right = val;
        return;
    }
    int mid = start + (end - start) / 2;
    if (start <= idx && idx <= mid) {
        update(2 * node, start, mid, idx, val);
    } else {
        update(2 * node + 1, mid + 1, end, idx, val);
    }
    
    tree[node] = mergeNodes(tree[2 * node], tree[2 * node + 1]);
}

Node query(int node, int start, int end, int l, int r) {
    if (r < start || end < l) {
        return {-1.0, -1.0}; 
    }

    if (l <= start && end <= r) {
        return tree[node];
    }
    
    int mid = start + (end - start) / 2;
    Node leftNode = query(2 * node, start, mid, l, r);
    Node rightNode = query(2 * node + 1, mid + 1, end, l, r);
    
    return mergeNodes(leftNode, rightNode);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n, q;
    if (!(cin >> n >> q)) return 0;

    int a, b;
    for (int i = 0; i < n; i++) {
        cin >> a >> b;
        probs[i] = (double) a / b;
    }

    build(1, 0, n - 1);

    int type, i, l, r;
    for (int j = 0; j < q; j++) {
        cin >> type;
        if (type == 1) {
            cin >> i >> a >> b;
            update(1, 0, n - 1, i - 1, (double) a / b);
        } else if (type == 2) {
            cin >> l >> r;
            Node result = query(1, 0, n - 1, l - 1, r - 1);
            
            printf("%.10f\n", result.left_to_right);
        }
    }

    return 0;
}