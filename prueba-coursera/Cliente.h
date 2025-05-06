#pragma once
#include <iostream>
#include <fstream> 
#include <conio.h>
#include <sstream>
#include <string>
using namespace std;

template <typename T>
class Cliente {
private:
    string _nombreCompleto;
    string _profesion;
    string _correo;
    string _contraseña;
    string _telefono;
    bool _premium;
public:
    Cliente(const string& nombre = "N/A", const string& profesion = "N/A", const string& correo = "N/A",
        const string& contra = "N/A", const string& telefono = "N/A", bool premium = false)
        : _nombreCompleto(nombre), _profesion(profesion),_correo(correo),
        _contraseña(contra), _telefono(telefono), _premium(premium) {}

    string get_nombreCompleto() const { return _nombreCompleto; }
    string get_Profesion() const { return _profesion; }
    string get_correo() const { return _correo; }
    string get_contraseña() const { return _contraseña; }
    string get_telefono() const { return _telefono; }
	bool get_premium() const { return _premium; }

    void set_NombreCompleto(const string& nombre) { _nombreCompleto = nombre; }
    void set_Profesion(const string& profesion) { _profesion = profesion; }
    void set_Correo(const string& correo) { _correo = correo; }
    void set_Contraseña(const string& contra) { _contraseña = contra; }
    void set_Telefono(const string& telefono) { _telefono = telefono; }
	void set_Premium(bool premium) { _premium = premium; }

    void mostrarCliente() const {
        cout << "\n\t* Datos del Cliente *\n";
        cout << "\nNombre: " << _nombreCompleto 
            << "\nProfesion: "<< _profesion 
            << "\nCorreo: " << _correo 
            << "\nContrasena: " << _contraseña 
            << "\nTelefono: " << _telefono  
            << "\nEs Premium?: " << (_premium ? "Si" : "No")
            << endl;
    }

    void guardarEnArchivo(ofstream& archivo) const {
        archivo << _nombreCompleto << "," 
            << _profesion << "," 
            << _correo << "," 
            << _contraseña << "," 
			<< _telefono << ","
            << _premium << endl;
    }

    static Cliente<T> cargarDesdeLinea(const string& linea) {
        string nombre, profesion, correo, contra, telefono, premiumS;
        stringstream ss(linea);
        getline(ss, nombre, ',');
        getline(ss, profesion, ',');
        getline(ss, correo, ',');
        getline(ss, contra, ',');
        getline(ss, telefono, ',');
        getline(ss, premiumS, ',');
        bool premium = (premiumS == "1" || premiumS == "true");
        return Cliente<T>(nombre, profesion, correo, contra, telefono, premium);
    }

};
