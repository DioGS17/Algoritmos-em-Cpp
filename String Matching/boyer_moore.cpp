#include <iostream>
#include <vector>
#include <list>

using namespace std;

vector<int> computa_tabela_saltos(string padrao){
    vector<int> r(256);

    for(int i = 0; i < r.size(); i++){
        r[i] = -1;
    }

    for(int i = 0; i < padrao.size(); i++){
        r[padrao[i]] = i;
    }

    return r;
}

void boyerMoore(string padrao, string texto){
    vector<int> r = computa_tabela_saltos(padrao);
    
    int n = texto.size();
    int m = padrao.size();
    int salto = 0;

    for(int i = 0; i <= n - m; i += salto){
        salto = 0;
        for(int j = m - 1; j >= 0; j--){
            if(padrao[j] != texto[i + j]){
                salto = j - r[texto[i + j]]; 
                if(salto < 1){
                    salto = 1;
                }
                break;
            }
        }
        cout << salto << " ";
        if(salto == 0){
            cout << "(" << i << ") ";
            salto = 1;
        }
    }
}

int main(){
    string texto = "MENSAGEM WAB ESTRELA QESSS TOURO LZAUSF ULASVQQJX II AMEACA IADFCO IANTECO VAA ESTRELA.";
    list<string> padrao;

    string str;
    while(str != "fim"){
        cin >> str;
        if (str != "fim"){
            for(int i = 0; i < str.length(); i++){
                str[i] -= 32;
            }
            padrao.push_back(str);
        }
    }

    for(auto i : padrao){
        cout << i << ": ";
        boyerMoore(i, texto);
        cout << endl;
    }

    return 0;
}