#include "modelos/OrdenServicio.hpp"
#include <iostream>

// Constructor de la clase OrdenServicio.
// Inicializa la información básica de la orden y enlaza
// el cliente, dispositivo y servicio correspondiente

OrdenServicio::OrdenServicio(std::string idOrden, std::string fecha, std::string problema, Cliente* cli, Dispositivo* disp, ServicioTecnico* serv){
    
    id_orden = idOrden;
    fecha_ingreso = fecha;
    problema_reportado = problema;

    // Estado inicial de la orden
    diagnostico = "Pendiente";
    estado = "Pendiente";

    // Se enlazan los objetos recibidos
    cliente = cli;
    dispositivo = disp;
    servicio = serv;

    // Al crear la orden todavía no existe un técnico asignado,
    // por eso el puntero apunta a nullptr.
    tecnico = nullptr;

}

// Devuelve el identificador de la orden
std::string OrdenServicio::getIdOrden() const{

    return id_orden;

}

// Devuelve el estado actual de la orden
std::string OrdenServicio::getEstado() const{

    return estado;

}

// Modifica el estado de la orden
void OrdenServicio::setEstado(std::string nuevoEstado){

    estado = nuevoEstado;

}

// Asigna un técnico a la orden
void OrdenServicio::asignarTecnico(Tecnico* tec){

    tecnico = tec;

}

// Registra el diagnóstico realizado
void OrdenServicio::registrarDiagnostico(std::string nuevoDiagnostico){

    diagnostico = nuevoDiagnostico;

}

// Calcula el costo final del servicio.
// Se verifica que el puntero servicio no sea nullptr
// para evitar acceder a una dirección de memoria inválida.
double OrdenServicio::calcularCostoFinal() const{

    if(servicio != nullptr)
        return servicio->calcularCosto();

    return 0;

}

// Muestra toda la información de la orden
void OrdenServicio::mostrarInformacion() const{

    std::cout << "\n========== ORDEN DE SERVICIO ==========" << std::endl;
    std::cout << "ID: " << id_orden << std::endl;
    std::cout << "Fecha: " << fecha_ingreso << std::endl;
    std::cout << "Problema Reportado: " << problema_reportado << std::endl;
    std::cout << "Diagnostico: " << diagnostico << std::endl;
    std::cout << "Estado: " << estado << std::endl;

    // Se verifica que el cliente exista antes de acceder
    // a sus datos.
    if(cliente != nullptr){
        std::cout << "Cliente: " << cliente->getNombre() << std::endl;
    }

    // Se verifica que el dispositivo exista antes de utilizarlo.
    if(dispositivo != nullptr){
        std::cout << "Dispositivo: " << dispositivo->getModelo() << std::endl;
    }

    // El técnico puede ser nullptr si todavía no se ha asignado
    // uno a la orden.
    if(tecnico != nullptr){
        std::cout << "Tecnico: " << tecnico->getNombre() << std::endl;
    }

    // Se verifica que el servicio exista antes de mostrar
    // su información.
    if(servicio != nullptr){
        std::cout << "Servicio: " << servicio->getNombre() << std::endl;
        std::cout << "Tipo: " << servicio->getTipo() << std::endl;
        std::cout << "Costo Final: " << calcularCostoFinal() << std::endl;
    }

}

// Destructor de la clase OrdenServicio
OrdenServicio::~OrdenServicio(){

}
