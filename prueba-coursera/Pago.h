#pragma once
#include "Curso.h"
#include "Cliente.h"
#include <sstream>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

template <typename T>
class Pago {
private:
	string _metodoPago;
	Cliente<T> pCliente;
	Curso<T> pCurso;
public:
	Pago(const string& metodoPago, const string& monto, const Cliente<T>& cliente, const Curso<T>& curso) 
		: _metodoPago(metodoPago), _montoTotal(monto), pCliente(cliente), pCurso(curso) {}


	string get_MetodoPago() const { return _metodoPago; }

	string SerializarPago() const {
		stringstream ss;
		ss << pCliente.get_correo() << "," << pCurso.get_CodigoCurso() << "," << pCurso.get_NombreCurso() << ","
			<< pCurso.get_Certificado() << "," << pCurso.get_Categoria << "," << pCurso.get_Duracion() << ","
			<< pCurso.get_Precio() << "," << _metodoPago ;
		return ss.str();
	}

	void mostrarPagos() const {
		cout << "\nUsuario: " << pCliente.get_correo()
			<< pCurso.mostrarCurso()
			<< "\n| Tipo Pago: " << _metodoPago << endl;
	}


};

