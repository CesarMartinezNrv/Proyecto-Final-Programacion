#include "modelos/Persona.hpp"
#include <iostream>
#include <cctype>

Persona::Persona() : codigoPersona{""}, nombre{""}, numeroDeTelefono{""}, correo{""}, cedula{""}{}

Persona::Persona(std::string codigoPersona,
std::string nombre,
std::string numeroDeTelefono,
std::string correo,
std::string cedula) : codigoPersona{codigoPersona}{
    setNombre(nombre);
    setNumeroDeTelefono(numeroDeTelefono);
    setCorreo(correo);
    setCedula(cedula);
}

//Getters
std::string Persona::getCodigoPersona() const{ return codigoPersona;}
std::string Persona::getNombre() const{ return nombre;}
std::string Persona::getNumeroDeTelefono() const{ return numeroDeTelefono;}
std::string Persona::getCorreo() const{ return correo;}
std::string Persona::getCedula() const{ return cedula;}

//Setters
bool Persona::setNombre(std::string nuevoNombre){
    if(validarTextoNoVacio(nuevoNombre) == false){
        std::cout<<"ERROR:el nombre no puede estar vacio."<<std::endl;
        return false;
    }
    nombre = nuevoNombre;
    return true;
}

bool Persona::setNumeroDeTelefono(std::string nuevoTelefono){
    if(validarTelefono(nuevoTelefono) == false){
        std::cout<<"ERROR:el telefono debe tener 10 digitos y empezar con 0."<<std::endl;
        return false;
    }
    numeroDeTelefono = nuevoTelefono;
    return true;
}

bool Persona::setCorreo(std::string nuevoCorreo){
    if(validarCorreo(nuevoCorreo) == false){
        std::cout<<"ERROR:el correo ingresado no es valido."<<std::endl;
        return false;
    }
    correo = nuevoCorreo;
    return true;
}

bool Persona::setCedula(std::string nuevaCedula){
    if(validarCedula(nuevaCedula) == false){
        std::cout<<"ERROR:la cedula ingresada no es valida."<<std::endl;
        return false;
    }
    cedula = nuevaCedula;
    return true;
}

//Validaciones
bool Persona::validarTextoNoVacio(std::string texto) const{
    return texto != "";
}

bool Persona::validarTelefono(std::string telefono) const{
    if(telefono.size() != 10){
        return false;
    }
    for(int i{0}; i < (int)telefono.size(); i++){
        if(isdigit(telefono[i]) == false){
            return false;
        }
    }
    if(telefono[0] != '0'){
        return false;
    }
    return true;
}

bool Persona::validarCorreo(std::string correo) const{
    if(validarTextoNoVacio(correo) == false){
        return false;
    }
    if(correo.find("@") == std::string::npos){
        return false;
    }
    if(correo.find(".") == std::string::npos){
        return false;
    }
    if(correo[0] == '@'){
        return false;
    }
    if(correo[correo.size() - 1] == '.'){
        return false;
    }
    return true;
}

//Cedula ecuatoriana simplificada: 10 digitos numericos
bool Persona::validarCedula(std::string cedula) const{
    if(cedula.size() != 10){
        return false;
    }
    for(int i{0}; i < (int)cedula.size(); i++){
        if(isdigit(cedula[i]) == false){
            return false;
        }
    }
    return true;
}

Persona::~Persona(){}
