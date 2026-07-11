#include "MantenimientoPreventivo.h"
#include <iostream>

MantenimientoPreventivo::MantenimientoPreventivo, std::string id, std::string nombre, std::string descripcion, double precioBase, int duracion, bool limpieza, bool pasta)
: ServicioTecnico(id,nombre,descripcion,precioBase,duracion)
{

    incluye_limpieza = limpieza;
    incluye_pasta_termica = pasta;

}

bool MantenimientoPreventivo::getIncluyeLimpieza() const{

    return incluye_limpieza;

}

bool MantenimientoPreventivo::getIncluyePastaTermica() const{

    return incluye_pasta_termica;

}

void MantenimientoPreventivo::setIncluyeLimpieza(bool limpieza){

    incluye_limpieza = limpieza;

}

void MantenimientoPreventivo::setIncluyePastaTermica(bool pasta){

    incluye_pasta_termica = pasta;

}

double MantenimientoPreventivo::calcularCosto() const{

    double total = precio_base;

    if(incluye_limpieza)
        total += RECARGO_LIMPIEZA;

    if(incluye_pasta_termica)
        total += RECARGO_PASTA;

    return total;

}

std::string MantenimientoPreventivo::getTipo() const{

    return "Mantenimiento Preventivo";

}

void MantenimientoPreventivo::mostrarInformacion() const{

    std::cout << "====== MANTENIMIENTO PREVENTIVO ======" << std::endl;
    std::cout << "ID: "<< id_servicio<< std::endl;
    std::cout << "Nombre: "<< nombre<< std::endl;
    std::cout << "Descripcion: "<< descripcion<< std::endl;
    std::cout << "Precio Base: "<< precio_base<< std::endl;
    std::cout << "Incluye limpieza: ";

    if(incluye_limpieza)
        std::cout << "Si";
    else
        std::cout << "No";

    std::cout << std::endl;

    std::cout << "Incluye pasta termica: ";

    if(incluye_pasta_termica)
        std::cout << "Si";
    else
        std::cout << "No";

    std::cout << std::endl;
    std::cout << "Costo Total: "<< calcularCosto()<< std::endl;

}

MantenimientoPreventivo::~MantenimientoPreventivo(){

}