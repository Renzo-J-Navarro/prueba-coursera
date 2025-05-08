#include "ListaUsuario.h"
#include "ListaCurso.h"
#include "Usuario.h"
#include "Curso.h"

#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;

void procesarCompra(Usuario<string> usuario, ListaCurso<Curso<string>>& listaCursos) {
    vector<Curso<string>> cursosSeleccionados;
    string eleccion;
    float totalPrecio = 0.0;
    int cantidad = 0;

    cout << "\n--- Lista de Cursos Disponibles ---\n";
    listaCursos.mostrar();

    do {
        int codigo;
        cout << "\nIngrese el codigo del curso que desea agregar (0 para terminar): ";
        cin >> codigo;

        if (codigo == 0) break;

        Curso<string>* curso = listaCursos.buscarPorCodigo(codigo);
        if (curso) {
            cursosSeleccionados.push_back(*curso);
            totalPrecio += curso->get_Precio();
            cantidad++;
            cout << "\nCurso agregado: " << curso->get_NombreCurso() << "\n";
        }
        else {
            cout << "Curso no encontrado.\n";
        }
    } while (true);

    // Confirmar si desea premium
    bool quierePremium = false;
    char opcionPremium;
    cout << "\nDesea activar Premium por S/.50.00? (s/n): ";
    cin >> opcionPremium;
    if (opcionPremium == 's' || opcionPremium == 'S') {
        quierePremium = true;
        totalPrecio += 50.0;
    }

    // Crear string de cursos separados por coma
    string listaCursosTexto = "";
    for (size_t i = 0; i < cursosSeleccionados.size(); i++) {
        listaCursosTexto += cursosSeleccionados[i].get_NombreCurso();
        if (i < cursosSeleccionados.size() - 1)
            listaCursosTexto += ",";
    }

    // Crear boleta
    string correo = usuario.getCliente().get_correo();
    string nombre = usuario.getCliente().get_nombre();
    string metodo = "Yape"; // ejemplo fijo
    string empresa = "OpenEduca";
    string numOperacion = to_string(rand() % 1000000);
    string fecha = "08/05/2025"; // Puedes automatizarlo con <ctime>
    string hora = "10:35 AM";    // idem
    float precioUnitario = (cantidad == 0) ? 0 : totalPrecio / cantidad;
    double descuento = (quierePremium && cantidad >= 2) ? 20.0 : 0.0;

    Boleta boleta(empresa, numOperacion, fecha, hora, metodo, correo, nombre,
        cantidad, listaCursosTexto, precioUnitario, descuento);

    // Mostrar por consola
    boleta.mostrarBoleta();
    boleta.enviarBoleta();

    // Guardar boleta en archivo individual
    fs::create_directories("boletas/" + correo);
    ofstream archivo("boletas/" + correo + "/boleta_" + numOperacion + ".txt");
    if (archivo.is_open()) {
        archivo << "BOLETA DE VENTA\n";
        archivo << "Empresa: " << empresa << "\n";
        archivo << "Operacion Nro: " << numOperacion << "\n";
        archivo << "Fecha: " << fecha << " - Hora: " << hora << "\n";
        archivo << "Cliente: " << nombre << " (" << correo << ")\n";
        archivo << "Metodo de pago: " << metodo << "\n";
        archivo << "\nCursos adquiridos:\n";
        // Usamos recursividad también aquí
        function<void(const string&, size_t)> mostrarCursosRec = [&](const string& lista, size_t idx) {
            if (idx >= lista.length()) return;
            size_t coma = lista.find(',', idx);
            if (coma == string::npos) {
                archivo << "- " << lista.substr(idx) << "\n";
            }
            else {
                archivo << "- " << lista.substr(idx, coma - idx) << "\n";
                mostrarCursosRec(lista, coma + 1);
            }
            };
        mostrarCursosRec(listaCursosTexto, 0);
        archivo << "\nCantidad: " << cantidad;
        archivo << "\nPrecio unitario: " << precioUnitario;
        archivo << "\nSubtotal: " << cantidad * precioUnitario;
        archivo << "\nDescuento: " << descuento;
        archivo << "\nIGV (18%): " << (cantidad * precioUnitario) * 0.18;
        archivo << "\nTOTAL A PAGAR: " << boleta.getMontoTotal() << "\n";
        archivo << "------------------------\n";
        archivo.close();
    }
    else {
        cout << "Error al guardar la boleta.\n";
    }
}
