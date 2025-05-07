#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <stack>

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

    void ordenar() {
        sort(valor.begin(), valor.end(), [](const T& a, const T& b) {
            return a.esPremium() > b.esPremium();
            });
    }

    void eliminarPorCorreo(const string& correo) {
        auto it = std::find_if(valor.begin(), valor.end(), [&correo](const T& usuario) {
            return usuario.getCliente().get_correo() == correo;
            });

        if (it != valor.end()) {
            valor.erase(it);
            cout << "Usuario eliminado correctamente.\n";
        }
        else {
            cout << "Usuario no encontrado.\n";
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

    void guardarArchivo(ofstream& archivo) const {
        for (const auto& elemento : valor) {
            archivo << elemento.serializarUsuario() << endl;
        }
    }
};