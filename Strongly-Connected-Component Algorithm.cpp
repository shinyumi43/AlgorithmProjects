#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
using namespace std;
//���� �׷����� ������ �׷����� Ȱ��

const int MAX = 500001; //������ �� ������� ��
bool visit[MAX]; //���� �׷����� ���� �湮 ���θ� ǥ��
bool discover[MAX]; //������ �׷����� ���� �湮 ���θ� ǥ��
bool finished[MAX]; //ó�� �Ϸ� ���θ� ǥ��
vector<int> G[MAX]; //���� �׷���, ��������Ʈ ����
vector<int> GT[MAX]; //������ �׷���, ��������Ʈ ����
stack<int> finishing; //SCC�� ���ؼ� Ȱ���� ���� ��ü
vector<int> S; //�߰� ������ ���� ���� ����
int SCC[MAX]; //�� leader�� ������ ǥ���� 1���� �迭 ����
int N; //���� ������� ��

//���� ������ ã�� �Լ�
bool compare(int a, int b) {
    if (GT[a].size() == GT[b].size()) { return a < b; }
    return GT[a].size() > GT[b].size();
}

//���� �׷��� DFS
void DFS(int cur) {
	visit[cur] = true; //�湮 ǥ��
    int size = G[cur].size(); //�湮�� ����� ����
    if(size >= 2) { //�湮�� ��尡 2�� �̻��� ���
        //�湮�� ��� ���, ���� G[cur]�� ����� ���� ����Ʈ�� �ش� ������� ��ü
        vector<int> follower;
        //�ȷο��� ���� �� ���� ����ڼ����� ��������, �ȷο��� ���� �����ϴٸ� ����� ��ȣ ������ �����ؼ� ���� ����Ʈ�� ����
        for(int i = 0; i < size; i++) { follower.push_back(G[cur][i]); }
        sort(follower.begin(), follower.end(), compare);
        G[cur] = follower;
    }
    for (int i = 0; i < G[cur].size(); i++) { //�ȷο��� ��带 ���������� Ȯ��
		int next = G[cur][i]; //�������� �湮�� ���
		if (visit[next]) continue; //�̹� �湮�ߴٸ�, ����
		DFS(next); //�湮���� �ʾҴٸ�, dfs Ž��
    }
    finishing.push(cur); //Ž���� ���� ������ ���ÿ� ����
    S.push_back(cur); //���ԵǴ� ������� ����
}

//������ �׷��� DFS
void DFS_T(int cur, int leader) {
    discover[cur] = true; //�湮 ǥ��
    SCC[cur] = leader; //�湮�� ������ leader�� ����
    int size = G[cur].size(); //�湮�� ����� ����
    if(size >= 2) { //�湮�� ��尡 2�� �̻��� ���
        //�湮�� ��� ���, ���� G[cur]�� ����� ���� ����Ʈ�� �ش� ������� ��ü
        vector<int> follower;
        //�ȷο��� ���� �� ���� ����ڼ����� ��������, �ȷο��� ���� �����ϴٸ� ����� ��ȣ ������ �����ؼ� ���� ����Ʈ�� ����
        for(int i = 0; i < size; i++) { follower.push_back(G[cur][i]); }
        sort(follower.begin(), follower.end(), compare);
        G[cur] = follower;
    }
	for (int i = 0; i < GT[cur].size(); i++) { //�ȷο��� ��带 ���������� Ȯ��
		int next = GT[cur][i]; //�������� �湮�� ���
		if (discover[next]) continue; //�̹� �湮�ߴٸ�, ����
		DFS_T(next, leader); //�湮���� �ʾҴٸ�, dfs Ž��
	}
    finished[cur] = true; //���̻� �� ���� ���� ��쿡 finished
}

int main(){
    //N�� ������� ��, M�� �ȷο� ��
    int M, A, B, leader;
    cin >> N >> M;
    for(int i = 0; i < M; i++) {
        cin >> A >> B;
        //����� A�� ����� B�� follow, ���� �׷��� 
        G[A].push_back(B);
        //����� B�� follower ����, ������ �׷��� ����
        GT[B].push_back(A);
    }
    //�˰��� �ܰ� 1
    //�湮�� ��� ���, ���� G[cur]�� ����� ���� ����Ʈ�� �ش� ������� ��ü
    vector<int> follower;
    //�ȷο��� ���� �� ���� ����ڼ����� ��������, �ȷο��� ���� �����ϴٸ� ����� ��ȣ ������ �����ؼ� ���� ����Ʈ�� ����
    for(int i = 1; i <= N; i++) { follower.push_back(i); }
    sort(follower.begin(), follower.end(), compare);
    for(int i = 0; i < follower.size(); i++) {
        int idx = follower[i];
        if(!visit[idx]) { DFS(follower[i]); }
    }
    for(int i = 0; i < S.size(); i++){
        cout << S[i] << " ";
    }
    cout << "\n";
    //�˰��� �ܰ� 2
    while(!finishing.empty()) { //������ ������ �� ������ ����
        int cur = finishing.top(); //���ÿ��� ����
        finishing.pop(); //���������� pop
        if(finished[cur]) { continue; } //�̹� ó���� �Ϸ�Ǿ��ٸ�, ����
        leader = cur; //ó������ �ʾҴٸ�, scc�� leader�� ����
        DFS_T(cur, leader); //pop�Ǵ� ������� Ž���� ����
    }
    //scc�� ã�� �˰��� ���� ��, ����� 1 ~ N���� ���� scc�� ������ ���
    for(int i = 1; i <= N; i++){
        cout << SCC[i] << " ";
    }
    return 0;
}