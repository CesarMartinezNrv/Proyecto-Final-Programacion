#include "modelos/Persona.hpp"
#include <iostream>
#include <cctype> //Libreria para utilizar la funcion isdigit()

//Creacion del constructor por defecto (strings vacios)
//Sirve para utilizarlo en los constructores pordefecto de las clases hijas
Persona::Persona() : codigoPersona{""}, nombre{""}, numeroDeTelefono{""}, correo{""}, cedula{""}{}


//Constructor con parametros
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
        std::cout<<"ERROR. El nombre no puede estar vacio."<<std::endl;
        return false;
    }
    nombre = nuevoNombre;
    return true;
}

bool Persona::setNumeroDeTelefono(std::string nuevoTelefono){
    if(validarTelefono(nuevoTelefono) == false){
        std::cout<<"ERROR. El telefono debe tener 10 digitos y empezar con 0."<<std::endl;
        return false;
    }
    numeroDeTelefono = nuevoTelefono;
    return true;
}

bool Persona::setCorreo(std::string nuevoCorreo){
    if(validarCorreo(nuevoCorreo) == false){
        std::cout<<"ERROR. El correo ingresado no es valido."<<std::endl;
        return false;
    }
    correo = nuevoCorreo;
    return true;
}

bool Persona::setCedula(std::string nuevaCedula){
    if(validarCedula(nuevaCedula) == false){
        std::cout<<"ERROR. La cedula ingresada no es valida."<<std::endl;
        return false;
    }
    cedula = nuevaCedula;
    return true;
}

//Se decidió añadir un proceso de validacion fuera de los setters

//Verifica si el texto esta vacio, si no lo esta 
bool Persona::validarTextoNoVacio(std::string texto) const{
    if(texto != ""){
        return true;
    }
    return false;
}

//Verifica la cantidad de digitos ingresados 
//(Los digitos de los numeros de telefono en ecuador son 10)
bool Persona::validarTelefono(std::string telefono) const{
    if(telefono.size() != 10){
        return false;
    }
    for(int i{0}; i < telefono.size(); i++){
        if(isdigit(telefono[i]) == false){ //Con la funcion isdigit se comprueba que todos
            return false;                   //los caracteres del string sean numeros
        }
    }
    if(telefono[0] != '0'){ //Si el numero de telefono inicia en otro valor que no sea 0
        return false;       //no existe el numero de telefono
    }
    return true;
}

//Verifica varios parametros que garantizan que exista un correo ingresado
bool Persona::validarCorreo(std::string correo) const{
    if(validarTextoNoVacio(correo) == false){
        return false;
    }

    if(correo.find("@") == std::string::npos){ //Se utiliza .find() para que se busque el caracter @
        return false;                          //Si encuentra @ .find devuelve el indice, si no encuentra
    }                                          // retorna string::npos (Representa un valor grande)
    if(correo.find(".") == std::string::npos){
        return false;
    }
    if(correo[0] == '@'){ //Si el primerar caracter del arreglo es @ no existe el correo
        return false;
    }
    if(correo[correo.size() - 1] == '.'){
        return false;
    }
    return true;
}

bool Persona::validarCedula(std::string cedula) const{
    if(cedula.size() != 10){   //La cedula ecuatoriana tiene 10 digitos numericos
        return false;
    }
    for(int i{0}; i < cedula.size(); i++){
        if(isdigit(cedula[i]) == false){ //Verificacion de que todos los caracteres en el arreglo
            return false;                //son numeros
        }
    }
    return true;
}

//Destructor
Persona::~Persona(){}
