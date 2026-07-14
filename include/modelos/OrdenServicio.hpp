#ifndef ORDENSERVICIO_H
#define ORDENSERVICIO_H
#include <string>
#include "modelos/Cliente.hpp"
#include "modelos/Tecnico.hpp"
#include "modelos/Dispositivo.hpp"
#include "modelos/ServicioTecnico.hpp"

// Clase que representa una orden de servicio
// y relaciona al cliente, el dispositivo,
// el técnico y el servicio realizado.

class OrdenServicio{

private:

    // Datos generales de la orden
    std::string id_orden;
    std::string fecha_ingreso;
    std::string problema_reportado;
    std::string diagnostico;
    std::string estado;

    // Relaciones con otras clases
    Cliente* cliente;
    Tecnico* tecnico;
    Dispositivo* dispositivo;
    ServicioTecnico* servicio;

public:

    // Constructor
    OrdenServicio(std::string idOrden, std::string fecha, std::string problema, Cliente* cli,Dispositivo* disp, ServicioTecnico* serv);

    // Getters
    std::string getIdOrden() const;
    std::string getEstado() const;

    // Setters
    void setEstado(std::string nuevoEstado);

    // Asigna un técnico a la orden
    void asignarTecnico(Tecnico* tec);

    // Registra el diagnóstico del servicio
    void registrarDiagnostico(std::string nuevoDiagnostico);

    // Calcula el costo final del servicio
    double calcularCostoFinal() const;

    // Muestra toda la información de la orden
    void mostrarInformacion() const;

    // Destructor
    ~OrdenServicio();

};

#endif
