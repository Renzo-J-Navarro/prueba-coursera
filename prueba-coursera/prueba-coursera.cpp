#include "Plataforma.h"

#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
#include <conio.h>

using namespace std;

static void adminMenuCurso() {
    cout << "\n--- MENU CURSOS ---\n";
    cout << "1. Registrar Curso" << endl;
    cout << "2. Mostrar Cursos" << endl;
    cout << "3. Listar por Precio" << endl;
    cout << "4. Buscar por Categoria" << endl;
    cout << "5. Buscar por Precio" << endl;
    cout << "6. Cargar Cursos desde archivo" << endl;
    cout << "7. Salir" << endl;
    cout << "Seleccione una opcion: ";
}
static void adminMenuUsuario() {
    cout << "\n--- MENU USUARIOS ---\n";
    cout << "1. Registrar Usuario" << endl;
    cout << "2. Mostrar Usuario" << endl;
    cout << "3. Listar por Usuario Premium" << endl;
    cout << "4. Cargar Usuarios desde archivo" << endl;
    cout << "5. Eliminar Cuenta Usuario" << endl;
    cout << "6. Salir" << endl;
    cout << "Seleccione una opcion: ";
}
static void admincompilaUsuario() {

    ListaUsuario<Usuario<string>> listaUsuario;
    int opcionUsuario;

    do {
        menuUsuario();
        while (!(cin >> opcionUsuario)) {
            cin.clear(); // limpia el estado de error
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // limpia el buffer
            cout << "\n\tEntrada invalida. Ingrese valores numericos !!! \n";
        }
        cin.ignore();

		if (opcionUsuario == 1) { // registrar usuario
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
        }
		else if (opcionUsuario == 2) { // mostrar todos los usuarios
            system("cls");
            cout << "\n\t--- Lista de Usuarios ---\n";
            listaUsuario.mostrar();
        }
		else if (opcionUsuario == 3) { // listar por premium
            system("cls");
            cout << "\n\t--- Usuarios Premium ---\n";
            listaUsuario.ordenarPremium();  // Ordena por Premium
            listaUsuario.mostrar();
        }
		else if (opcionUsuario == 4) { // cargar usuarios desde archivo
            system("cls");
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
                cout << "\n\tUsuarios cargados del archivo: " << cargados << endl;
                if (duplicados > 0) {
                    cout << "\n\tUsurio duplicados no cargados: " << duplicados << endl;
                }
            }
            else {
                cout << "\n\tNo se pudo abrir el archivo.\n";
            }
        }
		else if (opcionUsuario == 5) { // eliminar cuenta usuario
            system("cls");
            string correo;
            cout << "Ingrese el correo del usuario a eliminar: ";
            getline(cin, correo);
            if (listaUsuario.eliminarPorCorreo(correo)){
                ofstream archivo("usuarios.txt");
                if (archivo.is_open()) {
                    listaUsuario.guardarArchivo(archivo);
                    archivo.close();
                    cout << "\nUsuario eliminado y archivo actualizado.\n";
                }
            }
        }
        else if (opcionUsuario == 6) {
			cout << "\n\t\tSaliendo del programa.....\n";
        }
        else
        {
			cout << "\n\tOpcion no valida. Intente de nuevo.....\n";
        }

	} while(opcionUsuario != 6);
};
static void admincompilaCurso() {

	ListaCurso<Curso<string>> listaCurso;
	int opcionCurso;

    do
    {
        menuCurso();
        while (!(cin >> opcionCurso)) {
            cin.clear(); // limpia el estado de error
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // limpia el buffer
            cout << "\n\tEntrada invalida. Ingrese valores numericos !!! \n";
        }
        cin.ignore();

        if (opcionCurso == 1) { // agregar un curso adicional
            int codigo;
            string nombre, categoria, duracion;
            char certificadoChar;
            bool certificado = false;
            double precio;

			cout << "\nCodigo Curso: "; cin >> codigo;
            cin.ignore();
			cout << "Nombre Curso: "; getline(cin, nombre);
            cout << "Certificado? (s/n): "; cin >> certificadoChar;
            cin.ignore();
			cout << "Categoria: "; getline(cin, categoria);
			cout << "Duracion: "; getline(cin, duracion);
			cout << "Precio: "; cin >> precio;
            cin.ignore();

			if (certificadoChar == 's' || certificadoChar == 'S') { certificado = true; }
            Curso<string> nuevoCurso(codigo, nombre, certificado, categoria, duracion, precio);
            listaCurso.agregar(nuevoCurso);

            // Se guarda directamente en el archivo
            ofstream archivo("cursos.txt", ios::app);
            if (archivo.is_open()) {
                archivo << nuevoCurso.serializarCurso() << endl;
                archivo.close();
            }
            else
            {
                cout << "\n\tError al abrir el archivo.\n";
            }
            cout << "\nCurso agregado con exito.\n";
        }
        else if (opcionCurso == 2) { // mostrar todos los cursos
            system("cls");
            cout << "\n\t--- Lista de Cursos ---\n";
            listaCurso.mostrar();
        }
        else if (opcionCurso == 3) { // ordenar por precio
            system("cls");
			cout << "\n\t--- Cursos por Precio ---\n";
			listaCurso.ordenarPorPrecio();
            listaCurso.mostrar();
        }
		else if (opcionCurso == 4) { // buscar por categoria
            system("cls");
            string categoria;
            cout << "\nIngresa la categoria de cursos a buscar: ";
            getline(cin, categoria);
            listaCurso.buscarPorCategoria(categoria);
        }
        else if (opcionCurso == 5) { // buscar por precio
            system("cls");
			double precioMax;
            cout << "\nIngrese el precio maximo: ";
            while (!(cin>> precioMax)) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cout << "\n\tEntrada invalida. Ingrese un precio numerico... \n";
            }
            cin.ignore();
			listaCurso.buscarYOrdenarPorPrecio(precioMax);
        }
        else if (opcionCurso == 6) { // cargar cursos desde archivo
			system("cls");
			ifstream archivo("cursos.txt");
            if(archivo.is_open()) {
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
                cout << "\n\tCursos cargados del archivo: " << cargados << endl;
                if (duplicados > 0) {
                    cout << "\n\tCursos duplicados no cargados: " << duplicados << endl;
                }
            }
            else
            {
				cout << "\n\tNo se pudo abrir el archivo.\n";
            }
        }
        else if (opcionCurso == 7) {
            cout << "\n\t\tSaliendo del programa.....\n";
        }
        else
        {
            cout << "\n\tOpcion no valida. Intente de nuevo.....\n";
        }
    } while (opcionCurso != 7);
}

int main() {
    srand(time(0));
    Plataforma<string> listaPlataforma;
    int opcion;
    listaPlataforma.cargarDatos();
    do
    {
        menuPlataforma();
        while (!(cin >> opcion)) {
            cin.clear(); // limpia el estado de error
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // limpia el buffer
            cout << "\n\tEntrada invalida. Ingrese valores numericos !!! \n";
        }
        cin.ignore();

        if (opcion == 1) {
            system("cls");
            listaPlataforma.crearUsuario();
        }
        else if (opcion == 2) {
            system("cls");
            listaPlataforma.ingresarUsuario();
        }
        else if (opcion == 3) {
            cout << "\n\t\tSaliendo del programa.....\n";
        }
        else {
            cout << "\n\tOpcion no valida. Intente de nuevo.....\n";
        }
    } while (opcion != 3);


    system("pause");
    return 0;

}
    