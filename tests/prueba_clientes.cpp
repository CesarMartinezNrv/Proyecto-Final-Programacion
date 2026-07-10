#include "gestores/GestorClientes.hpp"
#include <cassert>
#include <iostream>

int main(){
    GestorClientes gestor;

    Cliente* cliente1{new Cliente("C001", "Ana Perez", "0991234567", "ana@correo.com", "1234567890", "Av. Amazonas", "2026-01-01", "activo")};
    assert(gestor.agregarCliente(cliente1) == true);
    assert(gestor.getCantidad() == 1);

    Cliente* clienteDuplicado{new Cliente("C001", "Otro Nombre", "0991234567", "otro@correo.com", "1234567890", "Av. 10 de Agosto", "2026-01-02", "activo")};
    assert(gestor.agregarCliente(clienteDuplicado) == false);
    delete clienteDuplicado;

    assert(gestor.buscarPorIdentificacion("C001") != nullptr);
    assert(gestor.buscarPorCedula("1234567890") != nullptr);
    assert(gestor.buscarPorIdentificacion("NOEXISTE") == nullptr);

    assert(gestor.eliminarCliente("C001") == true);
    assert(gestor.getCantidad() == 0);

    std::cout<<"prueba_clientes: OK"<<std::endl;
    return 0;
}
