#include "ServicioTecnico.h"
#include <iostream>

// Constructor de la clase ServicioTecnico.
// Inicializa los atributos y valida que el precio y la duración
// no sean valores negativos.

ServicioTecnico::ServicioTecnico(std::string idServicio, std::string nom, std::string des, double precio, int duracion){

    id_servicio = idServicio;
    nombre = nom;
    descripcion = des;

    // Validación del precio base
    if(precio >= 0)
        precio_base = precio;
    else
        precio_base = 0;

    // Validación de la duración del servicio
    if(duracion >= 0)
        duracion_minutos = duracion;
    else
        duracion_minutos = 0;
}

// Devuelve el identificador del servicio
std::string ServicioTecnico::getIdServicio() const{
    return id_servicio;
}

// Devuelve el nombre del servicio
std::string ServicioTecnico::getNombre() const{
    return nombre;
}

// Devuelve el precio base del servicio
double ServicioTecnico::getPrecioBase() const{
    return precio_base;
}

// Modifica el precio base si el valor ingresado es válido
void ServicioTecnico::setPrecioBase(double precio){

    if(precio >= 0)
        precio_base = precio;
}

// Modifica la duración del servicio si el valor es válido
void ServicioTecnico::setDuracionMinutos(int minutos){

    if(minutos >= 0)
        duracion_minutos = minutos;
}

// Destructor virtual de la clase
ServicioTecnico::~ServicioTecnico(){

}
