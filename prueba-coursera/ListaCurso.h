#pragma once
#include <algorithm>
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
	// agregar cursos
    void agregar(const T& curso) {
        cursos.push_back(curso);
    }

	// mostrar cursos
    void mostrar() const {
        for (const auto& curso : cursos) {
            curso.mostrarCurso();
        }
    }

	// ordenar cursos por precio
    void ordenarPorPrecio() {
        sort(cursos.begin(), cursos.end(), [](const T& a, const T& b) {
            return a.get_Precio() < b.get_Precio();
            });
    }

	// buscar curso por categoria con impresión
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

    // buscar curso por precio con impresión ordenada
    void buscarYOrdenarPorPrecio(double maxPrecio) const {
        vector<T> ordenaPrecio;

        // Se busca los cursos por precio menor o igual al máximo
        for (const auto& curso : cursos) {
            if (curso.get_Precio() <= maxPrecio) {
                ordenaPrecio.push_back(curso);
            }
        }

        // Ordenar los cursos por precio de mayor a menor
        sort(ordenaPrecio.begin(), ordenaPrecio.end(), [](const T& a, const T& b) {
            return a.get_Precio() > b.get_Precio();
            });

        // Muestra los cursos ordenados
        for (const auto& curso : ordenaPrecio) {
            curso.mostrarCurso();
        }
    }

    // buscar curso por código con impresión
    void buscarYMostrarPorCodigo(int codigoBuscado) const {
        bool encontrado = false;
        for (const auto& curso : cursos) {
            if (curso.get_CodigoCurso() == codigoBuscado) {
                cout << "\nCurso encontrado:\n";
                curso.mostrarCurso();
                encontrado = true;
                break;
            }
        }

        if (!encontrado) {
            cout << "\nCurso con código " << codigoBuscado << " no encontrado.\n";
        }
    }

    // Devuelve puntero al curso si existe, para selección o edición
    T* existeCodigo(int codigo) {
        for (auto& curso : cursos) {
            if (curso.get_CodigoCurso() == codigo) {
                return &curso;
            }
        }
        return nullptr;
    }

	// Cargar cursos desde archivo
    void guardarArchivo(ofstream& archivo) const {
        for (const auto& curso : cursos) {
            curso.guardarArchivo(archivo);
        }
    }

    // Extra: obtener lista de cursos por referencia para boleta
    const vector<T>& obtenerCursos() const {
        return cursos;
    }
};
