#include "modelos/Cliente.hpp"
#include "modelos/Tecnico.hpp"
#include "modelos/Dispositivo.hpp"
#include "modelos/ServicioTecnico.hpp"
#include "modelos/Diagnostico.hpp"
#include "modelos/Reparacion.hpp"
#include "modelos/MantenimientoPreventivo.hpp"
#include "modelos/OrdenServicio.hpp"
#include "modelos/HistorialServicio.hpp"
#include "gestores/GestorClientes.hpp"
#include "gestores/GestorTecnicos.hpp"
#include "gestores/GestorDispositivos.hpp"
#include "gestores/GestorServicios.hpp"
#include "gestores/GestorOrdenes.hpp"
#include "utilidades/Constantes.hpp"
#include <iostream>
#include <string>
#include <limits>

//Lee una opcion de menu de forma segura y limpia el resto de la linea
int leerOpcion();

void menuClientes(GestorClientes& gestorClientes);
void registrarCliente(GestorClientes& gestorClientes);
void buscarCliente(GestorClientes& gestorClientes);

void menuTecnicos(GestorTecnicos& gestorTecnicos);
void registrarTecnico(GestorTecnicos& gestorTecnicos);
void buscarTecnico(GestorTecnicos& gestorTecnicos);

void menuDispositivos(GestorDispositivos& gestorDispositivos, GestorClientes& gestorClientes);
void registrarDispositivo(GestorDispositivos& gestorDispositivos, GestorClientes& gestorClientes);
void buscarDispositivoPorIdentificacion(GestorDispositivos& gestorDispositivos);
void buscarDispositivoPorMarcaModelo(GestorDispositivos& gestorDispositivos);

void menuServicios(GestorServicios& gestorServicios);
void registrarServicio(GestorServicios& gestorServicios);
void buscarServicio(GestorServicios& gestorServicios);

void menuOrdenes(GestorOrdenes& gestorOrdenes, GestorClientes& gestorClientes, GestorTecnicos& gestorTecnicos, GestorDispositivos& gestorDispositivos, GestorServicios& gestorServicios);
void crearOrden(GestorOrdenes& gestorOrdenes, GestorClientes& gestorClientes, GestorTecnicos& gestorTecnicos, GestorDispositivos& gestorDispositivos, GestorServicios& gestorServicios);
void buscarOrden(GestorOrdenes& gestorOrdenes);
void actualizarEstadoOrden(GestorOrdenes& gestorOrdenes);

void menuHistorial();
void registrarHistorial();
void buscarHistorialPorDispositivo();
void buscarHistorialPorTecnico();

int main(){

GestorClientes gestorClientes;
GestorTecnicos gestorTecnicos;
GestorDispositivos gestorDispositivos;
GestorServicios gestorServicios;
GestorOrdenes gestorOrdenes;

gestorClientes.cargarArchivo(Constantes::ARCHIVO_CLIENTES);
gestorTecnicos.cargarArchivo(Constantes::ARCHIVO_TECNICOS);
gestorDispositivos.cargarArchivo(Constantes::ARCHIVO_DISPOSITIVOS);
gestorServicios.cargarArchivo("data/servicios.txt");
gestorOrdenes.cargarArchivo("data/ordenes.txt", gestorClientes, gestorTecnicos, gestorDispositivos, gestorServicios);
HistorialServicio::cargarArchivo(Constantes::ARCHIVO_HISTORIAL);

int opcion{-1};
while(opcion != 0){
    std::cout<<std::endl<<"===== SISTEMA DE GESTION DE SERVICIOS TECNICOS ====="<<std::endl;
    std::cout<<"1. Clientes"<<std::endl;
    std::cout<<"2. Tecnicos"<<std::endl;
    std::cout<<"3. Dispositivos"<<std::endl;
    std::cout<<"4. Servicios tecnicos"<<std::endl;
    std::cout<<"5. Ordenes de servicio"<<std::endl;
    std::cout<<"6. Historial"<<std::endl;
    std::cout<<"0. Salir"<<std::endl;
    std::cout<<"Seleccione una opcion: ";
    opcion = leerOpcion();

    if(opcion == 1){
        menuClientes(gestorClientes);
    }
    else if(opcion == 2){
        menuTecnicos(gestorTecnicos);
    }
    else if(opcion == 3){
        menuDispositivos(gestorDispositivos, gestorClientes);
    }
    else if(opcion == 4){
        menuServicios(gestorServicios);
    }
    else if(opcion == 5){
        menuOrdenes(gestorOrdenes, gestorClientes, gestorTecnicos, gestorDispositivos, gestorServicios);
    }
    else if(opcion == 6){
        menuHistorial();
    }
    else if(opcion != 0){
        std::cout<<"Opcion invalida."<<std::endl;
    }
}

gestorClientes.guardarArchivo(Constantes::ARCHIVO_CLIENTES);
gestorTecnicos.guardarArchivo(Constantes::ARCHIVO_TECNICOS);
gestorDispositivos.guardarArchivo(Constantes::ARCHIVO_DISPOSITIVOS);
gestorServicios.guardarArchivo("data/servicios.txt");
gestorOrdenes.guardarArchivo("data/ordenes.txt");
HistorialServicio::guardarArchivo(Constantes::ARCHIVO_HISTORIAL);
HistorialServicio::liberarMemoria();

std::cout<<"Datos guardados. Hasta pronto."<<std::endl;

return 0;
}

