#pragma once
#include<math.h>
#include<stdlib.h>
#include<exception>
#include<string>

class Matrix
{
private:
	double** matrix = nullptr;
	int rows = -1;
	int columns = -1;
	bool is_allocated = false;

	void allocate_matrix(int rows, int columns);
	void deallocate_matrix() noexcept;
	inline double* operator[](int row) { return is_allocated ? matrix[row] : nullptr; }

public:
	static int matrices_allocated;
	static int matrices_deallocated;

	Matrix() = default;
	Matrix(const int rows,const int columns,const double init_value = 0);
	Matrix(const Matrix& matrix) { *this = matrix; };
	Matrix(Matrix&& matrix) noexcept { *this = std::move(matrix); };
	Matrix& operator=(const Matrix& matrix);
	Matrix& operator=(Matrix&& matrix) noexcept;

	~Matrix() { deallocate_matrix(); }

	inline int get_rows() const { return rows; }
	inline int get_columns() const { return columns; }

	inline double get_element_at(const int row, const int column) const { return matrix[row][column]; }
	inline double& set_element_at(const int row,const int column) { return matrix[row][column]; }
	inline void set_element_at(const int row, const int column, const double value) { matrix[row][column] = value; }

	operator std::string()const;
	inline operator double** () { return matrix; }

	Matrix operator*(const double scalar);
	Matrix operator/(const double scalar);
	Matrix operator+(const Matrix& matrix);
	Matrix operator-(const Matrix& matrix);
	Matrix operator*(const Matrix& matrix);

	double get_determinant() const;
	Matrix get_transpose() const;
	Matrix get_adjugate() const;
	Matrix get_inverse() const;
};



