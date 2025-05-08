#include <iostream>
#include <fstream>
#include <limits>
#include "ListaCurso.h"
#include "ListaUsuario.h"
using namespace std;

// Clase Plataforma con templates, lambdas y recursividad

template <typename T>
class Plataforma {
private:
    ListaCurso<Curso<T>> listaCursos;
    ListaUsuario<Usuario<T>> listaUsuarios;

public:
    void cargarCursosDesdeArchivo(const string& nombreArchivo) {
        ifstream archivo(nombreArchivo);
        if (!archivo.is_open()) {
            cout << "No se pudo abrir el archivo de cursos.\n";
            return;
        }
        cargarCursosRecursivo(archivo);
        archivo.close();
    }

    void cargarUsuariosDesdeArchivo(const string& nombreArchivo) {
        ifstream archivo(nombreArchivo);
        if (!archivo.is_open()) {
            cout << "No se pudo abrir el archivo de usuarios.\n";
            return;
        }
        cargarUsuariosRecursivo(archivo);
        archivo.close();
    }

    void buscarCursosPorPrecio(double precioMax) {
        listaCursos.filtrarCursos([precioMax](const Curso<T>& c) {
            return c.get_precio() <= precioMax;
            });
    }

    void buscarCursosPorCategoria(const string& categoria) {
        listaCursos.filtrarCursos([categoria](const Curso<T>& c) {
            return c.get_categoria() == categoria;
            });
    }

    void mostrarCursos() {
        cout << "\n--- Cursos Registrados ---\n";
        mostrarCursosRecursivo(listaCursos.getCabeza());
    }

    void mostrarUsuariosPremium() {
        listaUsuarios.ordenarPremium();
        listaUsuarios.mostrar();
    }

    void agregarCurso(const Curso<T>& curso) {
        listaCursos.agregar(curso);
    }

    void agregarUsuario(const Usuario<T>& usuario) {
        listaUsuarios.agregar(usuario);
    }

private:
    void cargarCursosRecursivo(ifstream& archivo) {
        string linea;
        if (getline(archivo, linea)) {
            Curso<T> curso = Curso<T>::cargarDesdeLineaCu(linea);
            if (!listaCursos.existeCodigo(to_string(curso.get_CodigoCurso())))
                listaCursos.agregar(curso);
            cargarCursosRecursivo(archivo);
        }
    }

    void cargarUsuariosRecursivo(ifstream& archivo) {
        string linea;
        if (getline(archivo, linea)) {
            Usuario<T> usuario = Usuario<T>::cargarDesdeLineaUs(linea);
            if (!listaUsuarios.existeCorreo(usuario.getCliente().get_correo()))
                listaUsuarios.agregar(usuario);
            cargarUsuariosRecursivo(archivo);
        }
    }

    void mostrarCursosRecursivo(Nodo<Curso<T>>* nodo) {
        if (nodo != nullptr) {
            nodo->getValor().mostrarCurso();
            mostrarCursosRecursivo(nodo->getSiguiente());
        }
    }
};

// Menú principal de plataforma
void menuPlataforma() {
    cout << "\n===== MENU PLATAFORMA =====\n";
    cout << "1. Cargar Usuarios desde archivo\n";
    cout << "2. Cargar Cursos desde archivo\n";
    cout << "3. Mostrar Cursos\n";
    cout << "4. Buscar Cursos por Categoría\n";
    cout << "5. Buscar Cursos por Precio\n";
    cout << "6. Mostrar Usuarios Premium\n";
    cout << "7. Salir\n";
    cout << "Seleccione una opción: ";
}

int main() {
    Plataforma<string> plataforma;
    int opcion;

    do {
        menuPlataforma();
        while (!(cin >> opcion)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "\nEntrada invalida. Ingrese un número: ";
        }
        cin.ignore();

        switch (opcion) {
        case 1:
            plataforma.cargarUsuariosDesdeArchivo("usuarios.txt");
            break;
        case 2:
            plataforma.cargarCursosDesdeArchivo("cursos.txt");
            break;
        case 3:
            plataforma.mostrarCursos();
            break;
        case 4: {
            string categoria;
            cout << "Ingrese la categoría: ";
            getline(cin, categoria);
            plataforma.buscarCursosPorCategoria(categoria);
            break;
        }
        case 5: {
            double precio;
            cout << "Ingrese el precio máximo: ";
            while (!(cin >> precio)) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Entrada invalida. Ingrese un número: ";
            }
            cin.ignore();
            plataforma.buscarCursosPorPrecio(precio);
            break;
        }
        case 6:
            plataforma.mostrarUsuariosPremium();
            break;
        case 7:
            cout << "\nSaliendo del programa...\n";
            break;
        default:
            cout << "\nOpción no válida. Intente nuevamente.\n";
        }

    } while (opcion != 7);

    return 0;
}
