#include "gestores/GestorServicios.hpp"
#include "modelos/Diagnostico.hpp"
#include "modelos/Reparacion.hpp"
#include "modelos/MantenimientoPreventivo.hpp"
#include <iostream>
#include <fstream>

GestorServicios::GestorServicios(int capacidadInicial){

    capacidad = capacidadInicial;
    cantidad = 0;
    servicios = new ServicioTecnico*[capacidad];
}

void GestorServicios::redimensionar(){
    capacidad *= 2;
    ServicioTecnico** nuevo = new ServicioTecnico*[capacidad];
    for(int i = 0; i < cantidad; i++){
        nuevo[i] = servicios[i];
    }

    delete[] servicios;
    servicios = nuevo;

}
bool GestorServicios::agregarServicio(ServicioTecnico* servicio){
    if(servicio == nullptr){
        return false;
    }
    if(buscarPorId(servicio->getIdServicio()) != nullptr){
        std::cout<<"ERROR. Ya existe un servicio con ese id."<<std::endl;
        return false;
    }
    if(cantidad == capacidad){
        redimensionar();
    }

    servicios[cantidad] = servicio;
    cantidad++;
    return true;

}
ServicioTecnico* GestorServicios::buscarPorId(std::string id) const{
    for(int i = 0; i < cantidad; i++){
        if(servicios[i]->getIdServicio() == id){
            return servicios[i];
        }
    }
    return nullptr;
}

void GestorServicios::listarServicios() const{
    if(cantidad == 0){
        std::cout << "No existen servicios registrados."  << std::endl;
        return;
    }

    for(int i = 0; i < cantidad; i++){
        servicios[i]->mostrarInformacion();
        std::cout << "-----------------------------"  << std::endl;
    }

}
void GestorServicios::eliminarServicio(std::string id){
    for(int i = 0; i < cantidad; i++){
        if(servicios[i]->getIdServicio() == id){
            delete servicios[i];
            for(int j = i; j < cantidad - 1; j++){
                servicios[j] = servicios[j + 1];
            }
            servicios[cantidad - 1] = nullptr;
            cantidad--;
            std::cout << "Servicio eliminado correctamente."  << std::endl;
            return;
        }
    }

    std::cout << "Servicio no encontrado."  << std::endl;
}

void GestorServicios::guardarArchivo(const std::string& nombreArchivo) const{
    std::ofstream archivo(nombreArchivo);
    if(archivo.is_open() == false){
        std::cout<<"ERROR. No se pudo abrir el archivo para guardar los servicios."<<std::endl;
        return;
    }
    for(int i = 0; i < cantidad; i++){
        archivo<<servicios[i]->transformarArchivo()<<std::endl;
    }
    archivo.close();
}

std::string GestorServicios::extraerCampo(const std::string& linea, size_t& posicion) const{
    size_t siguiente{linea.find('|', posicion)};
    std::string campo;
    if(siguiente == std::string::npos){
        campo = linea.substr(posicion);
        posicion = linea.size();
    }
    else{
        campo = linea.substr(posicion, siguiente - posicion);
        posicion = siguiente + 1;
    }
    return campo;
}

void GestorServicios::cargarArchivo(const std::string& nombreArchivo){
    std::ifstream archivo(nombreArchivo);
    if(archivo.is_open() == false){
        std::cout<<"AVISO. No existe archivo previo de servicios, se inicia vacio."<<std::endl;
        return;
    }
    std::string linea;
    while(std::getline(archivo, linea)){
        if(linea == ""){
            continue;
        }
        size_t posicion{0};
        std::string tipo{extraerCampo(linea, posicion)};
        std::string id{extraerCampo(linea, posicion)};
        std::string nombreServicio{extraerCampo(linea, posicion)};
        std::string descripcion{extraerCampo(linea, posicion)};
        std::string precioTexto{extraerCampo(linea, posicion)};
        std::string duracionTexto{extraerCampo(linea, posicion)};
        double precioBase{std::stod(precioTexto)};
        int duracion{std::stoi(duracionTexto)};

        ServicioTecnico* nuevoServicio{nullptr};

        if(tipo == "diagnostico"){
            std::string nivel{extraerCampo(linea, posicion)};
            std::string reporteTexto{extraerCampo(linea, posicion)};
            nuevoServicio = new Diagnostico(id, nombreServicio, descripcion, precioBase, duracion, nivel, reporteTexto == "1");
        }
        else if(tipo == "reparacion"){
            std::string costoTexto{extraerCampo(linea, posicion)};
            std::string horasTexto{extraerCampo(linea, posicion)};
            nuevoServicio = new Reparacion(id, nombreServicio, descripcion, precioBase, duracion, std::stod(costoTexto), std::stod(horasTexto));
        }
        else if(tipo == "mantenimiento"){
            std::string limpiezaTexto{extraerCampo(linea, posicion)};
            std::string pastaTexto{extraerCampo(linea, posicion)};
            nuevoServicio = new MantenimientoPreventivo(id, nombreServicio, descripcion, precioBase, duracion, limpiezaTexto == "1", pastaTexto == "1");
        }
        else{
            std::cout<<"ADVERTENCIA. Tipo de servicio desconocido, linea ignorada."<<std::endl;
            continue;
        }

        if(agregarServicio(nuevoServicio) == false){
            delete nuevoServicio;
            nuevoServicio = nullptr;
        }
    }
    archivo.close();
}

GestorServicios::~GestorServicios(){
    for(int i = 0; i < cantidad; i++){
        delete servicios[i];
        servicios[i] = nullptr;
    }
    delete[] servicios;
    servicios = nullptr;

}