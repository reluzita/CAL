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
    return this->generate();
}

bool Sudoku::generate() {
    srand(time(NULL));
    bool found = false;
    int i, j, n;
    while(!found) {
        i = rand() % 9;
        j = rand() % 9;
        n = rand() % 9 + 1;
        if(numbers[i][j] == 0 && !columnHasNumber[j][n] && !lineHasNumber[i][n] && !block3x3HasNumber[i/3][j/3][n])
            found = true;
    }
    numbers[i][j] = n;
    countFilled++;
    initial++;
    columnHasNumber[j][n] = true;
    lineHasNumber[i][n] = true;
    block3x3HasNumber[i / 3][j / 3][n] = true;

    int numTemp[9][9];
    for (int l = 0; l < 9; l++)
    {
        for (int c = 0; c < 9; c++)
        {
            int m = numbers[l][c];
            numTemp[l][c] = m;
        }
    }

    solutions = 0;
    solve3();

    countFilled = 0;
    initial = 0;
    for (int l = 0; l < 9; l++)
    {
        for(int c = 1; c < 10; c++) {
            lineHasNumber[l][c] = false;
            columnHasNumber[l][c] = false;
            for(int b = 0; b < 3; b++) {
                block3x3HasNumber[l / 3][b][c] = false;
            }
        }

        for (int c = 0; c < 9; c++)
        {
            int m = numTemp[l][c];
            numbers[l][c] = m;
            if (m != 0) {
                countFilled++;
                initial++;
                lineHasNumber[l][m] = true;
                columnHasNumber[c][m] = true;
                block3x3HasNumber[l / 3][c / 3][m] = true;
            }
        }

    }

    if(solutions == 0) {
        numbers[i][j] = 0;
        countFilled--;
        columnHasNumber[j][n] = false;
        lineHasNumber[i][n] = false;
        block3x3HasNumber[i/3][j/3][n] = false;
        generate();
    } else if( solutions == 1 )
        return true;
    else {
        print();
        cout << endl;
        generate();
    }
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

