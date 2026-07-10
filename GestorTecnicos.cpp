#include "GestorTecnicos.hpp"
#include <iostream>
#include <fstream>
#include <sstream>

GestorTecnicos::GestorTecnicos() : tecnicos{nullptr}, capacidad{0}, cantidad{0}{}
GestorTecnicos::~GestorTecnicos(){
    for(int i{0}; i < cantidad; i++){
        delete tecnicos[i];
        tecnicos[i] = nullptr;
    }
    delete[] tecnicos;
    tecnicos = nullptr;
}
void GestorTecnicos::redimensionar(){
    int nuevaCapacidad{capacidad == 0 ? 4 : capacidad * 2};
    Tecnico** nuevoArreglo{new Tecnico*[nuevaCapacidad]};
    for(int i{0}; i < cantidad; i++){
        nuevoArreglo[i] = tecnicos[i];
    }
    delete[] tecnicos;
    tecnicos = nuevoArreglo;
    capacidad = nuevaCapacidad;
}
bool GestorTecnicos::agregarTecnico(Tecnico* nuevoTecnico){
    if(nuevoTecnico == nullptr){
        return false;
    }
    if(buscarPorIdentificacion(nuevoTecnico->getCodigoPersona()) != nullptr){
        std::cout<<"ERROR. Ya existe un tecnico con ese codigo."<<std::endl;
        return false;
    }
    if(cantidad == capacidad){
        redimensionar();
    }
    tecnicos[cantidad] = nuevoTecnico;
    cantidad++;
    return true;
}

Tecnico* GestorTecnicos::buscarPorIdentificacion(std::string codigoPersona) const{
    for(int i{0}; i < cantidad; i++){
        if(tecnicos[i]->getCodigoPersona() == codigoPersona){
            return tecnicos[i];
        }
    }
    return nullptr;
}

Tecnico* GestorTecnicos::buscarPorCedula(std::string cedula) const{
    for(int i{0}; i < cantidad; i++){
        if(tecnicos[i]->getCedula() == cedula){
            return tecnicos[i];
        }
    }
    return nullptr;
}

Tecnico* GestorTecnicos::buscarDisponible() const{
    for(int i{0}; i < cantidad; i++){
        if(tecnicos[i]->getEstadoDisponible() == true){
            return tecnicos[i];
        }
    }
    return nullptr;
}

bool GestorTecnicos::eliminarTecnico(std::string codigoPersona){
    for(int i{0}; i < cantidad; i++){
        if(tecnicos[i]->getCodigoPersona() == codigoPersona){
            delete tecnicos[i];
            for(int j{i}; j < cantidad - 1; j++){
                tecnicos[j] = tecnicos[j + 1];
            }
            tecnicos[cantidad - 1] = nullptr;
            cantidad--;
            return true;
        }
    }
    return false;
}

void GestorTecnicos::mostrarTodos() const{
    for(int i{0}; i < cantidad; i++){
        tecnicos[i]->imprimirInformacionPersona();
        std::cout<<"----------------------------"<<std::endl;
    }
}

int GestorTecnicos::getCantidad() const{
    return cantidad;
}

void GestorTecnicos::guardarArchivo(std::string nombreArchivo) const{
    std::ofstream archivo(nombreArchivo);
    if(archivo.is_open() == false){
        std::cout<<"ERROR. No se pudo abrir el archivo para guardar los tecnicos."<<std::endl;
        return;
    }
    for(int i{0}; i < cantidad; i++){
        archivo<<tecnicos[i]->transformarArchivo()<<std::endl;
    }
    archivo.close();
}

void GestorTecnicos::cargarArchivo(std::string nombreArchivo){
    std::ifstream archivo(nombreArchivo);
    if(archivo.is_open() == false){
        std::cout<<"AVISO. No existe archivo previo de tecnicos, se inicia vacio."<<std::endl;
        return;
    }
    std::string linea;
    while(std::getline(archivo, linea)){
        if(linea == ""){
            continue;
        }
        std::stringstream flujo(linea);
        std::string codigoPersona, nombre, numeroDeTelefono, correo, cedula, especialidad, disponibleTexto, serviciosTexto;
        std::getline(flujo, codigoPersona, '|');
        std::getline(flujo, nombre, '|');
        std::getline(flujo, numeroDeTelefono, '|');
        std::getline(flujo, correo, '|');
        std::getline(flujo, cedula, '|');
        std::getline(flujo, especialidad, '|');
        std::getline(flujo, disponibleTexto, '|');
        std::getline(flujo, serviciosTexto, '|');
        Tecnico* nuevoTecnico{new Tecnico(codigoPersona, nombre, numeroDeTelefono, correo, cedula, especialidad)};
        if(disponibleTexto == "0"){
            nuevoTecnico->marcarComoOcupado();
        }
        for(int i{0}; i < std::stoi(serviciosTexto); i++){
            nuevoTecnico->registrarServicioAtendido();
        }
        agregarTecnico(nuevoTecnico);
    }
    archivo.close();
}
