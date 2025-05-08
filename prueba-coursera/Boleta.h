#pragma once
#include <iostream>
#include <string>
using namespace std;

class Boleta {
private:
    string _empresa;
    string _numOperacion;
    string _fecha;
    string _hora;
    string _metodoPago;
    string _correo;
    string _nombreCliente;
    int _cantidad;
    string _cursos;  // lista de cursos separados por coma (por simplicidad)
    float _precioUnitario;
    float _subtotal;
    double _descuento;
    double _montoIGV;
    double _montoTotal;

public:
    Boleta(string empresa = "Coursera", string numOperacion = "N/A", string fecha = "N/A", string hora = "N/A",
        string metodoPago = "N/A", string correo = "N/A", string nombreCliente = "N/A", int cantidad = 0,
        string cursos = "N/A", float precioUnitario = 0.0, float subtotal = 0.0, double descuento = 0.0,
        double montoigv = 0.0, double montoTotal = 0.0)
        : _empresa(empresa), _numOperacion(numOperacion), _fecha(fecha), _hora(hora), _metodoPago(metodoPago), 
        _correo(correo), _nombreCliente(nombreCliente), _cantidad(cantidad), _cursos(cursos), _precioUnitario(precioUnitario), 
        _subtotal(subtotal), _descuento(descuento), _montoIGV(montoigv), _montoTotal(montoTotal) {
        generarBoleta();
    }

	// Getters
	double getMontoTotal() const { return _montoTotal; }


    // Metodos
    void generarBoleta() {
        // Lambda para calcular subtotal según cantidad y precio unitario
        auto calcularSubtotal = [=]() -> float {
            return _cantidad * _precioUnitario;
            };

        _subtotal = calcularSubtotal();

        // Lambda para obtener IGV (18%)
        auto calcularIGV = [](float base) -> double {
            return base * 0.18;
            };

        _montoIGV = calcularIGV(_subtotal);

        _montoTotal = _subtotal + _montoIGV - _descuento;
    }

    void mostrarBoleta() {
        cout << "\n--- BOLETA DE VENTA ---" << endl;
        cout << "Empresa: " << _empresa << endl;
        cout << "Operacion Nro: " << _numOperacion << endl;
        cout << "Fecha: " << _fecha << " - Hora: " << _hora << endl;
        cout << "Cliente: " << _nombreCliente << " (" << _correo << ")" << endl;
        cout << "Metodo de pago: " << _metodoPago << endl;

        cout << "\nCursos adquiridos:" << endl;
        mostrarCursosRecursivo(_cursos, 0);

        cout << "\nCantidad: " << _cantidad;
        cout << "\nPrecio unitario: " << _precioUnitario;
        cout << "\nSubtotal: " << _subtotal;
        cout << "\nDescuento: " << _descuento;
        cout << "\nIGV (18%): " << _montoIGV;
        cout << "\nTOTAL A PAGAR: " << _montoTotal << endl;
        cout << "------------------------" << endl;
    }

    void enviarBoleta() {
        cout << "Boleta enviada al correo: " << _correo << endl;
    }

private:
    // Recursividad para mostrar cursos separados por comas
    void mostrarCursosRecursivo(const string& lista, size_t index) {
        if (index >= lista.length()) return;

        size_t coma = lista.find(',', index);
        if (coma == string::npos) {
            cout << "- " << lista.substr(index) << endl;
        }
        else {
            cout << "- " << lista.substr(index, coma - index) << endl;
            mostrarCursosRecursivo(lista, coma + 1);
        }
    }
};
