#include "modelos/Reparacion.hpp"
#include <iostream>

// Constructor de la clase Reparacion.
// Inicializa los atributos y valida que los valores
// ingresados no sean negativos.

Reparacion::Reparacion(std::string identificacionServicio, std::string nombre, std::string descripcion, double precioBase, int duracion, double costoRepuesto, double horasManoObra)
: ServicioTecnico(identificacionServicio, nombre, descripcion, precioBase, duracion)
{

    // Validación del costo del repuesto
    if(costoRepuesto >= 0)
        costo_repuesto = costoRepuesto;
    else
        costo_repuesto = 0;

    // Validación de las horas de mano de obra
    if(horasManoObra >= 0)
        horas_mano_obra = horasManoObra;
    else
        horas_mano_obra = 0;

}

// Devuelve el costo del repuesto
double Reparacion::getCostoRepuesto() const{

    return costo_repuesto;

}

// Devuelve las horas de mano de obra
double Reparacion::getHorasManoObra() const{

    return horas_mano_obra;

}

// Modifica el costo del repuesto
void Reparacion::setCostoRepuesto(double costo){

    if(costo >= 0)
        costo_repuesto = costo;

}

// Modifica las horas de mano de obra
void Reparacion::setHorasManoObra(double horas){

    if(horas >= 0)
        horas_mano_obra = horas;

}

// Calcula el costo total de la reparación
double Reparacion::calcularCosto() const{

    return precio_base + costo_repuesto + (horas_mano_obra * VALOR_HORA);

}

// Devuelve el tipo de servicio
std::string Reparacion::getTipo() const{

    return "Reparacion";

}

// Muestra toda la información de la reparación
void Reparacion::mostrarInformacion() const{

    std::cout << "========== REPARACION ==========" << std::endl;
    std::cout << "ID: " << identificacion_servicio << std::endl;
    std::cout << "Nombre: " << nombre << std::endl;
    std::cout << "Descripcion: " << descripcion << std::endl;
    std::cout << "Costo del repuesto: " << costo_repuesto << std::endl;
    std::cout << "Horas mano de obra: " << horas_mano_obra << std::endl;
    std::cout << "Precio Base: " << precio_base << std::endl;
    std::cout << "Costo Total: " << calcularCosto() << std::endl;

}

// Convierte la reparacion en una linea de texto para el archivo
std::string Reparacion::transformarArchivo() const{

    return "Reparacion|" + identificacion_servicio + "|" + nombre + "|" + descripcion + "|" + std::to_string(precio_base) + "|" + std::to_string(duracion_minutos) + "|" + std::to_string(costo_repuesto) + "|" + std::to_string(horas_mano_obra);
}

// Destructor de la clase Reparacion
Reparacion::~Reparacion(){

}
