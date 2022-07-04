#include <iostream>
#include <string>
#include <vector>
using namespace std;
vector<int> find_index;

//preprocessing, O(m + s)��ŭ�� ���⵵ �߻�, m�� pattern�� ����, s�� ��ü �迭�� -1�� �ʱ�ȭ�ϴµ� �ɸ��� �ð�
vector<int> last_occurance_func(string p){
    //pattern�� ���� preprocessing ������ ����
    vector<int> L(26, -1); //alphabet�� �� ������ ��ġ�� -1�� �ʱ�ȭ
    for(int i = 0; i < p.size(); i++){ //pattern ���� alphabet�� �� ������ ��ġ�� ����
        char ch = p[i]; //pattern ���� char�� �ϳ��� ������
        if(ch == 'X'){ //'X'�� ��� ���ڿ� ���ؼ� ��ġ�Ѵٰ� �Ǵ��ϹǷ� 'X'�� ��Ÿ���� ���� ��� alphabet�� ������ ��ġ�� pattren ���� 'X'�� ��ġ�� �Ǵ�
            for(int j = 0; j < 26; j++){ //��� alphabet�� ������ ��ġ�� 'X'�� ��ġ�� ������Ʈ
                L[j] = i; //pattren�� ���� �ݺ����� �����鼭 �׶��� index�� ����
            }
        }
        else{ //'X'�� �ƴ� Ư�� alphabet�� ��Ÿ���� ��쿡�� �ش� alphabet�� pattern ������ ���������� ��Ÿ���� ������ pattern�� ���ڸ� �ϳ��� Ȯ���ϸ鼭 ������Ʈ
            int x = (int)ch; //a ~ z���� 0 ~ 25�� ��ġ�� ����
            L[x - 97] = i; //alphabet�� pattern ������ ���� ���������� ��Ÿ������ pattern ���� index�� ���� ���� 
        }
    }
    return L; //pattern ���� �� char�� �߻��ϴ� ��ġ�� ������Ʈ�� �迭�� ��ȯ
}

//searching, O(nm)��ŭ�� ���⵵ �߻�, �׻� match�Ǵٰ� ���������� mismatch�Ǵ� ��찡 �߻��� �� �����Ƿ�, text�� �� index���� n���� ���ϴ� �־��� ��찡 �߻�
void BoyerMooreMatch(string t, string p){
    vector<int> L = last_occurance_func(p); //last_occurance_func�� ���� alphabet�� ���� pattern ������ ���������� �߻��ϴ� ��ġ�� �޾ƿ�
    int n = t.size(); //text�� ����
    int m = p.size(); //pattern�� ����
    int i = m - 1; //text ���� �����ϴ� index�� m - 1�� �ʱ�ȭ, pattern�� �� �ں��� ��
    int j = m - 1; //pattern ���� �����ϴ� index�� m - 1�� �ʱ�ȭ
    while(i <= n - 1) { //��ü text�� Ž���ϴ� ���� �ݺ�
        if(t[i] == p[j] || p[j] == 'X'){ //pattern ���� char�� text ���� char�� ��ġ�ϰų� pattern ������ 'X'�� ��Ÿ���� ���, match
            if(j == 0){  //pattern�� ��� �κа� text ���� �Ϻΰ� �����ϰ� ��ġ
                find_index.push_back(i); //����̰� �а� �ִ� å���� ����̰� �����ϴ� ������ �߰�
                i = i + m - j; //index i�� ��ġ�� i + m - j(j = 0)�� ������Ʈ, ��ġ�ϴ� ������ ã�����Ƿ� �ٷ� pattern�� ���� ��ŭ �� ���� �̵� 
                j = m - 1; //j�� �ٽ� pattern�� �� �ں��� Ž���ϱ� ���� m - 1�� �ʱ�ȭ
                cout << 1 << " "; //match ���Ŀ� ���������� 1ĭ shift
            }
            else{
                i = i - 1; //�� char�� ��ġ�ϸ� ���� text ���� char�� pattern ���� char�� ��
                j = j - 1; // i = i - 1, j = j - 1, �������� �� ĭ�� �̵�
            }
        }
        else{ 
            char c = t[i]; //mismatch �߻�, �ش� char�� text ������ �޾ƿ�
            int idx = (int)c - 97; //�ش� char�� �޾ƿ���, alphabet ���� index�� ��ȯ
            int l = L[idx]; //char�� pattern ������ ���������� �߻��ϴ� ��ġ�� ��ȯ
            i = i + m - min(j, 1 + l); //j <= 1 + l, char�� pattern ������ ��������� �����ʿ��� �߻��ϴ� ���̽��� ��� m - j��ŭ i�� ����, 1 + l <= j�� ���, m - (1 + l)��ŭ ����
            if(j <= 1 + l){ cout << 1 << " "; } //char�� ��������� �����ʿ��� �߻��ϴ� ���, 1ĭ �̵�
            else{ cout << j-l << " "; } //char�� ��������� ���ʿ��� �߻��ϴ� ���, (pattern�� ���� ��ġ - pattern ���� char�� ���������� �߻��ϴ� ��ġ) j - l��ŭ �̵�
            j = m - 1; //text ������ �ٽ� ��ġ�ϴ� pattern Ž���� �����ϵ��� j�� �ٽ� pattern�� �� ���������� �̵�
        }
    }
}

//preprocessing, searching ������ �����Ͽ� ��ü������ O(nm + s)��ŭ�� ���⵵ �߻�
int main(){
    string t; //����̰� �а� �ִ� å�� ����
    string p; //����̰� �����ϴ� ����
    cin >> t;
    cin >> p;
    //1)BM �˰��� �� pattern�� ���������� �̵��� ���, �̵��� �Ÿ��� �������� �����Ͽ� �� �ٿ� ���
    BoyerMooreMatch(t, p); //BoyreMooreMatch()�� ���� 
    cout << "\n";
    //2)BM �˰��� ���� ��, ����̰� �а� �ִ� å���� ����̰� �����ϴ� ������ �����ϴ� ���� ��ġ���� �������� �����Ͽ� �� �ٿ� ���
    for(int i = 0; i < find_index.size(); i++){
        cout << find_index[i] << " ";
    }
    return 0;
}