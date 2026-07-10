#include "gestores/GestorTecnicos.hpp"
#include <cassert>
#include <iostream>

int main(){
    GestorTecnicos gestor;

    Tecnico* tecnico1{new Tecnico("T001", "Luis Ramirez", "0987654321", "luis@correo.com", "1122334455", "Hardware")};
    assert(gestor.agregarTecnico(tecnico1) == true);
    assert(gestor.getCantidad() == 1);
    assert(tecnico1->getEstadoDisponible() == true);

    tecnico1->marcarComoOcupado();
    assert(tecnico1->getEstadoDisponible() == false);
    assert(gestor.buscarDisponible() == nullptr);

    tecnico1->registrarServicioAtendido();
    assert(tecnico1->getCantidadServiciosAtendidos() == 1);

    assert(gestor.buscarPorIdentificacion("T001") != nullptr);
    assert(gestor.buscarPorCedula("1122334455") != nullptr);

    assert(gestor.eliminarTecnico("T001") == true);
    assert(gestor.getCantidad() == 0);

    std::cout<<"prueba_tecnicos: OK"<<std::endl;
    return 0;
}
