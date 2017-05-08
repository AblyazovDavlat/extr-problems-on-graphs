// extr-problems-on-graphs.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include "time.h"
#include <string>

using namespace std;

void searchEulerCycle(int vertex,vector < vector < int > > D, vector < int > &cycle)
{
	for (int i = 0; i < D[vertex].size(); ++i)
		if (D[vertex][i]) // если ребро есть
		{
			// проходим по нему
			D[vertex][i] = 0;
			D[i][vertex] = 0;
			searchEulerCycle(i, D, cycle);
		}
	cycle.push_back(vertex);
}
void countDegreeVertex(const vector <vector<int>> &D, vector <int> &degree)
{
	int n = D.size();
	degree.clear();
	degree.resize(n);

	for (int i = 0; i < n; ++i)
		for (int j = 0; j < n; ++j)
			if (D[i][j])
				++degree[i];
}
bool checkCycle(const vector<int> &degree)
{
	for (int i = 0; i < degree.size(); i++)
	{
		if (degree[i] % 2 != 0)
		{
			return false;
		}
	}
	return true;
}
void buldingLineGrapgh(const vector <vector<int>> &D, vector <vector<int>> &LG,vector<vector<int>> &vertexVector)
{
	//вычисление количества и построение множества вершин в реберном графе
	int m = 0;  
	for (int i = 0; i < D[0].size(); ++i)
		for (int j = i+1; j < D[0].size(); ++j)
		{
			if (D[i][j])
			{
				vertexVector[0].push_back(i);
				vertexVector[1].push_back(j);
			}
		}
	m = vertexVector[0].size();
	
	LG.resize(m);
	for (int i = 0; i < m; ++i) LG[i].resize(m);
	
	//матрица смежности для реберного графа
	for (int i = 0; i < m; ++i)
		for (int j = i + 1; j < m; ++j)
		{
			if (vertexVector[0][i] == vertexVector[0][j] || vertexVector[0][i] == vertexVector[1][j] ||
				vertexVector[1][i] == vertexVector[0][j] || vertexVector[1][i] == vertexVector[1][j])
				LG[i][j] = 1;
			else LG[i][j] = 0;
		}
	for (int i = 0; i < m; ++i)
		for (int j = i; j < m; ++j)
		{
			LG[i][i] = 0;
			LG[j][i] = LG[i][j];
		}
}


int _tmain(int argc, _TCHAR* argv[])
{
	vector<vector<int>> AdjMatrixG(5);
	vector<vector<int>> AdjMatrixLG;
	vector<vector<int>> vertexVectorLG(2);
	vector<int> degree(5);
	vector<int> cycle;

	AdjMatrixG[0] = { 0, 1, 1, 1, 0 };
	AdjMatrixG[1] = { 1, 0, 0, 0, 1 };
	AdjMatrixG[2] = { 1, 0, 0, 1, 0 };
	AdjMatrixG[3] = { 1, 0, 1, 0, 1 };
	AdjMatrixG[4] = { 0, 1, 0, 1, 0 };

	for (int i = 0; i < 5; ++i){
		for (int j = 0; j < 5; ++j)
			cout << AdjMatrixG[i][j] << ' ';
		cout << endl;
	}
	cout << endl;

	buldingLineGrapgh(AdjMatrixG, AdjMatrixLG, vertexVectorLG);

	for (int i = 0; i < 6; ++i){
		cout <<'('<< vertexVectorLG[0][i] << ',' << vertexVectorLG[1][i] <<')'<<' ';
		for (int j = 0; j < 6; ++j)
			cout << AdjMatrixLG[i][j] << ' ';
		cout << endl;
	}

	countDegreeVertex(AdjMatrixG, degree);
	if (checkCycle(degree))
		searchEulerCycle(0, AdjMatrixG, cycle);

	for (int i = 0; i != cycle.size(); i++)
	{
	cout << cycle[i] << endl;
	}

	return 0;
}

