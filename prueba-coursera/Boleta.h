#pragma once
#include <iostream>
#include <string>
#include <iomanip>
#include <filesystem>

using namespace std;
namespace fs = filesystem; // creacion de carpeta

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

    //setters
    void setMontoTotal(double montoTotal) { _montoTotal = montoTotal; }

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

    void mostrarBoletaCurso(ostream& texto = cout) const {
        // lambdas para imprimir boleta de curso
        auto boletaCurso = [&](ostream& texto) {

            texto << fixed << setprecision(2); // formatea montos a 2 decimales
            texto << endl;
            texto << "\t\t\t\t COURSERA APRENDIZAJE PARA TODOS  \n";
            texto << "\t\t\t\t-----------------------------------------------------\n";
            texto << "\t\t\t\t\tBOLETA ELECTRONICA\n";
            texto << "\t\t\t\t-----------------------------------------------------\n";
            texto << endl;
            texto << "\t\t\t\tID TRANSACCION:      \t" << _numOperacion << endl;
            texto << "\t\t\t\tFecha de Emision:    \t" << _fecha << "\t\tHora: \t" << _hora << endl;
            texto << "\t\t\t\tNombre Titular:      \t" << _nombreCliente << endl;
            texto << "\t\t\t\tMetodo de Pago:      \t" << _metodoPago << endl;
            texto << "\t\t\t\tCorreo Electronico:  \t" << _correo << endl;
            texto << endl;
            texto << "\t\t\t\t------------------------------------------------------\n";
            texto << "\t\t\t\t\tCURSOS ADQUIRIDOS\n";
            texto << "\t\t\t\t------------------------------------------------------\n";
            mostrarCursosRecursivo(_cursos, 0, texto);
            texto << "\t\t\t\t------------------------------------------------------\n";
            texto << "\t\t\t\t\tDETALLES DE LA COMPRA\t\n";
            texto << "\t\t\t\t------------------------------------------------------\n";
            texto << "\t\t\t\tCantidad \t\t Precio \t\t Subtotal\t\t\n";
            texto << endl;
            texto << "\t\t\t\t\t" << _cantidad << "\t\t\t $" << _precioUnitario << "\t\t\t $" << _subtotal << "\t\n";
            texto << "\t\t\t\t------------------------------------------------------\n";
            texto << "\t\t\t\tRESUMEN DE PAGO\t\n";
            texto << "\t\t\t\tSubtotal:    \t" << _subtotal << endl;
            texto << "\t\t\t\tDescuentos:  \t" << _descuento << endl;
            texto << "\t\t\t\tIGV (18%):   \t" << _montoIGV << endl;
            texto << "\t\t\t\tMonto Total: \t" << _montoTotal << endl;;
            texto << endl;
            texto << "*********************************************************\n";
            };

        boletaCurso(texto);
    }

    void mostrarBoletaPremium(ostream& texto = cout) const {
        // lambdas para imprimir boleta de premium
        auto boletaPremium = [&](ostream& texto) {
            texto << fixed << setprecision(2); // formatea montos a 2 decimales
            texto << endl;
            texto << "\t\t\t\t COURSERA APRENDIZAJE PARA TODOS  \n";
            texto << "\t\t\t\t-----------------------------------------------------\n";
            texto << "\t\t\t\t\tBOLETA ELECTRONICA\n";
            texto << "\t\t\t\t-----------------------------------------------------\n";
            texto << endl;
            texto << "\t\t\t\tID TRANSACCION:      \t" << _numOperacion << endl;
            texto << "\t\t\t\tFecha de Emision:    \t" << _fecha << "\tHora: \t" << _hora << endl;
            texto << "\t\t\t\tNombre Titular:      \t" << _nombreCliente << endl;
            texto << "\t\t\t\tMetodo de Pago:      \t" << _metodoPago << endl;
            texto << "\t\t\t\tCorreo Electronico:  \t" << _correo << endl;
            texto << "\t\t\t\t------------------------------------------------------\n";
            texto << "\t\t\t\t\tACTIVACION PREMIUM\n";
            texto << "\t\t\t\t------------------------------------------------------\n";
            texto << "\t\t\t\t\tDETALLES DE LA COMPRA\t\n";
            texto << "\t\t\t\t------------------------------------------------------\n";
            texto << "\t\t\t\tCantidad \t\t Precio \t\t Subtotal\t\t\n";
            texto << endl;
            texto << "\t\t\t\t\t" << _cantidad << "\t\t\t $" << _precioUnitario << "\t\t\t $" << _subtotal << "\n";
            texto << "\t\t\t\t------------------------------------------------------\n";
            texto << "\t\t\t\t\t\tRESUMEN DE PAGO\t\n";
            texto << "\t\t\t\tSubtotal:    \t" << _subtotal << endl;
            texto << "\t\t\t\tDescuentos:  \t" << _descuento << endl;
            texto << "\t\t\t\tIGV (18%):   \t" << _montoIGV << endl;
            texto << "\t\t\t\tMonto Total: \t" << _montoTotal << endl;;
            texto << endl;
            texto << "*********************************************************\n";
            };

        boletaPremium(texto);
    }

    void guardarBoletaEnArchivo(const string& ruta, bool esPremium = false ) const {  
       fs::path path(ruta); // Usar el alias para experimental::filesystem  
       fs::create_directories(path.parent_path()); // Crea carpeta si no existe  

       ofstream archivo(ruta);  
       if (archivo.is_open()) {  
           if (esPremium)
           {
               mostrarBoletaCurso(archivo);
           }
           else
           {
               mostrarBoletaPremium(archivo);
           }
           archivo.close();  
           cout << " Boleta guardada en " << ruta << endl;  
       }  
       else {  
           cout << " Error al guardar la boleta." << endl;  
       }  
    }

    void enviarBoleta(const string& correo) {
        cout << "Boleta enviada al correo: " << correo << endl;
    }

    string generarNombreArchivo() const {
        string nombreArchivo = _nombreCliente;
        replace(nombreArchivo.begin(), nombreArchivo.end(), ' ', '_');
        string archivo = "boletas/boleta_" + nombreArchivo + ".txt";
        return "boletas/boleta_" + nombreArchivo + ".txt";
    }

private:
    // Recursividad para mostrar cursos separados por comas
    void mostrarCursosRecursivo(const string& lista, size_t index, ostream& texto) const {
        if (index >= lista.length()) return;

        size_t coma = lista.find(',', index);
        if (coma == string::npos) {
            texto << "- " << lista.substr(index) << "\n";
        }
        else {
            texto << "- " << lista.substr(index, coma - index) << "\n";
            mostrarCursosRecursivo(lista, coma + 1, texto);
        }
    }
};
