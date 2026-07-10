#include "gestores/GestorClientes.hpp"
#include "gestores/GestorTecnicos.hpp"
#include "gestores/GestorDispositivos.hpp"
#include "modelos/HistorialServicio.hpp"
#include "utilidades/Constantes.hpp"
#include <iostream>
#include <limits>

void mostrarMenu();
void registrarCliente(GestorClientes& gestorClientes);
void registrarTecnico(GestorTecnicos& gestorTecnicos);
void registrarDispositivo(GestorDispositivos& gestorDispositivos, GestorClientes& gestorClientes);
void registrarHistorial(GestorDispositivos& gestorDispositivos, GestorTecnicos& gestorTecnicos);

int main(){
GestorClientes gestorClientes;
GestorTecnicos gestorTecnicos;
GestorDispositivos gestorDispositivos;

gestorClientes.cargarArchivo(Constantes::ARCHIVO_CLIENTES);
gestorTecnicos.cargarArchivo(Constantes::ARCHIVO_TECNICOS);
gestorDispositivos.cargarArchivo(Constantes::ARCHIVO_DISPOSITIVOS);
HistorialServicio::cargarArchivo(Constantes::ARCHIVO_HISTORIAL);

int opcion{-1};
while(opcion != 0){
    mostrarMenu();
    std::cin>>opcion;
    if(std::cin.fail()){
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout<<"ERROR:ingrese un numero valido."<<std::endl;
        continue;
    }
    switch(opcion){
        case 1:
            registrarCliente(gestorClientes);
            break;
        case 2:
            registrarTecnico(gestorTecnicos);
            break;
        case 3:
            registrarDispositivo(gestorDispositivos, gestorClientes);
            break;
        case 4:
            registrarHistorial(gestorDispositivos, gestorTecnicos);
            break;
        case 5:
            gestorClientes.mostrarTodos();
            break;
        case 6:
            gestorTecnicos.mostrarTodos();
            break;
        case 7:
            gestorDispositivos.mostrarTodos();
            break;
        case 8:
            HistorialServicio::mostrarTodos();
            break;
        case 0:
            std::cout<<"Guardando datos y cerrando el sistema..."<<std::endl;
            break;
        default:
            std::cout<<"Opcion invalida."<<std::endl;
            break;
    }
}

gestorClientes.guardarArchivo(Constantes::ARCHIVO_CLIENTES);
gestorTecnicos.guardarArchivo(Constantes::ARCHIVO_TECNICOS);
gestorDispositivos.guardarArchivo(Constantes::ARCHIVO_DISPOSITIVOS);
HistorialServicio::guardarArchivo(Constantes::ARCHIVO_HISTORIAL);
HistorialServicio::liberarMemoria();

return 0;
}

void mostrarMenu(){
    std::cout<<std::endl<<"===== Sistema de Gestion de Servicios Tecnologicos ====="<<std::endl;
    std::cout<<"1. Registrar cliente"<<std::endl;
    std::cout<<"2. Registrar tecnico"<<std::endl;
    std::cout<<"3. Registrar dispositivo"<<std::endl;
    std::cout<<"4. Registrar historial de servicio"<<std::endl;
    std::cout<<"5. Mostrar clientes"<<std::endl;
    std::cout<<"6. Mostrar tecnicos"<<std::endl;
    std::cout<<"7. Mostrar dispositivos"<<std::endl;
    std::cout<<"8. Mostrar historial de servicios"<<std::endl;
    std::cout<<"0. Salir"<<std::endl;
    std::cout<<"Seleccione una opcion: ";
}

void registrarCliente(GestorClientes& gestorClientes){
    std::string codigoPersona, nombre, telefono, correo, cedula, direccion, fecha, estado;
    std::cin.ignore();
    std::cout<<"Codigo de cliente: ";
    std::getline(std::cin, codigoPersona);
    std::cout<<"Nombre: ";
    std::getline(std::cin, nombre);
    std::cout<<"Telefono (10 digitos, inicia con 0): ";
    std::getline(std::cin, telefono);
    std::cout<<"Correo: ";
    std::getline(std::cin, correo);
    std::cout<<"Cedula (10 digitos): ";
    std::getline(std::cin, cedula);
    std::cout<<"Direccion: ";
    std::getline(std::cin, direccion);
    std::cout<<"Fecha de registro: ";
    std::getline(std::cin, fecha);
    std::cout<<"Estado de atencion (activo/inactivo): ";
    std::getline(std::cin, estado);

    Cliente* nuevoCliente{new Cliente(codigoPersona, nombre, telefono, correo, cedula, direccion, fecha, estado)};
    if(gestorClientes.agregarCliente(nuevoCliente) == false){
        delete nuevoCliente;
    }
}

