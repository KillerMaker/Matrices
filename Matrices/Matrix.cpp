#include "Matrix.h"
int Matrix::matrices_allocated = 0;
int Matrix::matrices_deallocated = 0;

Matrix::Matrix(int rows, int columns, double init_value):is_allocated(false)
{
	allocate_matrix(rows, columns);

	for (auto row = 0; row < rows; row++) 
		for (auto column = 0; column < columns; column++)
			matrix[row][column] = init_value;
}

Matrix& Matrix::operator=(const Matrix& matrix)
{
	if (is_allocated) deallocate_matrix();

	allocate_matrix(matrix.rows, matrix.columns);

	for (auto row = 0; row < rows; row++)
		for (auto col = 0; col < columns; col++)
			this->matrix[row][col] = matrix.matrix[row][col];

	return *this;
}

Matrix& Matrix::operator=(Matrix&& matrix) noexcept
{
	if (is_allocated) deallocate_matrix();

	this->matrix = matrix.matrix;
	this->columns = matrix.columns;
	this->rows = matrix.rows;
	this->is_allocated = true;

	matrix.matrix = nullptr;
	matrix.columns = -1;
	matrix.rows = -1;
	matrix.is_allocated = false;

	return *this;
}

void Matrix::allocate_matrix(int rows, int columns)
{
	this->matrix = new double* [rows];

	for (auto i = 0; i < rows; i++)
		this->matrix[i] = new double[columns];

	this->rows = rows;
	this->columns = columns;

	is_allocated = true;
	matrices_allocated++;
}

void Matrix::deallocate_matrix() noexcept
{
	if (!is_allocated) return;

	for (auto row = 0; row < rows; ++row)
		delete[] matrix[row];

	delete[] matrix;
	rows = -1;
	columns = -1;

	is_allocated = false;
	matrices_deallocated++;
}

Matrix::operator std::string() const
{
	std::string s = "";

	for (auto row = 0; row < rows; row++)
	{
		for (auto col = 0; col < columns; col++)
			s += "[" + std::to_string(matrix[row][col]) + "]" + "  ";
		s += "\n";
	}
	return s;
}

Matrix Matrix::operator*(double scalar)
{
	Matrix temp = *this;
	for (auto row = 0; row < this->rows; row++)
		for (auto col = 0; col < this->columns; col++)
			temp.matrix[row][col] *= scalar;

	return temp;
}

Matrix Matrix::operator/(double scalar)
{
	return *this *(1/scalar);
}

Matrix Matrix::operator+(const Matrix& right)
{
	if (this->rows != right.rows || this->columns != right.columns)
		throw std::exception("Imposible to sum matrices of different order");

	Matrix result(this->rows, this->columns);

	for (auto row = 0; row < result.rows; row++)
		for (auto col = 0; col < result.columns; col++)
			result[row][col] = this->get_element_at(row,col) + right.get_element_at(row, col);

	return result;
}

Matrix Matrix::operator-(const Matrix& right)
{
	Matrix temp = right;
	temp = temp * -1;
	return *this + temp;
}

Matrix Matrix::operator*(const Matrix& right)
{
	if (this->columns != right.rows)
		throw std::exception("Imposible to multiply matrices");

	Matrix result(this->rows, right.columns);

	for (int row = 0; row < result.get_rows(); row++)
	{
		for (int col = 0; col < result.get_columns(); col++)
		{
			double temp = 0;

			for (int it = 0; it < this->columns; it++)
				temp += this->get_element_at(row,it) * right.get_element_at(it, col);
			result[row][col] = temp;
		}
	}
	
	return result;
}

//Using the adjugate method
double Matrix::get_determinant() const
{
	if (rows != columns)
		throw std::exception("Not a squared matrix");
	else if (rows == 2)
		return matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
	else
	{
		double determinant = 0;
		Matrix adjugate = get_adjugate();

		for (auto col = 0; col < columns; col++)
			determinant += adjugate[0][col] * matrix[0][col];

		return determinant;
	}
}


//Using the Cofactor method, which is not very efficent but is the one i know :v
Matrix Matrix::get_adjugate() const
{
	if (rows != columns)
		throw std::exception("Not a squared matrix");
	else
	{
		Matrix adjugate(rows, columns);

		for (auto a_row = 0; a_row < rows; a_row++) 
		{
			for (auto a_col = 0; a_col < columns; a_col++)
			{
				Matrix cofactor(rows - 1, columns - 1);

				int c_row = 0;
				for (auto row = 0; row < rows; row++)
				{
					if (row == a_row) continue;

					int c_col = 0;
					for (auto col = 0; col < columns; col++)
					{
						if (col == a_col) continue;

						cofactor[c_row][c_col] = matrix[row][col];
						c_col++;
					}
					c_row++;
				}
				adjugate[a_row][a_col] = pow(-1,a_row+a_col)*cofactor.get_determinant();
			}
		}
		return adjugate;
	}
}

Matrix Matrix::get_transpose() const
{
	Matrix transpose(columns, rows);

	for (auto col = 0; col < rows; col++)
		for (auto row = 0; row < columns; row++)
			transpose[row][col] = matrix[col][row];

	return transpose;
}

Matrix Matrix::get_inverse() const
{
	return (get_transpose() * (1 / get_determinant()));
}

