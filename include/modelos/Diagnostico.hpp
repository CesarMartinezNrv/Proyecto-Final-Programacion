#ifndef DIAGNOSTICO_H
#define DIAGNOSTICO_H
#include "modelos/ServicioTecnico.hpp"
#include <string>

class Diagnostico : public ServicioTecnico{

private:

    std::string nivel_revision;
    bool requiere_reporte;

public:

    Diagnostico(std::string id, std::string nombre, std::string descripcion, double precio, int duracion, std::string nivel, bool reporte);

    std::string getNivelRevision() const;

    bool getRequiereReporte() const;

    void setNivelRevision(std::string nivel);

    void setRequiereReporte(bool reporte);

    double calcularCosto() const override;

    std::string getTipo() const override;

    void mostrarInformacion() const override;

    std::string transformarArchivo() const override;

    ~Diagnostico() override;

};

#endif