void registrarTecnico(GestorTecnicos& gestorTecnicos){
    std::string codigoPersona, nombre, telefono, correo, cedula, especialidad;
    std::cin.ignore();
    std::cout<<"Codigo de tecnico: ";
    std::getline(std::cin, codigoPersona);
    std::cout<<"Nombre: ";
    std::getline(std::cin, nombre);
    std::cout<<"Telefono (10 digitos, inicia con 0): ";
    std::getline(std::cin, telefono);
    std::cout<<"Correo: ";
    std::getline(std::cin, correo);
    std::cout<<"Cedula (10 digitos): ";
    std::getline(std::cin, cedula);
    std::cout<<"Especialidad: ";
    std::getline(std::cin, especialidad);

    Tecnico* nuevoTecnico{new Tecnico(codigoPersona, nombre, telefono, correo, cedula, especialidad)};
    if(gestorTecnicos.agregarTecnico(nuevoTecnico) == false){
        delete nuevoTecnico;
    }
}

void registrarDispositivo(GestorDispositivos& gestorDispositivos, GestorClientes& gestorClientes){
    std::string idDispositivo, idCliente, tipo, marca, modelo, numeroSerie, estado;
    std::cin.ignore();
    std::cout<<"ID de dispositivo: ";
    std::getline(std::cin, idDispositivo);
    std::cout<<"ID de cliente propietario: ";
    std::getline(std::cin, idCliente);

    Cliente* clienteEncontrado{gestorClientes.buscarPorId(idCliente)};
    if(clienteEncontrado == nullptr){
        std::cout<<"ERROR:no existe un cliente con ese id."<<std::endl;
        return;
    }

    std::cout<<"Tipo: ";
    std::getline(std::cin, tipo);
    std::cout<<"Marca: ";
    std::getline(std::cin, marca);
    std::cout<<"Modelo: ";
    std::getline(std::cin, modelo);
    std::cout<<"Numero de serie: ";
    std::getline(std::cin, numeroSerie);
    std::cout<<"Estado (activo/en_reparacion/dado_de_baja): ";
    std::getline(std::cin, estado);

    Dispositivo* nuevoDispositivo{new Dispositivo(idDispositivo, idCliente, tipo, marca, modelo, numeroSerie, estado)};
    if(gestorDispositivos.agregarDispositivo(nuevoDispositivo) == false){
        delete nuevoDispositivo;
        return;
    }
    clienteEncontrado->incrementarDispositivosRegistrados();
}

void registrarHistorial(GestorDispositivos& gestorDispositivos, GestorTecnicos& gestorTecnicos){
    std::string idServicio, idDispositivo, idTecnico, fecha, descripcion, diagnostico, solucion;
    double costo{0.0};
    std::cin.ignore();
    std::cout<<"ID de servicio: ";
    std::getline(std::cin, idServicio);
    std::cout<<"ID de dispositivo: ";
    std::getline(std::cin, idDispositivo);

    if(gestorDispositivos.buscarPorId(idDispositivo) == nullptr){
        std::cout<<"ERROR:no existe un dispositivo con ese id."<<std::endl;
        return;
    }

    std::cout<<"ID de tecnico: ";
    std::getline(std::cin, idTecnico);

    Tecnico* tecnicoEncontrado{gestorTecnicos.buscarPorIdentificacion(idTecnico)};
    if(tecnicoEncontrado == nullptr){
        std::cout<<"ERROR:no existe un tecnico con ese id."<<std::endl;
        return;
    }

    std::cout<<"Fecha: ";
    std::getline(std::cin, fecha);
    std::cout<<"Descripcion: ";
    std::getline(std::cin, descripcion);
    std::cout<<"Diagnostico: ";
    std::getline(std::cin, diagnostico);
    std::cout<<"Solucion: ";
    std::getline(std::cin, solucion);
    std::cout<<"Costo: ";
    std::cin>>costo;

    HistorialServicio* nuevoRegistro{new HistorialServicio(idServicio, idDispositivo, idTecnico, fecha, descripcion, diagnostico, solucion, costo)};
    if(HistorialServicio::agregar(nuevoRegistro) == false){
        delete nuevoRegistro;
        return;
    }
    tecnicoEncontrado->registrarServicioAtendido();
}
