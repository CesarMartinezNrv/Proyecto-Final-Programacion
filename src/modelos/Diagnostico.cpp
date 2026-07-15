#include "modelos/Diagnostico.hpp"
#include <iostream>

// Constructor de la clase Diagnostico.
// Inicializa los atributos propios y llama al constructor
// de la clase base ServicioTecnico.

Diagnostico::Diagnostico(std::string identificacionServicio, std::string nombre, std::string descripcion, double precio, int duracion, std::string nivel, bool reporte)
: ServicioTecnico(identificacionServicio, nombre, descripcion, precio, duracion)
{
    nivel_revision = nivel;
    requiere_reporte = reporte;
}

// Devuelve el nivel de revisión del diagnóstico
std::string Diagnostico::getNivelRevision() const{
    return nivel_revision;
}

// Indica si el diagnóstico requiere reporte
bool Diagnostico::getRequiereReporte() const{
    return requiere_reporte;
}

// Modifica el nivel de revisión
void Diagnostico::setNivelRevision(std::string nivel){
    nivel_revision = nivel;
}

// Modifica si el diagnóstico requiere reporte
void Diagnostico::setRequiereReporte(bool reporte){
    requiere_reporte = reporte;
}

// Calcula el costo final del diagnóstico
double Diagnostico::calcularCosto() const{

    double costo = precio_base;

    // Si requiere reporte, se agrega un recargo
    if(requiere_reporte)
        costo += 20;

    return costo;
}

// Devuelve el tipo de servicio
std::string Diagnostico::getTipo() const{
    return "Diagnostico";
}

// Muestra toda la información del diagnóstico
void Diagnostico::mostrarInformacion() const{

    std::cout << "========== SERVICIO ==========" << std::endl;
    std::cout << "ID: " << identificacion_servicio << std::endl;
    std::cout << "Nombre: " << nombre << std::endl;
    std::cout << "Descripcion: " << descripcion << std::endl;
    std::cout << "Tipo: " << getTipo() << std::endl;
    std::cout << "Nivel de revision: " << nivel_revision << std::endl;

    std::cout << "Requiere reporte: ";

    if(requiere_reporte)
        std::cout << "Si" << std::endl;
    else
        std::cout << "No" << std::endl;

    std::cout << "Precio base: " << precio_base << std::endl;
    std::cout << "Costo final: " << calcularCosto() << std::endl;
}

// Convierte el diagnostico en una linea de texto para el archivo
std::string Diagnostico::transformarArchivo() const{

    std::string reporteTexto;
    if(requiere_reporte){
        reporteTexto = "1";
    }
    else{
        reporteTexto = "0";
    }

    return "Diagnostico|" + identificacion_servicio + "|" + nombre + "|" + descripcion + "|" + std::to_string(precio_base) + "|" + std::to_string(duracion_minutos) + "|" + nivel_revision + "|" + reporteTexto;
}

// Destructor de la clase Diagnostico
Diagnostico::~Diagnostico(){

}
