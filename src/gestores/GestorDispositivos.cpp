#include "gestores/GestorDispositivos.hpp"
#include <iostream>
#include <fstream>

GestorDispositivos::GestorDispositivos() : dispositivos{nullptr}, capacidad{0}, cantidad{0}{}

GestorDispositivos::~GestorDispositivos(){
    for(int i{0}; i < cantidad; i++){
        delete dispositivos[i];
        dispositivos[i] = nullptr;
    }
    delete[] dispositivos;
    dispositivos = nullptr;
}

void GestorDispositivos::redimensionar(){
    int nuevaCapacidad{capacidad == 0 ? 4 : capacidad * 2};
    Dispositivo** nuevoArreglo{new Dispositivo*[nuevaCapacidad]};
    for(int i{0}; i < cantidad; i++){
        nuevoArreglo[i] = dispositivos[i];
    }
    delete[] dispositivos;
    dispositivos = nuevoArreglo;
    capacidad = nuevaCapacidad;
}

bool GestorDispositivos::agregarDispositivo(Dispositivo* nuevoDispositivo){
    if(nuevoDispositivo == nullptr){
        return false;
    }
    if(buscarPorIdentificacion(nuevoDispositivo->getIdentificacionDispositivo()) != nullptr){
        std::cout<<"ERROR. Ya existe un dispositivo con ese id."<<std::endl;
        return false;
    }
    if(cantidad == capacidad){
        redimensionar();
    }
    dispositivos[cantidad] = nuevoDispositivo;
    cantidad++;
    return true;
}

Dispositivo* GestorDispositivos::buscarPorIdentificacion(std::string identificacionDispositivo) const{
    for(int i{0}; i < cantidad; i++){
        if(dispositivos[i]->getIdentificacionDispositivo() == identificacionDispositivo){
            return dispositivos[i];
        }
    }
    return nullptr;
}

void GestorDispositivos::mostrarPorCliente(std::string idCliente) const{
    for(int i{0}; i < cantidad; i++){
        if(dispositivos[i]->getIdentificacionCliente() == idCliente){
            dispositivos[i]->mostrarInformacion();
            std::cout<<"----------------------------"<<std::endl;
        }
    }
}

bool GestorDispositivos::eliminarDispositivo(std::string identificacionDispositivo){
    for(int i{0}; i < cantidad; i++){
        if(dispositivos[i]->getIdentificacionDispositivo() == identificacionDispositivo){
            delete dispositivos[i];
            for(int j{i}; j < cantidad - 1; j++){
                dispositivos[j] = dispositivos[j + 1];
            }
            dispositivos[cantidad - 1] = nullptr;
            cantidad--;
            return true;
        }
    }
    return false;
}

void GestorDispositivos::mostrarTodos() const{
    for(int i{0}; i < cantidad; i++){
        dispositivos[i]->mostrarInformacion();
        std::cout<<"----------------------------"<<std::endl;
    }
}

int GestorDispositivos::getCantidad() const{
    return cantidad;
}

void GestorDispositivos::guardarArchivo(std::string nombreArchivo) const{
    std::ofstream archivo(nombreArchivo);
    if(archivo.is_open() == false){
        std::cout<<"ERROR. No se pudo abrir el archivo para guardar los dispositivos."<<std::endl;
        return;
    }
    for(int i{0}; i < cantidad; i++){
        archivo<<dispositivos[i]->aTextoArchivo()<<std::endl;
    }
    archivo.close();
}

void GestorDispositivos::cargarArchivo(std::string nombreArchivo){
    std::ifstream archivo(nombreArchivo);
    if(archivo.is_open() == false){
        std::cout<<"AVISO. No existe archivo previo de dispositivos, se inicia vacio."<<std::endl;
        return;
    }
    std::string linea;
    while(std::getline(archivo, linea)){
        if(linea == ""){
            continue;
        }
        Dispositivo* nuevoDispositivo{new Dispositivo(Dispositivo::desdeTextoArchivo(linea))};
        agregarDispositivo(nuevoDispositivo);
    }
    archivo.close();
}
