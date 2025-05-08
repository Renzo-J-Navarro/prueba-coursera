#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
#include <conio.h>
#include <limits>

#include "Curso.h"
#include "Usuario.h"
#include "Boleta.h"
#include "ListaCurso.h"
#include "ListaUsuario.h"
using namespace std;

//Menu de acciones para el usuario
static void menuCurso() {
    cout << "\n\t---* Biblioteca de Cursos *---\n";
    cout << "1. Mostrar todos los Cursos" << endl;
    cout << "2. Listar cursos por su Precio" << endl;
    cout << "3. Buscar Cursos por Categoria" << endl;
    cout << "4. Buscar Cursos por Precio" << endl;
    cout << "5. Salir" << endl;
    cout << "Seleccione una opcion: ";
}
static void menuUsuario() {
    cout << "\n\t---* Que deseas hacer hoy ? *---\n";
    cout << "1. Ver catalago de Cursos" << endl;
    cout << "2. Comprar Cursos y Certificados" << endl;
    cout << "3. Mostrar Compras Realizadas" << endl;
    cout << "4. Ver estado Premium" << endl;
    cout << "5. Elimar Cuenta Usuario" << endl;
	cout << "6. Salir" << endl;
    cout << "Seleccione una opcion: ";
}
static void menuPlataforma() {
    cout << "\n\t===*=== MENU PLATAFORMA ===*===\n";
    cout << "1. Crear Usuario." << endl;
    cout << "2. Eliminar Usuario." << endl;
    cout << "3. Completar Pagos" << endl;
    cout << "4. Salir\n";
    cout << "Seleccione una opción: ";
}

