#include <iostream>
#include"Matrix.h"

int main()
{
    std::string matrix;
    std::string matrix2;
    double det = 0;
    double det2 = 0;

    {
        Matrix m(3, 3);
        m.set_element_at(0, 0) = 4;
        m.set_element_at(0, 1) = 7;
        m.set_element_at(0, 2) = 2;
        m.set_element_at(1, 0) = -3;
        m.set_element_at(1, 1) = 21;
        m.set_element_at(1, 2) = 0;
        m.set_element_at(2, 0) = 2;
        m.set_element_at(2, 1) = 6;
        m.set_element_at(2, 2) = 9;

        Matrix m2 = m * m * 12;

        //Matrix r = m * m;

        det = m.get_determinant();
        det2 = m2.get_determinant();

        matrix = (std::string)m;
        matrix2 = (std::string)m2;
    }
    
    std::cout << matrix;
    std::cout <<det << std::endl<<std::endl<<std::endl;
    std::cout << matrix2;
    std::cout << det2 << std::endl << std::endl << std::endl;

    
    std::cout << "Matrices allocated:   " << Matrix::matrices_allocated<<std::endl;
    std::cout << "Matrices deallocated:   " << Matrix::matrices_deallocated << std::endl;

}

