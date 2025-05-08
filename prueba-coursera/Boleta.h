#pragma once
#include <iostream>
#include <string>
#include <iomanip>

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
	double getMontoIGV() const { return _montoIGV; }
	double getDescuento() const { return _descuento; }

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
        // lambdas para imprimir el flujo
        auto boleta = [&](ostream& texto) {

            texto << fixed << setprecision(2); // formatea montos a 2 decimales
            texto << endl;
            texto << "\t\t\t\t COURSERA APRENDIZAJE PARA TODOS  \n";
            texto << "-----------------------------------------------------\n";
            texto << "\t\t\t\t\tBOLETA ELECTRONICA\n";
            texto << "-----------------------------------------------------\n";
            texto << endl;
            texto << "ID TRANSACCION:      \t" << _numOperacion << endl;
            texto << "Fecha de Emision:    \t" << _fecha << "\t\tHora: \t" << _hora << endl;
            texto << "Nombre Titular:      \t" << _nombreCliente << endl;
            texto << "Metodo de Pago:      \t" << _metodoPago << endl;
            texto << "Correo Electronico:  \t" << _correo << endl;
            texto << endl;
            texto << "------------------------------------------------------\n";
            texto << "\t\t\t\t\tCURSOS ADQUIRIDOS\n";
            texto << "------------------------------------------------------\n";
            mostrarCursosRecursivo(_cursos, 0);
            texto << "------------------------------------------------------\n";
            texto << "\tDETALLES DE LA COMPRA\t\n";
            texto << "\tCantidad \t\t\t\t Precio \t\t\t Subtotal\t\t\n";
            texto << endl;
            texto << "\t" << _cantidad << "\t\t\t $" << _precioUnitario << "\t\t\t $" << _subtotal << "\t\n";
            texto << "------------------------------------------------------\n";
            texto << "\t\tRESUMEN DE PAGO\t\n";
            texto << "Subtotal:    \t" << _subtotal << endl;
            texto << "Descuentos:  \t" << _descuento << endl;
            texto << "IGV (18%):   \t" << _montoIGV << endl;
            texto << "Monto Total: \t" << _montoTotal << endl;;
            texto << endl;
            texto << "*********************************************************\n";
            };
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
