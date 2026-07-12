#include "Reparacion.h"
#include <iostream>

Reparacion::Reparacion(std::string id, std::string nombre, std::string descripcion, double precioBase, int duracion, double costoRepuesto, double horasManoObra)
: ServicioTecnico(id,nombre,descripcion,precioBase,duracion)
{

    if(costoRepuesto >= 0)
        costo_repuesto = costoRepuesto;
    else
        costo_repuesto = 0;

    if(horasManoObra >= 0)
        horas_mano_obra = horasManoObra;
    else
        horas_mano_obra = 0;

}

double Reparacion::getCostoRepuesto() const{

    return costo_repuesto;

}

double Reparacion::getHorasManoObra() const{

    return horas_mano_obra;

}

void Reparacion::setCostoRepuesto(double costo){

    if(costo >= 0)
        costo_repuesto = costo;

}

void Reparacion::setHorasManoObra(double horas){

    if(horas >= 0)
        horas_mano_obra = horas;

}

double Reparacion::calcularCosto() const{

    return precio_base +
           costo_repuesto +
           (horas_mano_obra * VALOR_HORA);

}

std::string Reparacion::getTipo() const{

    return "Reparacion";

}

void Reparacion::mostrarInformacion() const{

    std::cout << "========== REPARACION ==========" << std::endl;
    std::cout << "ID: "<< id_servicio<< std::endl;
    std::cout << "Nombre: "<< nombre<< std::endl;
    std::cout << "Descripcion: " << descripcion << std::endl;
    std::cout << "Costo del repuesto: " << costo_repuesto<< std::endl;
    std::cout << "Horas mano de obra: " << horas_mano_obra << std::endl;
    std::cout << "Precio Base: " << precio_base<< std::endl;
    std::cout << "Costo Total: "<< calcularCosto()<< std::endl;

}

Reparacion::~Reparacion(){

}