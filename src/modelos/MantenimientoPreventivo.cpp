#include "modelos/MantenimientoPreventivo.hpp"
#include <iostream>

// Constructor de la clase MantenimientoPreventivo.
// Inicializa los atributos propios y llama al constructor
// de la clase base ServicioTecnico.

MantenimientoPreventivo::MantenimientoPreventivo(std::string identificacionServicio, std::string nombre, std::string descripcion, double precioBase, int duracion, bool limpieza, bool pasta)
: ServicioTecnico(identificacionServicio, nombre, descripcion, precioBase, duracion)
{

    incluye_limpieza = limpieza;
    incluye_pasta_termica = pasta;

}

// Devuelve si el servicio incluye limpieza
bool MantenimientoPreventivo::getIncluyeLimpieza() const{

    return incluye_limpieza;

}

// Devuelve si el servicio incluye cambio de pasta térmica
bool MantenimientoPreventivo::getIncluyePastaTermica() const{

    return incluye_pasta_termica;

}

// Modifica si el servicio incluye limpieza
void MantenimientoPreventivo::setIncluyeLimpieza(bool limpieza){

    incluye_limpieza = limpieza;

}

// Modifica si el servicio incluye cambio de pasta térmica
void MantenimientoPreventivo::setIncluyePastaTermica(bool pasta){

    incluye_pasta_termica = pasta;

}

// Calcula el costo total del mantenimiento
double MantenimientoPreventivo::calcularCosto() const{

    double total = precio_base;

    if(incluye_limpieza)
        total += RECARGO_LIMPIEZA;

    if(incluye_pasta_termica)
        total += RECARGO_PASTA;

    return total;

}

// Devuelve el tipo de servicio
std::string MantenimientoPreventivo::getTipo() const{

    return "Mantenimiento Preventivo";

}

// Muestra la información del mantenimiento preventivo
void MantenimientoPreventivo::mostrarInformacion() const{

    std::cout << "====== MANTENIMIENTO PREVENTIVO ======" << std::endl;
    std::cout << "ID: " << identificacion_servicio << std::endl;
    std::cout << "Nombre: " << nombre << std::endl;
    std::cout << "Descripcion: " << descripcion << std::endl;
    std::cout << "Precio Base: " << precio_base << std::endl;

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
    std::cout << "Costo Total: " << calcularCosto() << std::endl;

}

// Convierte el mantenimiento en una linea de texto para el archivo
std::string MantenimientoPreventivo::transformarArchivo() const{

    std::string limpiezaTexto;
    if(incluye_limpieza){
        limpiezaTexto = "1";
    }
    else{
        limpiezaTexto = "0";
    }

    std::string pastaTexto;
    if(incluye_pasta_termica){
        pastaTexto = "1";
    }
    else{
        pastaTexto = "0";
    }

    return "MantenimientoPreventivo|" + identificacion_servicio + "|" + nombre + "|" + descripcion + "|" + std::to_string(precio_base) + "|" + std::to_string(duracion_minutos) + "|" + limpiezaTexto + "|" + pastaTexto;
}

// Destructor de la clase MantenimientoPreventivo
MantenimientoPreventivo::~MantenimientoPreventivo(){

}
