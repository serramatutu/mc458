#include <algorithm>
#include <iostream>
#include <vector>
#include <limits>

using namespace std;

/**
 * Lê a entrada para o problema de uma input stream.
 * 
 * @param input a input stream para leitura.
 * @returns A matriz de escalada lida.
 */
vector<vector<size_t> > read_input(istream& input) {
    size_t rows, columns;
    input >> rows >> columns;
    
    vector<vector<size_t>> ret(rows);
    for (size_t i = 0; i < rows; i++) {
        ret[i].reserve(columns + 2);        
        for (size_t j = 0; j < columns; j++) {
            size_t cost;
            input >> cost;
            ret[i].push_back(cost);
        }
    }

    return ret;
}

/**
 * Escala uma única linha da parede, calculando o custo até ali com base nos custos da linha anterior.
 * 
 * @param row a linha a ser escalada
 * @param costs os custos da linha anterior, com padding de infinito na primeira e última posições
 * @returns o vetor de custos de `row`, com padding de infinito na primeira e última posições
 */
vector<size_t> climb_row(const vector<size_t>& row, const vector<size_t>& costs) {
    vector<size_t> new_costs;
    new_costs.reserve(row.size() + 2);
    new_costs.push_back(numeric_limits<size_t>::max());

    for (size_t column = 1; column <= row.size(); column++) {
        size_t min_prev_cost = *min_element(costs.cbegin() + column - 1, costs.cbegin() + column + 2);
        size_t row_cost = row[column - 1];
        new_costs.push_back(min_prev_cost + row_cost);
    }

    new_costs.push_back(numeric_limits<size_t>::max());

    return new_costs;
}

/**
 * Inicializa um vetor de custos com base na primeira linha da escalada, com padding de infinito na primeira e última posições.
 * 
 * @param first_row a primeira linha da escalada
 * @returns o vetor de custos correspondente
 */
vector<size_t> initialize_costs(const vector<size_t>& first_row) {
    vector<size_t> costs;
    costs.reserve(first_row.size() + 2);
    costs.push_back(numeric_limits<size_t>::max());
    costs.insert(costs.begin() + 1, first_row.cbegin(), first_row.cend());
    costs.push_back(numeric_limits<size_t>::max());

    return costs;
}

/**
 * Calcula o menor custo para se escalar uma matriz.
 * 
 * @param matrix A matriz a ser escalada
 * @returns O menor custo para se escalar `matrix`
 */
size_t climb(const vector<vector<size_t> >& matrix) {
    vector<size_t> costs(initialize_costs(matrix[0]));

    for (size_t row = 1; row < matrix.size(); row++) {
        costs = climb_row(matrix[row], costs);
    }

    return *min_element(costs.cbegin(), costs.cend());
}

int main() {
    vector<vector<size_t> > matrix(read_input(cin));
    cout << climb(matrix) << endl;

    return 0;
}