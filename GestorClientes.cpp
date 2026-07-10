#include "GestorClientes.hpp"
#include <iostream>
#include <fstream>
#include <sstream>

GestorClientes::GestorClientes() : clientes{nullptr}, capacidad{0}, cantidad{0}{}

GestorClientes::~GestorClientes(){
    for(int i{0}; i < cantidad; i++){
        delete clientes[i];
        clientes[i] = nullptr;
    }
    delete[] clientes;
    clientes = nullptr;
}

void GestorClientes::redimensionar(){
    int nuevaCapacidad{capacidad == 0 ? 4 : capacidad * 2};
    Cliente** nuevoArreglo{new Cliente*[nuevaCapacidad]};
    for(int i{0}; i < cantidad; i++){
        nuevoArreglo[i] = clientes[i];
    }
    delete[] clientes;
    clientes = nuevoArreglo;
    capacidad = nuevaCapacidad;
}

bool GestorClientes::agregarCliente(Cliente* nuevoCliente){
    if(nuevoCliente == nullptr){
        return false;
    }
    if(buscarPorIdentificacion(nuevoCliente->getCodigoPersona()) != nullptr){
        std::cout<<"ERROR. Ya existe un cliente con ese codigo."<<std::endl;
        return false;
    }
    if(cantidad == capacidad){
        redimensionar();
    }
    clientes[cantidad] = nuevoCliente;
    cantidad++;
    return true;
}

Cliente* GestorClientes::buscarPorIdentificacion(std::string codigoPersona) const{
    for(int i{0}; i < cantidad; i++){
        if(clientes[i]->getCodigoPersona() == codigoPersona){
            return clientes[i];
        }
    }
    return nullptr;
}

Cliente* GestorClientes::buscarPorCedula(std::string cedula) const{
    for(int i{0}; i < cantidad; i++){
        if(clientes[i]->getCedula() == cedula){
            return clientes[i];
        }
    }
    return nullptr;
}

bool GestorClientes::eliminarCliente(std::string codigoPersona){
    for(int i{0}; i < cantidad; i++){
        if(clientes[i]->getCodigoPersona() == codigoPersona){
            delete clientes[i];
            for(int j{i}; j < cantidad - 1; j++){
                clientes[j] = clientes[j + 1];
            }
            clientes[cantidad - 1] = nullptr;
            cantidad--;
            return true;
        }
    }
    return false;
}

void GestorClientes::mostrarTodos() const{
    for(int i{0}; i < cantidad; i++){
        clientes[i]->imprimirInformacionPersona();
        std::cout<<"----------------------------"<<std::endl;
    }
}

int GestorClientes::getCantidad() const{
    return cantidad;
}

void GestorClientes::guardarArchivo(std::string nombreArchivo) const{
    std::ofstream archivo(nombreArchivo);
    if(archivo.is_open() == false){
        std::cout<<"ERROR No se pudo abrir el archivo para guardar los clientes."<<std::endl;
        return;
    }
    for(int i{0}; i < cantidad; i++){
        archivo<<clientes[i]->transformarArchivo()<<std::endl;
    }
    archivo.close();
}

void GestorClientes::cargarArchivo(std::string nombreArchivo){
    std::ifstream archivo(nombreArchivo);
    if(archivo.is_open() == false){
        std::cout<<"AVISO. No existe archivo previo de clientes, se inicia vacio."<<std::endl;
        return;
    }
    std::string linea;
    while(std::getline(archivo, linea)){
        if(linea == ""){
            continue;
        }
        std::stringstream flujo(linea);
        std::string codigoPersona, nombre, numeroDeTelefono, correo, cedula, direccion, fechaDeRegistro, estadoAtencionCliente, dispositivosTexto;
        std::getline(flujo, codigoPersona, '|');
        std::getline(flujo, nombre, '|');
        std::getline(flujo, numeroDeTelefono, '|');
        std::getline(flujo, correo, '|');
        std::getline(flujo, cedula, '|');
        std::getline(flujo, direccion, '|');
        std::getline(flujo, fechaDeRegistro, '|');
        std::getline(flujo, estadoAtencionCliente, '|');
        std::getline(flujo, dispositivosTexto, '|');
        Cliente* nuevoCliente{new Cliente(codigoPersona, nombre, numeroDeTelefono, correo, cedula, direccion, fechaDeRegistro, estadoAtencionCliente)};
        for(int i{0}; i < std::stoi(dispositivosTexto); i++){
            nuevoCliente->incrementarDispositivosRegistrados();
        }
        agregarCliente(nuevoCliente);
    }
    archivo.close();
}
