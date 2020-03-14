/*
 * Sudoku.cpp
 *
 */

#include <vector>
#include "Sudoku.h"





/** Inicia um Sudoku vazio.
 */
Sudoku::Sudoku()
{
	this->initialize();
}

/**
 * Inicia um Sudoku com um conte�do inicial.
 * Lan�a excep��o IllegalArgumentException se os valores
 * estiverem fora da gama de 1 a 9 ou se existirem n�meros repetidos
 * por linha, coluna ou bloc 3x3.
 *
 * @param nums matriz com os valores iniciais (0 significa por preencher)
 */
Sudoku::Sudoku(int nums[9][9])
{
	this->initialize();

	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			if (nums[i][j] != 0)
			{
				int n = nums[i][j];
				numbers[i][j] = n;
				lineHasNumber[i][n] = true;
				columnHasNumber[j][n] = true;
				block3x3HasNumber[i / 3][j / 3][n] = true;
				countFilled++;
				initial++;
			}
		}
	}
}

void Sudoku::initialize()
{
    solutions = 0;
    initial = 0;
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			for (int n = 0; n < 10; n++)
			{
				numbers[i][j] = 0;
				lineHasNumber[i][n] = false;
				columnHasNumber[j][n] = false;
				block3x3HasNumber[i / 3][j / 3][n] = false;
			}
		}
	}

	this->countFilled = 0;
}

/**
 * Obtem o conte�do actual (s� para leitura!).
 */
int** Sudoku::getNumbers()
{
	int** ret = new int*[9];

	for (int i = 0; i < 9; i++)
	{
		ret[i] = new int[9];

		for (int a = 0; a < 9; a++)
			ret[i][a] = numbers[i][a];
	}

	return ret;
}

/**
 * Verifica se o Sudoku j� est� completamente resolvido
 */
bool Sudoku::isComplete()
{
	return countFilled == 9 * 9;
}



/**
 * Resolve o Sudoku.
 * Retorna indica��o de sucesso ou insucesso (sudoku imposs�vel).
 */
bool Sudoku::solve() {
    if (isComplete()){
        print();
        return true;
    }
    for (int i = 0; i < 9; i++){
        for (int j = 0; j < 9; j++) {
            if (numbers[i][j] == 0) {
                for (int n = 1; n < 10; n++) {
                    if (!columnHasNumber[j][n] && !lineHasNumber[i][n] && !block3x3HasNumber[i/3][j/3][n]) {
                        numbers[i][j] = n;
                        countFilled++;
                        columnHasNumber[j][n] = true;
                        lineHasNumber[i][n] = true;
                        block3x3HasNumber[i/3][j/3][n] = true;
                        bool solved = solve();
                        if (solved)
                            return true;
                        else {
                            numbers[i][j] = 0;
                            countFilled--;
                            columnHasNumber[j][n] = false;
                            lineHasNumber[i][n] = false;
                            block3x3HasNumber[i/3][j/3][n] = false;
                        }
                    }
                }
                return false;
            }
        }
    }
    return isComplete();
}


bool Sudoku::solve2() {
    if (isComplete()){
        solutions++;
        return true;
    }
    for (int i = 0; i < 9; i++){
        for (int j = 0; j < 9; j++) {
            if (numbers[i][j] == 0) {
                for (int n = 1; n < 10; n++) {
                    if (!columnHasNumber[j][n] && !lineHasNumber[i][n] && !block3x3HasNumber[i/3][j/3][n]) {
                        numbers[i][j] = n;
                        countFilled++;
                        columnHasNumber[j][n] = true;
                        lineHasNumber[i][n] = true;
                        block3x3HasNumber[i/3][j/3][n] = true;
                        solve2();
                        numbers[i][j] = 0;
                        countFilled--;
                        columnHasNumber[j][n] = false;
                        lineHasNumber[i][n] = false;
                        block3x3HasNumber[i / 3][j / 3][n] = false;
                    }
                }
                if (countFilled == initial) {
                    cout << "No of solutions: " << solutions << endl;
                    return solutions > 0;
                } else {
                    return false;
                }
            }
        }
    }
    //cout << solutions << endl;
    return true;
}

bool Sudoku::solve3() {
    if (isComplete()){
        solutions++;
        return true;
    }
    for (int i = 0; i < 9; i++){
        for (int j = 0; j < 9; j++) {
            if (numbers[i][j] == 0) {
                for (int n = 1; n < 10; n++) {
                    if (!columnHasNumber[j][n] && !lineHasNumber[i][n] && !block3x3HasNumber[i/3][j/3][n]) {
                        numbers[i][j] = n;
                        countFilled++;
                        columnHasNumber[j][n] = true;
                        lineHasNumber[i][n] = true;
                        block3x3HasNumber[i/3][j/3][n] = true;
                        solve3();
                        if(solutions > 1)
                            return false;
                        numbers[i][j] = 0;
                        countFilled--;
                        columnHasNumber[j][n] = false;
                        lineHasNumber[i][n] = false;
                        block3x3HasNumber[i / 3][j / 3][n] = false;
                    }
                }
                if (countFilled == initial) {
                    cout << "No of solutions: " << solutions << endl;
                    return solutions > 0;
                } else {
                    return false;
                }
            }
        }
    }
    //cout << solutions << endl;
    return true;
}

bool Sudoku::generateSudoku() {
    this->initialize();
    int** ret = new int*[9];

    for (int i = 0; i < 9; i++)
    {
        ret[i] = new int[9];
        for (int j = 0; j < 9; j++)
            ret[i][j] = 0;
    }
    if(generate(ret)) {
        for (int a = 0; a < 9; a++) {
            for (int b = 0; b < 9; b++) {
                int n = ret[a][b];
                numbers[a][b] = n;
                if (n != 0) {
                    lineHasNumber[a][n] = true;
                    columnHasNumber[b][n] = true;
                    block3x3HasNumber[a / 3][b / 3][n] = true;
                    countFilled++;
                    initial++;
                }
            }
        }
        return true;
    } else
        return false;
}

bool generate(int** array) {
    int numbers[9][9];
    for (int a = 0; a < 9; a++)
    {
        for (int b = 0; b < 9; b++)
            numbers[a][b] = array[a][b];
    }
    Sudoku s(numbers);
    srand(time(NULL));
    bool found = false;
    int i, j, n;
    while(!found) {
        i = rand() % 9;
        j = rand() % 9;
        n = rand() % 9 + 1;
        found = s.canFill(i, j, n);
    }
    s.insert(i, j, n);
    s.solve3();
    int sol = s.getSolutions();
    if(sol == 1) {
        array[i][j] = n;
        return true;
    } else if(sol == 0) {
        return generate(array);
    } else {
        array[i][j] = n;
        return generate(array);
    }
}

bool Sudoku::canFill(int line, int col, int num) {
    return (numbers[line][col] == 0) && !lineHasNumber[line][num] && !columnHasNumber[col][num] && !block3x3HasNumber[line/3][col/3][num];
}

void Sudoku::insert(int line, int col, int num) {
    numbers[line][col] = num;
    countFilled++;
    initial++;
    columnHasNumber[col][num] = true;
    lineHasNumber[line][num] = true;
    block3x3HasNumber[line/3][col/3][num] = true;

}

int Sudoku::getSolutions() {
    return solutions;
}

/**
 * Imprime o Sudoku.
 */
void Sudoku::print()
{
	for (int i = 0; i < 9; i++)
	{
		for (int a = 0; a < 9; a++)
			cout << this->numbers[i][a] << " ";

		cout << endl;
	}
}