template <typename T>
class Plataforma {
private:
    ListaUsuario<Usuario<T>> listaUsuario;
    ListaCurso<Curso<T>> listaCurso;

public:
    // se creara un usuario
    int crearUsuario() const {
        string nombre, profesion, correo, contra, telefono;
        char premiumChar;
        bool premium = false;

        cout << "\nNombre completo: "; getline(cin, nombre);
        cout << "Profesion: "; getline(cin, profesion);
        cout << "Correo: "; getline(cin, correo);

        // verificamos si el correo ya existe
        if (listaUsuario.existeCorreo(correo)) {
            cout << "\n\tYa se creo una Cuenta con este correo ..!!.\n";
            continue;
        }

        cout << "Contrasena: "; getline(cin, contra);
        cout << "Telefono: "; getline(cin, telefono);
        cout << "Desea obtener Premium? (s/n): "; cin >> premiumChar; cin.ignore();

        if (premiumChar == 's' || premiumChar == 'S') { premium = true; }

        Cliente<string> nuevoCliente(nombre, profesion, correo, contra, telefono);
        Usuario<string> nuevoUsuario(nuevoCliente, premium);
        listaUsuarios.agregar(nuevoUsuario);

        // Se guarda directamente en el archivo
        ofstream archivo("usuarios.txt", ios::app);
        if (archivo.is_open()) {
            archivo << nuevoUsuario.serializarUsuario() << endl;
            archivo.close();
        }
        else
        {
            cout << "\n\tError al abrir el archivo.\n";
        }

        cout << "\nUsuario registrado exitosamente.\n";
    }
	// se cargaran los usuarios y cursos registrados en el archivo
    void cargarDatos() {
		// Cargar usuarios desde archivo
        ifstream archivo("usuarios.txt");
        if (archivo.is_open()) {
            string linea;
            int cargados = 0, duplicados = 0; // registra cantidad de duplicados y usuarios para cargar
            while (getline(archivo, linea)) {
                Usuario<string> usuario = Usuario<string>::cargarDesdeLineaUs(linea);
                string correo = usuario.getCliente().get_correo();

                if (!listaUsuario.existeCorreo(correo)) {
                    listaUsuario.agregar(usuario);
                    cargados++;
                }
                else {
                    duplicados++;
                }
            }
            archivo.close();
            cout << "\tUsuarios cargados del archivo: " << cargados << endl;
            if (duplicados > 0) {
                cout << "\tUsurio duplicados no cargados: " << duplicados << endl;
            }
        }
        else {
            cout << "\n\tNo se pudo abrir el archivo.\n";
        }

		// Cargar cursos desde archivo
        ifstream archivo("cursos.txt");
        if (archivo.is_open()) {
            string linea;
            int cargados = 0, duplicados = 0; // registra cantidad de duplicados y usuarios para cargar
            while (getline(archivo, linea)) {
                Curso<string> curso = Curso<string>::cargarDesdeLineaCu(linea);
                if (!listaCurso.existeCodigo(curso.get_CodigoCurso())) {
                    listaCurso.agregar(curso);
                    cargados++;
                }
                else {
                    duplicados++;
                }
            }
            archivo.close();
            cout << "\tCursos cargados del archivo: " << cargados << endl;
            if (duplicados > 0) {
                cout << "\tCursos duplicados no cargados: " << duplicados << endl;
            }
        }
        else
        {
            cout << "\n\tNo se pudo abrir el archivo.\n";
        }
    }
    // el usuario ingresa a al plataforma
	int ingresarUsuario() const {
        cargarDatos();
		string correo, contrasena;
        int opcionUsuario;
        int opcionCurso;
		cout << "\n\t---* Inicie Sesion con su Cuenta *---\n";
        cout << "Usuario: "; getline(cin, correo);
		cout << "Contrasena: "; getline(cin, contrasena);
		// Verifica si el usuario existe
		if (listaUsuario.existeCorreo(correo) && listaUsuario.existeContrasena(contrasena)) {
		    cout << "\n\tCoursera te da la Bienvenida *\n";
			cout << "\n\tQue bueno tenerte de regreso " << correo << endl;
			system("cls");
            
			// Aquí se agrega las acciones que puede accer el usuario
            do
            {
                menuUsuario();
                while (!(cin >> opcionUsuario)) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "\n\tEntrada invalida. Ingrese valores numericos !!! \n";
                }
                cin.ignore();
                if (opcionUsuario == 1) {
                    do
                    {
                        menuCurso();
                        while (!(cin >> opcionCurso)) {
                            cin.clear(); // limpia el estado de error
                            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // limpia el buffer
                            cout << "\n\tEntrada invalida. Ingrese valores numericos !!! \n";
                        }
						cin.ignore();
						if (opcionCurso == 1) { // mostrar todos los cursos
							system("cls");
							cout << "\n\t--- Lista de todos los Cursos ---\n";
							listaCurso.mostrar();
						}
                        // listar cursos por precio
						else if (opcionCurso == 2) { 
							system("cls");
							cout << "\n\t--- Lista de Cursos por Precio ---\n";
							listaCurso.buscarYOrdenarPorPrecio();
							listaCurso.mostrar();
						}
                        // buscar cursos por categoria
                        else if (opcionCurso == 3) {
							system("cls");
							string categoria;
							cout << "\nIngresa la categoria de cursos a buscar: ";
							getline(cin, categoria);
							listaCurso.buscarPorCategoria(categoria);
						}
                        // buscar cursos por precio
						else if (opcionCurso == 4) { 
							system("cls");
							double precioMax;
							cout << "\nIngrese el precio maximo: ";
							while (!(cin >> precioMax)) {
								cin.clear();
								cin.ignore(numeric_limits<streamsize>::max(), '\n');
								cout << "\n\tEntrada invalida. Ingrese un precio numerico... \n";
							}
							cin.ignore();
							listaCurso.buscarYOrdenarPorPrecio(precioMax);
						}
                        // salir del menu cursos
						else if (opcionCurso == 5) { 
							cout << "\n\t\tSaliendo del menu de cursos.....\n";
						}
                        else {
                            cout << "\n\tOpcion no valida. Intente de nuevo.....\n";
                        }
                    } while (opcionCurso!=5);
				}
				else if (opcionUsuario == 2) { // comprar cursos
					system("cls");
					cout << "\n\t--- Comprar Cursos ---\n";
					listaCurso.mostrar();
					// Aquí se puede agregar la lógica para comprar cursos
				}
				else if (opcionUsuario == 3) { // mostrar compras realizadas
					system("cls");
					cout << "\n\t--- Compras Realizadas ---\n";
					// Aquí se puede agregar la lógica para mostrar compras realizadas
				}
				else if (opcionUsuario == 4) { // ver estado premium
					system("cls");
					cout << "\n\t--- Estado Premium ---\n";
					// Aquí se puede agregar la lógica para ver el estado premium
				}
				else if (opcionUsuario == 5) {
					cout << "\n\t\tSaliendo del programa.....\n";
				}
                else if (opcionCurso == 6) {
                    string correo;
                    cout << "Ingrese el correo del usuario a eliminar: ";
                    getline(cin, correo);
                    if (listaUsuario.eliminarPorCorreo(correo)) {
                        ofstream archivo("usuarios.txt");
                        if (archivo.is_open()) {
                            listaUsuario.guardarArchivo(archivo);
                            archivo.close();
                            cout << "\nUsuario eliminado y archivo actualizado.\n";
                        }
                    }
                }
                else {
                    cout << "\n\tOpcion no valida. Intente de nuevo.....\n";
                }
            } while (opcionUsuario != 6);
		}
		else {
			cout << "\n\tUsuario no encontrado.\n";
		}
	}
       
};
