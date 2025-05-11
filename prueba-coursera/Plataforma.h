#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
#include <conio.h>
#include <limits>
#include <filesystem>

#include "Curso.h"
#include "Usuario.h"
#include "Boleta.h"
#include "ListaCurso.h"
#include "ListaUsuario.h"
using namespace std;
namespace fs = filesystem;

//Menu de acciones para el usuario
static void menuCurso() {
    cout << "\n\t---* Biblioteca de Cursos *---\n";
    cout << "1. Mostrar todos los Cursos" << endl;
    cout << "2. Listar cursos por su Precio" << endl;
    cout << "3. Buscar Cursos por Categoria" << endl;
    cout << "4. Buscar Cursos por Precio" << endl;
    cout << "5. Realizar Compra." << endl;
    cout << "6. Salir" << endl;
    cout << "Seleccione una opcion: ";
}
static void menuUsuario() {
    cout << "\n\t---* Que deseas hacer hoy ? *---\n";
    cout << "1. Ver catalago de Cursos" << endl;
    cout << "2. Realizar Compra" << endl;
    cout << "3. Ver estado Premium" << endl;
    cout << "4. Elimar Cuenta Usuario" << endl;
	cout << "5. Salir" << endl;
    cout << "Seleccione una opcion: ";
}
static void menuPlataforma() {
    cout << "\n\t===*=== MENU PLATAFORMA ===*===\n";
    cout << "1. Crear Usuario." << endl;
    cout << "2. Ingresar Cuenta Usuario." << endl;
    cout << "3. Salir\n";
    cout << "Seleccione una opcion: ";
}
static void menuVenta() {
    cout << "\n\t---* Proceso de Compras *---\n";
    cout << "1. Comprar y Pagar Cursos." << endl;
    cout << "2. Activar Premium." << endl;
    cout << "3. Ver Boletas." << endl;
    cout << "4. Salir." << endl;
    cout << "Seleccione una opcion: ";
}

template <typename T>
class Plataforma {
private:
    ListaUsuario<Usuario<T>> listaUsuario;
    ListaCurso<Curso<T>> listaCurso;
    Usuario<T>* actualUser = nullptr;

public:

    Plataforma() {}

