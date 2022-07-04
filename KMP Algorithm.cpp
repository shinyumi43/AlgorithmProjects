#include <iostream>
#include <string>
#include <vector>
using namespace std;
vector<int> find_index; 

//preprocessing, O(m)만큼의 복잡도 발생, pattern 내의 char을 전부 스캔하기 때문에 pattern의 길이만큼 발생
vector<int> failure_function(string p){
    int m = p.size(); //pattern의 크기
    vector<int> f(m); ////pattern 크기의 failure table 생성
    f[0] = 0; //f[0] = 0으로 초기화
    int i = 1; //text에 대한 index
    int j = 0; //pattern에 대한 index
    while(i < m){ //m-1까지 접근하는 동안 반복
        if(p[i] == p[j]){ //pattern이 char by char로 같으면,
            f[i] = j + 1; //j+1개의 char 만큼의 pattern이 match
            i++; //i를 오른쪽으로 한 칸 이동
            j++; //j를 오른쪽으로 한 칸 이동
        }
        else if(j > 0){ //j > 0, p[i] != p[j]으로 mismatch가 발생하면,
            j = f[j - 1]; //기존에 match된 정보를 활용하여 j를 f[j - 1]로 교체
        }
        else{ //바로 mismatch가 된다면,
            f[i] = 0; //그때의 prefix에서 suffix와 일치하는 가장 긴 길이가 존재하지 않음
            i++; //i를 오른쪽으로 한 칸 이동
        }
    }
    return f;
}

//searching, 2n번의 iteration을 절대 넘지 않기 때문에 searching은 O(n)만큼의 복잡도가 발생
void kmp_match(string t, string p){
    vector<int> f = failure_function(p); //가장 먼저 pattern에 대해 failure function을 계산
    int i = 0; //text에 대한 index, text는 읽고 있는 책의 내용
    int j = 0; //pattern에 대한 index, pattern은 좋아하는 구문의 내용
    int n = t.size(); //text t의 크기
    int m = p.size(); //pattern p의 크기
    while(i < n){ //i에 의해 iteration을 수행(0 ~ n-1), text 내의 pattern을 모두 찾아야 하므로 text 전체를 탐색
        if(t[i] == p[j]){ //읽고 있는 책의 내용과 좋아하는 구문의 내용이 char by char로 같으면,
            if(j == m - 1){ //char by char 비교 중에 현재 pattern의 index가 pattern의 끝 인덱스인 m-1에 도달하면, match
                //text 전체 길이 끝에서 pattern이 정확하게 match 되었다면,
                if(i == n - 1) { cout << j - f[j] + 1 << " "; }  //이동거리 = 현재의 j 인덱스 - 그때의 prefix에서 suffix와 일치하는 가장 긴 길이 + 1
                find_index.push_back(i - j); //text에서 pattern이 존재하는 시작 위치를 삽입
            }
            i++; //text, 읽고 있는 책 내용의 다음 char로 이동
            j++; //pattern, 좋아하는 구문 내용의 다음 char로 이동
        }
        else if(j > 0){ //j > 0, t[i] != p[j], mismatch가 발생하면,
            //이동한 거리 = 현재 j index - 업데이트된 index
            cout << j - f[j - 1] << " ";
            j = f[j - 1]; //기존에 match된 정보를 활용하여 j를 f[j - 1]로 교체
        }
        else{ //바로 mismatch가 된다면,
            //이동한 거리 = 1
            cout << 1 << " ";
            i++; //i를 오른쪽으로 한 칸 이동
        }
    }

}

//preprocessing과 searching에 의해 전체적으로 O(m + n)만큼의 복잡도가 발생
int main(){
    string t; //비룡이가 읽고 있는 책의 내용
    string p; //비룡이가 좋아하는 구문
    cin >> t;
    cin >> p;
    //1) kmp 알고리즘 진행 중 패턴이 오른쪽으로 이동할 때마다 이동 거리를 공백으로 구분하여 출력
    kmp_match(t, p);
    cout << "\n";
    //2) kmp 알고리즘 종료 후, 비룡이가 읽고 있는 책에서 비룡이가 좋아하는 구문이 존재하는 시작 위치들을 공백으로 구분하여 출력
    for(int i = 0; i < find_index.size(); i++){
        cout << find_index[i] << " ";
    }
    return 0;
}