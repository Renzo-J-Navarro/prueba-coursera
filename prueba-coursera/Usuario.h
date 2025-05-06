#pragma once
#include "Cliente.h"
#include <iostream>

template <typename T>
class Usuario {
private:
    Cliente<T> _cliente;
public:
    Usuario(const Cliente<T>& cliente)
        : _cliente(cliente) {
    }

    Cliente<T> getCliente() const { return _cliente; }

    bool esPremium() const { return _cliente.get_premium(); }

    string serializarUsuario() const {
        stringstream ss;
        ss << _cliente.get_nombreCompleto() << "," << _cliente.get_Profesion() << ","
            << _cliente.get_correo() << "," << _cliente.get_contraseña() << ","
            << _cliente.get_telefono() << "," << (_cliente.get_premium() ? "1" : "0");
        return ss.str();
    }

    void mostrar() const {
        cout << "\nID del Usuario: " << _cliente.get_correo() << endl;
        _cliente.mostrarCliente();
    }

};
