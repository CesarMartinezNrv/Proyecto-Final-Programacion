#include "modelos/Dispositivo.hpp"
#include <iostream>
#include <sstream>

Dispositivo::Dispositivo() : identificacionDispositivo{""}, identificacionCliente{""}, tipo{""}, marca{""}, modelo{""}, numeroSerie{""}, estado{"activo"}{}

Dispositivo::Dispositivo(std::string identificacionDispositivo,
std::string identificacionCliente,
std::string tipo,
std::string marca,
std::string modelo,
std::string numeroSerie,
std::string estado) : identificacionDispositivo{identificacionDispositivo}, identificacionCliente{identificacionCliente}{
    setTipo(tipo);
    setMarca(marca);
    setModelo(modelo);
    setNumeroSerie(numeroSerie);
    setEstado(estado);
}

//Getters
std::string Dispositivo::getIdentificacionDispositivo() const{ return identificacionDispositivo;}
std::string Dispositivo::getIdentificacionCliente() const{ return identificacionCliente;}
std::string Dispositivo::getTipo() const{ return tipo;}
std::string Dispositivo::getMarca() const{ return marca;}
std::string Dispositivo::getModelo() const{ return modelo;}
std::string Dispositivo::getNumeroSerie() const{ return numeroSerie;}
std::string Dispositivo::getEstado() const{ return estado;}

//Setters
bool Dispositivo::setTipo(std::string nuevoTipo){
    if(validarTextoNoVacio(nuevoTipo) == false){
        std::cout<<"ERROR. El tipo de dispositivo no puede estar vacio."<<std::endl;
        return false;
    }
    else{
    tipo = nuevoTipo;
    return true;
    }
}

bool Dispositivo::setMarca(std::string nuevaMarca){
    if(validarTextoNoVacio(nuevaMarca) == false){
        std::cout<<"ERROR:la marca no puede estar vacia."<<std::endl;
        return false;
    }
    marca = nuevaMarca;
    return true;
}

bool Dispositivo::setModelo(std::string nuevoModelo){
    if(validarTextoNoVacio(nuevoModelo) == false){
        std::cout<<"ERROR. El modelo no puede estar vacio."<<std::endl;
        return false;
    }
    else{
    modelo = nuevoModelo;
    return true;
    }
}

bool Dispositivo::setNumeroSerie(std::string nuevoNumeroSerie){
    if(validarTextoNoVacio(nuevoNumeroSerie) == false){
        std::cout<<"ERROR. El numero de serie no puede estar vacio."<<std::endl;
        return false;
    }
    else{
    numeroSerie = nuevoNumeroSerie;
    return true;
    }
}

bool Dispositivo::setEstado(std::string nuevoEstado){
    if(validarEstado(nuevoEstado) == false){
        std::cout<<"ERROR. El estado debe ser activo, en_reparacion o dado_de_baja."<<std::endl;
        return false;
    }
    else{
    estado = nuevoEstado;
    return true;
    }
}

void Dispositivo::mostrarInformacion() const{
    std::cout<<"ID dispositivo: "<<identificacionDispositivo<<std::endl;
    std::cout<<"ID cliente: "<<identificacionCliente<<std::endl;
    std::cout<<"Tipo: "<<tipo<<std::endl;
    std::cout<<"Marca: "<<marca<<std::endl;
    std::cout<<"Modelo: "<<modelo<<std::endl;
    std::cout<<"Numero de serie: "<<numeroSerie<<std::endl;
    std::cout<<"Estado: "<<estado<<std::endl;
}

std::string Dispositivo::aTextoArchivo() const{
    return identificacionDispositivo<<"|"<<identificacionCliente<<"|"<<tipo<<"|"<<marca<<"|"<<modelo<<"|"<<numeroSerie<<"|"<<estado;
}

Dispositivo Dispositivo::desdeTextoArchivo(std::string linea){
    std::stringstream flujo(linea);
    std::string identificacionDispositivo, identificacionCliente, tipo, marca, modelo, numeroSerie, estado;
    std::getline(flujo, identificacionDispositivo, '|');
    std::getline(flujo, identificacionCliente, '|');
    std::getline(flujo, tipo, '|');
    std::getline(flujo, marca, '|');
    std::getline(flujo, modelo, '|');
    std::getline(flujo, numeroSerie, '|');
    std::getline(flujo, estado, '|');
    return Dispositivo(identificacionDispositivo, identificacionCliente, tipo, marca, modelo, numeroSerie, estado);
}

bool Dispositivo::operator==(const Dispositivo& otro) const{
    return identificacionDispositivo == otro.identificacionDispositivo;
}

bool Dispositivo::validarTextoNoVacio(std::string texto) const{
    return texto != "";
}

bool Dispositivo::validarEstado(std::string estado) const{
    if(estado == "activo"){
        return true;
    }
    else if(estado == "en_reparacion"){
        return true;
    }
    else if(estado == "dado_de_baja"){
        return true;
    }
    else{
        return false;
    }
}
