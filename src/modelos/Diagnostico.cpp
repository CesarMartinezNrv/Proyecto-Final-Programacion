#include "modelos/Diagnostico.hpp"
#include <iostream>

Diagnostico::Diagnostico(std::string id, std::string nombre, std::string descripcion, double precio, int duracion, std::string nivel, bool reporte)
: ServicioTecnico(id, nombre, descripcion, precio, duracion)
{
    nivel_revision = nivel;
    requiere_reporte = reporte;
}

std::string Diagnostico::getNivelRevision() const{
    return nivel_revision;
}

bool Diagnostico::getRequiereReporte() const{
    return requiere_reporte;
}

void Diagnostico::setNivelRevision(std::string nivel){
    nivel_revision = nivel;
}

void Diagnostico::setRequiereReporte(bool reporte){
    requiere_reporte = reporte;
}

double Diagnostico::calcularCosto() const{

    double costo = precio_base;

    if(requiere_reporte)
        costo += 20;

    return costo;
}

std::string Diagnostico::getTipo() const{
    return "Diagnostico";
}

void Diagnostico::mostrarInformacion() const{

    std::cout << "========== SERVICIO ==========" << std::endl;
    std::cout << "ID: " << id_servicio << std::endl;
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

std::string Diagnostico::transformarArchivo() const{
    return "diagnostico|"+id_servicio+"|"+nombre+"|"+descripcion+"|"+std::to_string(precio_base)+"|"+std::to_string(duracion_minutos)+"|"+nivel_revision+"|"+std::to_string(requiere_reporte);
}

Diagnostico::~Diagnostico(){

}