#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
using namespace std;
//방향 그래프와 역방향 그래프를 활용

const int MAX = 500001; //가능한 총 사용자의 수
bool visit[MAX]; //방향 그래프에 대한 방문 여부를 표시
bool discover[MAX]; //역방향 그래프에 대한 방문 여부를 표시
bool finished[MAX]; //처리 완료 여부를 표시
vector<int> G[MAX]; //방향 그래프, 인접리스트 형태
vector<int> GT[MAX]; //역방향 그래프, 인접리스트 형태
stack<int> finishing; //SCC를 위해서 활용할 스택 객체
vector<int> S; //중간 정보를 담을 벡터 생성
int SCC[MAX]; //각 leader의 정보를 표시할 1차원 배열 생성
int N; //실제 사용자의 수

//다음 정점을 찾는 함수
bool compare(int a, int b) {
    if (GT[a].size() == GT[b].size()) { return a < b; }
    return GT[a].size() > GT[b].size();
}

//방향 그래프 DFS
void DFS(int cur) {
	visit[cur] = true; //방문 표시
    int size = G[cur].size(); //방문할 노드의 개수
    if(size >= 2) { //방문할 노드가 2개 이상인 경우
        //방문할 노드 목록, 기존 G[cur]에 연결된 인접 리스트에 해당 목록으로 교체
        vector<int> follower;
        //팔로워의 수가 더 많은 사용자순으로 내림차순, 팔로워의 수가 동일하다면 사용자 번호 순서로 정렬해서 인접 리스트로 삽입
        for(int i = 0; i < size; i++) { follower.push_back(G[cur][i]); }
        sort(follower.begin(), follower.end(), compare);
        G[cur] = follower;
    }
    for (int i = 0; i < G[cur].size(); i++) { //팔로우한 노드를 순차적으로 확인
		int next = G[cur][i]; //다음으로 방문할 노드
		if (visit[next]) continue; //이미 방문했다면, 생략
		DFS(next); //방문하지 않았다면, dfs 탐색
    }
    finishing.push(cur); //탐색이 끝난 순서로 스택에 삽입
    S.push_back(cur); //삽입되는 순서대로 저장
}

//역방향 그래프 DFS
void DFS_T(int cur, int leader) {
    discover[cur] = true; //방문 표시
    SCC[cur] = leader; //방문할 때마다 leader를 지정
    int size = G[cur].size(); //방문할 노드의 개수
    if(size >= 2) { //방문할 노드가 2개 이상인 경우
        //방문할 노드 목록, 기존 G[cur]에 연결된 인접 리스트에 해당 목록으로 교체
        vector<int> follower;
        //팔로워의 수가 더 많은 사용자순으로 내림차순, 팔로워의 수가 동일하다면 사용자 번호 순서로 정렬해서 인접 리스트로 삽입
        for(int i = 0; i < size; i++) { follower.push_back(G[cur][i]); }
        sort(follower.begin(), follower.end(), compare);
        G[cur] = follower;
    }
	for (int i = 0; i < GT[cur].size(); i++) { //팔로우한 노드를 순차적으로 확인
		int next = GT[cur][i]; //다음으로 방문할 노드
		if (discover[next]) continue; //이미 방문했다면, 생략
		DFS_T(next, leader); //방문하지 않았다면, dfs 탐색
	}
    finished[cur] = true; //더이상 갈 곳이 없는 경우에 finished
}

int main(){
    //N은 사용자의 수, M은 팔로우 수
    int M, A, B, leader;
    cin >> N >> M;
    for(int i = 0; i < M; i++) {
        cin >> A >> B;
        //사용자 A가 사용자 B를 follow, 방향 그래프 
        G[A].push_back(B);
        //사용자 B의 follower 정보, 역방향 그래프 생성
        GT[B].push_back(A);
    }
    //알고리즘 단계 1
    //방문할 노드 목록, 기존 G[cur]에 연결된 인접 리스트에 해당 목록으로 교체
    vector<int> follower;
    //팔로워의 수가 더 많은 사용자순으로 내림차순, 팔로워의 수가 동일하다면 사용자 번호 순서로 정렬해서 인접 리스트로 삽입
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
    //알고리즘 단계 2
    while(!finishing.empty()) { //스택이 완전히 빌 때까지 수행
        int cur = finishing.top(); //스택에서 추출
        finishing.pop(); //순차적으로 pop
        if(finished[cur]) { continue; } //이미 처리가 완료되었다면, 생략
        leader = cur; //처리되지 않았다면, scc의 leader로 지정
        DFS_T(cur, leader); //pop되는 순서대로 탐색을 진행
    }
    //scc를 찾는 알고리즘 종료 후, 사용자 1 ~ N까지 각각 scc의 리더를 출력
    for(int i = 1; i <= N; i++){
        cout << SCC[i] << " ";
    }
    return 0;
}