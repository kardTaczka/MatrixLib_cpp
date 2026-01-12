#pragma once
#include <iostream>
#include <vector>
#include <iomanip>

template <typename T> class Matrix
{
protected:
    int m_row{};
    int m_col{};
    std::vector<std::vector<T>> data;
public:
    Matrix(int row, int column) : m_row(row), m_col(column), data(row, std::vector<T>(column, 0)) {
        if (row < 0 || column < 0) {
            throw std::invalid_argument("Number of rows and columns shall be greater than 0.\n");
        }
    };

    Matrix(std::vector<std::vector<T>> value) : m_row(value.size()), m_col(value[0].size()), data{value} {};


    void setRowVal(int row, std::vector<T> vec_of_val){
        if (row >= m_row){
            throw std::invalid_argument("Index out of bounds, try using addRow().\n");
        }
        if (vec_of_val.size() != m_col){
            throw std::invalid_argument("Size of vector isn't equal to number of columns.\n");
        }
        for (int i = 0; i < m_col; i++){
            data[row][i] = vec_of_val[i];
        }
    }

    void setColVal(int column, std::vector<T> vec_of_val){
        if (column >= m_col){
            throw std::invalid_argument("Index out of bounds, try using addColumn().\n");
        }

        if (vec_of_val.size() != m_row) {
            throw std::invalid_argument("Size of vector is not equal to number of rows.\n");
        }

        for (int i = 0; i < m_row; i++){
            data[i][column] = vec_of_val[i];
        }
    }


    void printMatrix() const {

        std::cout << std::fixed << std::setprecision(3);

        for (int r = 0; r < m_row; r++){
            for (int c = 0; c < m_col; c++){
                std::cout << std::setw(20) << data[r][c] << " ";
            }
            std::cout << std::endl;
        }
        std::cout << "--------------------------------\n";
    } 


    void addRow(std::vector<T> vec_of_val){
        if(vec_of_val.size() != m_col) {
            throw std::invalid_argument("Size of vector is not equal to number of columns.\n");
        }

        data.push_back(std::vector<T>(m_col, 0));
        m_row += 1;
        for (int i = 0; i < m_col; i++){
            data[m_row - 1][i] = vec_of_val[i];
        }
    }

    void addColumn(std::vector<T> vec_of_val){
        if (vec_of_val.size() != m_row){
            throw std::invalid_argument("Size of vector is not equal to number of rows.\n");
        }

        for (int r = 0; r < m_row; r++){
            data[r].push_back(0);
        }
        m_col += 1;
        for (int i = 0; i < m_row; i++){
            data[i][m_col - 1] = vec_of_val[i];
        }
    }

    bool checkIfSameSize(const Matrix &other){
        return (data.size() == other.data.size() && data[0].size() == other.data[0].size());
    }

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

    void multiplyByConstant(T c){
        for (int mat_row = 0; mat_row < m_row; mat_row++){
            for (int mat_col = 0; mat_col < m_col; mat_col++){
                data[mat_row][mat_col] *= c;
            }
        }
    }


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



    Matrix multiplyByMatrix(const Matrix &other) const {
        if (m_col == other.m_row){
            int right_row = data.size();
            int right_col = data[0].size();
            int left_col = data[0].size();
            Matrix result(right_row, left_col);
            for(int r = 0; r < right_row; r++){
                for(int c = 0; c < left_col; c++){
                    for(int i = 0; i < right_col; i++){
                        result.data[r][c] += data[r][i] * other.data[i][c];
                    }
                }
            }
            return result;
        } else {
            throw std::invalid_argument("Right matrix's row number must be equal to left matrix's columns number.\n");
        }
    }

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

    Matrix& operator+=(const Matrix& other) {
        addMatrix(other);
        return *this;
    }


    Matrix operator+(const Matrix& other) const {
        Matrix result = *this; 
        result.addMatrix(other); 
        return result;
    }


    Matrix& operator-=(const Matrix& other) {
        subtractMatrix(other);
        return *this;
    }

    Matrix operator-(const Matrix& other) const {
        Matrix result = *this;
        result.subtractMatrix(other);
        return result;
    }


    Matrix operator*(const Matrix& other) const {
        return multiplyByMatrix(other);
    }


    Matrix operator*(T constant) const {
        Matrix result = *this;
        result.multiplyByConstant(constant);
        return result;
    }
    

    Matrix operator/(T constant) const {
        Matrix result = *this;
        result.divideByConstant(constant);
        return result;
    }

};

