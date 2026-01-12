#pragma once
#include <iostream>
#include <vector>
#include "Matrix.hpp"

template <typename T>
class Square_Matrix : public Matrix<T> {
private:
    // Funkcja pomocnicza do wycinania mniejszej macierzy (do wyznacznika i dopełnień)
    void getCofactor(const std::vector<std::vector<T>>& mat, std::vector<std::vector<T>>& temp, int p, int q, int n) const {
        int i = 0, j = 0;
        for (int row = 0; row < n; row++) {
            for (int col = 0; col < n; col++) {
                if (row != p && col != q) {
                    temp[i][j++] = mat[row][col];
                    if (j == n - 1) {
                        j = 0;
                        i++;
                    }
                }
            }
        }
    }

    // Rekurencyjna funkcja licząca wyznacznik
    T determinantRecursive(const std::vector<std::vector<T>>& mat, int n) const {
        if (n == 1)
            return mat[0][0];

        T det = 0;
        std::vector<std::vector<T>> temp(n, std::vector<T>(n));
        int sign = 1;

        for (int f = 0; f < n; f++) {
            getCofactor(mat, temp, 0, f, n);
            det += sign * mat[0][f] * determinantRecursive(temp, n - 1);
            sign = -sign;
        }
        return det;
    }

public:
    // Konstruktor: przyjmuje tylko jeden wymiar (bo N x N)
    Square_Matrix(int n) : Matrix<T>(n, n) {
        if (n <= 0) throw std::invalid_argument("Size must be positive.\n");
    }

    // Konstruktor z wektora wektorów: sprawdza czy jest kwadratowa
    Square_Matrix(std::vector<std::vector<T>> value) : Matrix<T>(value) {
        if (this->m_row != this->m_col) { // Używamy this-> bo to szablon
            throw std::invalid_argument("Square Matrix must have equal rows and columns.\n");
        }
    }

    // --- Metoda: Obliczanie wyznacznika ---
    T determinant() const {
        return determinantRecursive(this->data, this->m_row);
    }

    // --- Metoda: Macierz dołączona (Adjugate Matrix) ---
    // Potrzebna do odwracania
    Square_Matrix adjoint() const {
        int n = this->m_row;
        Square_Matrix adj(n);
        if (n == 1) {
            adj.data[0][0] = 1;
            return adj;
        }

        int sign = 1;
        std::vector<std::vector<T>> temp(n, std::vector<T>(n));

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                getCofactor(this->data, temp, i, j, n);
                sign = ((i + j) % 2 == 0) ? 1 : -1;
                // Transpozycja dzieje się "w locie" (zamiana indeksów [j][i])
                adj.data[j][i] = (sign) * (determinantRecursive(temp, n - 1));
            }
        }
        return adj;
    }

    // --- Metoda: Odwracanie macierzy ---
    Square_Matrix inverse() const {
        T det = determinant();
        if (det == static_cast<T>(0)) {
            throw std::invalid_argument("Cannot calculate inverse: Determinant is 0 (Singular Matrix).\n");
        }

        Square_Matrix adj = adjoint();
        
        // Wzór: A^-1 = (1/det) * adj(A)
        // Dzielimy każdy element macierzy dołączonej przez wyznacznik
        // UWAGA: Dla typu int wynik zostanie ucięty do 0. Zalecane użycie Matrix<double>.
        Square_Matrix inv(this->m_row);
        for (int i = 0; i < this->m_row; i++) {
            for (int j = 0; j < this->m_col; j++) {
                inv.data[i][j] = adj.data[i][j] / det;
            }
        }
        return inv;
    }
};