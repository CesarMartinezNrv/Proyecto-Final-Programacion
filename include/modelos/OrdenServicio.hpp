#ifndef ORDENSERVICIO_H
#define ORDENSERVICIO_H
#include <string>
#include "modelos/Cliente.hpp"
#include "modelos/Tecnico.hpp"
#include "modelos/Dispositivo.hpp"
#include "modelos/ServicioTecnico.hpp"

class OrdenServicio{

private:

    std::string id_orden;
    std::string fecha_ingreso;
    std::string problema_reportado;
    std::string diagnostico;
    std::string estado;

    Cliente* cliente;
    Tecnico* tecnico;
    Dispositivo* dispositivo;
    ServicioTecnico* servicio;

public:

    OrdenServicio(std::string idOrden, std::string fecha, std::string problema, Cliente* cli, Dispositivo* disp, ServicioTecnico* serv);

    std::string getIdOrden() const;

    std::string getEstado() const;

    void setEstado(std::string nuevoEstado);

    void asignarTecnico(Tecnico* tec);

    void registrarDiagnostico(std::string nuevoDiagnostico);

    double calcularCostoFinal() const;

    void mostrarInformacion() const;

    //Serializa la orden guardando los IDs de las entidades relacionadas, no las direcciones de memoria
    std::string transformarArchivo() const;

    ~OrdenServicio();

};

#endif