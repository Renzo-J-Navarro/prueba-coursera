#pragma once
#include "Cliente.h"
#include "Curso.h"
#include <iostream>
#include <fstream>
#include <sstream>

template <typename T>
class Usuario {
private:
    Cliente<T> _cliente;
	bool _premium;
public:
    Usuario(const Cliente<T>& cliente, bool premium = false)
        : _cliente(cliente), _premium(premium) {
    }

    //getters
    const Cliente<T>& getCliente() const { return _cliente; }
    bool get_Premium() const { return _premium; }
    //setters
	void set_Premiun(bool premium) { _premium = premium; }
    //metodos
    string serializarUsuario() const {
        stringstream ss;
        ss << _cliente.get_nombreCompleto() << ","
            << _cliente.get_Profesion() << ","
            << _cliente.get_correo() << ","
            << _cliente.get_contraseña() << ","
            << _cliente.get_telefono() << ","
            << (_premium ? "1" : "0");
        return ss.str();
    }

    static Usuario<T> cargarDesdeLineaUs(const string& linea) {
        string nombre, profesion, correo, contra, telefono, premiumStr;
        stringstream ss(linea);
        getline(ss, nombre, ',');
        getline(ss, profesion, ',');
        getline(ss, correo, ',');
        getline(ss, contra, ',');
        getline(ss, telefono, ',');
        getline(ss, premiumStr, ',');
        Cliente<T> cliente(nombre, profesion, correo, contra, telefono);
        bool premium = (premiumStr == "1" || premiumStr == "true");
        return Usuario<T>(cliente, premium);
    }
    void mostrarUsuario() const {
        cout << "\nID del Usuario: " << _cliente.get_correo() << endl;
        _cliente.mostrarCliente();
		cout << "Premium: " << (_premium ? "Pendiente" : "No Tiene") << endl;
    }
    // 
    void agregarCursoCompletado(const Curso<T>& curso) {
        _cursosCompletados.push_back(curso);
    }
};
