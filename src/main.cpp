#include <iostream>
#include <string>
#include <vector>
#include "MatrixLib.hpp"

int main() {
    try {
        std::vector<std::vector<double>> init_data = {
            {1.0, 2.0},
            {3.0, 4.0}
        };

        Matrix<double> mat_a(init_data);
        mat_a.printMatrix();

        Matrix<double> mat_b(2, 2);
        mat_b.printMatrix();

        mat_b.setRowVal(0, {5.0, 6.0});
        mat_b.printMatrix();

        mat_b.setRowVal(1, {7.0, 8.0});
        mat_b.printMatrix();

        mat_a.setColVal(0, {9.0, 9.0});
        mat_a.printMatrix();

        mat_a.addMatrix(mat_b);    
        mat_a.printMatrix();

        mat_a.subtractMatrix(mat_b); 
        mat_a.printMatrix();

        mat_a.multiplyByConstant(2.0);
        mat_a.printMatrix();
        
        mat_a.divideByConstant(2.0); 
        mat_a.printMatrix();

        Matrix<double> mat_c = mat_a + mat_b;
        mat_c.printMatrix();

        Matrix<double> mat_d = mat_a - mat_b;
        mat_d.printMatrix();

        Matrix<double> mat_e = mat_a * 3.0;
        mat_e.printMatrix();

        Matrix<double> mat_f = mat_a / 2.0;
        mat_f.printMatrix();

        mat_a += mat_b;
        mat_a.printMatrix();

        mat_a -= mat_b;
        mat_a.printMatrix();

        mat_a.addRow({1.0, 1.0});
        mat_a.printMatrix();

        mat_a.addColumn({2.0, 2.0, 2.0});
        mat_a.printMatrix();

        mat_a.getValue(1, 1);
        mat_a.getCol(0);
        mat_a.getRow(1);

        mat_a.transpose();
        mat_a.printMatrix();

        std::vector<std::vector<double>> rect_data = {
            {1.0, 2.0, 3.0},
            {4.0, 5.0, 6.0}
        };
        Matrix<double> mat_rect(rect_data); 
        mat_rect.printMatrix();

        Matrix<double> result = mat_b * mat_rect; 
        result.printMatrix();

        //Matrix<double> error_mat = mat_rect * mat_b;

    } catch (const std::exception& e) {
        std::cerr << "Error occured: " << e.what() << std::endl;
        return 1;
    }

    std::vector<std::vector<double>> init = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 8}
    };

    try {
        Square_Matrix<double> sq(init);
        
        std::cout << "Original Matrix:\n";
        sq.printMatrix();

        double det = sq.determinant();
        std::cout << "Determinant: " << det << "\n\n";


        std::cout << "Inverse Matrix:\n";
        Square_Matrix<double> inv = sq.inverse();
        inv.printMatrix();

        std::cout << "Check (A * A^-1):\n";
        Matrix<double> identity = sq * inv;
        identity.printMatrix();

    } catch (const std::exception& e) {
        std::cout << "Error occured: " << e.what() << "\n";
    }


    return 0;
}

