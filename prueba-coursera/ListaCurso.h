#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <stack>
#include <queue>

using namespace std;

template <typename T>
class ListaCurso {
private:
    vector<T> cursos;
public:
    void agregar(const T& curso) {
        cursos.push_back(curso);
    }

    void mostrar() const {
        for (const auto& curso : cursos) {
            curso.mostrarCurso();
        }
    }

    void ordenarPorPrecio() {
        sort(cursos.begin(), cursos.end(), [](const T& a, const T& b) {
            return a.get_Precio() < b.get_Precio();
            });
    }

    void buscarPorCategoria(const string& cat) const {
        stack<T> pila;
        for (const auto& curso : cursos) {
            if (curso.get_Categoria() == cat) pila.push(curso);
        }
        while (!pila.empty()) {
            pila.top().mostrarCurso();
            pila.pop();
        }
    }

    void buscarPorPrecio(double maxPrecio) const {
        queue<T> cola;
        for (const auto& curso : cursos) {
            if (curso.get_Precio() <= maxPrecio) cola.push(curso);
        }
        while (!cola.empty()) {
            cola.front().mostrarCurso();
            cola.pop();
        }
    }

    void guardarArchivo(ofstream& archivo) const {
        for (const auto& curso : cursos) {
            curso.guardarArchivo(archivo);
        }
    }

    void cargarDesdeArchivo(const string& nombreArchivo) {
        ifstream archivo(nombreArchivo);
        if (!archivo.is_open()) {
            cout << "Error al abrir archivo.\n";
            return;
        }

        string linea;
        while (getline(archivo, linea)) {
            cursos.push_back(T::cargarDesdeLineaCu(linea));
        }
        archivo.close();
    }
};
