#include "modelos/Tecnico.hpp"
#include <iostream>

//Constructor por defecto
Tecnico::Tecnico() : Persona(), especialidad{""}, estadoDisponible{true}, cantidadServiciosAtendidos{0}{}

//Constructor con parámetros
Tecnico::Tecnico(std::string codigoPersona,
std::string nombre,
std::string numeroDeTelefono,
std::string correo,
std::string cedula,
std::string especialidad) : Persona(codigoPersona, nombre, numeroDeTelefono, correo, cedula), estadoDisponible{true}, cantidadServiciosAtendidos{0}{
    setEspecialidad(especialidad);
}

//Getters
std::string Tecnico::getEspecialidad() const{ return especialidad;}
bool Tecnico::getEstadoDisponible() const{ return estadoDisponible;}
int Tecnico::getCantidadServiciosAtendidos() const{ return cantidadServiciosAtendidos;}

//Setter
bool Tecnico::setEspecialidad(std::string nuevaEspecialidad){
    if(validarTextoNoVacio(nuevaEspecialidad) == false){
        std::cout<<"ERROR. La especialidad no puede estar vacia."<<std::endl;
        return false;
    }
    especialidad = nuevaEspecialidad;
    return true;
}


void Tecnico::marcarComoOcupado(){ //Cambia su disponibilidad como ocupado
    estadoDisponible = false;
}
void Tecnico::marcarComoDisponible(){ //Cambia su disponibilidad a disponible
    estadoDisponible = true;
}
void Tecnico::registrarServicioAtendido(){ //Aumenta el contador de servicios
    cantidadServiciosAtendidos++;
}

//Descripcion del nombre el objeto
std::string Tecnico::tipoDePersona() const{
    return "Tecnico";
}

void Tecnico::imprimirInformacionPersona() const{
    std::cout<<"Codigo: "<<getCodigoPersona()<<std::endl;
    std::cout<<"Nombre: "<<getNombre()<<std::endl;
    std::cout<<"Cedula: "<<getCedula()<<std::endl;
    std::cout<<"Telefono: "<<getNumeroDeTelefono()<<std::endl;
    std::cout<<"Correo: "<<getCorreo()<<std::endl;
    std::cout<<"Especialidad: "<<especialidad<<std::endl;
    std::cout<<"Disponible: "<<(estadoDisponible ? "si" : "no")<<std::endl; //Si el estado disponible es true imprime "si", sino imprime "no".
    std::cout<<"Servicios atendidos: "<<cantidadServiciosAtendidos<<std::endl;
}

std::string Tecnico::transformarArchivo() const{
    return getCodigoPersona()+"|"+getNombre()+"|"+getNumeroDeTelefono()+"|"+getCorreo()+"|"+getCedula()+"|"+especialidad+"|"+(estadoDisponible ? "1" : "0")+"|"+std::to_string(cantidadServiciosAtendidos);
}
//Destructor
Tecnico::~Tecnico(){}
