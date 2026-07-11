#ifndef REPARACION_H
#define REPARACION_H
#include <string>
#include "ServicioTecnico.h"

class Reparacion : public ServicioTecnico{

private:

    double costo_repuesto;
    double horas_mano_obra;

    static constexpr double VALOR_HORA = 25.0;

public:

    Reparacion(std::string id, std::string nombre, std::string descripcion, double precioBase, int duracion, double costoRepuesto, double horasManoObra);

    double getCostoRepuesto() const;
    double getHorasManoObra() const;

    void setCostoRepuesto(double costo);
    void setHorasManoObra(double horas);

    double calcularCosto() const override;

    std::string getTipo() const override;

    void mostrarInformacion() const override;

    ~Reparacion() override;

};

#endif