    // se creara un usuario
    int crearUsuario() {
        string nombre, profesion, correo, contra, telefono;
        char premiumChar;
        bool premium = false;

        cout << "\nNombre completo: "; getline(cin, nombre);
        cout << "Profesion: "; getline(cin, profesion);
        cout << "Correo: "; getline(cin, correo);

        // verificamos si el correo ya existe
        if (listaUsuario.existeCorreo(correo)) {
            cout << "\n\tYa se creo una Cuenta con este correo ..!!.\n";
            return 1;
        }

        cout << "Contrasena: "; getline(cin, contra);
        cout << "Telefono: "; getline(cin, telefono);
        cout << "Desea obtener Premium? (s/n): "; cin >> premiumChar; cin.ignore();

        if (premiumChar == 's' || premiumChar == 'S') { premium = true; }

        Cliente<string> nuevoCliente(nombre, profesion, correo, contra, telefono);
        Usuario<string> nuevoUsuario(nuevoCliente, premium);
        listaUsuario.agregar(nuevoUsuario);

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
        return 0;
    }
	// se cargaran los usuarios y cursos registrados en el archivo
    void cargarDatos() {
		// Cargar usuarios desde archivo
        ifstream archivoUsuario("usuarios.txt");
        if (archivoUsuario.is_open()) {
            string linea;
            int cargados = 0, duplicados = 0; // registra cantidad de duplicados y usuarios para cargar
            while (getline(archivoUsuario, linea)) {
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
            archivoUsuario.close();
            cout << "\tUsuarios cargados del archivo: " << cargados << endl;
            if (duplicados > 0) {
                cout << "\tUsurio duplicados no cargados: " << duplicados << endl;
            }
        }
        else {
            cout << "\n\tNo se pudo abrir el archivo.\n";
        }

		// Cargar cursos desde archivo
        ifstream archivoCurso("cursos.txt");
        if (archivoCurso.is_open()) {
            string linea;
            int cargados = 0, duplicados = 0; // registra cantidad de duplicados y usuarios para cargar
            while (getline(archivoCurso, linea)) {
                Curso<string> curso = Curso<string>::cargarDesdeLineaCu(linea);
                if (!listaCurso.existeCodigo(curso.get_CodigoCurso())) {
                    listaCurso.agregar(curso);
                    cargados++;
                }
                else {
                    duplicados++;
                }
            }
            archivoCurso.close();
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
	void ingresarUsuario() {
		string correo, contrasena;
        int opcionUsuario;
        int opcionCurso;
		cout << "\n\t---* Inicie Sesion con su Cuenta *---\n";
        cout << "Usuario: "; getline(cin, correo);
		cout << "Contrasena: "; getline(cin, contrasena);
		// Verifica si el usuario existe
        actualUser = listaUsuario.obtenerUsuarioPorCorreo(correo);
		if (actualUser && listaUsuario.existeContrasena(contrasena)) {
		    cout << "\n\tCoursera te da la Bienvenida *\n";
			cout << "\n\tQue bueno tenerte de regreso " << correo << endl;
			system("cls");
            
			// Aqu� se agrega las acciones que puede realizar el usuario
            do
            {
                menuUsuario();
                while (!(cin >> opcionUsuario)) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "\n\tEntrada invalida. Ingrese valores numericos !!! \n";
                }
                cin.ignore();
                // menu de Cursos
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
                        // mostrar todos los cursos
                        if (opcionCurso == 1) { 
                            system("cls");
                            cout << "\n\t--- Lista de todos los Cursos ---\n";
                            listaCurso.mostrar();
                        }
                        // listar cursos por precio
                        else if (opcionCurso == 2) {
                            system("cls");
                            cout << "\n\t--- Lista de Cursos por Precio ---\n";
                            //listaCurso.buscarYOrdenarPorPrecio();
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
                        // realizar compra de cursos
                        else if (opcionCurso == 5) {
                            gestorPago();
                        }
                        // salir del menu cursos
                        else if (opcionCurso == 6) {
                            cout << "\n\t\tSaliendo del menu de cursos.....\n";
                        }
                        else {
                            cout << "\n\tOpcion no valida. Intente de nuevo.....\n";
                        }
                    } while (opcionCurso != 6);
                }
                // comprar cursos
                else if (opcionUsuario == 2) {
                    system("cls");
                    cout << "\n\t--- Comprar Cursos ---\n";
                    listaCurso.mostrar();
                    // Aqu� se puede agregar la l�gica para comprar cursos
                }
                // listado de premium
                else if (opcionUsuario == 3) {
					system("cls");
					cout << "\n\t--- Estado Premium ---\n";
					// Aqu� se puede agregar la l�gica para ver el estado premium
				}
                // eliminar correo del usuario
				else if (opcionUsuario == 4) {
                    string correo;
                    cout << "Ingrese el correo del usuario a eliminar: ";
                    getline(cin, correo);
                    if (listaUsuario.eliminarPorCorreo(correo)) {
                        ofstream archivoUsuario("usuarios.txt");
                        if (archivoUsuario.is_open()) {
                            listaUsuario.guardarArchivo(archivoUsuario);
                            archivoUsuario.close();
                            cout << "\nUsuario eliminado y archivo actualizado.\n";
                        }
                    }
				}
                // salir del menu usuarios
                else if (opcionUsuario == 5) {
					cout << "\n\t\tSaliendo del menu del Usuario.....\n";
                }
                else {
                    cout << "\n\tOpcion no valida. Intente de nuevo.....\n";
                }
            } while (opcionUsuario != 5);
		}
		else 
        {
			cout << "\n\tUsuario no encontrado.\n";
		}
	}
    // completar pagos
    void gestorPago() {
        int opcionPago;
        do
        {
            menuVenta();
            while (!(cin >> opcionPago)) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "\n\tEntrada invalida. Ingrese valores numericos !!! \n";
            }
            cin.ignore();
            // validar confirmacion de usuario
            if (!actualUser) {
                cout << "\nDebes iniciar sesi�n para realizar pagos.\n";
                return;
            }
            // Comprar y pagar cursos
            if (opcionPago == 1) {
                
            }
            // Activar premium si es que en el registro dijo que si
            else if (opcionPago == 2) {
                system("cls");
                cout << "\n\t--- Activar Premium ---\n";
                cout << "\n El precio para activar premium es de ($40 / mensual) ";
                if (!actualUser->get_Premium()) {
                    actualUser->set_Premiun(true);
                    cout << "Premium activado correctamente.\n";
                }
                else {
                    cout << "Ya tienes cuenta Premium activa.\n";
                }
            }
            // Mostrar las boletas
            else if (opcionPago == 3) {
                system("cls");
                string nombre = actualUser->getCliente().get_nombreCompleto();
                string archivo = "boletas/boleta_" + nombre + ".txt";
                ifstream file(archivo);
                if (file.is_open()) {
                    cout << "\n--- Boleta del usuario ---\n";
                    string linea;
                    while (getline(file, linea)) {
                        cout << linea << endl;
                    }
                    file.close();
                }
                else {
                    cout << "\nNo hay boleta registrada para este usuario.\n";
                }
            }
            // Salir de menu de compras
            else if (opcionPago == 4) {
                cout << "\n\t\tSaliendo del menu de compras.....\n";
            }
            else {
                cout << "\n\tOpcion no valida. Intente de nuevo.....\n";
            }

        } while (opcionPago != 4);
    }


};
