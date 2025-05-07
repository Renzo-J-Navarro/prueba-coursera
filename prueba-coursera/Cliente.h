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
    T _nombreCompleto;
    T _profesion;
    T _correo;
    T _contrase�a;
    T _telefono;

    void guardarAutomaticamente() const {
        ofstream archivo("usuarios.txt", ios::app);
        if (archivo.is_open()) {
            archivo << _nombreCompleto << ","
                << _profesion << ","
                << _correo << ","
                << _contrase�a << ","
                << _telefono << "," << endl;
            archivo.close();
        }
    }

public:
    Cliente(const T& nombre = "N/A", const T& profesion = "N/A", const T& correo = "N/A",
        const T& contra = "N/A", const T& telefono = "N/A")
        : _nombreCompleto(nombre), _profesion(profesion),_correo(correo),
        _contrase�a(contra), _telefono(telefono) {
    }

    T get_nombreCompleto() const { return _nombreCompleto; }
    T get_Profesion() const { return _profesion; }
    T get_correo() const { return _correo; }
    T get_contrase�a() const { return _contrase�a; }
    T get_telefono() const { return _telefono; }

    void set_NombreCompleto(const T& nombre) { _nombreCompleto = nombre; }
    void set_Profesion(const T& profesion) { _profesion = profesion; }
    void set_Correo(const T& correo) { _correo = correo; }
    void set_Contrase�a(const T& contra) { _contrase�a = contra; }
    void set_Telefono(const T& telefono) { _telefono = telefono; }

    void mostrarCliente() const {
        cout << "\n\t* Datos del Cliente *\n";
        cout << "\nNombre: " << _nombreCompleto 
            << "\nProfesion: "<< _profesion 
            << "\nCorreo: " << _correo 
            << "\nContrasena: " << _contrase�a 
            << "\nTelefono: " << _telefono  
            << endl;
    }
    static Cliente<T> cargarDesdeLineaCli(const string& linea) {
        string nombre, profesion, correo, contra, telefono;
        stringstream ss(linea);
        getline(ss, nombre, ',');
        getline(ss, profesion, ',');
        getline(ss, correo, ',');
        getline(ss, contra, ',');
        getline(ss, telefono, ',');
        return Cliente<T>(nombre, profesion, correo, contra, telefono);
    }
};