#include "modelos/Cliente.hpp"
#include <iostream>

//Constructor por defecto
Cliente::Cliente() : Persona(), direccion{""}, fechaDeRegistro{""}, estadoAtencionCliente{""}, cantidadDispositivosRegistrados{0}{}

//Constructor con parametros
Cliente::Cliente(std::string codigoPersona,
std::string nombre,
std::string numeroDeTelefono,
std::string correo,
std::string cedula,
std::string direccion,
std::string fechaDeRegistro,
std::string estadoAtencionCliente) : Persona(codigoPersona, nombre, numeroDeTelefono, correo, cedula), cantidadDispositivosRegistrados{0}{
    setDireccion(direccion);
    setFechaDeRegistro(fechaDeRegistro);
    setEstadoAtencionCliente(estadoAtencionCliente);
}

//Getters
std::string Cliente::getDireccion() const{ return direccion;}
std::string Cliente::getFechaDeRegistro() const{ return fechaDeRegistro;}
std::string Cliente::getEstadoAtencionCliente() const{ return estadoAtencionCliente;}
int Cliente::getCantidadDispositivosRegistrados() const{ return cantidadDispositivosRegistrados;}

//Setters
bool Cliente::setDireccion(std::string nuevaDireccion){
    if(validarTextoNoVacio(nuevaDireccion) == false){
        std::cout<<"ERROR. La direccion no puede estar vacia."<<std::endl;
        return false;
    }
    direccion = nuevaDireccion;
    return true;
}

bool Cliente::setFechaDeRegistro(std::string nuevaFecha){
    if(validarTextoNoVacio(nuevaFecha) == false){
        std::cout<<"ERROR. La fecha de registro no puede estar vacia."<<std::endl;
        return false;
    }
    fechaDeRegistro = nuevaFecha;
    return true;
}

bool Cliente::setEstadoAtencionCliente(std::string nuevoEstado){
    if(validarEstadoAtencionCliente(nuevoEstado) == false){ //Solo valida "activo" o "inactivo"
        std::cout<<"ERROR. El estado de atencion debe ser activo o inactivo."<<std::endl;
        return false;
    }
    estadoAtencionCliente = nuevoEstado;
    return true;
}

void Cliente::incrementarDispositivosRegistrados(){ //Incrementa el contador de dispotivos ligados al cliente
    cantidadDispositivosRegistrados++;
}

//Override de la clase Persona 
//Retorna el string en base a la clase a la que pertence
std::string Cliente::tipoDePersona() const{
    return "Cliente";
}

void Cliente::imprimirInformacionPersona() const{
    std::cout<<"Codigo: "<<getCodigoPersona()<<std::endl;
    std::cout<<"Nombre: "<<getNombre()<<std::endl;
    std::cout<<"Cedula: "<<getCedula()<<std::endl;
    std::cout<<"Telefono: "<<getNumeroDeTelefono()<<std::endl;
    std::cout<<"Correo: "<<getCorreo()<<std::endl;
    std::cout<<"Direccion: "<<direccion<<std::endl;
    std::cout<<"Fecha de registro: "<<fechaDeRegistro<<std::endl;
    std::cout<<"Estado de atencion: "<<estadoAtencionCliente<<std::endl;
    std::cout<<"Dispositivos registrados: "<<cantidadDispositivosRegistrados<<std::endl;
}

//Transforma el objeto en una linea
std::string Cliente::transformarArchivo() const{
    return getCodigoPersona()+"|"+getNombre()+"|"+getNumeroDeTelefono()+"|"+getCorreo()+"|"+getCedula()+"|"+direccion+"|"+fechaDeRegistro+"|"+estadoAtencionCliente+"|"+std::to_string(cantidadDispositivosRegistrados);
    //Se utiliza std::to_string para convertir otro tipo de dato a tipo string 
}

//Solo valida el string "activo" o "inactivo" entonces string invalidos son:
// Activo,INACTIVO, pendiente, atendido, bloqueado
bool Cliente::validarEstadoAtencionCliente(std::string estado) const{
    if(estado == "activo"){
        return true;
    }
    else if(estado == "inactivo"){
        return true;
    }
    else{
        return false;
    }
}

Cliente::~Cliente(){}
