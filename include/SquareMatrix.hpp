#pragma once
#include <iostream>
#include <vector>
#include <stdexcept>
#include "Matrix.hpp"

/**
 * @class Square_Matrix
 * @brief A specialized Matrix class for square matrices (NxN).
 * Inherits from Matrix<T> and adds functionality for determinant and inverse calculation.
 */
template <typename T>
class Square_Matrix : public Matrix<T> {
private:
    /**
     * @brief Helper function to get the cofactor matrix (submatrix excluding row p and col q).
     * Used internally for determinant and adjugate calculations.
     * @param mat Source matrix.
     * @param temp Destination matrix for the cofactor.
     * @param p Row to exclude.
     * @param q Column to exclude.
     * @param n Current dimension.
     */
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

    /**
     * @brief Recursive helper function to calculate the determinant using Laplace expansion.
     * @param mat The matrix to calculate.
     * @param n Current dimension of the matrix.
     * @return The calculated determinant value.
     */
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
    /**
     * @brief Constructs an empty Square Matrix of size NxN.
     * @param n The dimension (number of rows/columns).
     * @throws std::invalid_argument if n is not positive.
     * @note Example: Square_Matrix<double> sq(3); // Creates 3x3 square matrix
     */
    Square_Matrix(int n) : Matrix<T>(n, n) {
        if (n <= 0) throw std::invalid_argument("Size must be positive.\n");
    }

    /**
     * @brief Constructs a Square Matrix from a vector of vectors.
     * Validates that the input is actually square.
     * @param value Initial data.
     * @throws std::invalid_argument if rows != columns.
     * @note Example: Square_Matrix<int> sq({{1, 2}, {3, 4}});
     */
    Square_Matrix(std::vector<std::vector<T>> value) : Matrix<T>(value) {
        if (this->m_row != this->m_col) {
            throw std::invalid_argument("Square Matrix must have equal rows and columns.\n");
        }
    }

    /**
     * @brief Calculates the determinant of the matrix.
     * @return The determinant value.
     * @note Example: double det = sq.determinant();
     */
    T determinant() const {
        return determinantRecursive(this->data, this->m_row);
    }

    /**
     * @brief Calculates the Adjugate Matrix.
     * The Adjugate is the transpose of the Cofactor Matrix.
     * @return A new Square_Matrix representing the adjugate.
     * @note Example: Square_Matrix adj = sq.adjugate();
     */
    Square_Matrix adjugate() const {
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
                adj.data[j][i] = (sign) * (determinantRecursive(temp, n - 1));
            }
        }
        return adj;
    }

    /**
     * @brief Calculates the Inverse Matrix.
     * Formula: A^-1 = (1 / det(A)) * adj(A).
     * @return A new Square_Matrix representing the inverse.
     * @throws std::invalid_argument if the matrix is singular (determinant is 0).
     * @note Recommended to use with floating point types (float/double).
     * @note Example: Square_Matrix inv = sq.inverse();
     */
    Square_Matrix inverse() const {
        T det = determinant();
        if (det == static_cast<T>(0)) {
            throw std::invalid_argument("Cannot calculate inverse: Determinant is 0.\n");
        }

        Square_Matrix adj = adjugate();
        
        Square_Matrix inv(this->m_row);
        for (int i = 0; i < this->m_row; i++) {
            for (int j = 0; j < this->m_col; j++) {
                inv.data[i][j] = adj.data[i][j] / det;
            }
        }
        return inv;
    }
};
