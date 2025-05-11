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
	T _metodoPago;
	Cliente<string> pcliente;
	string _detallePago;
	float _monto;

public:
	// Constructor por defecto
	Pago(const T& metodoPago = "N/A")
		: _metodoPago(metodoPago), _detallePago(""), _monto(0.0) {
	}

	// Constructor con datos completos
	Pago(const T& metodoPago, const Cliente<string>& cliente, const string& detallePago, float monto)
		: _metodoPago(metodoPago), pcliente(cliente), _detallePago(detallePago), _monto(monto) {
	}

	// Getters
	T get_MetodoPago() const { return _metodoPago; }
	string get_DetallePago() const { return _detallePago; }
	float get_Monto() const { return _monto; }
	Cliente<string> getpcliente() const { return pcliente; }

	// Setters
	void set_MetodoPago(const T& metodoPago) { _metodoPago = metodoPago; }
	void set_DetallePago(const string& detalle) { _detallePago = detalle; }
	void set_Monto(float monto) { _monto = monto; }

	// Serializar pago como string
	string SerializarPago() const {
		stringstream ss;
		ss << "Cliente: " << pcliente.get_nombreCompleto() << ", "
			<< "Correo: " << pcliente.get_correo() << ", "
			<< "Detalle: " << _detallePago << ", "
			<< "Monto: $" << _monto << ", "
			<< "Pago via: " << _metodoPago;
		return ss.str();
	}

	// Guardar pago en archivo
	void guardarEnArchivo(const string& ruta) const {
		ofstream file(ruta, ios::app);
		if (file.is_open()) {
			file << SerializarPago() << endl;
			file.close();
		}
	}
};
