#include <iostream>
#include <string>
#include <vector>
using namespace std;
vector<int> find_index; 

//preprocessing, O(m)��ŭ�� ���⵵ �߻�, pattern ���� char�� ���� ��ĵ�ϱ� ������ pattern�� ���̸�ŭ �߻�
vector<int> failure_function(string p){
    int m = p.size(); //pattern�� ũ��
    vector<int> f(m); ////pattern ũ���� failure table ����
    f[0] = 0; //f[0] = 0���� �ʱ�ȭ
    int i = 1; //text�� ���� index
    int j = 0; //pattern�� ���� index
    while(i < m){ //m-1���� �����ϴ� ���� �ݺ�
        if(p[i] == p[j]){ //pattern�� char by char�� ������,
            f[i] = j + 1; //j+1���� char ��ŭ�� pattern�� match
            i++; //i�� ���������� �� ĭ �̵�
            j++; //j�� ���������� �� ĭ �̵�
        }
        else if(j > 0){ //j > 0, p[i] != p[j]���� mismatch�� �߻��ϸ�,
            j = f[j - 1]; //������ match�� ������ Ȱ���Ͽ� j�� f[j - 1]�� ��ü
        }
        else{ //�ٷ� mismatch�� �ȴٸ�,
            f[i] = 0; //�׶��� prefix���� suffix�� ��ġ�ϴ� ���� �� ���̰� �������� ����
            i++; //i�� ���������� �� ĭ �̵�
        }
    }
    return f;
}

//searching, 2n���� iteration�� ���� ���� �ʱ� ������ searching�� O(n)��ŭ�� ���⵵�� �߻�
void kmp_match(string t, string p){
    vector<int> f = failure_function(p); //���� ���� pattern�� ���� failure function�� ���
    int i = 0; //text�� ���� index, text�� �а� �ִ� å�� ����
    int j = 0; //pattern�� ���� index, pattern�� �����ϴ� ������ ����
    int n = t.size(); //text t�� ũ��
    int m = p.size(); //pattern p�� ũ��
    while(i < n){ //i�� ���� iteration�� ����(0 ~ n-1), text ���� pattern�� ��� ã�ƾ� �ϹǷ� text ��ü�� Ž��
        if(t[i] == p[j]){ //�а� �ִ� å�� ����� �����ϴ� ������ ������ char by char�� ������,
            if(j == m - 1){ //char by char �� �߿� ���� pattern�� index�� pattern�� �� �ε����� m-1�� �����ϸ�, match
                //text ��ü ���� ������ pattern�� ��Ȯ�ϰ� match �Ǿ��ٸ�,
                if(i == n - 1) { cout << j - f[j] + 1 << " "; }  //�̵��Ÿ� = ������ j �ε��� - �׶��� prefix���� suffix�� ��ġ�ϴ� ���� �� ���� + 1
                find_index.push_back(i - j); //text���� pattern�� �����ϴ� ���� ��ġ�� ����
            }
            i++; //text, �а� �ִ� å ������ ���� char�� �̵�
            j++; //pattern, �����ϴ� ���� ������ ���� char�� �̵�
        }
        else if(j > 0){ //j > 0, t[i] != p[j], mismatch�� �߻��ϸ�,
            //�̵��� �Ÿ� = ���� j index - ������Ʈ�� index
            cout << j - f[j - 1] << " ";
            j = f[j - 1]; //������ match�� ������ Ȱ���Ͽ� j�� f[j - 1]�� ��ü
        }
        else{ //�ٷ� mismatch�� �ȴٸ�,
            //�̵��� �Ÿ� = 1
            cout << 1 << " ";
            i++; //i�� ���������� �� ĭ �̵�
        }
    }

}

//preprocessing�� searching�� ���� ��ü������ O(m + n)��ŭ�� ���⵵�� �߻�
int main(){
    string t; //����̰� �а� �ִ� å�� ����
    string p; //����̰� �����ϴ� ����
    cin >> t;
    cin >> p;
    //1) kmp �˰��� ���� �� ������ ���������� �̵��� ������ �̵� �Ÿ��� �������� �����Ͽ� ���
    kmp_match(t, p);
    cout << "\n";
    //2) kmp �˰��� ���� ��, ����̰� �а� �ִ� å���� ����̰� �����ϴ� ������ �����ϴ� ���� ��ġ���� �������� �����Ͽ� ���
    for(int i = 0; i < find_index.size(); i++){
        cout << find_index[i] << " ";
    }
    return 0;
}