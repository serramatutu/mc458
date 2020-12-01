#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <fstream>

using namespace std;

bool resposta_correta(const vector<double>& v, int k, const vector<double>& r);
void quick_sort(vector<double>& v);
double tempo();
void kmin_to_file(vector<double>& r);

vector<double> metodo_1(const vector<double>& v, int k) {
    vector<double> r;
    r.reserve(k);

    for (int i=0; i < k; i++) {
        int min = v[0];
        for (int i=0; i<v.size(); i++) {
            if (v[i] < min) {
                min = v[i];
            }
        }
        r.push_back(min);
    }

    return r;
}

vector<double> metodo_2(const vector<double>& v_original, int k) {
    vector<double> v(v_original);
    quick_sort(v);

    vector<double> r(v.begin(), v.begin() + k);
    return r;
}

void heapify_elem(vector<double>& v, int i) {
    int esq = 2*i,
        dir = 2*i + 1,
        menor = i;

    if (esq < v.size() && v[esq] < v[menor]) {
        menor = esq;
    }
    if (dir < v.size() && v[dir] < v[menor]) {
        menor = dir;
    }

    if (menor != i) {
        double aux = v[i];
        v[i] = v[menor];
        v[menor] = aux;
        heapify_elem(v, menor);
    }
}

void heapify(vector<double>& v) {
    for (int i=v.size()/2; i > -1; i--) {
        heapify_elem(v, i);
    }
}

vector<double> metodo_3(const vector<double>& v_original, int k) {
    vector<double> v(v_original);
    heapify(v);

    vector<double> r(v.begin(), v.begin() + k);
    return r;
}

vector<double> le_arq(char* nomearq) {
    ifstream arq(nomearq);

    int n;
    arq >> n;

    vector<double> v;
    v.reserve(n);

    for (int i = 0; i < n; i++) {
        arq >> v[i];
    }

    arq.close();

    return v;
}



int main(int argc, char **argv){
    tempo();

    if(argc != 4){
        if(argc == 3 && argv[2][0] != '0'){
            cerr << "Uso Método 0: ./kmin <arq> 0\n";
        }
        else if(argc != 3){
            cerr << "Uso geral: ./kmin <arq> <metodo> <k>\n";
        }
        return 1;
    }

    char *nomearq = argv[1];
    char metodo = argv[2][0];
    int k;

    if(argc == 4) {
        k = atoi(argv[3]);
    }

    vector<double> v(le_arq(nomearq));
    vector<double> k_menores(metodo_1(v, k));

    cout << resposta_correta(v, k, k_menores) ? "OK" : "NOK";

    // double tempo_exec = tempo();
    // printf("%.6f\n", tempo_exec);

    return 0;
}
