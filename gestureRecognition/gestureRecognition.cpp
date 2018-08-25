#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

struct dato {
	string clase;
	vector<vector<int>> valores;
};

struct sigma {
	string clase;
	vector<int> valor;
};

vector<dato> readCSV(string ruta); //Lee el archivo de excel con extension csv. Regresa un vector con los valores de EMG
void printVector(vector<dato> raws); //Funcion para imprimir el vector de vectores
vector<dato> changeType(vector<vector<string>> raws); //Recibe un vector con vectores de cadenas para regresar un vector con vectores de enteros
vector<sigma> standardDeviation(vector<dato> vals); //Funcion para calcular la desviacion estandar de el vector con vectores de enteros, regresa los valores de sigma en un vector de enteros

int main(){
	vector<dato> vals;
	vector<int> sigma;
	vals = readCSV("excel/valores-final.csv");
	//sigma = standardDeviation(vals);
	return 0;
}

vector<dato> readCSV(string ruta) {
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

void printVector(vector<dato> raws){
	for (int i = 0; i < raws.size(); i++) {
		cout << raws[i].clase << endl;
		for (int j = 0; j < raws[i].valores.size(); j++) {
			for (int k = 0; k < raws[i].valores[j].size(); k++) {
				cout << raws[i].valores[j][k] << '\t';
			}
			cout << endl;
		}
		cout << endl;
	}
}

vector<dato> changeType(vector<vector<string>> raws) {
	vector<dato> vals;
	vector<int> val;
	dato aux;
	int x = 0;
	bool in;
	for (int i = 1; i < raws.size(); i++) {
		in = false;
		if (vals.size() == 0) {
			for (int j = 0; j < raws[i].size() - 1; j++) {
				stringstream stream(raws[i][j]);
				stream >> x;
				val.push_back(x);
			}
			aux.clase = raws[i][raws[i].size() - 1];
			aux.valores.push_back(val);
			vals.push_back(aux);
			val.clear();
		}
		else {
			for (int j = 0; j < raws[i].size() - 1; j++) {
				stringstream stream(raws[i][j]);
				stream >> x;
				val.push_back(x);
			}
			for (int j = 0; j < vals.size(); j++) {
				if (vals[j].clase == raws[i][raws[i].size() - 1]) {
					vals[j].valores.push_back(val);
					val.clear();
					in = true;
					break;
				}
			}
			if (in == false) {
				aux.clase = raws[i][raws[i].size() - 1];
				aux.valores.push_back(val);
				vals.push_back(aux);
				val.clear();
			}
		}
	}
	return vals;
}

/*vector<int> standardDeviation(vector<vector<int>> vals) {
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
}*/

/*vector<sigma> standardDeviation(vector<dato> vals) {
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
}*/