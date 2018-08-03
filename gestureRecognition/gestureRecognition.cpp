#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

vector<vector<int> > readCSV(string ruta); //Lee el archivo de excel con extension csv. Regresa un vector con los valores de EMG
void printVector(vector<vector<int>> raws); //Funcion para imprimir el vector de vectores
vector<vector<int>> changeType(vector<vector<string>> raws); //Recibe un vector con vectores de cadenas para regresar un vector con vectores de enteros
vector<int> standardDeviation(vector<vector<int>> vals); //Funcion para calcular la desviacion estandar de el vector con vectores de enteros, regresa los valores de sigma en un vector de enteros

int main(){
	vector<vector<int>> vals;
	vector<int> sigma;
	vals = readCSV("excel/valores-final.csv");
	printVector(vals);
	sigma = standardDeviation(vals);
	return 0;
}

vector<vector<int> > readCSV(string ruta) {
	ifstream  data(ruta);
	vector<string> raw;
	vector<vector<string> > raws;

	string line;
	while (getline(data, line))
	{
		stringstream  lineStream(line);
		string        cell;
		while (getline(lineStream, cell, ','))
		{
			raw.push_back(cell);

		}
		raws.push_back(raw);
		raw.clear();
	}
	return changeType(raws);
}

void printVector(vector<vector<int>> raws){
	for (int i = 0; i < raws.size(); i++) {
		for (int j = 0; j < raws[i].size(); j++) {
			cout << raws[i][j] << '\t';
		}
		cout << endl;
	}
}

vector<vector<int>> changeType(vector<vector<string>> raws) {
	vector<vector<int>> vals;
	vector<int> val;
	int x = 0;
	for (int i = 1; i < raws.size(); i++) {
		for (int j = 0; j < raws[i].size()-1; j++) {
			stringstream geek(raws[i][j]);
			geek >> x;
			val.push_back(x);
		}
		vals.push_back(val);
		val.clear();
	}
	return vals;
}

vector<int> standardDeviation(vector<vector<int>> vals) {
	int sigma[8] = { 0 };
	vector<int> SIGMA;
	for (int i = 0; i < vals.size(); i++) {
		for (int j = 0; j < vals[i].size(); j++) {
			sigma[j] = sigma[j] + vals[i][j];
		}
	}
	for (int i = 0; i < 8; i++) {
		cout << sigma[i] << endl;
		SIGMA.push_back(sigma[i]);
	}
	return SIGMA;
}