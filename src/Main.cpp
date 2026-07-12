#include <iostream>
#include "ServicioTecnico.h"
#include "Diagnostico.h"
#include "Reparacion.h"
#include "MantenimientoPreventivo.h"
#include "OrdenServicio.h"
#include "GestorServicios.h"
#include "GestorOrdenes.h"
#include "Archivos.h"
#include "Cliente.h"
#include "Tecnico.h"
#include "Dispositivo.h"

int main(){

    std::cout << "==========================================" << std::endl;
    std::cout << " SISTEMA DE GESTION DE SERVICIOS TECNICOS " << std::endl;
    std::cout << "==========================================" << std::endl;

    Cliente* cliente = new Cliente("C001","Juan Perez");
    Tecnico* tecnico = new Tecnico("T001","Carlos Ruiz");
    Dispositivo* dispositivo = new Dispositivo("D001","Laptop Dell");

    ServicioTecnico* servicio1 = new Diagnostico(
        "S001",
        "Diagnostico General",
        "Revision completa",
        30,
        45,
        "Completo",
        true
    );

    ServicioTecnico* servicio2 = new Reparacion(
        "S002",
        "Cambio de Pantalla",
        "Pantalla dañada",
        50,
        90,
        120,
        2
    );

    ServicioTecnico* servicio3 = new MantenimientoPreventivo(
        "S003",
        "Mantenimiento",
        "Limpieza interna",
        40,
        60,
        true,
        true
    );

    GestorServicios gestorServicios;

    gestorServicios.agregarServicio(servicio1);
    gestorServicios.agregarServicio(servicio2);
    gestorServicios.agregarServicio(servicio3);

    std::cout << std::endl;
    std::cout << "LISTA DE SERVICIOS" << std::endl;

    gestorServicios.listarServicios();

    OrdenServicio* orden1 = new OrdenServicio(
        "O001",
        "11/07/2026",
        "El equipo no enciende",
        cliente,
        dispositivo,
        servicio1
    );

    orden1->asignarTecnico(tecnico);

    orden1->registrarDiagnostico(
        "Se detecto una falla en la fuente de poder."
    );

    orden1->setEstado("En proceso");

    GestorOrdenes gestorOrdenes;

    gestorOrdenes.agregarOrden(orden1);

    std::cout << std::endl;
    std::cout << "LISTA DE ORDENES" << std::endl;

    gestorOrdenes.listarOrdenes();

    gestorOrdenes.actualizarEstado(
        "O001",
        "Finalizada"
    );

    std::cout << std::endl;
    std::cout << "ORDENES PENDIENTES" << std::endl;

    gestorOrdenes.listarOrdenesPendientes();

    Archivos archivos;

    archivos.guardarClientes();
    archivos.guardarTecnicos();
    archivos.guardarDispositivos();
    archivos.guardarServicios();
    archivos.guardarOrdenes();

    std::cout << std::endl;
    std::cout << "LECTURA DE ARCHIVOS" << std::endl;

    archivos.cargarClientes();
    archivos.cargarTecnicos();
    archivos.cargarDispositivos();
    archivos.cargarServicios();
    archivos.cargarOrdenes();

    delete cliente;
    delete tecnico;
    delete dispositivo;

    return 0;
}