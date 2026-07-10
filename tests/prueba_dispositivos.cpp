#include "gestores/GestorDispositivos.hpp"
#include <cassert>
#include <iostream>

int main(){
    GestorDispositivos gestor;

    Dispositivo* dispositivo1{new Dispositivo("D001", "C001", "Laptop", "Dell", "Inspiron 15", "SN12345", "activo")};
    assert(gestor.agregarDispositivo(dispositivo1) == true);
    assert(gestor.getCantidad() == 1);

    Dispositivo* dispositivoDuplicado{new Dispositivo("D001", "C002", "Laptop", "HP", "Pavilion", "SN99999", "activo")};
    assert(gestor.agregarDispositivo(dispositivoDuplicado) == false);
    delete dispositivoDuplicado;

    assert(gestor.buscarPorIdentificacion("D001") != nullptr);
    assert(gestor.buscarPorIdentificacion("NOEXISTE") == nullptr);

    assert(gestor.eliminarDispositivo("D001") == true);
    assert(gestor.getCantidad() == 0);

    std::cout<<"prueba_dispositivos: OK"<<std::endl;
    return 0;
}
