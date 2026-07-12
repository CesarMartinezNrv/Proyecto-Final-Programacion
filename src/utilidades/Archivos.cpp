#include "Archivos.h"
#include <fstream>
#include <iostream>

void Archivos::guardarClientes(){
    std::ofstream archivo("clientes.txt");
    if(archivo.is_open()){
        archivo << "Clientes guardados correctamente." << std::endl;
        archivo.close();
    }
}

void Archivos::cargarClientes(){
    std::ifstream archivo("clientes.txt");
    std::string linea;
    while(getline(archivo,linea)){
        std::cout << linea << std::endl;
    }
    archivo.close();
}

void Archivos::guardarTecnicos(){
    std::ofstream archivo("tecnicos.txt");
    if(archivo.is_open()){
        archivo << "Tecnicos guardados correctamente."  << std::endl;
        archivo.close();
    }
}

void Archivos::cargarTecnicos(){
    std::ifstream archivo("tecnicos.txt");
    std::string linea;
    while(getline(archivo,linea)){
        std::cout << linea << std::endl;
    }
    archivo.close();
}

void Archivos::guardarDispositivos(){
    std::ofstream archivo("dispositivos.txt");
    if(archivo.is_open()){
        archivo << "Dispositivos guardados correctamente." << std::endl;
        archivo.close();
    }
}

void Archivos::cargarDispositivos(){
    std::ifstream archivo("dispositivos.txt");
    std::string linea;
    while(getline(archivo,linea)){
        std::cout << linea << std::endl;
    }
    archivo.close();
}

void Archivos::guardarServicios(){
    std::ofstream archivo("servicios.txt");
    if(archivo.is_open()){
        archivo << "Servicios guardados correctamente." << std::endl;
        archivo.close();
    }
}

void Archivos::cargarServicios(){
    std::ifstream archivo("servicios.txt");
    std::string linea;
    while(getline(archivo,linea)){
        std::cout << linea << std::endl;
    }
    archivo.close();
}

void Archivos::guardarOrdenes(){
    std::ofstream archivo("ordenes.txt");
    if(archivo.is_open()){
        archivo << "Ordenes guardadas correctamente." << std::endl;
        archivo.close();
    }
}

void Archivos::cargarOrdenes(){
    std::ifstream archivo("ordenes.txt");
    std::string linea;
    while(getline(archivo,linea)){
        std::cout << linea << std::endl;
    }
    archivo.close();
}
Archivos::~Archivos(){
}