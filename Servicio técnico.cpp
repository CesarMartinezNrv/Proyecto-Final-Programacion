#include "ServicioTecnico.h"
#include <iostream> 

ServicioTecnico::ServicioTecnico(std::string id, std::string nom, std::string des, double precio, int duracion){

    id_servicio = id;
    nombre = nom;
    descripcion = des;

    if(precio >= 0)
        precio_base = precio;
    else
        precio_base = 0;

    if(duracion >= 0)
        duracion_minutos = duracion;
    else
        duracion_minutos = 0;
}

std::string ServicioTecnico::getIdServicio() const{
    return id_servicio;
}

std::string ServicioTecnico::getNombre() const{
    return nombre;
}

double ServicioTecnico::getPrecioBase() const{
    return precio_base;
}

void ServicioTecnico::setPrecioBase(double precio){

    if(precio >= 0)
        precio_base = precio;
}

void ServicioTecnico::setDuracionMinutos(int minutos){

    if(minutos >= 0)
        duracion_minutos = minutos;
}

ServicioTecnico::~ServicioTecnico(){

}