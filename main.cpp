#include <iostream>
#include "ServicioTecnico.h"
#include "Diagnostico.h"
#include "Reparacion.h"
#include "MantenimientoPreventivo.h"

int main(){

    ServicioTecnico* servicios[3];

    servicios[0] = new Diagnostico(
        "S001",
        "Diagnostico General",
        "Revision completa del equipo",
        30,
        45,
        "Completo",
        true
    );

    servicios[1] = new Reparacion(
        "S002",
        "Cambio de Pantalla",
        "Reemplazo de pantalla dañada",
        50,
        90,
        120,
        2
    );

    servicios[2] = new MantenimientoPreventivo(
        "S003",
        "Mantenimiento Laptop",
        "Limpieza interna del equipo",
        40,
        60,
        true,
        true
    );

    std::cout << "======================================" << std::endl;
    std::cout << "   SISTEMA DE SERVICIOS TECNICOS" << std::endl;
    std::cout << "======================================" << std::endl;

    for(int i = 0; i < 3; i++){

        servicios[i]->mostrarInformacion();

        std::cout << "Tipo de Servicio: " << servicios[i]->getTipo() << std::endl;
        std::cout << "Costo Calculado: " << servicios[i]->calcularCosto() << std::endl;
        std::cout << "--------------------------------------"
                  << std::endl;
    }

    for(int i = 0; i < 3; i++){

        delete servicios[i];

    }

    return 0;
}