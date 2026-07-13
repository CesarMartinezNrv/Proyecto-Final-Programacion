#ifndef GESTORORDENES_H
#define GESTORORDENES_H
#include <string>
#include "modelos/OrdenServicio.hpp"
#include "gestores/GestorClientes.hpp"
#include "gestores/GestorTecnicos.hpp"
#include "gestores/GestorDispositivos.hpp"
#include "gestores/GestorServicios.hpp"

class GestorOrdenes{

private:

    OrdenServicio** ordenes;
    int cantidad;
    int capacidad;

    void redimensionar();

    //Extrae el campo que va desde posicion hasta el siguiente '|' y avanza posicion
    std::string extraerCampo(const std::string& linea, size_t& posicion) const;

public:

    GestorOrdenes(int capacidadInicial = 10);

    bool agregarOrden(OrdenServicio* orden);

    OrdenServicio* buscarPorId(std::string id) const;

    void listarOrdenes() const;

    void listarOrdenesPendientes() const;

    void actualizarEstado(std::string idOrden,  std::string nuevoEstado);

    //Persistencia con delimitador "|". Guarda IDs, no punteros
    void guardarArchivo(const std::string& nombreArchivo) const;

    //Reconstruye cada orden buscando sus referencias por ID en los gestores ya cargados
    void cargarArchivo(
        const std::string& nombreArchivo,
        const GestorClientes& gestorClientes,
        const GestorTecnicos& gestorTecnicos,
        const GestorDispositivos& gestorDispositivos,
        const GestorServicios& gestorServicios
    );

    ~GestorOrdenes();

};

#endif