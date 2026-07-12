#ifndef ORDENSERVICIO_H
#define ORDENSERVICIO_H
#include <string>
#include "Cliente.h"
#include "Tecnico.h"
#include "Dispositivo.h"
#include "ServicioTecnico.h"

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

    ~OrdenServicio();

};

#endif