int leerOpcion(){
    int opcion{-1};
    std::cin>>opcion;
    if(std::cin.fail()){
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout<<"ERROR. Ingrese un numero valido."<<std::endl;
        return -1;
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return opcion;
}

//===== Clientes =====

void menuClientes(GestorClientes& gestorClientes){
    int opcion{-1};
    while(opcion != 0){
        std::cout<<std::endl<<"--- Clientes ---"<<std::endl;
        std::cout<<"1. Registrar cliente"<<std::endl;
        std::cout<<"2. Mostrar clientes"<<std::endl;
        std::cout<<"3. Buscar cliente"<<std::endl;
        std::cout<<"0. Volver"<<std::endl;
        std::cout<<"Seleccione una opcion: ";
        opcion = leerOpcion();

        if(opcion == 1){
            registrarCliente(gestorClientes);
        }
        else if(opcion == 2){
            gestorClientes.mostrarTodos();
        }
        else if(opcion == 3){
            buscarCliente(gestorClientes);
        }
        else if(opcion != 0){
            std::cout<<"Opcion invalida."<<std::endl;
        }
    }
}

void registrarCliente(GestorClientes& gestorClientes){
    std::string codigoPersona, nombre, telefono, correo, cedula, direccion, fecha, estado;

    std::cout<<"Codigo del cliente: ";
    std::getline(std::cin, codigoPersona);
    std::cout<<"Nombre: ";
    std::getline(std::cin, nombre);
    std::cout<<"Telefono: ";
    std::getline(std::cin, telefono);
    std::cout<<"Correo: ";
    std::getline(std::cin, correo);
    std::cout<<"Cedula: ";
    std::getline(std::cin, cedula);
    std::cout<<"Direccion: ";
    std::getline(std::cin, direccion);
    std::cout<<"Fecha de registro: ";
    std::getline(std::cin, fecha);
    std::cout<<"Estado de atencion (activo): ";
    std::getline(std::cin, estado);

    Cliente* nuevoCliente{new Cliente(codigoPersona, nombre, telefono, correo, cedula, direccion, fecha, estado)};
    if(gestorClientes.agregarCliente(nuevoCliente) == false){
        delete nuevoCliente;
        std::cout<<"No se pudo registrar el cliente."<<std::endl;
    }
    else{
        std::cout<<"Cliente registrado correctamente."<<std::endl;
    }
}

void buscarCliente(GestorClientes& gestorClientes){
    std::string codigoPersona;
    std::cout<<"Codigo del cliente a buscar: ";
    std::getline(std::cin, codigoPersona);

    Cliente* encontrado{gestorClientes.buscarPorIdentificacion(codigoPersona)};
    if(encontrado == nullptr){
        std::cout<<"No existe un cliente con ese codigo."<<std::endl;
    }
    else{
        encontrado->imprimirInformacionPersona();
    }
}

//===== Tecnicos =====

void menuTecnicos(GestorTecnicos& gestorTecnicos){
    int opcion{-1};
    while(opcion != 0){
        std::cout<<std::endl<<"--- Tecnicos ---"<<std::endl;
        std::cout<<"1. Registrar tecnico"<<std::endl;
        std::cout<<"2. Mostrar tecnicos"<<std::endl;
        std::cout<<"3. Buscar tecnico"<<std::endl;
        std::cout<<"0. Volver"<<std::endl;
        std::cout<<"Seleccione una opcion: ";
        opcion = leerOpcion();

        if(opcion == 1){
            registrarTecnico(gestorTecnicos);
        }
        else if(opcion == 2){
            gestorTecnicos.mostrarTodos();
        }
        else if(opcion == 3){
            buscarTecnico(gestorTecnicos);
        }
        else if(opcion != 0){
            std::cout<<"Opcion invalida."<<std::endl;
        }
    }
}

void registrarTecnico(GestorTecnicos& gestorTecnicos){
    std::string codigoPersona, nombre, telefono, correo, cedula, especialidad;

    std::cout<<"Codigo del tecnico: ";
    std::getline(std::cin, codigoPersona);
    std::cout<<"Nombre: ";
    std::getline(std::cin, nombre);
    std::cout<<"Telefono: ";
    std::getline(std::cin, telefono);
    std::cout<<"Correo: ";
    std::getline(std::cin, correo);
    std::cout<<"Cedula: ";
    std::getline(std::cin, cedula);
    std::cout<<"Especialidad: ";
    std::getline(std::cin, especialidad);

    Tecnico* nuevoTecnico{new Tecnico(codigoPersona, nombre, telefono, correo, cedula, especialidad)};
    if(gestorTecnicos.agregarTecnico(nuevoTecnico) == false){
        delete nuevoTecnico;
        std::cout<<"No se pudo registrar el tecnico."<<std::endl;
    }
    else{
        std::cout<<"Tecnico registrado correctamente."<<std::endl;
    }
}

void buscarTecnico(GestorTecnicos& gestorTecnicos){
    std::string codigoPersona;
    std::cout<<"Codigo del tecnico a buscar: ";
    std::getline(std::cin, codigoPersona);

    Tecnico* encontrado{gestorTecnicos.buscarPorIdentificacion(codigoPersona)};
    if(encontrado == nullptr){
        std::cout<<"No existe un tecnico con ese codigo."<<std::endl;
    }
    else{
        encontrado->imprimirInformacionPersona();
    }
}

//===== Dispositivos =====

void menuDispositivos(GestorDispositivos& gestorDispositivos, GestorClientes& gestorClientes){
    int opcion{-1};
    while(opcion != 0){
        std::cout<<std::endl<<"--- Dispositivos ---"<<std::endl;
        std::cout<<"1. Registrar dispositivo"<<std::endl;
        std::cout<<"2. Mostrar dispositivos"<<std::endl;
        std::cout<<"3. Buscar por identificacion"<<std::endl;
        std::cout<<"4. Buscar por marca y modelo"<<std::endl;
        std::cout<<"5. Mostrar dispositivos de un cliente"<<std::endl;
        std::cout<<"0. Volver"<<std::endl;
        std::cout<<"Seleccione una opcion: ";
        opcion = leerOpcion();

        if(opcion == 1){
            registrarDispositivo(gestorDispositivos, gestorClientes);
        }
        else if(opcion == 2){
            gestorDispositivos.mostrarTodos();
        }
        else if(opcion == 3){
            buscarDispositivoPorIdentificacion(gestorDispositivos);
        }
        else if(opcion == 4){
            buscarDispositivoPorMarcaModelo(gestorDispositivos);
        }
        else if(opcion == 5){
            std::string idCliente;
            std::cout<<"Codigo del cliente: ";
            std::getline(std::cin, idCliente);
            gestorDispositivos.mostrarPorCliente(idCliente);
        }
        else if(opcion != 0){
            std::cout<<"Opcion invalida."<<std::endl;
        }
    }
}

void registrarDispositivo(GestorDispositivos& gestorDispositivos, GestorClientes& gestorClientes){
    std::string idDispositivo, idCliente, tipo, marca, modelo, numeroSerie, estado;

    std::cout<<"ID del dispositivo: ";
    std::getline(std::cin, idDispositivo);
    std::cout<<"Codigo del cliente propietario: ";
    std::getline(std::cin, idCliente);

    if(gestorClientes.buscarPorIdentificacion(idCliente) == nullptr){
        std::cout<<"No existe un cliente con ese codigo."<<std::endl;
        return;
    }
    Dispositivo* nuevoDispositivo{new Dispositivo(idDispositivo, idCliente, tipo, marca, modelo, numeroSerie, estado)};
    if(gestorDispositivos.agregarDispositivo(nuevoDispositivo) == false){
        delete nuevoDispositivo;
        std::cout<<"No se pudo registrar el dispositivo."<<std::endl;
    }
    else{
        std::cout<<"Dispositivo registrado correctamente."<<std::endl;
    }
}

void buscarDispositivoPorIdentificacion(GestorDispositivos& gestorDispositivos){
    std::string idDispositivo;
    std::cout<<"ID del dispositivo a buscar: ";
    std::getline(std::cin, idDispositivo);

    Dispositivo* encontrado{gestorDispositivos.buscar(idDispositivo)};
    if(encontrado == nullptr){
        std::cout<<"No existe un dispositivo con ese id."<<std::endl;
    }
    else{
        encontrado->mostrarInformacion();
    }
}

void buscarDispositivoPorMarcaModelo(GestorDispositivos& gestorDispositivos){
    std::string marca, modelo;
    std::cout<<"Marca: ";
    std::getline(std::cin, marca);
    std::cout<<"Modelo: ";
    std::getline(std::cin, modelo);

    Dispositivo* encontrado{gestorDispositivos.buscar(marca, modelo)};
    if(encontrado == nullptr){
        std::cout<<"No existe un dispositivo con esa marca y modelo."<<std::endl;
    }
    else{
        encontrado->mostrarInformacion();
    }
}

//===== Servicios tecnicos =====

void menuServicios(GestorServicios& gestorServicios){
    int opcion{-1};
    while(opcion != 0){
        std::cout<<std::endl<<"--- Servicios tecnicos ---"<<std::endl;
        std::cout<<"1. Registrar servicio"<<std::endl;
        std::cout<<"2. Mostrar servicios"<<std::endl;
        std::cout<<"3. Buscar servicio"<<std::endl;
        std::cout<<"0. Volver"<<std::endl;
        std::cout<<"Seleccione una opcion: ";
        opcion = leerOpcion();

        if(opcion == 1){
            registrarServicio(gestorServicios);
        }
        else if(opcion == 2){
            gestorServicios.listarServicios();
        }
        else if(opcion == 3){
            buscarServicio(gestorServicios);
        }
        else if(opcion != 0){
            std::cout<<"Opcion invalida."<<std::endl;
        }
    }
}

void registrarServicio(GestorServicios& gestorServicios){
    std::cout<<"1. Diagnostico"<<std::endl;
    std::cout<<"2. Reparacion"<<std::endl;
    std::cout<<"3. Mantenimiento preventivo"<<std::endl;
    std::cout<<"Tipo de servicio: ";
    int tipo{leerOpcion()};

    if(tipo != 1 && tipo != 2 && tipo != 3){
        std::cout<<"Tipo invalido."<<std::endl;
        return;
    }

    std::string id, nombre, descripcion;
    double precioBase{0.0};
    int duracion{0};

    std::cout<<"ID del servicio: ";
    std::getline(std::cin, id);
    std::cout<<"Nombre: ";
    std::getline(std::cin, nombre);
    std::cout<<"Descripcion: ";
    std::getline(std::cin, descripcion);
    std::cout<<"Precio base: ";
    std::cin>>precioBase;
    std::cout<<"Duracion en minutos: ";
    std::cin>>duracion;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    ServicioTecnico* nuevoServicio{nullptr};

    if(tipo == 1){
        std::string nivel;
        char respuesta{'n'};
        std::cout<<"Nivel de revision: ";
        std::getline(std::cin, nivel);
        std::cout<<"Requiere reporte (s/n): ";
        std::cin>>respuesta;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        nuevoServicio = new Diagnostico(id, nombre, descripcion, precioBase, duracion, nivel, respuesta == 's');
    }
    else if(tipo == 2){
        double costoRepuesto{0.0};
        double horasManoObra{0.0};
        std::cout<<"Costo de repuesto: ";
        std::cin>>costoRepuesto;
        std::cout<<"Horas de mano de obra: ";
        std::cin>>horasManoObra;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        nuevoServicio = new Reparacion(id, nombre, descripcion, precioBase, duracion, costoRepuesto, horasManoObra);
    }
    else{
        char limpieza{'n'};
        char pasta{'n'};
        std::cout<<"Incluye limpieza (s/n): ";
        std::cin>>limpieza;
        std::cout<<"Incluye pasta termica (s/n): ";
        std::cin>>pasta;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        nuevoServicio = new MantenimientoPreventivo(id, nombre, descripcion, precioBase, duracion, limpieza == 's', pasta == 's');
    }

    if(gestorServicios.agregarServicio(nuevoServicio) == false){
        delete nuevoServicio;
        std::cout<<"No se pudo registrar el servicio."<<std::endl;
    }
    else{
        std::cout<<"Servicio registrado correctamente."<<std::endl;
    }
}

void buscarServicio(GestorServicios& gestorServicios){
    std::string id;
    std::cout<<"ID del servicio a buscar: ";
    std::getline(std::cin, id);

    ServicioTecnico* encontrado{gestorServicios.buscarPorId(id)};
    if(encontrado == nullptr){
        std::cout<<"No existe un servicio con ese id."<<std::endl;
    }
    else{
        encontrado->mostrarInformacion();
    }
}

//===== Ordenes de servicio =====

void menuOrdenes(GestorOrdenes& gestorOrdenes, GestorClientes& gestorClientes, GestorTecnicos& gestorTecnicos, GestorDispositivos& gestorDispositivos, GestorServicios& gestorServicios){
    int opcion{-1};
    while(opcion != 0){
        std::cout<<std::endl<<"--- Ordenes de servicio ---"<<std::endl;
        std::cout<<"1. Crear orden"<<std::endl;
        std::cout<<"2. Mostrar todas las ordenes"<<std::endl;
        std::cout<<"3. Mostrar ordenes pendientes"<<std::endl;
        std::cout<<"4. Actualizar estado"<<std::endl;
        std::cout<<"5. Buscar orden"<<std::endl;
        std::cout<<"0. Volver"<<std::endl;
        std::cout<<"Seleccione una opcion: ";
        opcion = leerOpcion();

        if(opcion == 1){
            crearOrden(gestorOrdenes, gestorClientes, gestorTecnicos, gestorDispositivos, gestorServicios);
        }
        else if(opcion == 2){
            gestorOrdenes.listarOrdenes();
        }
        else if(opcion == 3){
            gestorOrdenes.listarOrdenesPendientes();
        }
        else if(opcion == 4){
            actualizarEstadoOrden(gestorOrdenes);
        }
        else if(opcion == 5){
            buscarOrden(gestorOrdenes);
        }
        else if(opcion != 0){
            std::cout<<"Opcion invalida."<<std::endl;
        }
    }
}

void crearOrden(GestorOrdenes& gestorOrdenes, GestorClientes& gestorClientes, GestorTecnicos& gestorTecnicos, GestorDispositivos& gestorDispositivos, GestorServicios& gestorServicios){
    std::string idOrden, idCliente, idDispositivo, idServicio, fecha, problema;

    std::cout<<"ID de la orden: ";
    std::getline(std::cin, idOrden);
    std::cout<<"Codigo del cliente: ";
    std::getline(std::cin, idCliente);

    Cliente* cliente{gestorClientes.buscarPorIdentificacion(idCliente)};
    if(cliente == nullptr){
        std::cout<<"No existe un cliente con ese codigo."<<std::endl;
        return;
    }

    std::cout<<"ID del dispositivo: ";
    std::getline(std::cin, idDispositivo);

    Dispositivo* dispositivo{gestorDispositivos.buscar(idDispositivo)};
    if(dispositivo == nullptr){
        std::cout<<"No existe un dispositivo con ese id."<<std::endl;
        return;
    }

    std::cout<<"ID del servicio: ";
    std::getline(std::cin, idServicio);

    ServicioTecnico* servicio{gestorServicios.buscarPorId(idServicio)};
    if(servicio == nullptr){
        std::cout<<"No existe un servicio con ese id."<<std::endl;
        return;
    }

    std::cout<<"Fecha: ";
    std::getline(std::cin, fecha);
    std::cout<<"Problema reportado: ";
    std::getline(std::cin, problema);

    OrdenServicio* nuevaOrden{new OrdenServicio(idOrden, fecha, problema, cliente, dispositivo, servicio)};

    std::string idTecnico;
    std::cout<<"Codigo del tecnico a asignar (vacio para omitir): ";
    std::getline(std::cin, idTecnico);
    if(idTecnico != ""){
        Tecnico* tecnico{gestorTecnicos.buscarPorIdentificacion(idTecnico)};
        if(tecnico == nullptr){
            std::cout<<"No existe un tecnico con ese codigo, la orden queda sin tecnico asignado."<<std::endl;
        }
        else{
            nuevaOrden->asignarTecnico(tecnico);
        }
    }

    if(gestorOrdenes.agregarOrden(nuevaOrden) == false){
        delete nuevaOrden;
        std::cout<<"No se pudo crear la orden."<<std::endl;
    }
    else{
        std::cout<<"Orden creada correctamente."<<std::endl;
    }
}

void buscarOrden(GestorOrdenes& gestorOrdenes){
    std::string idOrden;
    std::cout<<"ID de la orden a buscar: ";
    std::getline(std::cin, idOrden);

    OrdenServicio* encontrada{gestorOrdenes.buscarPorId(idOrden)};
    if(encontrada == nullptr){
        std::cout<<"No existe una orden con ese id."<<std::endl;
    }
    else{
        encontrada->mostrarInformacion();
    }
}

void actualizarEstadoOrden(GestorOrdenes& gestorOrdenes){
    std::string idOrden, nuevoEstado;
    std::cout<<"ID de la orden: ";
    std::getline(std::cin, idOrden);
    std::cout<<"Nuevo estado (Pendiente/En proceso/Finalizada): ";
    std::getline(std::cin, nuevoEstado);

    gestorOrdenes.actualizarEstado(idOrden, nuevoEstado);
}

//===== Historial =====

void menuHistorial(){
    int opcion{-1};
    while(opcion != 0){
        std::cout<<std::endl<<"--- Historial ---"<<std::endl;
        std::cout<<"1. Registrar historial"<<std::endl;
        std::cout<<"2. Mostrar historial"<<std::endl;
        std::cout<<"3. Buscar por dispositivo"<<std::endl;
        std::cout<<"4. Buscar por tecnico"<<std::endl;
        std::cout<<"0. Volver"<<std::endl;
        std::cout<<"Seleccione una opcion: ";
        opcion = leerOpcion();

        if(opcion == 1){
            registrarHistorial();
        }
        else if(opcion == 2){
            HistorialServicio::mostrarTodos();
        }
        else if(opcion == 3){
            buscarHistorialPorDispositivo();
        }
        else if(opcion == 4){
            buscarHistorialPorTecnico();
        }
        else if(opcion != 0){
            std::cout<<"Opcion invalida."<<std::endl;
        }
    }
}

void registrarHistorial(){
    std::string idServicio, idDispositivo, idTecnico, fecha, descripcion, diagnostico, solucion;
    double costo{0.0};

    std::cout<<"ID de servicio: ";
    std::getline(std::cin, idServicio);
    std::cout<<"ID de dispositivo: ";
    std::getline(std::cin, idDispositivo);
    std::cout<<"ID de tecnico: ";
    std::getline(std::cin, idTecnico);
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
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    HistorialServicio* nuevoRegistro{new HistorialServicio(idServicio, idDispositivo, idTecnico, fecha, descripcion, diagnostico, solucion, costo)};
    if(HistorialServicio::agregar(nuevoRegistro) == false){
        delete nuevoRegistro;
        std::cout<<"No se pudo registrar el historial."<<std::endl;
    }
    else{
        std::cout<<"Historial registrado correctamente."<<std::endl;
    }
}

void buscarHistorialPorDispositivo(){
    std::string idDispositivo;
    std::cout<<"ID de dispositivo: ";
    std::getline(std::cin, idDispositivo);

    HistorialServicio* encontrado{HistorialServicio::buscarPorDispositivo(idDispositivo)};
    if(encontrado == nullptr){
        std::cout<<"No existe historial para ese dispositivo."<<std::endl;
    }
    else{
        encontrado->mostrarInformacion();
    }
}

void buscarHistorialPorTecnico(){
    std::string idTecnico;
    std::cout<<"ID de tecnico: ";
    std::getline(std::cin, idTecnico);

    HistorialServicio* encontrado{HistorialServicio::buscarPorTecnico(idTecnico)};
    if(encontrado == nullptr){
        std::cout<<"No existe historial para ese tecnico."<<std::endl;
    }
    else{
        encontrado->mostrarInformacion();
    }
}