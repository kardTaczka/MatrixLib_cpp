#pragma once
#include <iostream>
#include <vector>
#include <iomanip>
#include <stdexcept>

/**
 * @class Matrix
 * @brief A template class for mathematical matrix operations.
 * Supports basic arithmetic, resizing, and matrix multiplication.
 */
template <typename T> class Matrix
{
protected:
    int m_row{};
    int m_col{};
    std::vector<std::vector<T>> data;

    int precision = 3; //Default value of precision

public:

    /**
     * @brief Constructs a Matrix with specified dimensions initialized to zero.
     * @param row Number of rows.
     * @param column Number of columns.
     * @throws std::invalid_argument if dimensions are negative.
     * @note Example: Matrix<int> mat(3, 3); // Creates a 3x3 zero matrix
     */
    Matrix(int row, int column) : m_row(row), m_col(column), data(row, std::vector<T>(column)) {
        if (row < 0 || column < 0) {
            throw std::invalid_argument("Number of rows and columns shall be greater than 0.\n");
        }
    };

    /**
     * @brief Constructs a Matrix from a 2D vector.
     * @param value A vector of vectors containing the initial data.
     * @note Example: Matrix<int> mat({{1, 2}, {3, 4}});
     */
    Matrix(std::vector<std::vector<T>> value) : m_row(value.size()), m_col(value[0].size()), data{value} {};

    /**
     * @brief Retrieves a single element from the matrix.
     * @param row The row index.
     * @param col The column index.
     * @return The value at the specified position.
     * @throws std::invalid_argument if indices are out of bounds.
     * @note Example: double val = mat.getVal(21, 37);
     */
    T getValue(int row, int col) const {
        if (row < 0 || row >= m_row || col < 0 || col >= m_col) {
            throw std::invalid_argument("Index out of bounds.\n");
        }
        return data[row][col];
    }

    /**
     * @brief Retrieves an entire row as a vector.
     * @param row Index of the row to retrieve.
     * @return A std::vector containing the row values.
     * @throws std::invalid_argument if row index is out of bounds.
     * @note Example: double val = mat.getRow(1);
     */
    std::vector<T> getRow(int row) const {
        if (row < 0 || row >= m_row) {
            throw std::invalid_argument("Row index out of bounds.\n");
        }
        return data[row];
    }

    /**
     * @brief Retrieves an entire column as a vector.
     * @param col Index of the column to retrieve.
     * @return A std::vector containing the column values.
     * @throws std::invalid_argument if column index is out of bounds.
     * @note Example: double val = mat.getCol(4);
     */
    std::vector<T> getCol(int col) const {
        if (col < 0 || col >= m_col) {
            throw std::invalid_argument("Column index out of bounds.\n");
        }

        std::vector<T> column_vector;

        for (int i = 0; i < m_row; i++) {
            column_vector.push_back(data[i][col]);
        }
        return column_vector;
    }

    /**
     * @brief Overwrites a specific row with new values.
     * @param row The index of the row to replace.
     * @param vec_of_val Vector containing the new values.
     * @throws std::invalid_argument if the index is out of bounds or vector size is incorrect.
     * @note Example: mat.setRowVal(0, {1, 2, 3});
     */
    void setRowVal(int row, std::vector<T> vec_of_val){
        if (row >= m_row || row < 0){
            throw std::invalid_argument("Index out of bounds, try using addRow().\n");
        }
        if (vec_of_val.size() != m_col){
            throw std::invalid_argument("Size of vector isn't equal to number of columns.\n");
        }
        data[row] = vec_of_val;
    }

    /**
     * @brief Overwrites a specific column with new values.
     * @param column The index of the column to replace.
     * @param vec_of_val Vector containing the new values.
     * @throws std::invalid_argument if the index is out of bounds or vector size is incorrect.
     * @note Example: mat.setColVal(1, {5, 6, 7});
     */
    void setColVal(int column, std::vector<T> vec_of_val){
        if (column >= m_col || column < 0){
            throw std::invalid_argument("Index out of bounds, try using addColumn().\n");
        }

        if (vec_of_val.size() != m_row) {
            throw std::invalid_argument("Size of vector is not equal to number of rows.\n");
        }

        for (int i = 0; i < m_row; i++){
            data[i][column] = vec_of_val[i];
        }
    }

    /**
     * @brief Prints the matrix to the standard output with formatted spacing.
     * Uses fixed point notation and precision of .
     * @note Example: mat.printMatrix();
     */
    void printMatrix() const {
        std::cout << std::fixed << std::setprecision(precision);

        for (int r = 0; r < m_row; r++){
            for (int c = 0; c < m_col; c++){
                std::cout << std::setw(10) << data[r][c] << " ";
            }
            std::cout << std::endl;
        }
        std::cout << "--------------------------------\n";
    } 

    /**
     * @brief Appends a new row to the bottom of the matrix.
     * @param vec_of_val Values for the new row.
     * @note Example: mat.addRow({10, 11, 12});
     */
    void addRow(std::vector<T> vec_of_val){
        if(vec_of_val.size() != m_col) {
            throw std::invalid_argument("Size of vector is not equal to number of columns.\n");
        }

        data.push_back(vec_of_val);
        m_row += 1;
    }

    /**
     * @brief Appends a new column to the right side of the matrix.
     * @param vec_of_val Values for the new column.
     * @note Example: mat.addColumn({10, 11, 12});
     */
    void addColumn(std::vector<T> vec_of_val){
        if (vec_of_val.size() != m_row){
            throw std::invalid_argument("Size of vector is not equal to number of rows.\n");
        }

        for (int r = 0; r < m_row; r++){
            data[r].push_back(vec_of_val[r]);
        }
        m_col += 1;
    }

    /**
     * @brief Checks if two matrices have the same dimensions.
     * @param other The matrix to compare against.
     * @return true if rows and columns match, false otherwise.
     */
    bool checkIfSameSize(const Matrix &other) const {
        return (m_row == other.m_row && m_col == other.m_col);
    }

    /**
     * @brief Adds another matrix to this one element-wise.
     * Modifies the current object.
     * @note Example: mat.addMatrix(otherMat);
     */
    void addMatrix(const Matrix &other){
        if (!checkIfSameSize(other)){
            throw std::invalid_argument("Both matrices must be the same size.\n");
        }

        for (int matA_row = 0; matA_row < m_row; matA_row++){
            for (int matA_col = 0; matA_col < m_col; matA_col++){
                data[matA_row][matA_col] += other.data[matA_row][matA_col];
            }
        }
    }

    /**
     * @brief Subtracts another matrix from this one element-wise.
     * Modifies the current object.
     * @note Example: mat.subtractMatrix(otherMat);
     */
    void subtractMatrix(const Matrix &other){
        if (!checkIfSameSize(other)){
            throw std::invalid_argument("Both matrices must be the same size.\n");
        }
        for (int matA_row = 0; matA_row < m_row; matA_row++){
            for (int matA_col = 0; matA_col < m_col; matA_col++){
                data[matA_row][matA_col] -= other.data[matA_row][matA_col];
            }
        }
    }

    /**
     * @brief Multiplies every element in the matrix by a scalar constant.
     * Modifies the current object.
     * @note Example: mat.multiplyByConstant(2.5);
     */
    void multiplyByConstant(T c){
        for (int mat_row = 0; mat_row < m_row; mat_row++){
            for (int mat_col = 0; mat_col < m_col; mat_col++){
                data[mat_row][mat_col] *= c;
            }
        }
    }

    /**
     * @brief Divides every element in the matrix by a scalar constant.
     * Modifies the current object.
     * @throws std::invalid_argument if dividing by zero.
     * @note Example: mat.divideByConstant(2);
     */
    void divideByConstant(T c){
        if (c == static_cast<T>(0)){
            throw std::invalid_argument("Constant must be a nonzero value.\n");
        }

        for (int mat_row = 0; mat_row < m_row; mat_row++){
            for (int mat_col = 0; mat_col < m_col; mat_col++){
                data[mat_row][mat_col] /= c;
            }
        }
    }

    /**
     * @brief Performs matrix multiplication (Dot Product).
     * @param other The matrix to multiply by (Right-hand side).
     * @return A new Matrix object containing the result.
     * @throws std::invalid_argument if column count of A != row count of B.
     * @note Example: Matrix result = matA.multiplyByMatrix(matB);
     */
    Matrix multiplyByMatrix(const Matrix &other) const {
        if (m_col == other.m_row){
            int rows_A = m_row;
            int cols_A = m_col;
            int cols_B = other.m_col;

            Matrix result(rows_A, cols_B);

            for(int r = 0; r < rows_A; r++){
                for(int c = 0; c < cols_B; c++){
                    for(int i = 0; i < cols_A; i++){
                        result.data[r][c] += data[r][i] * other.data[i][c];
                    }
                }
            }
            return result;
        } else {
            throw std::invalid_argument("Right matrix's row number must be equal to left matrix's columns number.\n");
        }
    }
    

    /**
     * @brief Transposes the matrix (swaps rows and columns) in place.
     * A matrix of size MxN becomes NxM.
     * @note Example: mat.transpose();
     */
    void transpose(){
        std::vector<std::vector<T>> temp(m_col, std::vector<T>(m_row));
        for(int r = 0; r < m_row; r++){
            for(int c = 0; c < m_col; c++){
                temp[c][r] = data[r][c];
            }
        }
        data = temp;
        std::swap(m_row, m_col);
    }

    // --- OPERATORS ---

    /**
     * @brief Compound assignment operator for addition.
     * @note Example: matA += matB;
     */
    Matrix& operator+=(const Matrix& other) {
        addMatrix(other);
        return *this;
    }

    /**
     * @brief Binary operator for addition. Returns a new object.
     * @note Example: Matrix matC = matA + matB;
     */
    Matrix operator+(const Matrix& other) const {
        Matrix result = *this; 
        result.addMatrix(other); 
        return result;
    }

    /**
     * @brief Compound assignment operator for subtraction.
     * @note Example: matA -= matB;
     */
    Matrix& operator-=(const Matrix& other) {
        subtractMatrix(other);
        return *this;
    }

    /**
     * @brief Binary operator for subtraction. Returns a new object.
     * @note Example: Matrix matC = matA - matB;
     */
    Matrix operator-(const Matrix& other) const {
        Matrix result = *this;
        result.subtractMatrix(other);
        return result;
    }

    /**
     * @brief Binary operator for matrix multiplication. Returns a new object.
     * @note Example: Matrix matC = matA * matB;
     */
    Matrix operator*(const Matrix& other) const {
        return multiplyByMatrix(other);
    }

    /**
     * @brief Binary operator for scalar multiplication. Returns a new object.
     * @note Example: Matrix matB = matA * 5.0;
     */
    Matrix operator*(T constant) const {
        Matrix result = *this;
        result.multiplyByConstant(constant);
        return result;
    }
    
    /**
     * @brief Binary operator for scalar division. Returns a new object.
     * @note Example: Matrix matB = matA / 2.0;
     */
    Matrix operator/(T constant) const {
        Matrix result = *this;
        result.divideByConstant(constant);
        return result;
    }
};
