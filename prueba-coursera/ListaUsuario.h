#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <stack>
#include <algorithm>

using namespace std;

template <typename T>
class ListaUsuario {
private:
    vector<T> valor;
public:

    void agregar(const T& elemento) {
        valor.push_back(elemento);
    }

    void mostrar() const {
        for (const auto& elemento : valor) {
            elemento.mostrar(); 
        }
    }

    void ordenarPremium() {
        sort(valor.begin(), valor.end(), [](const T& a, const T& b) {
            if (a.get_Premium() == b.get_Premium()) {
                return a.getCliente().get_nombreCompleto() < b.getCliente().get_nombreCompleto();
            }
            return a.get_Premium() > b.get_Premium();
            });
    }

    bool eliminarPorCorreo(const string& correo) {
        auto it = find_if(valor.begin(), valor.end(), [&correo](const T& usuario) {
            return usuario.getCliente().get_correo() == correo;
            });
        if (it != valor.end()) {
            valor.erase(it);
            cout << "Usuario eliminado correctamente.\n";
            return true;
        }
        else {
            cout << "Usuario no encontrado.\n";
            return false;
        }
    }

    bool existeCorreo(const string& correo) const {
        for (const auto& elemento : valor) {
            if (elemento.getCliente().get_correo() == correo) {
                return true;
            }
        }
        return false;
    }

    void guardarArchivo(ofstream& archivo, ios::app) const {
        for (const auto& elemento : valor) {
            archivo << elemento.serializarUsuario() << endl;
        }
    }
};