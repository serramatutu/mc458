#include <algorithm>
#include <iostream>
#include <limits>
#include <vector>
#include <fstream>
#include <cmath>

using namespace std;

bool resposta_correta(const vector<double>& v, int k, const vector<double>& r);
void quick_sort(vector<double>& v);
double tempo();
void kmin_to_file(vector<double>& r);

vector<double> metodo_1(vector<double> v, size_t k) {
    vector<double> r;
    r.reserve(k);
    int max_r = numeric_limits<int>::min();

    for (size_t i=0; i < k; i++) {
        int min = numeric_limits<int>::max();
        for (size_t i=0; i < v.size(); i++) {
            if (v[i] < min && (v[i] > max_r || v.size() == 0)) {
                min = v[i];
            }
        }
        max_r = min;
        r.push_back(min);
    }

    return r;
}

vector<double> metodo_2(vector<double> v, size_t k) {
    quick_sort(v);

    vector<double> r(v.begin(), v.begin() + k);
    return r;
}

#define HEAP_ESQ(i) (2*i + 1)
#define HEAP_DIR(i) (2*i + 2)

void heapify_elem(vector<double>& v, size_t i) {
    size_t esq = HEAP_ESQ(i),
        dir = HEAP_DIR(i),
        menor = i;

    if (esq < v.size() && v[esq] < v[menor]) {
        menor = esq;
    }
    if (dir < v.size() && v[dir] < v[menor]) {
        menor = dir;
    }

    if (menor != i) {
        iter_swap(v.begin() + i, v.begin() + menor);
        heapify_elem(v, menor);
    }
}

void heapify(vector<double>& v) {
    for (int i=v.size()/2 - 1; i > -1; i--) {
        heapify_elem(v, i);
    }
}

void heap_descend(vector<double>& h) {
    size_t i = 0,
        esq = HEAP_ESQ(i),
        dir = HEAP_DIR(i);
    while (esq < h.size()) {
        size_t menor = dir < h.size() && h[dir] < h[esq] ? dir : esq;

        if (h[i] < h[menor]) {
            break;
        }

        iter_swap(h.begin() + i, h.begin() + menor);

        i = menor;
        esq = HEAP_ESQ(i);
        dir = HEAP_DIR(i);
    }
}

double heap_pop(vector<double>& h) {
    double ret = h[0];
    
    h[0] = h.back();
    h.pop_back();

    if (h.size() >= 1) {
        heap_descend(h);
    }

    return ret;
}

vector<double> metodo_3(vector<double> v, size_t k) {
    heapify(v);

    vector<double> r;
    for (size_t i=0; i < k; i++) {
        r.push_back(heap_pop(v));
    }
    return r;
}

vector<double> le_arq(char* nomearq) {
    ifstream arq(nomearq);

    size_t n;
    arq >> n;

    vector<double> v;
    v.reserve(n);

    for (size_t i = 0; i < n; i++) {
        double num;
        arq >> num;
        v.push_back(num);
    }

    arq.close();

    return v;
}

typedef vector<double> (*kmin)(vector<double> v, size_t k);

kmin metodos[] { metodo_1, metodo_2, metodo_3 };

double benchmark(kmin metodo, vector<double>& v, size_t k) {
    tempo();
    metodo(v, k);
    return tempo();
}

size_t k_entre_metodos(kmin melhor_antes, kmin melhor_depois, vector<double>& v, size_t esq, size_t dir) {
    static double thresh = 0.001;

    while (esq <= dir) {
        size_t meio = floor((esq + dir)/2);
        double t_melhor_antes = benchmark(melhor_antes, v, meio),
            t_melhor_depois = benchmark(melhor_depois, v, meio);

        if (abs(t_melhor_depois - t_melhor_antes) < thresh) {
            return meio;
        }

        if (t_melhor_antes < t_melhor_depois) {
            esq = meio + 1;
        }
        else {
            dir = meio - 1;
        }
    }

    return 0;
}

pair<size_t, size_t> metodo_0(vector<double>& v) {
    double k1 = k_entre_metodos(metodo_1, metodo_3, v, 1, 250),
        k2 = k_entre_metodos(metodo_3, metodo_2, v, k1 + 1, v.size());

    return pair<size_t, size_t>(k1, k2);
}

int main(int argc, char **argv) {
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
    char num_metodo = atoi(argv[2]);
    size_t k;

    if(argc == 4) {
        k = atoi(argv[3]);
    }

    vector<double> v(le_arq(nomearq));
    if (num_metodo == 0) {
        pair<size_t, size_t> p = metodo_0(v);
        cout << "k1: " << p.first << endl;
        cout << "k2: " << p.second << endl;
    }
    else {
        kmin metodo = metodos[num_metodo - 1];

        tempo();
        vector<double> k_menores(metodo(v, k));
        double tempo_exec = tempo();

        kmin_to_file(k_menores);

        printf("%.6f\n", tempo_exec);
        cout << endl;
    }

    return 0;
}
