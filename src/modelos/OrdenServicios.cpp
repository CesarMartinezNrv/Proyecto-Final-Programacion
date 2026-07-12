#include "OrdenServicio.h"
#include <iostream>

OrdenServicio::OrdenServicio(std::string idOrden, std::string fecha, std::string problema, Cliente* cli, Dispositivo* disp, ServicioTecnico* serv){

    id_orden = idOrden;
    fecha_ingreso = fecha;
    problema_reportado = problema;

    diagnostico = "Pendiente";
    estado = "Pendiente";

    cliente = cli;
    dispositivo = disp;
    servicio = serv;
    tecnico = nullptr;

}

std::string OrdenServicio::getIdOrden() const{

    return id_orden;
}

std::string OrdenServicio::getEstado() const{

    return estado;
}

void OrdenServicio::setEstado(std::string nuevoEstado){

    estado = nuevoEstado;
}

void OrdenServicio::asignarTecnico(Tecnico* tec){

    tecnico = tec;
}

void OrdenServicio::registrarDiagnostico(std::string nuevoDiagnostico){

    diagnostico = nuevoDiagnostico;
}

double OrdenServicio::calcularCostoFinal() const{

    if(servicio != nullptr)
        return servicio->calcularCosto();

    return 0;
}

void OrdenServicio::mostrarInformacion() const{

    std::cout << "\n========== ORDEN DE SERVICIO ==========" << std::endl;
    std::cout << "ID: "  << id_orden  << std::endl;
    std::cout << "Fecha: "  << fecha_ingreso  << std::endl;
    std::cout << "Problema Reportado: "  << problema_reportado  << std::endl;
    std::cout << "Diagnostico: "  << diagnostico  << std::endl;
    std::cout << "Estado: "  << estado  << std::endl;

    if(cliente != nullptr){
        std::cout << "Cliente: "  << cliente->getNombre()  << std::endl;

    }

    if(dispositivo != nullptr){
        std::cout << "Dispositivo: "  << dispositivo->getModelo()  << std::endl;

    }

    if(tecnico != nullptr){
        std::cout << "Tecnico: "  << tecnico->getNombre()  << std::endl;
    }

    if(servicio != nullptr){
        std::cout << "Servicio: "  << servicio->getNombre()  << std::endl;
        std::cout << "Tipo: "  << servicio->getTipo()  << std::endl;
        std::cout << "Costo Final: "  << calcularCostoFinal()  << std::endl;
    }

}

OrdenServicio::~OrdenServicio(){

}