#include <iostream>
#include <string>
#include <vector>
using namespace std;
vector<int> find_index;

//preprocessing, O(m + s)만큼의 복잡도 발생, m은 pattern의 길이, s는 전체 배열을 -1로 초기화하는데 걸리는 시간
vector<int> last_occurance_func(string p){
    //pattern에 대한 preprocessing 과정을 진행
    vector<int> L(26, -1); //alphabet의 각 마지막 위치를 -1로 초기화
    for(int i = 0; i < p.size(); i++){ //pattern 내의 alphabet의 각 마지막 위치를 저장
        char ch = p[i]; //pattern 내의 char을 하나씩 가져옴
        if(ch == 'X'){ //'X'는 모든 문자에 대해서 일치한다고 판단하므로 'X'가 나타났을 때는 모든 alphabet의 마지막 위치를 pattren 내의 'X'의 위치로 판단
            for(int j = 0; j < 26; j++){ //모든 alphabet의 마지막 위치를 'X'의 위치로 업데이트
                L[j] = i; //pattren에 대한 반복문을 돌리면서 그때의 index를 삽입
            }
        }
        else{ //'X'가 아닌 특정 alphabet이 나타났을 경우에는 해당 alphabet이 pattern 내에서 마지막으로 나타나는 정보를 pattern의 문자를 하나씩 확인하면서 업데이트
            int x = (int)ch; //a ~ z까지 0 ~ 25의 위치로 지정
            L[x - 97] = i; //alphabet이 pattern 내에서 언제 마지막으로 나타났는지 pattern 내의 index를 통해 저장 
        }
    }
    return L; //pattern 내의 각 char가 발생하는 위치를 업데이트한 배열을 반환
}

//searching, O(nm)만큼의 복잡도 발생, 항상 match되다가 마지막에서 mismatch되는 경우가 발생할 수 있으므로, text의 각 index마다 n번씩 비교하는 최악의 경우가 발생
void BoyerMooreMatch(string t, string p){
    vector<int> L = last_occurance_func(p); //last_occurance_func을 통해 alphabet이 각각 pattern 내에서 마지막으로 발생하는 위치를 받아옴
    int n = t.size(); //text의 길이
    int m = p.size(); //pattern의 길이
    int i = m - 1; //text 내의 접근하는 index를 m - 1로 초기화, pattern의 맨 뒤부터 비교
    int j = m - 1; //pattern 내의 접근하는 index를 m - 1로 초기화
    while(i <= n - 1) { //전체 text를 탐색하는 동안 반복
        if(t[i] == p[j] || p[j] == 'X'){ //pattern 내의 char와 text 내의 char가 일치하거나 pattern 내에서 'X'가 나타났을 경우, match
            if(j == 0){  //pattern의 모든 부분과 text 내의 일부가 완전하게 일치
                find_index.push_back(i); //비룡이가 읽고 있는 책에서 비룡이가 좋아하는 구문을 발견
                i = i + m - j; //index i의 위치를 i + m - j(j = 0)로 업데이트, 일치하는 구문을 찾았으므로 바로 pattern의 길이 만큼 한 번에 이동 
                j = m - 1; //j는 다시 pattern의 맨 뒤부터 탐색하기 위해 m - 1로 초기화
                cout << 1 << " "; //match 이후에 오른쪽으로 1칸 shift
            }
            else{
                i = i - 1; //각 char가 일치하면 다음 text 내의 char과 pattern 내의 char를 비교
                j = j - 1; // i = i - 1, j = j - 1, 왼쪽으로 한 칸씩 이동
            }
        }
        else{ 
            char c = t[i]; //mismatch 발생, 해당 char를 text 내에서 받아옴
            int idx = (int)c - 97; //해당 char를 받아오고, alphabet 내의 index를 반환
            int l = L[idx]; //char가 pattern 내에서 마지막으로 발생하는 위치를 반환
            i = i + m - min(j, 1 + l); //j <= 1 + l, char가 pattern 내에서 상대적으로 오른쪽에서 발생하는 케이스의 경우 m - j만큼 i를 증가, 1 + l <= j일 경우, m - (1 + l)만큼 증가
            if(j <= 1 + l){ cout << 1 << " "; } //char가 상대적으로 오른쪽에서 발생하는 경우, 1칸 이동
            else{ cout << j-l << " "; } //char가 상대적으로 왼쪽에서 발생하는 경우, (pattern의 현재 위치 - pattern 내의 char가 마지막으로 발생하는 위치) j - l만큼 이동
            j = m - 1; //text 내에서 다시 일치하는 pattern 탐색을 진행하도록 j를 다시 pattern의 맨 오른쪽으로 이동
        }
    }
}

//preprocessing, searching 과정을 통합하여 전체적으로 O(nm + s)만큼의 복잡도 발생
int main(){
    string t; //비룡이가 읽고 있는 책의 내용
    string p; //비룡이가 좋아하는 구문
    cin >> t;
    cin >> p;
    //1)BM 알고리즘 중 pattern이 오른쪽으로 이동할 경우, 이동한 거리를 공백으로 구분하여 한 줄에 출력
    BoyerMooreMatch(t, p); //BoyreMooreMatch()을 통해 
    cout << "\n";
    //2)BM 알고리즘 종료 후, 비룡이가 읽고 있는 책에서 비룡이가 좋아하는 구문이 존재하는 시작 위치들을 공백으로 구분하여 한 줄에 출력
    for(int i = 0; i < find_index.size(); i++){
        cout << find_index[i] << " ";
    }
    return 0;
}