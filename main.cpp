#include <bits/stdc++.h>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

void split_str (const string &s, const string &delimiter, vector<string> &data) {
    size_t pos_start = 0, pos_end, delim_len = delimiter.length();
    string token;

    while ((pos_end = s.find (delimiter, pos_start)) != string::npos) {
        token = s.substr (pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;
        data.push_back (token);
    }

    data.push_back (s.substr (pos_start));
}

class Matrix {
      private:
        int n, m;
        double** matrix;
        string matrix_delimeter, size_delimeter;

      public:
        Matrix(int n) {
            this->n = n;
            this->m = n;
            this->matrix_delimeter = " ";
            this->size_delimeter = "x";
            this->create_initial_matrix(this->rows(), this->cols());
        }

        Matrix(int n, int m) {
            this->n = n;
            this->m = m;
            this->matrix_delimeter = " ";
            this->size_delimeter = "x";
            this->create_initial_matrix(this->rows(), this->cols());
        }

        Matrix(const string path) {
            this->matrix_delimeter = " ";
            this->size_delimeter = "x";

            ifstream s(path.c_str());
            string line;
            size_t pos;
            vector <string> matrix_data;

            // get matrix size from the first line
            getline(s, line);
            pos = line.find(size_delimeter);
            this->n = stoi(line.substr(0, pos));
            this->m = stoi(line.substr(pos + 1));
            this->matrix = new double*[n];

            for (int i = 0; i < this->rows(); i++) {
                matrix_data.clear();
                this->matrix[i] = new double[this->cols()];
                getline(s, line);
                split_str(line, matrix_delimeter, matrix_data);

                for (int j = 0; j < this->cols(); j++) {
                    if (!matrix_data[j].empty()) {
                        this->set(i, j, stod(matrix_data[j]));
                    }
                }

                cout << endl;
            }
        }

        Matrix(const Matrix &m) {
            for (int i = 0; i < m.cols(); i++) {
                for (int j = 0; j < rows(); j++) {
                    set(i, j, m.get(i, j));
                }
            }
        }

        ~Matrix() {
            if (matrix) {
                if (*matrix) {
                    for (int i = 0; i < cols(); i++) {
                        delete[] matrix[i];
                    }
                }

                delete[] matrix;
            }
        }

        Matrix add(const Matrix& matrix_input) {
            Matrix temp(rows(), cols());

              if (this->rows() != matrix_input.rows() || this->cols() != matrix_input.cols()) {
                throw invalid_argument("Matrix addition is workable for matrices with the same dimensions.");
              }

              for (int i = 0; i < this->rows(); i++) {
                for (int j = 0; j < this->cols(); j++) {
                    temp.set(i, j, this->get(i, j) + matrix_input.get(i, j));
                }
              }

            return temp;
        }

        void create_initial_matrix(int rows, int cols) {
            matrix = new double* [rows];

            for (int i = 0; i < rows; i++) {
                matrix[i] = new double[cols];
                memset(matrix[i], 0, cols * sizeof(double));
            }

            for (int i = 0; i < rows; i++) {
                for (int j = 0; j < cols; j++) {
                    this->set(i, j, 0);
                }
            }
        }

        int cols() const {
            return this->m ? this->m : this->n;
        }

        double get(int n, int m) const {
            return this->matrix[n][m];
        }

        Matrix multiply(const Matrix& matrix_input) {
            Matrix temp(rows(), cols());

            if (this->rows() != matrix_input.cols() || this->cols() != matrix_input.rows()) {
                throw invalid_argument("Matrix multiplication is workable for matrices with the same dimensions.");
            }

            double calculations[this->cols()][matrix_input.rows()];

            for (int i = 0; i < this->cols(); i++) {
                for (int j = 0; j < matrix_input.rows(); j++) {
                    calculations[i][j] = 0;
                }
            }

            for (int i = 0; i < this->cols(); i++) {
                for (int j = 0; j < matrix_input.rows(); j++){
                    for (int k = 0; k < this->rows(); k++) {
                        calculations[i][j] += this->matrix[i][k] * matrix_input.get(k, j);
                    }
                }
            }

            for (int i = 0; i < this->cols(); i++) {
                for (int j = 0; j < matrix_input.rows(); j++) {
                    temp.set(i, j, calculations[i][j]);
                }
            }

            return temp;
        }

        void print() {
            for (int i = 0; i < this->rows(); i++) {
                for (int j = 0; j < this->cols(); j++) {
                    cout << this->matrix[i][j] << this->matrix_delimeter;
                }

                cout << endl;
            }

            cout << endl;
        }

        int rows() const {
            return this->n;
        }

        void set(int n, int m, double val) const {
            this->matrix[n][m] = val;
        }

        void store(const string filename, const string path) {
            string filepath = path + filename;
            ofstream s(filepath.c_str());

            s << this->rows() << this->size_delimeter << this->cols() << endl;

            for (int i = 0; i < this->rows(); i++) {
                for (int j = 0; j < this->cols(); j++) {
                    s << this->matrix[i][j] << this->matrix_delimeter;
                }


                s << endl;
            }

            s.close();
        }

        Matrix subtract(const Matrix &matrix_input) {
            Matrix temp(rows(), cols());

            if (this->rows() != matrix_input.rows() || this->cols() != matrix_input.cols()) {
                throw invalid_argument("Matrix subtraction is workable for matrices with the same dimensions.");
            }

            for (int i = 0; i < this->rows(); i++) {
                for (int j = 0; j < this->cols(); j++) {
                    temp.set(i, j, this->get(i, j) - matrix_input.get(i, j));
                }
            }   

            return temp;
        }
};

int main() {
    Matrix matrix(5);
    matrix.set(0, 3, 2);
    matrix.set(1, 1, 1);
    matrix.set(1, 0, 2);
    matrix.set(2, 3, 1);
    matrix.set(1, 3, 4);
    matrix.set(1, 2, 1);
    cout << "Matrix 1:" << endl;
    matrix.print();

    Matrix matrix2(5, 5);
    matrix2.set(0, 1, 1);
    matrix2.set(1, 2, 1);
    matrix2.set(2, 0, 1);
    cout << "Matrix 2:" << endl;
    matrix2.print();

    cout << "After addition:" << endl;
    Matrix add = matrix.add(matrix2);
    add.print();

    cout << "After subtraction:" << endl;
    Matrix subtract = matrix.subtract(matrix2);
    subtract.print();

    cout << "After multiplication:" << endl;
    Matrix multiply = matrix.multiply(matrix2);
    multiply.print();

    cout << "Data saved to file: matrix.txt" << endl;
    matrix.store("matrix.txt", "");

    cout << "Matrix 3 (created based on file: matrix.txt):" << endl;
    Matrix matrix3("matrix.txt");
    matrix3.print();

    return 0;
}
