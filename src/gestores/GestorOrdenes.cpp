#include "GestorOrdenes.h"
#include <iostream>

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

void GestorOrdenes::agregarOrden(OrdenServicio* orden) {
	if(cantidad == capacidad) {
		redimensionar();
	}

	ordenes[cantidad] = orden;
	cantidad++;

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

GestorOrdenes::~GestorOrdenes() {
	for(int i = 0; i < cantidad; i++) {

		delete ordenes[i];

	}

	delete[] ordenes;

}