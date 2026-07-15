#include "utilidades/Archivos.hpp"
#include <fstream>
#include <iostream>

// Guarda la información de los clientes
// en el archivo clientes.txt.
void Archivos::guardarClientes(){

    std::ofstream archivo("clientes.txt");

    // Se verifica que el archivo se haya abierto correctamente.
    if(archivo.is_open()){

        archivo << "Clientes guardados correctamente." << std::endl;

        // Se cierra el archivo para guardar los cambios.
        archivo.close();
    }

}

// Carga y muestra la información almacenada
// en el archivo clientes.txt.
void Archivos::cargarClientes(){

    std::ifstream archivo("clientes.txt");
    std::string linea;

    // Se lee el archivo línea por línea.
    while(getline(archivo, linea)){
        std::cout << linea << std::endl;
    }

    // Se cierra el archivo.
    archivo.close();

}

// Guarda la información de los técnicos.
void Archivos::guardarTecnicos(){

    std::ofstream archivo("tecnicos.txt");

    if(archivo.is_open()){

        archivo << "Tecnicos guardados correctamente." << std::endl;

        archivo.close();
    }

}

// Carga la información de los técnicos.
void Archivos::cargarTecnicos(){

    std::ifstream archivo("tecnicos.txt");
    std::string linea;

    while(getline(archivo, linea)){
        std::cout << linea << std::endl;
    }

    archivo.close();

}

// Guarda la información de los dispositivos.
void Archivos::guardarDispositivos(){

    std::ofstream archivo("dispositivos.txt");

    if(archivo.is_open()){

        archivo << "Dispositivos guardados correctamente." << std::endl;

        archivo.close();
    }

}

// Carga la información de los dispositivos.
void Archivos::cargarDispositivos(){

    std::ifstream archivo("dispositivos.txt");
    std::string linea;

    while(getline(archivo, linea)){
        std::cout << linea << std::endl;
    }

    archivo.close();

}

// Guarda la información de los servicios.
void Archivos::guardarServicios(){

    std::ofstream archivo("servicios.txt");

    if(archivo.is_open()){

        archivo << "Servicios guardados correctamente." << std::endl;

        archivo.close();
    }

}

// Carga la información de los servicios.
void Archivos::cargarServicios(){

    std::ifstream archivo("servicios.txt");
    std::string linea;

    while(getline(archivo, linea)){
        std::cout << linea << std::endl;
    }

    archivo.close();

}

// Guarda la información de las órdenes de servicio.
void Archivos::guardarOrdenes(){

    std::ofstream archivo("ordenes.txt");

    if(archivo.is_open()){

        archivo << "Ordenes guardadas correctamente." << std::endl;

        archivo.close();
    }

}

// Carga la información de las órdenes de servicio.
void Archivos::cargarOrdenes(){

    std::ifstream archivo("ordenes.txt");
    std::string linea;

    while(getline(archivo, linea)){
        std::cout << linea << std::endl;
    }

    archivo.close();

}

// Destructor de la clase Archivos.
Archivos::~Archivos(){

}
