#include "gestores/GestorOrdenes.hpp"
#include <iostream>
#include <fstream>

GestorOrdenes::GestorOrdenes(int capacidadInicial) {
	capacidad = capacidadInicial;
	cantidad = 0;
	ordenes = new OrdenServicio*[capacidad];

}

void GestorOrdenes::redimensionar() {
	capacidad *= 2;
	OrdenServicio** nuevo = new OrdenServicio*[capacidad];
	for(int i = 0; i < cantidad; i++) {
		nuevo[i] = ordenes[i];
	}

	delete[] ordenes;
	ordenes = nuevo;

}

bool GestorOrdenes::agregarOrden(OrdenServicio* orden) {
	if(orden == nullptr) {
		return false;
	}
	if(buscarPorId(orden->getIdOrden()) != nullptr) {
		std::cout << "ERROR. Ya existe una orden con ese id." << std::endl;
		return false;
	}
	if(cantidad == capacidad) {
		redimensionar();
	}

	ordenes[cantidad] = orden;
	cantidad++;
	return true;

}

OrdenServicio* GestorOrdenes::buscarPorId(std::string id) const {
	for(int i = 0; i < cantidad; i++) {
		if(ordenes[i]->getIdOrden() == id) {
			return ordenes[i];
		}
	}
	return nullptr;

}

void GestorOrdenes::listarOrdenes() const {
	if(cantidad == 0) {
		std::cout << "No existen ordenes registradas."  << std::endl;
		return;
	}

	for(int i = 0; i < cantidad; i++) {
		ordenes[i]->mostrarInformacion();
		std::cout << "-----------------------------"  << std::endl;
	}
}

void GestorOrdenes::listarOrdenesPendientes() const {
	for(int i = 0; i < cantidad; i++) {
		if(ordenes[i]->getEstado() == "Pendiente") {
			ordenes[i]->mostrarInformacion();
			std::cout << "-----------------------------"  << std::endl;
		}
	}
}

void GestorOrdenes::actualizarEstado(std::string idOrden, std::string nuevoEstado) {
	OrdenServicio* orden = buscarPorId(idOrden);
	if(orden != nullptr) {
		orden->setEstado(nuevoEstado);
		std::cout << "Estado actualizado correctamente."  << std::endl;
	}
	else {
		std::cout << "Orden no encontrada."  << std::endl;

	}
}

void GestorOrdenes::guardarArchivo(const std::string& nombreArchivo) const {
	std::ofstream archivo(nombreArchivo);
	if(archivo.is_open() == false) {
		std::cout << "ERROR. No se pudo abrir el archivo para guardar las ordenes." << std::endl;
		return;
	}
	for(int i = 0; i < cantidad; i++) {
		archivo << ordenes[i]->transformarArchivo() << std::endl;
	}
	archivo.close();
}

std::string GestorOrdenes::extraerCampo(const std::string& linea, size_t& posicion) const {
	size_t siguiente{linea.find('|', posicion)};
	std::string campo;
	if(siguiente == std::string::npos) {
		campo = linea.substr(posicion);
		posicion = linea.size();
	}
	else {
		campo = linea.substr(posicion, siguiente - posicion);
		posicion = siguiente + 1;
	}
	return campo;
}

void GestorOrdenes::cargarArchivo(
	const std::string& nombreArchivo,
	const GestorClientes& gestorClientes,
	const GestorTecnicos& gestorTecnicos,
	const GestorDispositivos& gestorDispositivos,
	const GestorServicios& gestorServicios
) {
	std::ifstream archivo(nombreArchivo);
	if(archivo.is_open() == false) {
		std::cout << "AVISO. No existe archivo previo de ordenes, se inicia vacio." << std::endl;
		return;
	}
	std::string linea;
	while(std::getline(archivo, linea)) {
		if(linea == "") {
			continue;
		}
		size_t posicion{0};
		std::string idOrden{extraerCampo(linea, posicion)};
		std::string idCliente{extraerCampo(linea, posicion)};
		std::string idTecnico{extraerCampo(linea, posicion)};
		std::string idDispositivo{extraerCampo(linea, posicion)};
		std::string idServicio{extraerCampo(linea, posicion)};
		std::string fecha{extraerCampo(linea, posicion)};
		std::string problema{extraerCampo(linea, posicion)};
		std::string diagnostico{extraerCampo(linea, posicion)};
		std::string estado{extraerCampo(linea, posicion)};

		Cliente* cliente{gestorClientes.buscarPorIdentificacion(idCliente)};
		Dispositivo* dispositivo{gestorDispositivos.buscar(idDispositivo)};
		ServicioTecnico* servicio{gestorServicios.buscarPorId(idServicio)};

		if(cliente == nullptr || dispositivo == nullptr || servicio == nullptr) {
			std::cout << "ADVERTENCIA. Orden " << idOrden << " ignorada, referencia inexistente." << std::endl;
			continue;
		}

		//Si idTecnico no esta vacio, debe existir; un id invalido descarta la linea en vez de convertirse en nullptr
		Tecnico* tecnico{nullptr};
		if(idTecnico != "") {
			tecnico = gestorTecnicos.buscarPorIdentificacion(idTecnico);
			if(tecnico == nullptr) {
				std::cout << "ADVERTENCIA. Orden " << idOrden << " ignorada, tecnico inexistente." << std::endl;
				continue;
			}
		}

		OrdenServicio* nuevaOrden{new OrdenServicio(idOrden, fecha, problema, cliente, dispositivo, servicio)};

		if(tecnico != nullptr) {
			nuevaOrden->asignarTecnico(tecnico);
		}

		nuevaOrden->registrarDiagnostico(diagnostico);
		nuevaOrden->setEstado(estado);

		if(agregarOrden(nuevaOrden) == false) {
			delete nuevaOrden;
			nuevaOrden = nullptr;
		}
	}
	archivo.close();
}

GestorOrdenes::~GestorOrdenes() {
	for(int i = 0; i < cantidad; i++) {

		delete ordenes[i];
		ordenes[i] = nullptr;

	}

	delete[] ordenes;
	ordenes = nullptr;

}