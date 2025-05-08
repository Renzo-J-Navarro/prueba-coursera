#pragma once
#include <iostream>
#include <algorithm>
#include <fstream>
#include <sstream>	

using namespace std;

template <typename T>
class Curso {
private:
	int _codigoCurso;
	string _nombreCurso;
	bool _certificado;
	string _categoria;
	string _duracion;
	double _precio;
public:

	Curso(int codigoCurso, const string& nombreCurso = "N/A", bool certificado = false
		, const string& categoria = "N/A", const string& duracion = "N/A", double precio = 0)
		: _codigoCurso(codigoCurso), _nombreCurso(nombreCurso), _certificado(certificado), _categoria(categoria),
		_duracion(duracion), _precio(precio) {
	}
	//getters
	int get_CodigoCurso() const { return _codigoCurso; }
	string get_NombreCurso() const { return _nombreCurso; }
	bool get_Certificado() const { return _certificado; }
	string get_Categoria() const { return _categoria; }
	string get_Duracion() const { return _duracion; }
	double get_Precio() const { return _precio; }
	//setters
	void set_CodigoCurso(int codigoCurso) { _codigoCurso = codigoCurso; }
	void set_NombreCurso(const string& nombreCurso) { _nombreCurso = nombreCurso; }
	void set_Certificado(bool certificado) { _certificado = certificado; }
	void set_Categoria(const string& categoria) { _categoria = categoria; }
	void set_Duracion(const string& duracion) { _duracion = duracion; }
	void set_Precio(double precio) { _precio = precio; }
	//metodos
	void mostrarCurso() const {
		// codigo, nombre, certificado, categoria, duracion, precio 
		cout << "[" << _codigoCurso << "] " << _nombreCurso << " | Certificado: " << (_certificado ? "Pendiente" : "No") 
			<< " | " << _categoria << " | " << _duracion << " | $" << _precio << endl;
	}
	void guardarArchivo(ofstream& archivo) const {
		archivo << _codigoCurso << "," << _nombreCurso << "," << _certificado << "," << _categoria << ","
			<< _duracion << "," << _precio << endl;
	}

	string serializarCurso() const {
		stringstream ss;
		ss << _codigoCurso << "," << _nombreCurso << "," << _certificado << "," << _categoria << "," << _duracion << ","
			<< _precio << endl;
		return ss.str();
	}

	static Curso<T> cargarDesdeLineaCu(const string& linea) {
		string codigoS, nombre, certificadoS, categoria, duracion, precioS;
		stringstream ss(linea);
		getline(ss,codigoS,',');	
		getline(ss,nombre,',');
		getline(ss,certificadoS,',');
		getline(ss,categoria,',');
		getline(ss,duracion,',');
		getline(ss,precioS,',');
		int codigo = stoi(codigoS);
		double precio = stod(precioS);
		bool certificado = (certificadoS == "1" || certificadoS == "true");
		return Curso<T>(codigo, nombre, certificado, categoria, duracion, precio);
	}

};

