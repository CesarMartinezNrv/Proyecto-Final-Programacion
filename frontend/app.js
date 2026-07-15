'use strict';

/* ==========================================================================
   SGST · Sistema de Gestión de Servicios Técnicos
   Frontend demostrativo — HTML5 + CSS3 + JavaScript vanilla + localStorage
   Refleja las clases y gestores reales del proyecto en C++.
   ========================================================================== */

/* ============================================================
   1. CONFIGURACIÓN GENERAL
   ============================================================ */

const CONFIGURACION_APP = {
  duracionToast: 4200,
  limiteActividad: 40,
  estadosOrdenPermitidos: ['Pendiente', 'En proceso', 'Finalizada'],
  estadosClientePermitidos: ['activo', 'inactivo'],
  estadosDispositivoPermitidos: ['activo', 'en reparacion', 'dado de baja'],
  longitudTelefono: 10,
  longitudCedula: 10,
  recargoReporteDiagnostico: 20,
  valorHoraReparacion: 25,
  recargoLimpiezaMantenimiento: 20,
  recargoPastaMantenimiento: 35
};

/* ============================================================
   2. CLAVES DE ALMACENAMIENTO
   ============================================================ */

const CLAVES_ALMACENAMIENTO = {
  clientes: 'sgst_clientes',
  tecnicos: 'sgst_tecnicos',
  dispositivos: 'sgst_dispositivos',
  servicios: 'sgst_servicios',
  ordenes: 'sgst_ordenes',
  historial: 'sgst_historial',
  configuracion: 'sgst_configuracion',
  actividad: 'sgst_actividad'
};

let datosApp = null;
let clavesCorruptasDetectadas = [];

/* ============================================================
   3. DATOS INICIALES DE DEMOSTRACIÓN
   ============================================================ */

function crearDatosDemostracion(){
  const clientes = [
    { codigoPersona: 'CLI001', nombre: 'Andrea Salazar', numeroDeTelefono: '0991234567', correo: 'andrea.salazar@correo.com', cedula: '1712345678', direccion: 'Av. Amazonas N34-100, Quito', fechaDeRegistro: '2026-05-12', estadoAtencionCliente: 'activo', cantidadDispositivosRegistrados: 2 },
    { codigoPersona: 'CLI002', nombre: 'Marco Villacís', numeroDeTelefono: '0987654321', correo: 'marco.villacis@correo.com', cedula: '1723456789', direccion: 'Calle Rocafuerte 245, Quito', fechaDeRegistro: '2026-05-20', estadoAtencionCliente: 'activo', cantidadDispositivosRegistrados: 1 },
    { codigoPersona: 'CLI003', nombre: 'Paola Guerrero', numeroDeTelefono: '0978912345', correo: 'paola.guerrero@correo.com', cedula: '1734567890', direccion: 'Av. 6 de Diciembre y Colón, Quito', fechaDeRegistro: '2026-06-02', estadoAtencionCliente: 'inactivo', cantidadDispositivosRegistrados: 1 },
    { codigoPersona: 'CLI004', nombre: 'Ismael Rosero', numeroDeTelefono: '0965432198', correo: 'ismael.rosero@correo.com', cedula: '1745678901', direccion: 'Sector La Floresta, Quito', fechaDeRegistro: '2026-06-18', estadoAtencionCliente: 'activo', cantidadDispositivosRegistrados: 1 }
  ];

  const tecnicos = [
    { codigoPersona: 'TEC001', nombre: 'Renata Cevallos', numeroDeTelefono: '0991112233', correo: 'renata.cevallos@sgst.com', cedula: '1701122334', especialidad: 'Hardware', estadoDisponible: true, cantidadServiciosAtendidos: 4 },
    { codigoPersona: 'TEC002', nombre: 'Diego Farinango', numeroDeTelefono: '0992223344', correo: 'diego.farinango@sgst.com', cedula: '1702233445', especialidad: 'Redes', estadoDisponible: false, cantidadServiciosAtendidos: 2 },
    { codigoPersona: 'TEC003', nombre: 'Lucía Andrango', numeroDeTelefono: '0993334455', correo: 'lucia.andrango@sgst.com', cedula: '1703344556', especialidad: 'Software', estadoDisponible: true, cantidadServiciosAtendidos: 3 }
  ];

  const dispositivos = [
    { identificacionDispositivo: 'DIS001', identificacionCliente: 'CLI001', tipo: 'laptop', marca: 'Lenovo', modelo: 'ThinkPad T14', numeroSerie: 'SN-88213', estado: 'activo' },
    { identificacionDispositivo: 'DIS002', identificacionCliente: 'CLI001', tipo: 'celular', marca: 'Samsung', modelo: 'Galaxy A54', numeroSerie: 'SN-77120', estado: 'en reparacion' },
    { identificacionDispositivo: 'DIS003', identificacionCliente: 'CLI002', tipo: 'consola', marca: 'Sony', modelo: 'PlayStation 5', numeroSerie: 'SN-55310', estado: 'activo' },
    { identificacionDispositivo: 'DIS004', identificacionCliente: 'CLI003', tipo: 'laptop', marca: 'HP', modelo: 'Pavilion 15', numeroSerie: 'SN-99901', estado: 'dado de baja' },
    { identificacionDispositivo: 'DIS005', identificacionCliente: 'CLI004', tipo: 'impresora', marca: 'Epson', modelo: 'L3250', numeroSerie: 'SN-44002', estado: 'activo' }
  ];

  const servicios = [
    { identificacionServicio: 'SER001', tipo: 'Diagnostico', nombre: 'Diagnóstico general', descripcion: 'Revisión completa de hardware y software del equipo.', precioBase: 15, duracionMinutos: 40, nivelRevision: 'Básico', requiereReporte: true },
    { identificacionServicio: 'SER002', tipo: 'Reparacion', nombre: 'Cambio de pantalla', descripcion: 'Reemplazo de pantalla dañada por una original.', precioBase: 20, duracionMinutos: 90, costoRepuesto: 60, horasManoObra: 1.5 },
    { identificacionServicio: 'SER003', tipo: 'MantenimientoPreventivo', nombre: 'Mantenimiento estándar', descripcion: 'Limpieza interna y cambio de pasta térmica.', precioBase: 10, duracionMinutos: 60, incluyeLimpieza: true, incluyePastaTermica: true },
    { identificacionServicio: 'SER004', tipo: 'Diagnostico', nombre: 'Diagnóstico exprés', descripcion: 'Revisión rápida sin generación de reporte.', precioBase: 8, duracionMinutos: 20, nivelRevision: 'Rápido', requiereReporte: false },
    { identificacionServicio: 'SER005', tipo: 'Reparacion', nombre: 'Reparación de placa', descripcion: 'Soldadura y reparación de componentes en la placa madre.', precioBase: 25, duracionMinutos: 150, costoRepuesto: 45, horasManoObra: 3 }
  ];

  const ordenes = [
    { identificacionOrden: 'ORD001', fechaIngreso: '2026-07-02', problemaReportado: 'El equipo se reinicia solo de forma intermitente.', diagnostico: 'Pendiente', estado: 'Finalizada', identificacionCliente: 'CLI001', identificacionDispositivo: 'DIS001', identificacionServicio: 'SER001', identificacionTecnico: 'TEC001' },
    { identificacionOrden: 'ORD002', fechaIngreso: '2026-07-08', problemaReportado: 'Pantalla rota tras una caída accidental.', diagnostico: 'Pendiente', estado: 'En proceso', identificacionCliente: 'CLI001', identificacionDispositivo: 'DIS002', identificacionServicio: 'SER002', identificacionTecnico: 'TEC002' },
    { identificacionOrden: 'ORD003', fechaIngreso: '2026-07-10', problemaReportado: 'Mantenimiento preventivo solicitado por el cliente.', diagnostico: 'Pendiente', estado: 'Pendiente', identificacionCliente: 'CLI002', identificacionDispositivo: 'DIS003', identificacionServicio: 'SER003', identificacionTecnico: '' },
    { identificacionOrden: 'ORD004', fechaIngreso: '2026-07-12', problemaReportado: 'La impresora no enciende.', diagnostico: 'Pendiente', estado: 'Pendiente', identificacionCliente: 'CLI004', identificacionDispositivo: 'DIS005', identificacionServicio: 'SER004', identificacionTecnico: 'TEC003' }
  ];

  const historial = [
    { identificacionServicio: 'SER001', identificacionDispositivo: 'DIS001', identificacionTecnico: 'TEC001', fecha: '2026-07-02', descripcion: 'Revisión completa por reinicios inesperados.', diagnostico: 'Fuente de poder inestable.', solucion: 'Se reemplazó la fuente de poder del equipo.', costo: 35 },
    { identificacionServicio: 'SER002', identificacionDispositivo: 'DIS002', identificacionTecnico: 'TEC002', fecha: '2026-07-09', descripcion: 'Cambio de pantalla dañada por caída.', diagnostico: 'Panel LCD roto.', solucion: 'Se instaló una pantalla nueva original.', costo: 95 },
    { identificacionServicio: 'SER005', identificacionDispositivo: 'DIS004', identificacionTecnico: 'TEC003', fecha: '2026-06-20', descripcion: 'Equipo no encendía al presionar el botón de encendido.', diagnostico: 'Corto circuito en la placa madre.', solucion: 'Se reparó la pista dañada en la placa madre.', costo: 70 }
  ];

  const actividad = [
    { mensaje: 'Sistema inicializado con datos de demostración.', momento: new Date().toLocaleString('es-EC', { hour12: false }) }
  ];

  return { clientes: clientes, tecnicos: tecnicos, dispositivos: dispositivos, servicios: servicios, ordenes: ordenes, historial: historial, actividad: actividad };
}

/* ============================================================
   4. FUNCIONES DE ALMACENAMIENTO
   ============================================================ */

function leerAlmacenamiento(clave, valorPorDefecto){
  let crudo = null;
  try{
    crudo = localStorage.getItem(clave);
  } catch(error){
    return valorPorDefecto;
  }
  if(crudo === null) return valorPorDefecto;
  try{
    return JSON.parse(crudo);
  } catch(error){
    clavesCorruptasDetectadas.push(clave);
    return valorPorDefecto;
  }
}

function escribirAlmacenamiento(clave, valor){
  try{
    localStorage.setItem(clave, JSON.stringify(valor));
    return true;
  } catch(error){
    console.error('No se pudo guardar en localStorage', error);
    mostrarNotificacion('error', 'No se pudo guardar la información. Verifique el espacio disponible del navegador.');
    return false;
  }
}

function verificarDisponibilidadAlmacenamiento(){
  try{
    const clavePrueba = '__prueba_sgst__';
    localStorage.setItem(clavePrueba, '1');
    localStorage.removeItem(clavePrueba);
    return true;
  } catch(error){
    return false;
  }
}

function cargarDatosApp(){
  const configuracionExistente = leerAlmacenamiento(CLAVES_ALMACENAMIENTO.configuracion, null);
  const primeraEjecucion = configuracionExistente === null;

  datosApp = {
    clientes: leerAlmacenamiento(CLAVES_ALMACENAMIENTO.clientes, []),
    tecnicos: leerAlmacenamiento(CLAVES_ALMACENAMIENTO.tecnicos, []),
    dispositivos: leerAlmacenamiento(CLAVES_ALMACENAMIENTO.dispositivos, []),
    servicios: leerAlmacenamiento(CLAVES_ALMACENAMIENTO.servicios, []),
    ordenes: leerAlmacenamiento(CLAVES_ALMACENAMIENTO.ordenes, []),
    historial: leerAlmacenamiento(CLAVES_ALMACENAMIENTO.historial, []),
    actividad: leerAlmacenamiento(CLAVES_ALMACENAMIENTO.actividad, [])
  };

  ['clientes', 'tecnicos', 'dispositivos', 'servicios', 'ordenes', 'historial', 'actividad'].forEach(function(clave){
    if(Array.isArray(datosApp[clave]) === false){
      datosApp[clave] = [];
    }
  });

  if(primeraEjecucion){
    const semilla = crearDatosDemostracion();
    datosApp.clientes = semilla.clientes;
    datosApp.tecnicos = semilla.tecnicos;
    datosApp.dispositivos = semilla.dispositivos;
    datosApp.servicios = semilla.servicios;
    datosApp.ordenes = semilla.ordenes;
    datosApp.historial = semilla.historial;
    datosApp.actividad = semilla.actividad;
    guardarTodosLosDatos();
    escribirAlmacenamiento(CLAVES_ALMACENAMIENTO.configuracion, { version: 1, inicializado: true, lateralColapsado: false });
  }
}

function guardarClientes(){ escribirAlmacenamiento(CLAVES_ALMACENAMIENTO.clientes, datosApp.clientes); }
function guardarTecnicos(){ escribirAlmacenamiento(CLAVES_ALMACENAMIENTO.tecnicos, datosApp.tecnicos); }
function guardarDispositivos(){ escribirAlmacenamiento(CLAVES_ALMACENAMIENTO.dispositivos, datosApp.dispositivos); }
function guardarServicios(){ escribirAlmacenamiento(CLAVES_ALMACENAMIENTO.servicios, datosApp.servicios); }
function guardarOrdenes(){ escribirAlmacenamiento(CLAVES_ALMACENAMIENTO.ordenes, datosApp.ordenes); }
function guardarHistorial(){ escribirAlmacenamiento(CLAVES_ALMACENAMIENTO.historial, datosApp.historial); }
function guardarActividad(){ escribirAlmacenamiento(CLAVES_ALMACENAMIENTO.actividad, datosApp.actividad); }

function guardarTodosLosDatos(){
  guardarClientes();
  guardarTecnicos();
  guardarDispositivos();
  guardarServicios();
  guardarOrdenes();
  guardarHistorial();
  guardarActividad();
}

function restablecerDatosDemostracion(){
  const semilla = crearDatosDemostracion();
  datosApp.clientes = semilla.clientes;
  datosApp.tecnicos = semilla.tecnicos;
  datosApp.dispositivos = semilla.dispositivos;
  datosApp.servicios = semilla.servicios;
  datosApp.ordenes = semilla.ordenes;
  datosApp.historial = semilla.historial;
  datosApp.actividad = semilla.actividad;
  guardarTodosLosDatos();
  escribirAlmacenamiento(CLAVES_ALMACENAMIENTO.configuracion, { version: 1, inicializado: true, lateralColapsado: false });
  refrescarTodaLaInterfaz();
  mostrarNotificacion('exito', 'Los datos de demostración se restablecieron correctamente.');
}

/* ============================================================
   5. UTILIDADES
   ============================================================ */

function escaparTexto(valor){
  const contenedor = document.createElement('div');
  contenedor.textContent = (valor === undefined || valor === null) ? '' : String(valor);
  return contenedor.innerHTML;
}

function formatearMoneda(valor){
  const numero = (typeof valor === 'number' && !Number.isNaN(valor)) ? valor : 0;
  return '$' + numero.toFixed(2);
}

function obtenerFechaHoyISO(){
  const ahora = new Date();
  const mes = String(ahora.getMonth() + 1).padStart(2, '0');
  const dia = String(ahora.getDate()).padStart(2, '0');
  return ahora.getFullYear() + '-' + mes + '-' + dia;
}

function obtenerClientePorIdentificacion(identificacion){
  return datosApp.clientes.find(function(cliente){ return cliente.codigoPersona === identificacion; }) || null;
}
function obtenerTecnicoPorIdentificacion(identificacion){
  return datosApp.tecnicos.find(function(tecnico){ return tecnico.codigoPersona === identificacion; }) || null;
}
function obtenerDispositivoPorIdentificacion(identificacion){
  return datosApp.dispositivos.find(function(dispositivo){ return dispositivo.identificacionDispositivo === identificacion; }) || null;
}
function obtenerServicioPorIdentificacion(identificacion){
  return datosApp.servicios.find(function(servicio){ return servicio.identificacionServicio === identificacion; }) || null;
}
function obtenerOrdenPorIdentificacion(identificacion){
  return datosApp.ordenes.find(function(orden){ return orden.identificacionOrden === identificacion; }) || null;
}

function calcularCostoServicio(servicio){
  if(!servicio) return 0;
  if(servicio.tipo === 'Diagnostico'){
    return servicio.precioBase + (servicio.requiereReporte ? CONFIGURACION_APP.recargoReporteDiagnostico : 0);
  }
  if(servicio.tipo === 'Reparacion'){
    return servicio.precioBase + servicio.costoRepuesto + (servicio.horasManoObra * CONFIGURACION_APP.valorHoraReparacion);
  }
  if(servicio.tipo === 'MantenimientoPreventivo'){
    let total = servicio.precioBase;
    if(servicio.incluyeLimpieza) total += CONFIGURACION_APP.recargoLimpiezaMantenimiento;
    if(servicio.incluyePastaTermica) total += CONFIGURACION_APP.recargoPastaMantenimiento;
    return total;
  }
  return servicio.precioBase;
}

function calcularCostoFinalOrden(orden){
  const servicio = obtenerServicioPorIdentificacion(orden.identificacionServicio);
  return servicio ? calcularCostoServicio(servicio) : 0;
}

function obtenerNombreTipoServicio(tipo){
  if(tipo === 'Diagnostico') return 'Diagnóstico';
  if(tipo === 'Reparacion') return 'Reparación';
  if(tipo === 'MantenimientoPreventivo') return 'Mantenimiento preventivo';
  return tipo;
}

function registrarActividad(mensaje){
  const ahora = new Date();
  datosApp.actividad.unshift({ mensaje: mensaje, momento: ahora.toLocaleString('es-EC', { hour12: false }) });
  if(datosApp.actividad.length > CONFIGURACION_APP.limiteActividad){
    datosApp.actividad.length = CONFIGURACION_APP.limiteActividad;
  }
  guardarActividad();
}

function construirInsigniaEstadoOrden(estado){
  const clases = { 'Pendiente': 'insignia-ambar', 'En proceso': 'insignia-azul', 'Finalizada': 'insignia-verde' };
  return '<span class="insignia ' + (clases[estado] || 'insignia-gris') + '">' + escaparTexto(estado) + '</span>';
}
function construirInsigniaDisponibilidad(disponible){
  return disponible
    ? '<span class="insignia insignia-verde">Disponible</span>'
    : '<span class="insignia insignia-ambar">Ocupado</span>';
}
function construirInsigniaEstadoCliente(estado){
  return estado === 'activo'
    ? '<span class="insignia insignia-verde">Activo</span>'
    : '<span class="insignia insignia-gris">Inactivo</span>';
}
function construirInsigniaEstadoDispositivo(estado){
  const mapaClases = { 'activo': 'insignia-verde', 'en reparacion': 'insignia-ambar', 'dado de baja': 'insignia-roja' };
  const mapaEtiquetas = { 'activo': 'Activo', 'en reparacion': 'En reparación', 'dado de baja': 'Dado de baja' };
  return '<span class="insignia ' + (mapaClases[estado] || 'insignia-gris') + '">' + (mapaEtiquetas[estado] || escaparTexto(estado)) + '</span>';
}

/* ============================================================
   6. VALIDACIONES (equivalentes a Persona.cpp, Validaciones.cpp,
      Cliente.cpp y Dispositivo.cpp del proyecto en C++)
   ============================================================ */

function validarTextoNoVacio(texto){
  return typeof texto === 'string' && texto.length > 0;
}

function validarTelefono(telefono){
  if(typeof telefono !== 'string' || telefono.length !== CONFIGURACION_APP.longitudTelefono) return false;
  if(/^[0-9]+$/.test(telefono) === false) return false;
  if(telefono.charAt(0) !== '0') return false;
  return true;
}

function validarCorreo(correo){
  if(validarTextoNoVacio(correo) === false) return false;
  if(correo.indexOf('@') === -1) return false;
  if(correo.indexOf('.') === -1) return false;
  if(correo.charAt(0) === '@') return false;
  if(correo.charAt(correo.length - 1) === '.') return false;
  return true;
}

function validarCedula(cedula){
  if(typeof cedula !== 'string' || cedula.length !== CONFIGURACION_APP.longitudCedula) return false;
  return /^[0-9]+$/.test(cedula);
}

function validarCosto(costo){
  return typeof costo === 'number' && !Number.isNaN(costo) && costo > 0;
}

function validarEstadoCliente(estado){
  return CONFIGURACION_APP.estadosClientePermitidos.indexOf(estado) !== -1;
}
function validarEstadoDispositivo(estado){
  return CONFIGURACION_APP.estadosDispositivoPermitidos.indexOf(estado) !== -1;
}
function validarEstadoOrden(estado){
  return CONFIGURACION_APP.estadosOrdenPermitidos.indexOf(estado) !== -1;
}

function marcarError(id, mensaje){
  const grupo = document.getElementById('grupo-' + id);
  const error = document.getElementById('error-' + id);
  if(grupo) grupo.classList.add('campo-invalido');
  if(error) error.textContent = mensaje;
}
function limpiarError(id){
  const grupo = document.getElementById('grupo-' + id);
  const error = document.getElementById('error-' + id);
  if(grupo) grupo.classList.remove('campo-invalido');
  if(error) error.textContent = '';
}
function limpiarErrores(idsCampos){
  idsCampos.forEach(limpiarError);
}
function enfocarPrimerError(idsCampos){
  for(let indice = 0; indice < idsCampos.length; indice++){
    const grupo = document.getElementById('grupo-' + idsCampos[indice]);
    if(grupo && grupo.classList.contains('campo-invalido')){
      const campo = document.getElementById('campo-' + idsCampos[indice]);
      if(campo) campo.focus();
      return;
    }
  }
}

/* ============================================================
   7. NAVEGACIÓN
   ============================================================ */

const SECCIONES_VALIDAS = ['dashboard', 'clientes', 'tecnicos', 'dispositivos', 'servicios', 'ordenes', 'historial'];
const TITULOS_SECCION = {
  dashboard: 'Dashboard',
  clientes: 'Clientes',
  tecnicos: 'Técnicos',
  dispositivos: 'Dispositivos',
  servicios: 'Servicios técnicos',
  ordenes: 'Órdenes de servicio',
  historial: 'Historial de servicios'
};

function navegarASeccion(nombreSeccion){
  if(SECCIONES_VALIDAS.indexOf(nombreSeccion) === -1) nombreSeccion = 'dashboard';

  document.querySelectorAll('.seccion').forEach(function(seccion){ seccion.classList.remove('activa'); });
  const seccionDestino = document.getElementById('seccion-' + nombreSeccion);
  if(seccionDestino) seccionDestino.classList.add('activa');

  document.querySelectorAll('.enlace-navegacion[data-seccion]').forEach(function(enlace){
    const esActivo = enlace.dataset.seccion === nombreSeccion;
    enlace.classList.toggle('activo', esActivo);
    if(esActivo){ enlace.setAttribute('aria-current', 'page'); }
    else{ enlace.removeAttribute('aria-current'); }
  });

  document.getElementById('titulo-seccion-actual').textContent = TITULOS_SECCION[nombreSeccion];
  document.title = 'SGST | ' + TITULOS_SECCION[nombreSeccion];

  cerrarMenuMovil();

  if(location.hash !== '#' + nombreSeccion){
    history.replaceState(null, '', '#' + nombreSeccion);
  }

  ejecutarActualizacionSeccion(nombreSeccion);

  if(seccionDestino){
    const encabezado = seccionDestino.querySelector('h2');
    if(encabezado){
      encabezado.setAttribute('tabindex', '-1');
      encabezado.focus();
    }
  }
}

function ejecutarActualizacionSeccion(nombreSeccion){
  if(nombreSeccion === 'dashboard'){ actualizarDashboard(); }
  else if(nombreSeccion === 'clientes'){ actualizarTablaClientes(); }
  else if(nombreSeccion === 'tecnicos'){ actualizarTablaTecnicos(); }
  else if(nombreSeccion === 'dispositivos'){ actualizarSelectoresDispositivos(); actualizarTablaDispositivos(); }
  else if(nombreSeccion === 'servicios'){ actualizarListaServicios(); }
  else if(nombreSeccion === 'ordenes'){ actualizarSelectoresOrdenes(); actualizarTablaOrdenes(); }
  else if(nombreSeccion === 'historial'){ actualizarSelectoresHistorial(); actualizarTablaHistorial(); }
}

function refrescarTodaLaInterfaz(){
  actualizarDashboard();
  actualizarTablaClientes();
  actualizarTablaTecnicos();
  actualizarSelectoresDispositivos();
  actualizarTablaDispositivos();
  actualizarListaServicios();
  actualizarSelectoresOrdenes();
  actualizarTablaOrdenes();
  actualizarSelectoresHistorial();
  actualizarTablaHistorial();
}

function alternarColapsoLateral(){
  const app = document.getElementById('app');
  const colapsado = app.classList.toggle('lateral-colapsado');
  document.getElementById('boton-colapsar').setAttribute('aria-pressed', String(colapsado));
  const configuracion = leerAlmacenamiento(CLAVES_ALMACENAMIENTO.configuracion, { version: 1, inicializado: true, lateralColapsado: false });
  configuracion.lateralColapsado = colapsado;
  escribirAlmacenamiento(CLAVES_ALMACENAMIENTO.configuracion, configuracion);
}

function abrirMenuMovil(){
  document.getElementById('app').classList.add('lateral-movil-abierta');
  document.getElementById('fondo-superpuesto').hidden = false;
  document.getElementById('boton-menu-movil').setAttribute('aria-expanded', 'true');
  const primerEnlace = document.querySelector('.enlace-navegacion');
  if(primerEnlace) primerEnlace.focus();
}
function cerrarMenuMovil(){
  document.getElementById('app').classList.remove('lateral-movil-abierta');
  document.getElementById('fondo-superpuesto').hidden = true;
  document.getElementById('boton-menu-movil').setAttribute('aria-expanded', 'false');
}

function actualizarRelojSistema(){
  const ahora = new Date();
  const opcionesFecha = { weekday: 'long', year: 'numeric', month: 'long', day: 'numeric' };
  document.getElementById('fecha-actual').textContent = ahora.toLocaleDateString('es-EC', opcionesFecha);
  document.getElementById('hora-actual').textContent = ahora.toLocaleTimeString('es-EC', { hour12: false });
}

function actualizarIndicadorEstadoSistema(disponible){
  const indicador = document.getElementById('indicador-estado-sistema');
  indicador.innerHTML = '<span class="punto-estado" aria-hidden="true"></span>' + (disponible ? 'Sistema operativo' : 'Almacenamiento no disponible');
  indicador.classList.toggle('indicador-error', disponible === false);
}

/* ============================================================
   8. DASHBOARD
   ============================================================ */

function construirGraficoDonut(segmentos){
  const total = segmentos.reduce(function(suma, segmento){ return suma + segmento.valor; }, 0);
  if(total === 0){
    return '<p class="texto-sin-datos">Aún no hay órdenes registradas.</p>';
  }
  const radio = 15.9155;
  let acumulado = 0;
  let circulos = '';
  segmentos.forEach(function(segmento){
    const porcentaje = (segmento.valor / total) * 100;
    const desplazamiento = 25 - acumulado;
    circulos += '<circle class="segmento-donut" cx="21" cy="21" r="' + radio + '" fill="transparent" stroke="' + segmento.color + '" stroke-width="5.5" stroke-dasharray="' + porcentaje + ' ' + (100 - porcentaje) + '" stroke-dashoffset="' + desplazamiento + '"></circle>';
    acumulado += porcentaje;
  });
  const svg = '<svg viewBox="0 0 42 42" class="grafico-donut" width="150" height="150" role="img" aria-label="Distribución de órdenes por estado">' + circulos + '<text x="21" y="23" text-anchor="middle">' + total + '</text></svg>';
  const leyenda = '<div class="leyenda-grafico">' + segmentos.map(function(segmento){
    return '<span class="item-leyenda"><span class="punto-leyenda" style="background:' + segmento.color + '"></span>' + escaparTexto(segmento.etiqueta) + ': ' + segmento.valor + '</span>';
  }).join('') + '</div>';
  return '<div>' + svg + leyenda + '</div>';
}

function construirGraficoBarras(items){
  if(items.length === 0){
    return '<p class="texto-sin-datos">Sin datos suficientes todavía.</p>';
  }
  const maximo = Math.max.apply(null, items.map(function(item){ return item.valor; }));
  return items.map(function(item){
    const porcentaje = maximo === 0 ? 0 : Math.round((item.valor / maximo) * 100);
    return '<div class="fila-barra"><span class="etiqueta-barra" title="' + escaparTexto(item.etiqueta) + '">' + escaparTexto(item.etiqueta) + '</span><span class="pista-barra"><span class="relleno-barra" style="width:' + porcentaje + '%"></span></span><span class="valor-barra">' + item.valor + '</span></div>';
  }).join('');
}

function renderizarAccesosRapidos(){
  const accesos = [
    { etiqueta: 'Registrar cliente', icono: 'icono-cliente', accion: abrirModalNuevoCliente },
    { etiqueta: 'Registrar técnico', icono: 'icono-tecnico', accion: abrirModalNuevoTecnico },
    { etiqueta: 'Registrar dispositivo', icono: 'icono-dispositivo', accion: abrirModalNuevoDispositivo },
    { etiqueta: 'Registrar servicio', icono: 'icono-servicio', accion: abrirModalNuevoServicio },
    { etiqueta: 'Crear orden', icono: 'icono-orden', accion: abrirModalNuevaOrden },
    { etiqueta: 'Registrar historial', icono: 'icono-historial', accion: abrirModalNuevoHistorial }
  ];
  const contenedor = document.getElementById('rejilla-accesos-rapidos');
  contenedor.innerHTML = '';
  accesos.forEach(function(acceso){
    const boton = document.createElement('button');
    boton.type = 'button';
    boton.className = 'acceso-rapido';
    boton.innerHTML = '<svg aria-hidden="true"><use href="#' + acceso.icono + '"></use></svg>';
    const texto = document.createElement('span');
    texto.textContent = acceso.etiqueta;
    boton.appendChild(texto);
    boton.addEventListener('click', acceso.accion);
    contenedor.appendChild(boton);
  });
}

function actualizarDashboard(){
  const clientes = datosApp.clientes;
  const tecnicos = datosApp.tecnicos;
  const dispositivos = datosApp.dispositivos;
  const servicios = datosApp.servicios;
  const ordenes = datosApp.ordenes;
  const historial = datosApp.historial;

  const tecnicosDisponibles = tecnicos.filter(function(tecnico){ return tecnico.estadoDisponible; }).length;
  const tecnicosOcupados = tecnicos.length - tecnicosDisponibles;
  const ordenesPendientes = ordenes.filter(function(orden){ return orden.estado === 'Pendiente'; }).length;
  const ordenesEnProceso = ordenes.filter(function(orden){ return orden.estado === 'En proceso'; }).length;
  const ordenesFinalizadas = ordenes.filter(function(orden){ return orden.estado === 'Finalizada'; }).length;

  const tarjetas = [
    { etiqueta: 'Clientes registrados', valor: clientes.length, icono: 'icono-cliente', acento: '' },
    { etiqueta: 'Técnicos registrados', valor: tecnicos.length, icono: 'icono-tecnico', acento: 'acento-cian' },
    { etiqueta: 'Técnicos disponibles', valor: tecnicosDisponibles, icono: 'icono-estado', acento: 'acento-verde' },
    { etiqueta: 'Técnicos ocupados', valor: tecnicosOcupados, icono: 'icono-estado', acento: 'acento-ambar' },
    { etiqueta: 'Dispositivos registrados', valor: dispositivos.length, icono: 'icono-dispositivo', acento: '' },
    { etiqueta: 'Servicios en catálogo', valor: servicios.length, icono: 'icono-servicio', acento: 'acento-morado' },
    { etiqueta: 'Órdenes totales', valor: ordenes.length, icono: 'icono-orden', acento: '' },
    { etiqueta: 'Órdenes pendientes', valor: ordenesPendientes, icono: 'icono-orden', acento: 'acento-ambar' },
    { etiqueta: 'Órdenes en proceso', valor: ordenesEnProceso, icono: 'icono-orden', acento: 'acento-cian' },
    { etiqueta: 'Órdenes finalizadas', valor: ordenesFinalizadas, icono: 'icono-orden', acento: 'acento-verde' },
    { etiqueta: 'Registros de historial', valor: historial.length, icono: 'icono-historial', acento: 'acento-morado' }
  ];

  document.getElementById('cuadricula-estadisticas').innerHTML = tarjetas.map(function(tarjeta){
    return '<div class="tarjeta-estadistica ' + tarjeta.acento + '">' +
      '<div class="icono-estadistica"><svg aria-hidden="true"><use href="#' + tarjeta.icono + '"></use></svg></div>' +
      '<div><div class="valor-estadistica">' + tarjeta.valor + '</div><div class="etiqueta-estadistica">' + tarjeta.etiqueta + '</div></div>' +
    '</div>';
  }).join('');

  document.getElementById('grafico-estado-ordenes').innerHTML = construirGraficoDonut([
    { etiqueta: 'Pendiente', valor: ordenesPendientes, color: 'var(--ambar-advertencia)' },
    { etiqueta: 'En proceso', valor: ordenesEnProceso, color: 'var(--azul-electrico)' },
    { etiqueta: 'Finalizada', valor: ordenesFinalizadas, color: 'var(--verde-tecnologico)' }
  ]);

  const conteoServicios = {};
  ordenes.forEach(function(orden){
    conteoServicios[orden.identificacionServicio] = (conteoServicios[orden.identificacionServicio] || 0) + 1;
  });
  const serviciosMasUsados = Object.keys(conteoServicios).map(function(identificacion){
    const servicio = obtenerServicioPorIdentificacion(identificacion);
    return { etiqueta: servicio ? servicio.nombre : identificacion, valor: conteoServicios[identificacion] };
  }).sort(function(a, b){ return b.valor - a.valor; }).slice(0, 5);
  document.getElementById('grafico-servicios-usados').innerHTML = construirGraficoBarras(serviciosMasUsados);

  const conteoTipos = {};
  dispositivos.forEach(function(dispositivo){
    conteoTipos[dispositivo.tipo] = (conteoTipos[dispositivo.tipo] || 0) + 1;
  });
  const dispositivosPorTipo = Object.keys(conteoTipos).map(function(tipo){
    return { etiqueta: tipo, valor: conteoTipos[tipo] };
  }).sort(function(a, b){ return b.valor - a.valor; });
  document.getElementById('grafico-dispositivos-tipo').innerHTML = construirGraficoBarras(dispositivosPorTipo);

  const ordenesRecientes = ordenes.slice(-6).reverse();
  const cuerpoRecientes = document.querySelector('#tabla-ordenes-recientes tbody');
  if(ordenesRecientes.length === 0){
    cuerpoRecientes.innerHTML = '<tr><td colspan="4" class="mensaje-vacio">Sin órdenes registradas.</td></tr>';
  } else {
    cuerpoRecientes.innerHTML = ordenesRecientes.map(function(orden){
      const cliente = obtenerClientePorIdentificacion(orden.identificacionCliente);
      return '<tr><td>' + escaparTexto(orden.identificacionOrden) + '</td><td>' + escaparTexto(cliente ? cliente.nombre : orden.identificacionCliente) + '</td><td>' + construirInsigniaEstadoOrden(orden.estado) + '</td><td>' + formatearMoneda(calcularCostoFinalOrden(orden)) + '</td></tr>';
    }).join('');
  }

  const listaActividad = document.getElementById('lista-actividad-reciente');
  if(datosApp.actividad.length === 0){
    listaActividad.innerHTML = '<li class="texto-sin-datos">Todavía no hay actividad registrada en esta sesión.</li>';
  } else {
    listaActividad.innerHTML = datosApp.actividad.slice(0, 8).map(function(entrada){
      return '<li class="item-actividad"><span class="punto-actividad" aria-hidden="true"></span><div class="texto-actividad">' + escaparTexto(entrada.mensaje) + '<span class="hora-actividad">' + escaparTexto(entrada.momento) + '</span></div></li>';
    }).join('');
  }

  const tarjetaAlerta = document.getElementById('tarjeta-alerta-pendientes');
  if(ordenesPendientes > 0){
    tarjetaAlerta.hidden = false;
    document.getElementById('texto-alerta-pendientes').textContent = ordenesPendientes === 1
      ? 'Hay 1 orden pendiente por atender'
      : 'Hay ' + ordenesPendientes + ' órdenes pendientes por atender';
  } else {
    tarjetaAlerta.hidden = true;
  }
}

/* ============================================================
   9. CLIENTES (Persona + Cliente + GestorClientes)
   ============================================================ */

function actualizarTablaClientes(){
  const filtroCodigo = document.getElementById('buscar-cliente-codigo').value.trim();
  const filtroNombre = document.getElementById('buscar-cliente-nombre').value.trim().toLowerCase();
  const filtroEstado = document.getElementById('filtro-cliente-estado').value;

  let lista = datosApp.clientes.slice();
  if(filtroCodigo !== ''){ lista = lista.filter(function(cliente){ return cliente.codigoPersona === filtroCodigo; }); }
  if(filtroNombre !== ''){ lista = lista.filter(function(cliente){ return cliente.nombre.toLowerCase().indexOf(filtroNombre) !== -1; }); }
  if(filtroEstado !== ''){ lista = lista.filter(function(cliente){ return cliente.estadoAtencionCliente === filtroEstado; }); }

  const cuerpo = document.querySelector('#tabla-clientes tbody');
  document.getElementById('mensaje-vacio-clientes').hidden = lista.length !== 0;

  cuerpo.innerHTML = lista.map(function(cliente){
    return '<tr>' +
      '<td>' + escaparTexto(cliente.codigoPersona) + '</td>' +
      '<td>' + escaparTexto(cliente.nombre) + '</td>' +
      '<td>' + escaparTexto(cliente.numeroDeTelefono) + '</td>' +
      '<td>' + escaparTexto(cliente.correo) + '</td>' +
      '<td>' + escaparTexto(cliente.cedula) + '</td>' +
      '<td>' + escaparTexto(cliente.direccion) + '</td>' +
      '<td>' + escaparTexto(cliente.fechaDeRegistro) + '</td>' +
      '<td>' + construirInsigniaEstadoCliente(cliente.estadoAtencionCliente) + '</td>' +
      '<td>' + cliente.cantidadDispositivosRegistrados + '</td>' +
      '<td><button type="button" class="boton boton-secundario boton-pequeno" data-accion="ver-cliente" data-identificacion="' + escaparTexto(cliente.codigoPersona) + '"><svg class="icono-boton" aria-hidden="true"><use href="#icono-ver"></use></svg>Ver</button></td>' +
    '</tr>';
  }).join('');
}

function construirFormularioCliente(){
  return '' +
  '<form class="formulario" id="formulario-cliente" novalidate>' +
    '<div class="rejilla-formulario">' +
      campoTexto('cliente-codigo', 'Código del cliente', 'text', true) +
      campoTexto('cliente-nombre', 'Nombre completo', 'text', true) +
      campoTexto('cliente-telefono', 'Teléfono', 'text', true, '10 dígitos, debe iniciar en 0') +
      campoTexto('cliente-correo', 'Correo electrónico', 'email', true) +
      campoTexto('cliente-cedula', 'Cédula', 'text', true, '10 dígitos numéricos') +
      campoTexto('cliente-direccion', 'Dirección', 'text', true) +
      campoTexto('cliente-fecha', 'Fecha de registro', 'date', true) +
      campoSelect('cliente-estado', 'Estado de atención', [['activo', 'Activo'], ['inactivo', 'Inactivo']], true) +
    '</div>' +
    botonesFormulario('Registrar cliente') +
  '</form>';
}

function abrirModalNuevoCliente(){
  abrirModal('Registrar cliente', construirFormularioCliente());
  document.getElementById('campo-cliente-fecha').value = obtenerFechaHoyISO();
  document.getElementById('campo-cliente-estado').value = 'activo';
  document.getElementById('formulario-cliente').addEventListener('submit', manejarEnvioNuevoCliente);
}

function manejarEnvioNuevoCliente(evento){
  evento.preventDefault();
  const campos = ['cliente-codigo', 'cliente-nombre', 'cliente-telefono', 'cliente-correo', 'cliente-cedula', 'cliente-direccion', 'cliente-fecha', 'cliente-estado'];
  limpiarErrores(campos);

  const codigo = document.getElementById('campo-cliente-codigo').value.trim();
  const nombre = document.getElementById('campo-cliente-nombre').value.trim();
  const telefono = document.getElementById('campo-cliente-telefono').value.trim();
  const correo = document.getElementById('campo-cliente-correo').value.trim();
  const cedula = document.getElementById('campo-cliente-cedula').value.trim();
  const direccion = document.getElementById('campo-cliente-direccion').value.trim();
  const fecha = document.getElementById('campo-cliente-fecha').value.trim();
  const estado = document.getElementById('campo-cliente-estado').value;

  let esValido = true;
  if(validarTextoNoVacio(codigo) === false){ marcarError('cliente-codigo', 'El código es obligatorio.'); esValido = false; }
  else if(obtenerClientePorIdentificacion(codigo) !== null){ marcarError('cliente-codigo', 'Ya existe un cliente con ese código.'); esValido = false; }

  if(validarTextoNoVacio(nombre) === false){ marcarError('cliente-nombre', 'El nombre no puede estar vacío.'); esValido = false; }
  if(validarTelefono(telefono) === false){ marcarError('cliente-telefono', 'El teléfono debe tener 10 dígitos y empezar con 0.'); esValido = false; }
  if(validarCorreo(correo) === false){ marcarError('cliente-correo', 'Ingrese un correo válido (debe contener @ y un punto).'); esValido = false; }
  if(validarCedula(cedula) === false){ marcarError('cliente-cedula', 'La cédula debe tener 10 dígitos numéricos.'); esValido = false; }
  if(validarTextoNoVacio(direccion) === false){ marcarError('cliente-direccion', 'La dirección no puede estar vacía.'); esValido = false; }
  if(validarTextoNoVacio(fecha) === false){ marcarError('cliente-fecha', 'La fecha de registro es obligatoria.'); esValido = false; }
  if(validarEstadoCliente(estado) === false){ marcarError('cliente-estado', 'El estado debe ser activo o inactivo.'); esValido = false; }

  if(esValido === false){
    enfocarPrimerError(campos);
    mostrarNotificacion('error', 'Revisa los campos marcados en el formulario.');
    return;
  }

  datosApp.clientes.push({
    codigoPersona: codigo, nombre: nombre, numeroDeTelefono: telefono, correo: correo, cedula: cedula,
    direccion: direccion, fechaDeRegistro: fecha, estadoAtencionCliente: estado, cantidadDispositivosRegistrados: 0
  });
  guardarClientes();
  registrarActividad('Se registró el cliente ' + nombre + ' (' + codigo + ').');
  cerrarModal();
  actualizarTablaClientes();
  actualizarDashboard();
  mostrarNotificacion('exito', 'Cliente registrado correctamente.');
}

function abrirModalDetalleCliente(codigo){
  const cliente = obtenerClientePorIdentificacion(codigo);
  if(!cliente){ mostrarNotificacion('error', 'No se encontró el cliente solicitado.'); return; }
  const dispositivosDelCliente = datosApp.dispositivos.filter(function(dispositivo){ return dispositivo.identificacionCliente === codigo; });
  const contenido =
    '<div class="bloque-detalle">' +
      '<div class="rejilla-detalle">' +
        itemDetalle('Código', cliente.codigoPersona) +
        itemDetalle('Nombre', cliente.nombre) +
        itemDetalle('Teléfono', cliente.numeroDeTelefono) +
        itemDetalle('Correo', cliente.correo) +
        itemDetalle('Cédula', cliente.cedula) +
        itemDetalle('Dirección', cliente.direccion) +
        itemDetalle('Fecha de registro', cliente.fechaDeRegistro) +
        itemDetalle('Estado', cliente.estadoAtencionCliente === 'activo' ? 'Activo' : 'Inactivo') +
      '</div>' +
      '<p class="subtitulo-detalle">Dispositivos registrados (' + cliente.cantidadDispositivosRegistrados + ')</p>' +
      (dispositivosDelCliente.length === 0
        ? '<p class="texto-sin-datos">Este cliente no tiene dispositivos registrados.</p>'
        : '<div class="lista-atributos">' + dispositivosDelCliente.map(function(dispositivo){
            return '<div><span>' + escaparTexto(dispositivo.identificacionDispositivo) + ' — ' + escaparTexto(dispositivo.marca) + ' ' + escaparTexto(dispositivo.modelo) + '</span><span>' + escaparTexto(dispositivo.estado) + '</span></div>';
          }).join('') + '</div>') +
    '</div>';
  abrirModal('Detalle del cliente', contenido);
}

/* ============================================================
   10. TÉCNICOS (Persona + Tecnico + GestorTecnicos)
   ============================================================ */

function actualizarTablaTecnicos(){
  const filtroCodigo = document.getElementById('buscar-tecnico-codigo').value.trim();
  const filtroTexto = document.getElementById('buscar-tecnico-texto').value.trim().toLowerCase();
  const filtroDisponibilidad = document.getElementById('filtro-tecnico-disponibilidad').value;

  let lista = datosApp.tecnicos.slice();
  if(filtroCodigo !== ''){ lista = lista.filter(function(tecnico){ return tecnico.codigoPersona === filtroCodigo; }); }
  if(filtroTexto !== ''){
    lista = lista.filter(function(tecnico){
      return tecnico.nombre.toLowerCase().indexOf(filtroTexto) !== -1 || tecnico.especialidad.toLowerCase().indexOf(filtroTexto) !== -1;
    });
  }
  if(filtroDisponibilidad === 'disponible'){ lista = lista.filter(function(tecnico){ return tecnico.estadoDisponible === true; }); }
  else if(filtroDisponibilidad === 'ocupado'){ lista = lista.filter(function(tecnico){ return tecnico.estadoDisponible === false; }); }

  const cuerpo = document.querySelector('#tabla-tecnicos tbody');
  document.getElementById('mensaje-vacio-tecnicos').hidden = lista.length !== 0;

  cuerpo.innerHTML = lista.map(function(tecnico){
    return '<tr>' +
      '<td>' + escaparTexto(tecnico.codigoPersona) + '</td>' +
      '<td>' + escaparTexto(tecnico.nombre) + '</td>' +
      '<td>' + escaparTexto(tecnico.numeroDeTelefono) + '</td>' +
      '<td>' + escaparTexto(tecnico.correo) + '</td>' +
      '<td>' + escaparTexto(tecnico.cedula) + '</td>' +
      '<td>' + escaparTexto(tecnico.especialidad) + '</td>' +
      '<td>' + construirInsigniaDisponibilidad(tecnico.estadoDisponible) + '</td>' +
      '<td>' + tecnico.cantidadServiciosAtendidos + '</td>' +
      '<td><button type="button" class="boton boton-secundario boton-pequeno" data-accion="ver-tecnico" data-identificacion="' + escaparTexto(tecnico.codigoPersona) + '"><svg class="icono-boton" aria-hidden="true"><use href="#icono-ver"></use></svg>Ver</button></td>' +
    '</tr>';
  }).join('');
}

function construirFormularioTecnico(){
  return '' +
  '<form class="formulario" id="formulario-tecnico" novalidate>' +
    '<div class="rejilla-formulario">' +
      campoTexto('tecnico-codigo', 'Código del técnico', 'text', true) +
      campoTexto('tecnico-nombre', 'Nombre completo', 'text', true) +
      campoTexto('tecnico-telefono', 'Teléfono', 'text', true, '10 dígitos, debe iniciar en 0') +
      campoTexto('tecnico-correo', 'Correo electrónico', 'email', true) +
      campoTexto('tecnico-cedula', 'Cédula', 'text', true, '10 dígitos numéricos') +
      campoTexto('tecnico-especialidad', 'Especialidad', 'text', true) +
    '</div>' +
    '<p class="texto-ayuda">Todo técnico nuevo inicia como disponible, igual que en el sistema original.</p>' +
    botonesFormulario('Registrar técnico') +
  '</form>';
}

function abrirModalNuevoTecnico(){
  abrirModal('Registrar técnico', construirFormularioTecnico());
  document.getElementById('formulario-tecnico').addEventListener('submit', manejarEnvioNuevoTecnico);
}

function manejarEnvioNuevoTecnico(evento){
  evento.preventDefault();
  const campos = ['tecnico-codigo', 'tecnico-nombre', 'tecnico-telefono', 'tecnico-correo', 'tecnico-cedula', 'tecnico-especialidad'];
  limpiarErrores(campos);

  const codigo = document.getElementById('campo-tecnico-codigo').value.trim();
  const nombre = document.getElementById('campo-tecnico-nombre').value.trim();
  const telefono = document.getElementById('campo-tecnico-telefono').value.trim();
  const correo = document.getElementById('campo-tecnico-correo').value.trim();
  const cedula = document.getElementById('campo-tecnico-cedula').value.trim();
  const especialidad = document.getElementById('campo-tecnico-especialidad').value.trim();

  let esValido = true;
  if(validarTextoNoVacio(codigo) === false){ marcarError('tecnico-codigo', 'El código es obligatorio.'); esValido = false; }
  else if(obtenerTecnicoPorIdentificacion(codigo) !== null){ marcarError('tecnico-codigo', 'Ya existe un técnico con ese código.'); esValido = false; }
  if(validarTextoNoVacio(nombre) === false){ marcarError('tecnico-nombre', 'El nombre no puede estar vacío.'); esValido = false; }
  if(validarTelefono(telefono) === false){ marcarError('tecnico-telefono', 'El teléfono debe tener 10 dígitos y empezar con 0.'); esValido = false; }
  if(validarCorreo(correo) === false){ marcarError('tecnico-correo', 'Ingrese un correo válido.'); esValido = false; }
  if(validarCedula(cedula) === false){ marcarError('tecnico-cedula', 'La cédula debe tener 10 dígitos numéricos.'); esValido = false; }
  if(validarTextoNoVacio(especialidad) === false){ marcarError('tecnico-especialidad', 'La especialidad no puede estar vacía.'); esValido = false; }

  if(esValido === false){
    enfocarPrimerError(campos);
    mostrarNotificacion('error', 'Revisa los campos marcados en el formulario.');
    return;
  }

  datosApp.tecnicos.push({
    codigoPersona: codigo, nombre: nombre, numeroDeTelefono: telefono, correo: correo, cedula: cedula,
    especialidad: especialidad, estadoDisponible: true, cantidadServiciosAtendidos: 0
  });
  guardarTecnicos();
  registrarActividad('Se registró el técnico ' + nombre + ' (' + codigo + ').');
  cerrarModal();
  actualizarTablaTecnicos();
  actualizarDashboard();
  mostrarNotificacion('exito', 'Técnico registrado correctamente.');
}

function abrirModalDetalleTecnico(codigo){
  const tecnico = obtenerTecnicoPorIdentificacion(codigo);
  if(!tecnico){ mostrarNotificacion('error', 'No se encontró el técnico.'); return; }
  const ordenesAsignadas = datosApp.ordenes.filter(function(orden){ return orden.identificacionTecnico === codigo; });
  const contenido =
    '<div class="bloque-detalle">' +
      '<div class="rejilla-detalle">' +
        itemDetalle('Código', tecnico.codigoPersona) +
        itemDetalle('Nombre', tecnico.nombre) +
        itemDetalle('Teléfono', tecnico.numeroDeTelefono) +
        itemDetalle('Correo', tecnico.correo) +
        itemDetalle('Cédula', tecnico.cedula) +
        itemDetalle('Especialidad', tecnico.especialidad) +
        itemDetalle('Disponibilidad', tecnico.estadoDisponible ? 'Disponible' : 'Ocupado') +
        itemDetalle('Servicios atendidos', String(tecnico.cantidadServiciosAtendidos)) +
      '</div>' +
      '<p class="subtitulo-detalle">Órdenes asignadas (' + ordenesAsignadas.length + ')</p>' +
      (ordenesAsignadas.length === 0
        ? '<p class="texto-sin-datos">Este técnico no tiene órdenes asignadas.</p>'
        : '<div class="lista-atributos">' + ordenesAsignadas.map(function(orden){
            return '<div><span>' + escaparTexto(orden.identificacionOrden) + '</span><span>' + escaparTexto(orden.estado) + '</span></div>';
          }).join('') + '</div>') +
    '</div>';
  abrirModal('Detalle del técnico', contenido);
}

/* ============================================================
   11. DISPOSITIVOS (Dispositivo + GestorDispositivos)
   ============================================================ */

function actualizarSelectoresDispositivos(){
  const selectCliente = document.getElementById('filtro-dispositivo-cliente');
  const valorPrevioCliente = selectCliente.value;
  selectCliente.innerHTML = '<option value="">Todos</option>' + datosApp.clientes.map(function(cliente){
    return '<option value="' + escaparTexto(cliente.codigoPersona) + '">' + escaparTexto(cliente.nombre) + '</option>';
  }).join('');
  selectCliente.value = valorPrevioCliente;

  const tiposUnicos = Array.from(new Set(datosApp.dispositivos.map(function(dispositivo){ return dispositivo.tipo; }))).filter(function(tipo){ return tipo !== ''; });
  const selectTipo = document.getElementById('filtro-dispositivo-tipo');
  const valorPrevioTipo = selectTipo.value;
  selectTipo.innerHTML = '<option value="">Todos</option>' + tiposUnicos.map(function(tipo){
    return '<option value="' + escaparTexto(tipo) + '">' + escaparTexto(tipo) + '</option>';
  }).join('');
  selectTipo.value = valorPrevioTipo;
}

function actualizarTablaDispositivos(){
  const filtroIdentificacion = document.getElementById('buscar-dispositivo-identificacion').value.trim();
  const filtroMarca = document.getElementById('buscar-dispositivo-marca').value.trim().toLowerCase();
  const filtroModelo = document.getElementById('buscar-dispositivo-modelo').value.trim().toLowerCase();
  const filtroCliente = document.getElementById('filtro-dispositivo-cliente').value;
  const filtroTipo = document.getElementById('filtro-dispositivo-tipo').value;
  const filtroEstado = document.getElementById('filtro-dispositivo-estado').value;

  let lista = datosApp.dispositivos.slice();
  if(filtroIdentificacion !== ''){ lista = lista.filter(function(dispositivo){ return dispositivo.identificacionDispositivo === filtroIdentificacion; }); }
  if(filtroMarca !== ''){ lista = lista.filter(function(dispositivo){ return dispositivo.marca.toLowerCase().indexOf(filtroMarca) !== -1; }); }
  if(filtroModelo !== ''){ lista = lista.filter(function(dispositivo){ return dispositivo.modelo.toLowerCase().indexOf(filtroModelo) !== -1; }); }
  if(filtroCliente !== ''){ lista = lista.filter(function(dispositivo){ return dispositivo.identificacionCliente === filtroCliente; }); }
  if(filtroTipo !== ''){ lista = lista.filter(function(dispositivo){ return dispositivo.tipo === filtroTipo; }); }
  if(filtroEstado !== ''){ lista = lista.filter(function(dispositivo){ return dispositivo.estado === filtroEstado; }); }

  const cuerpo = document.querySelector('#tabla-dispositivos tbody');
  document.getElementById('mensaje-vacio-dispositivos').hidden = lista.length !== 0;

  cuerpo.innerHTML = lista.map(function(dispositivo){
    const cliente = obtenerClientePorIdentificacion(dispositivo.identificacionCliente);
    return '<tr>' +
      '<td>' + escaparTexto(dispositivo.identificacionDispositivo) + '</td>' +
      '<td>' + escaparTexto(cliente ? cliente.nombre : dispositivo.identificacionCliente) + '</td>' +
      '<td>' + escaparTexto(dispositivo.tipo) + '</td>' +
      '<td>' + escaparTexto(dispositivo.marca) + '</td>' +
      '<td>' + escaparTexto(dispositivo.modelo) + '</td>' +
      '<td>' + escaparTexto(dispositivo.numeroSerie) + '</td>' +
      '<td>' + construirInsigniaEstadoDispositivo(dispositivo.estado) + '</td>' +
      '<td><button type="button" class="boton boton-secundario boton-pequeno" data-accion="ver-dispositivo" data-identificacion="' + escaparTexto(dispositivo.identificacionDispositivo) + '"><svg class="icono-boton" aria-hidden="true"><use href="#icono-ver"></use></svg>Ver</button></td>' +
    '</tr>';
  }).join('');
}

function construirFormularioDispositivo(){
  const opcionesClientes = datosApp.clientes.map(function(cliente){ return [cliente.codigoPersona, cliente.codigoPersona + ' — ' + cliente.nombre]; });
  return '' +
  '<form class="formulario" id="formulario-dispositivo" novalidate>' +
    '<div class="rejilla-formulario">' +
      campoTexto('dispositivo-identificacion', 'Identificación del dispositivo', 'text', true) +
      campoSelect('dispositivo-cliente', 'Cliente propietario', opcionesClientes, true) +
      campoTextoConLista('dispositivo-tipo', 'Tipo de equipo', 'lista-tipos-dispositivo', ['laptop', 'celular', 'consola', 'tablet', 'impresora', 'monitor', 'otro']) +
      campoTexto('dispositivo-marca', 'Marca', 'text', true) +
      campoTexto('dispositivo-modelo', 'Modelo', 'text', true) +
      campoTexto('dispositivo-serie', 'Número de serie', 'text', true) +
      campoSelect('dispositivo-estado', 'Estado', [['activo', 'Activo'], ['en reparacion', 'En reparación'], ['dado de baja', 'Dado de baja']], true) +
    '</div>' +
    botonesFormulario('Registrar dispositivo') +
  '</form>';
}

function abrirModalNuevoDispositivo(){
  if(datosApp.clientes.length === 0){
    mostrarNotificacion('advertencia', 'Registra al menos un cliente antes de registrar un dispositivo.');
    return;
  }
  abrirModal('Registrar dispositivo', construirFormularioDispositivo());
  document.getElementById('campo-dispositivo-estado').value = 'activo';
  document.getElementById('formulario-dispositivo').addEventListener('submit', manejarEnvioNuevoDispositivo);
}

function manejarEnvioNuevoDispositivo(evento){
  evento.preventDefault();
  const campos = ['dispositivo-identificacion', 'dispositivo-cliente', 'dispositivo-tipo', 'dispositivo-marca', 'dispositivo-modelo', 'dispositivo-serie', 'dispositivo-estado'];
  limpiarErrores(campos);

  const identificacion = document.getElementById('campo-dispositivo-identificacion').value.trim();
  const identificacionCliente = document.getElementById('campo-dispositivo-cliente').value;
  const tipo = document.getElementById('campo-dispositivo-tipo').value.trim();
  const marca = document.getElementById('campo-dispositivo-marca').value.trim();
  const modelo = document.getElementById('campo-dispositivo-modelo').value.trim();
  const numeroSerie = document.getElementById('campo-dispositivo-serie').value.trim();
  const estado = document.getElementById('campo-dispositivo-estado').value;

  let esValido = true;
  if(validarTextoNoVacio(identificacion) === false){ marcarError('dispositivo-identificacion', 'La identificación es obligatoria.'); esValido = false; }
  else if(obtenerDispositivoPorIdentificacion(identificacion) !== null){ marcarError('dispositivo-identificacion', 'Ya existe un dispositivo con esa identificación.'); esValido = false; }

  const cliente = obtenerClientePorIdentificacion(identificacionCliente);
  if(!cliente){ marcarError('dispositivo-cliente', 'Selecciona un cliente existente.'); esValido = false; }

  if(validarTextoNoVacio(tipo) === false){ marcarError('dispositivo-tipo', 'El tipo no puede estar vacío.'); esValido = false; }
  if(validarTextoNoVacio(marca) === false){ marcarError('dispositivo-marca', 'La marca no puede estar vacía.'); esValido = false; }
  if(validarTextoNoVacio(modelo) === false){ marcarError('dispositivo-modelo', 'El modelo no puede estar vacío.'); esValido = false; }

  if(validarTextoNoVacio(numeroSerie) === false){ marcarError('dispositivo-serie', 'El número de serie no puede estar vacío.'); esValido = false; }
  else if(datosApp.dispositivos.some(function(dispositivo){ return dispositivo.numeroSerie === numeroSerie; })){
    marcarError('dispositivo-serie', 'Ya existe un dispositivo con ese número de serie.');
    esValido = false;
  }
  if(validarEstadoDispositivo(estado) === false){ marcarError('dispositivo-estado', 'Selecciona un estado válido.'); esValido = false; }

  if(esValido === false){
    enfocarPrimerError(campos);
    mostrarNotificacion('error', 'Revisa los campos marcados en el formulario.');
    return;
  }

  datosApp.dispositivos.push({
    identificacionDispositivo: identificacion, identificacionCliente: cliente.codigoPersona,
    tipo: tipo, marca: marca, modelo: modelo, numeroSerie: numeroSerie, estado: estado
  });
  cliente.cantidadDispositivosRegistrados += 1;
  guardarDispositivos();
  guardarClientes();
  registrarActividad('Se registró el dispositivo ' + identificacion + ' para ' + cliente.nombre + '.');
  cerrarModal();
  actualizarSelectoresDispositivos();
  actualizarTablaDispositivos();
  actualizarTablaClientes();
  actualizarDashboard();
  mostrarNotificacion('exito', 'Dispositivo registrado correctamente.');
}

function abrirModalDetalleDispositivo(identificacion){
  const dispositivo = obtenerDispositivoPorIdentificacion(identificacion);
  if(!dispositivo){ mostrarNotificacion('error', 'No se encontró el dispositivo.'); return; }
  const cliente = obtenerClientePorIdentificacion(dispositivo.identificacionCliente);
  const contenido =
    '<div class="bloque-detalle"><div class="rejilla-detalle">' +
      itemDetalle('Identificación', dispositivo.identificacionDispositivo) +
      itemDetalle('Cliente', cliente ? cliente.nombre + ' (' + cliente.codigoPersona + ')' : dispositivo.identificacionCliente) +
      itemDetalle('Tipo', dispositivo.tipo) +
      itemDetalle('Marca', dispositivo.marca) +
      itemDetalle('Modelo', dispositivo.modelo) +
      itemDetalle('N.° de serie', dispositivo.numeroSerie) +
      itemDetalle('Estado', dispositivo.estado) +
    '</div></div>';
  abrirModal('Detalle del dispositivo', contenido);
}

/* ============================================================
   12. SERVICIOS (ServicioTecnico, Diagnostico, Reparacion,
       MantenimientoPreventivo + GestorServicios)
   ============================================================ */

function obtenerAtributosEspecificosServicio(servicio){
  if(servicio.tipo === 'Diagnostico'){
    return '<div><span>Nivel de revisión</span><span>' + escaparTexto(servicio.nivelRevision) + '</span></div>' +
           '<div><span>Requiere reporte</span><span>' + (servicio.requiereReporte ? 'Sí (+$' + CONFIGURACION_APP.recargoReporteDiagnostico + ')' : 'No') + '</span></div>';
  }
  if(servicio.tipo === 'Reparacion'){
    return '<div><span>Costo de repuesto</span><span>' + formatearMoneda(servicio.costoRepuesto) + '</span></div>' +
           '<div><span>Horas de mano de obra</span><span>' + servicio.horasManoObra + ' h</span></div>';
  }
  return '<div><span>Incluye limpieza</span><span>' + (servicio.incluyeLimpieza ? 'Sí (+$' + CONFIGURACION_APP.recargoLimpiezaMantenimiento + ')' : 'No') + '</span></div>' +
         '<div><span>Incluye pasta térmica</span><span>' + (servicio.incluyePastaTermica ? 'Sí (+$' + CONFIGURACION_APP.recargoPastaMantenimiento + ')' : 'No') + '</span></div>';
}

function actualizarListaServicios(){
  const filtroIdentificacion = document.getElementById('buscar-servicio-identificacion').value.trim();
  const filtroTipo = document.getElementById('filtro-servicio-tipo').value;

  let lista = datosApp.servicios.slice();
  if(filtroIdentificacion !== ''){ lista = lista.filter(function(servicio){ return servicio.identificacionServicio === filtroIdentificacion; }); }
  if(filtroTipo !== ''){ lista = lista.filter(function(servicio){ return servicio.tipo === filtroTipo; }); }

  const contenedor = document.getElementById('rejilla-servicios');
  document.getElementById('mensaje-vacio-servicios').hidden = lista.length !== 0;

  contenedor.innerHTML = lista.map(function(servicio){
    return '<article class="tarjeta-hud tarjeta-servicio">' +
      '<div class="tarjeta-servicio-cabecera">' +
        '<div><h4>' + escaparTexto(servicio.nombre) + '</h4><span class="tarjeta-servicio-id">' + escaparTexto(servicio.identificacionServicio) + '</span></div>' +
        '<span class="insignia insignia-azul">' + escaparTexto(obtenerNombreTipoServicio(servicio.tipo)) + '</span>' +
      '</div>' +
      '<p class="tarjeta-servicio-descripcion">' + escaparTexto(servicio.descripcion) + '</p>' +
      '<div class="lista-atributos">' +
        '<div><span>Precio base</span><span>' + formatearMoneda(servicio.precioBase) + '</span></div>' +
        '<div><span>Duración</span><span>' + servicio.duracionMinutos + ' min</span></div>' +
        obtenerAtributosEspecificosServicio(servicio) +
      '</div>' +
      '<div class="tarjeta-servicio-costo"><span>Costo calculado</span><span class="valor">' + formatearMoneda(calcularCostoServicio(servicio)) + '</span></div>' +
    '</article>';
  }).join('');
}

function construirFormularioServicio(){
  return '' +
  '<form class="formulario" id="formulario-servicio" novalidate>' +
    '<div class="grupo-campo ancho-completo">' +
      '<label>Tipo de servicio *</label>' +
      '<div class="selector-tipo-servicio">' +
        '<label class="opcion-tipo-servicio"><input type="radio" name="tipo-servicio" value="Diagnostico" checked> Diagnóstico</label>' +
        '<label class="opcion-tipo-servicio"><input type="radio" name="tipo-servicio" value="Reparacion"> Reparación</label>' +
        '<label class="opcion-tipo-servicio"><input type="radio" name="tipo-servicio" value="MantenimientoPreventivo"> Mantenimiento preventivo</label>' +
      '</div>' +
    '</div>' +
    '<div class="rejilla-formulario">' +
      campoTexto('servicio-identificacion', 'Identificación del servicio', 'text', true) +
      campoTexto('servicio-nombre', 'Nombre', 'text', true) +
      campoTextarea('servicio-descripcion', 'Descripción', true) +
      campoNumero('servicio-precio', 'Precio base ($)', true, 0, '0.01', 'Los valores negativos se ajustan automáticamente a 0.') +
      campoNumero('servicio-duracion', 'Duración (minutos)', true, 0, '1', 'Los valores negativos se ajustan automáticamente a 0.') +
    '</div>' +
    '<div class="bloque-especifico visible" id="bloque-diagnostico">' +
      campoTexto('servicio-nivel', 'Nivel de revisión', 'text', true) +
      '<div class="grupo-campo"><label class="casilla-campo"><input type="checkbox" id="campo-servicio-reporte"> Requiere reporte (+$' + CONFIGURACION_APP.recargoReporteDiagnostico + ')</label></div>' +
    '</div>' +
    '<div class="bloque-especifico" id="bloque-reparacion">' +
      campoNumero('servicio-costo-repuesto', 'Costo de repuesto ($)', true, 0, '0.01', 'Se ajusta a 0 si es negativo.') +
      campoNumero('servicio-horas', 'Horas de mano de obra', true, 0, '0.5', 'Cada hora agrega $' + CONFIGURACION_APP.valorHoraReparacion + '.') +
    '</div>' +
    '<div class="bloque-especifico" id="bloque-mantenimiento">' +
      '<div class="grupo-campo"><label class="casilla-campo"><input type="checkbox" id="campo-servicio-limpieza"> Incluye limpieza (+$' + CONFIGURACION_APP.recargoLimpiezaMantenimiento + ')</label></div>' +
      '<div class="grupo-campo"><label class="casilla-campo"><input type="checkbox" id="campo-servicio-pasta"> Incluye pasta térmica (+$' + CONFIGURACION_APP.recargoPastaMantenimiento + ')</label></div>' +
    '</div>' +
    '<div class="aviso-costo-calculado"><span>Costo calculado</span><strong id="texto-costo-calculado">$0.00</strong></div>' +
    botonesFormulario('Registrar servicio') +
  '</form>';
}

function leerFormularioServicio(){
  const tipo = document.querySelector('input[name="tipo-servicio"]:checked').value;
  let precioBase = parseFloat(document.getElementById('campo-servicio-precio').value);
  let duracion = parseInt(document.getElementById('campo-servicio-duracion').value, 10);
  precioBase = (Number.isNaN(precioBase) || precioBase < 0) ? 0 : precioBase;
  duracion = (Number.isNaN(duracion) || duracion < 0) ? 0 : duracion;

  const servicio = {
    identificacionServicio: document.getElementById('campo-servicio-identificacion').value.trim(),
    tipo: tipo,
    nombre: document.getElementById('campo-servicio-nombre').value.trim(),
    descripcion: document.getElementById('campo-servicio-descripcion').value.trim(),
    precioBase: precioBase,
    duracionMinutos: duracion
  };

  if(tipo === 'Diagnostico'){
    servicio.nivelRevision = document.getElementById('campo-servicio-nivel').value.trim();
    servicio.requiereReporte = document.getElementById('campo-servicio-reporte').checked;
  } else if(tipo === 'Reparacion'){
    const costoRepuesto = parseFloat(document.getElementById('campo-servicio-costo-repuesto').value);
    const horas = parseFloat(document.getElementById('campo-servicio-horas').value);
    servicio.costoRepuesto = (Number.isNaN(costoRepuesto) || costoRepuesto < 0) ? 0 : costoRepuesto;
    servicio.horasManoObra = (Number.isNaN(horas) || horas < 0) ? 0 : horas;
  } else {
    servicio.incluyeLimpieza = document.getElementById('campo-servicio-limpieza').checked;
    servicio.incluyePastaTermica = document.getElementById('campo-servicio-pasta').checked;
  }
  return servicio;
}

function recalcularCostoFormularioServicio(){
  const servicio = leerFormularioServicio();
  document.getElementById('texto-costo-calculado').textContent = formatearMoneda(calcularCostoServicio(servicio));
}

function abrirModalNuevoServicio(){
  abrirModal('Registrar servicio técnico', construirFormularioServicio());

  const radiosTipo = document.querySelectorAll('input[name="tipo-servicio"]');
  const bloques = {
    Diagnostico: document.getElementById('bloque-diagnostico'),
    Reparacion: document.getElementById('bloque-reparacion'),
    MantenimientoPreventivo: document.getElementById('bloque-mantenimiento')
  };

  function actualizarBloqueVisible(){
    const tipoSeleccionado = document.querySelector('input[name="tipo-servicio"]:checked').value;
    Object.keys(bloques).forEach(function(tipo){ bloques[tipo].classList.toggle('visible', tipo === tipoSeleccionado); });
    recalcularCostoFormularioServicio();
  }
  radiosTipo.forEach(function(radio){ radio.addEventListener('change', actualizarBloqueVisible); });
  document.getElementById('formulario-servicio').addEventListener('input', recalcularCostoFormularioServicio);
  actualizarBloqueVisible();

  document.getElementById('formulario-servicio').addEventListener('submit', manejarEnvioNuevoServicio);
}

function manejarEnvioNuevoServicio(evento){
  evento.preventDefault();
  const camposComunes = ['servicio-identificacion', 'servicio-nombre', 'servicio-descripcion', 'servicio-precio', 'servicio-duracion'];
  limpiarErrores(camposComunes);
  limpiarErrores(['servicio-nivel']);

  const servicio = leerFormularioServicio();
  let esValido = true;

  if(validarTextoNoVacio(servicio.identificacionServicio) === false){ marcarError('servicio-identificacion', 'La identificación es obligatoria.'); esValido = false; }
  else if(obtenerServicioPorIdentificacion(servicio.identificacionServicio) !== null){ marcarError('servicio-identificacion', 'Ya existe un servicio con esa identificación.'); esValido = false; }

  if(validarTextoNoVacio(servicio.nombre) === false){ marcarError('servicio-nombre', 'El nombre es obligatorio.'); esValido = false; }
  if(validarTextoNoVacio(servicio.descripcion) === false){ marcarError('servicio-descripcion', 'La descripción es obligatoria.'); esValido = false; }

  if(servicio.tipo === 'Diagnostico' && validarTextoNoVacio(servicio.nivelRevision) === false){
    marcarError('servicio-nivel', 'El nivel de revisión es obligatorio.');
    esValido = false;
  }

  if(esValido === false){
    enfocarPrimerError(camposComunes.concat(['servicio-nivel']));
    mostrarNotificacion('error', 'Revisa los campos marcados en el formulario.');
    return;
  }

  datosApp.servicios.push(servicio);
  guardarServicios();
  registrarActividad('Se registró el servicio ' + servicio.nombre + ' (' + servicio.identificacionServicio + ').');
  cerrarModal();
  actualizarListaServicios();
  actualizarDashboard();
  mostrarNotificacion('exito', 'Servicio registrado correctamente.');
}

/* ============================================================
   13. ÓRDENES (OrdenServicio + GestorOrdenes)
   ============================================================ */

function actualizarSelectoresOrdenes(){
  const selectTecnico = document.getElementById('filtro-orden-tecnico');
  const valorPrevioTecnico = selectTecnico.value;
  selectTecnico.innerHTML = '<option value="">Todos</option>' + datosApp.tecnicos.map(function(tecnico){
    return '<option value="' + escaparTexto(tecnico.codigoPersona) + '">' + escaparTexto(tecnico.nombre) + '</option>';
  }).join('');
  selectTecnico.value = valorPrevioTecnico;

  const selectCliente = document.getElementById('filtro-orden-cliente');
  const valorPrevioCliente = selectCliente.value;
  selectCliente.innerHTML = '<option value="">Todos</option>' + datosApp.clientes.map(function(cliente){
    return '<option value="' + escaparTexto(cliente.codigoPersona) + '">' + escaparTexto(cliente.nombre) + '</option>';
  }).join('');
  selectCliente.value = valorPrevioCliente;
}

function actualizarTablaOrdenes(){
  const filtroIdentificacion = document.getElementById('buscar-orden-identificacion').value.trim();
  const filtroEstado = document.getElementById('filtro-orden-estado').value;
  const filtroTecnico = document.getElementById('filtro-orden-tecnico').value;
  const filtroCliente = document.getElementById('filtro-orden-cliente').value;
  const soloPendientes = document.getElementById('filtro-orden-solo-pendientes').checked;

  let lista = datosApp.ordenes.slice();
  if(filtroIdentificacion !== ''){ lista = lista.filter(function(orden){ return orden.identificacionOrden === filtroIdentificacion; }); }
  if(filtroEstado !== ''){ lista = lista.filter(function(orden){ return orden.estado === filtroEstado; }); }
  if(filtroTecnico !== ''){ lista = lista.filter(function(orden){ return orden.identificacionTecnico === filtroTecnico; }); }
  if(filtroCliente !== ''){ lista = lista.filter(function(orden){ return orden.identificacionCliente === filtroCliente; }); }
  if(soloPendientes){ lista = lista.filter(function(orden){ return orden.estado === 'Pendiente'; }); }

  const cuerpo = document.querySelector('#tabla-ordenes tbody');
  document.getElementById('mensaje-vacio-ordenes').hidden = lista.length !== 0;

  cuerpo.innerHTML = lista.slice().reverse().map(function(orden){
    const cliente = obtenerClientePorIdentificacion(orden.identificacionCliente);
    const dispositivo = obtenerDispositivoPorIdentificacion(orden.identificacionDispositivo);
    const servicio = obtenerServicioPorIdentificacion(orden.identificacionServicio);
    const tecnico = obtenerTecnicoPorIdentificacion(orden.identificacionTecnico);
    return '<tr>' +
      '<td>' + escaparTexto(orden.identificacionOrden) + '</td>' +
      '<td>' + escaparTexto(orden.fechaIngreso) + '</td>' +
      '<td>' + escaparTexto(cliente ? cliente.nombre : orden.identificacionCliente) + '</td>' +
      '<td>' + escaparTexto(dispositivo ? dispositivo.marca + ' ' + dispositivo.modelo : orden.identificacionDispositivo) + '</td>' +
      '<td>' + escaparTexto(servicio ? servicio.nombre : orden.identificacionServicio) + '</td>' +
      '<td>' + (tecnico ? escaparTexto(tecnico.nombre) : '<span class="insignia insignia-gris">Sin asignar</span>') + '</td>' +
      '<td>' + construirInsigniaEstadoOrden(orden.estado) + '</td>' +
      '<td>' + formatearMoneda(calcularCostoFinalOrden(orden)) + '</td>' +
      '<td class="celda-acciones">' +
        '<button type="button" class="boton boton-secundario boton-pequeno" data-accion="ver-orden" data-identificacion="' + escaparTexto(orden.identificacionOrden) + '"><svg class="icono-boton" aria-hidden="true"><use href="#icono-ver"></use></svg>Ver</button> ' +
        '<button type="button" class="boton boton-secundario boton-pequeno" data-accion="actualizar-estado-orden" data-identificacion="' + escaparTexto(orden.identificacionOrden) + '">Estado</button>' +
      '</td>' +
    '</tr>';
  }).join('');
}

function construirFormularioOrden(){
  const opcionesClientes = datosApp.clientes.map(function(cliente){ return [cliente.codigoPersona, cliente.codigoPersona + ' — ' + cliente.nombre]; });
  const opcionesServicios = datosApp.servicios.map(function(servicio){
    return [servicio.identificacionServicio, servicio.identificacionServicio + ' — ' + servicio.nombre + ' (' + formatearMoneda(calcularCostoServicio(servicio)) + ')'];
  });
  const opcionesTecnicos = [['', 'Sin asignar']].concat(datosApp.tecnicos.map(function(tecnico){
    return [tecnico.codigoPersona, tecnico.codigoPersona + ' — ' + tecnico.nombre + (tecnico.estadoDisponible ? ' (Disponible)' : ' (Ocupado)')];
  }));

  return '' +
  '<form class="formulario" id="formulario-orden" novalidate>' +
    '<div class="rejilla-formulario">' +
      campoTexto('orden-identificacion', 'Identificación de la orden', 'text', true) +
      campoTexto('orden-fecha', 'Fecha de ingreso', 'date', true) +
      campoSelect('orden-cliente', 'Cliente', opcionesClientes, true) +
      campoSelect('orden-dispositivo', 'Dispositivo', [], true) +
      campoSelect('orden-servicio', 'Servicio', opcionesServicios, true) +
      campoSelect('orden-tecnico', 'Técnico (opcional)', opcionesTecnicos, false) +
    '</div>' +
    campoTextarea('orden-problema', 'Problema reportado', true) +
    '<p class="panel-disponibilidad-tecnico" id="panel-disponibilidad-tecnico" hidden></p>' +
    botonesFormulario('Crear orden') +
  '</form>';
}

function abrirModalNuevaOrden(){
  if(datosApp.clientes.length === 0){ mostrarNotificacion('advertencia', 'Registra al menos un cliente antes de crear una orden.'); return; }
  if(datosApp.dispositivos.length === 0){ mostrarNotificacion('advertencia', 'Registra al menos un dispositivo antes de crear una orden.'); return; }
  if(datosApp.servicios.length === 0){ mostrarNotificacion('advertencia', 'Registra al menos un servicio antes de crear una orden.'); return; }

  abrirModal('Crear orden de servicio', construirFormularioOrden());
  document.getElementById('campo-orden-fecha').value = obtenerFechaHoyISO();

  const selectCliente = document.getElementById('campo-orden-cliente');
  const selectDispositivo = document.getElementById('campo-orden-dispositivo');
  const selectTecnico = document.getElementById('campo-orden-tecnico');
  const panelDisponibilidad = document.getElementById('panel-disponibilidad-tecnico');

  function refrescarDispositivosDelCliente(){
    const dispositivosDelCliente = datosApp.dispositivos.filter(function(dispositivo){ return dispositivo.identificacionCliente === selectCliente.value; });
    selectDispositivo.innerHTML = dispositivosDelCliente.length === 0
      ? '<option value="">Este cliente no tiene dispositivos</option>'
      : dispositivosDelCliente.map(function(dispositivo){
          return '<option value="' + escaparTexto(dispositivo.identificacionDispositivo) + '">' + escaparTexto(dispositivo.identificacionDispositivo) + ' — ' + escaparTexto(dispositivo.marca) + ' ' + escaparTexto(dispositivo.modelo) + '</option>';
        }).join('');
  }
  refrescarDispositivosDelCliente();
  selectCliente.addEventListener('change', refrescarDispositivosDelCliente);

  selectTecnico.addEventListener('change', function(){
    if(selectTecnico.value === ''){ panelDisponibilidad.hidden = true; return; }
    const tecnico = obtenerTecnicoPorIdentificacion(selectTecnico.value);
    panelDisponibilidad.hidden = false;
    panelDisponibilidad.textContent = tecnico
      ? 'Disponibilidad actual: ' + (tecnico.estadoDisponible ? 'Disponible.' : 'Ocupado. El sistema original permite asignarlo igualmente.')
      : '';
  });

  document.getElementById('formulario-orden').addEventListener('submit', manejarEnvioNuevaOrden);
}

function manejarEnvioNuevaOrden(evento){
  evento.preventDefault();
  const campos = ['orden-identificacion', 'orden-fecha', 'orden-cliente', 'orden-dispositivo', 'orden-servicio', 'orden-problema'];
  limpiarErrores(campos);

  const identificacion = document.getElementById('campo-orden-identificacion').value.trim();
  const fecha = document.getElementById('campo-orden-fecha').value.trim();
  const identificacionCliente = document.getElementById('campo-orden-cliente').value;
  const identificacionDispositivo = document.getElementById('campo-orden-dispositivo').value;
  const identificacionServicio = document.getElementById('campo-orden-servicio').value;
  const identificacionTecnico = document.getElementById('campo-orden-tecnico').value;
  const problema = document.getElementById('campo-orden-problema').value.trim();

  let esValido = true;
  if(validarTextoNoVacio(identificacion) === false){ marcarError('orden-identificacion', 'La identificación de la orden es obligatoria.'); esValido = false; }
  else if(obtenerOrdenPorIdentificacion(identificacion) !== null){ marcarError('orden-identificacion', 'Ya existe una orden con esa identificación.'); esValido = false; }

  if(validarTextoNoVacio(fecha) === false){ marcarError('orden-fecha', 'La fecha es obligatoria.'); esValido = false; }

  const cliente = obtenerClientePorIdentificacion(identificacionCliente);
  if(!cliente){ marcarError('orden-cliente', 'Selecciona un cliente válido.'); esValido = false; }

  const dispositivo = obtenerDispositivoPorIdentificacion(identificacionDispositivo);
  if(!dispositivo){ marcarError('orden-dispositivo', 'Selecciona un dispositivo válido del cliente elegido.'); esValido = false; }
  else if(cliente && dispositivo.identificacionCliente !== cliente.codigoPersona){ marcarError('orden-dispositivo', 'El dispositivo seleccionado no pertenece a este cliente.'); esValido = false; }

  const servicio = obtenerServicioPorIdentificacion(identificacionServicio);
  if(!servicio){ marcarError('orden-servicio', 'Selecciona un servicio válido.'); esValido = false; }

  if(validarTextoNoVacio(problema) === false){ marcarError('orden-problema', 'Describe el problema reportado.'); esValido = false; }

  if(esValido === false){
    enfocarPrimerError(campos);
    mostrarNotificacion('error', 'Revisa los campos marcados en el formulario.');
    return;
  }

  datosApp.ordenes.push({
    identificacionOrden: identificacion,
    fechaIngreso: fecha,
    problemaReportado: problema,
    diagnostico: 'Pendiente',
    estado: 'Pendiente',
    identificacionCliente: cliente.codigoPersona,
    identificacionDispositivo: dispositivo.identificacionDispositivo,
    identificacionServicio: servicio.identificacionServicio,
    identificacionTecnico: identificacionTecnico || ''
  });
  guardarOrdenes();
  registrarActividad('Se creó la orden ' + identificacion + ' para el cliente ' + cliente.nombre + '.');
  cerrarModal();
  actualizarSelectoresOrdenes();
  actualizarTablaOrdenes();
  actualizarDashboard();
  mostrarNotificacion('exito', 'Orden creada correctamente.');
}

function abrirModalActualizarEstado(identificacion){
  const orden = obtenerOrdenPorIdentificacion(identificacion);
  if(!orden){ mostrarNotificacion('error', 'No se encontró la orden.'); return; }
  const contenido =
    '<form class="formulario" id="formulario-estado-orden" novalidate>' +
      '<p class="texto-ayuda">Orden ' + escaparTexto(orden.identificacionOrden) + ' — estado actual: ' + construirInsigniaEstadoOrden(orden.estado) + '</p>' +
      campoSelect('estado-orden-nuevo', 'Nuevo estado', CONFIGURACION_APP.estadosOrdenPermitidos.map(function(estado){ return [estado, estado]; }), true) +
      botonesFormulario('Actualizar estado') +
    '</form>';
  abrirModal('Actualizar estado de orden', contenido);
  document.getElementById('campo-estado-orden-nuevo').value = orden.estado;
  document.getElementById('formulario-estado-orden').addEventListener('submit', function(evento){
    evento.preventDefault();
    const nuevoEstado = document.getElementById('campo-estado-orden-nuevo').value;
    if(validarEstadoOrden(nuevoEstado) === false){
      mostrarNotificacion('error', 'Estado no permitido.');
      return;
    }
    orden.estado = nuevoEstado;
    guardarOrdenes();
    registrarActividad('La orden ' + orden.identificacionOrden + ' cambió de estado a "' + nuevoEstado + '".');
    cerrarModal();
    actualizarTablaOrdenes();
    actualizarDashboard();
    mostrarNotificacion('exito', 'Estado actualizado correctamente.');
  });
}

function abrirModalDetalleOrden(identificacion){
  const orden = obtenerOrdenPorIdentificacion(identificacion);
  if(!orden){ mostrarNotificacion('error', 'No se encontró la orden.'); return; }
  const cliente = obtenerClientePorIdentificacion(orden.identificacionCliente);
  const dispositivo = obtenerDispositivoPorIdentificacion(orden.identificacionDispositivo);
  const servicio = obtenerServicioPorIdentificacion(orden.identificacionServicio);
  const tecnico = obtenerTecnicoPorIdentificacion(orden.identificacionTecnico);
  const contenido =
    '<div class="bloque-detalle">' +
      '<div class="rejilla-detalle">' +
        itemDetalle('Identificación', orden.identificacionOrden) +
        itemDetalle('Fecha de ingreso', orden.fechaIngreso) +
        itemDetalle('Estado', orden.estado) +
        itemDetalle('Diagnóstico', orden.diagnostico) +
        itemDetalle('Cliente', cliente ? cliente.nombre + ' (' + cliente.codigoPersona + ')' : orden.identificacionCliente) +
        itemDetalle('Dispositivo', dispositivo ? dispositivo.marca + ' ' + dispositivo.modelo + ' (' + dispositivo.identificacionDispositivo + ')' : orden.identificacionDispositivo) +
        itemDetalle('Servicio', servicio ? servicio.nombre + ' (' + servicio.identificacionServicio + ')' : orden.identificacionServicio) +
        itemDetalle('Técnico asignado', tecnico ? tecnico.nombre : 'Sin asignar') +
        itemDetalle('Costo final', formatearMoneda(calcularCostoFinalOrden(orden))) +
      '</div>' +
      '<p class="subtitulo-detalle">Problema reportado</p>' +
      '<p>' + escaparTexto(orden.problemaReportado) + '</p>' +
    '</div>';
  abrirModal('Detalle de la orden', contenido);
}

/* ============================================================
   14. HISTORIAL (HistorialServicio)
   ============================================================ */

function actualizarSelectoresHistorial(){
  const dispositivosUnicos = Array.from(new Set(datosApp.historial.map(function(registro){ return registro.identificacionDispositivo; }))).filter(function(valor){ return valor !== ''; });
  const selectDispositivo = document.getElementById('buscar-historial-dispositivo');
  const valorPrevioDispositivo = selectDispositivo.value;
  selectDispositivo.innerHTML = '<option value="">Seleccione…</option>' + dispositivosUnicos.map(function(valor){
    return '<option value="' + escaparTexto(valor) + '">' + escaparTexto(valor) + '</option>';
  }).join('');
  selectDispositivo.value = valorPrevioDispositivo;

  const tecnicosUnicos = Array.from(new Set(datosApp.historial.map(function(registro){ return registro.identificacionTecnico; }))).filter(function(valor){ return valor !== ''; });
  const selectTecnico = document.getElementById('buscar-historial-tecnico');
  const valorPrevioTecnico = selectTecnico.value;
  selectTecnico.innerHTML = '<option value="">Seleccione…</option>' + tecnicosUnicos.map(function(valor){
    return '<option value="' + escaparTexto(valor) + '">' + escaparTexto(valor) + '</option>';
  }).join('');
  selectTecnico.value = valorPrevioTecnico;
}

function actualizarTablaHistorial(){
  const filtroDispositivo = document.getElementById('buscar-historial-dispositivo').value;
  const filtroTecnico = document.getElementById('buscar-historial-tecnico').value;
  const filtroFecha = document.getElementById('filtro-historial-fecha').value.trim().toLowerCase();

  let lista = datosApp.historial.slice();
  if(filtroDispositivo !== ''){ lista = lista.filter(function(registro){ return registro.identificacionDispositivo === filtroDispositivo; }); }
  if(filtroTecnico !== ''){ lista = lista.filter(function(registro){ return registro.identificacionTecnico === filtroTecnico; }); }
  if(filtroFecha !== ''){ lista = lista.filter(function(registro){ return registro.fecha.toLowerCase().indexOf(filtroFecha) !== -1; }); }

  const cuerpo = document.querySelector('#tabla-historial tbody');
  document.getElementById('mensaje-vacio-historial').hidden = lista.length !== 0;

  cuerpo.innerHTML = lista.map(function(registro){
    const indice = datosApp.historial.indexOf(registro);
    return '<tr>' +
      '<td>' + escaparTexto(registro.identificacionServicio) + '</td>' +
      '<td>' + escaparTexto(registro.identificacionDispositivo) + '</td>' +
      '<td>' + escaparTexto(registro.identificacionTecnico) + '</td>' +
      '<td>' + escaparTexto(registro.fecha) + '</td>' +
      '<td>' + escaparTexto(registro.descripcion) + '</td>' +
      '<td>' + formatearMoneda(registro.costo) + '</td>' +
      '<td><button type="button" class="boton boton-secundario boton-pequeno" data-accion="ver-historial" data-indice="' + indice + '"><svg class="icono-boton" aria-hidden="true"><use href="#icono-ver"></use></svg>Ver</button></td>' +
    '</tr>';
  }).join('');
}

function construirFormularioHistorial(){
  return '' +
  '<form class="formulario" id="formulario-historial" novalidate>' +
    '<div class="rejilla-formulario">' +
      campoTexto('historial-servicio', 'Identificación de servicio', 'text', true) +
      campoTexto('historial-dispositivo', 'Identificación de dispositivo', 'text', true) +
      campoTexto('historial-tecnico', 'Identificación de técnico', 'text', true) +
      campoTexto('historial-fecha', 'Fecha', 'date', true) +
      campoNumero('historial-costo', 'Costo ($)', true, 0.01, '0.01', 'Debe ser mayor a 0.') +
    '</div>' +
    campoTextarea('historial-descripcion', 'Descripción', true) +
    campoTextarea('historial-diagnostico', 'Diagnóstico', true) +
    campoTextarea('historial-solucion', 'Solución aplicada', true) +
    '<p class="texto-ayuda">Este registro es independiente: el sistema original no valida que el servicio, dispositivo o técnico ya existan.</p>' +
    botonesFormulario('Registrar historial') +
  '</form>';
}

function abrirModalNuevoHistorial(){
  abrirModal('Registrar historial de servicio', construirFormularioHistorial());
  document.getElementById('campo-historial-fecha').value = obtenerFechaHoyISO();
  document.getElementById('formulario-historial').addEventListener('submit', manejarEnvioNuevoHistorial);
}

function manejarEnvioNuevoHistorial(evento){
  evento.preventDefault();
  const campos = ['historial-servicio', 'historial-dispositivo', 'historial-tecnico', 'historial-fecha', 'historial-costo', 'historial-descripcion', 'historial-diagnostico', 'historial-solucion'];
  limpiarErrores(campos);

  const identificacionServicio = document.getElementById('campo-historial-servicio').value.trim();
  const identificacionDispositivo = document.getElementById('campo-historial-dispositivo').value.trim();
  const identificacionTecnico = document.getElementById('campo-historial-tecnico').value.trim();
  const fecha = document.getElementById('campo-historial-fecha').value.trim();
  const costo = parseFloat(document.getElementById('campo-historial-costo').value);
  const descripcion = document.getElementById('campo-historial-descripcion').value.trim();
  const diagnostico = document.getElementById('campo-historial-diagnostico').value.trim();
  const solucion = document.getElementById('campo-historial-solucion').value.trim();

  let esValido = true;
  if(validarTextoNoVacio(identificacionServicio) === false){ marcarError('historial-servicio', 'Campo obligatorio.'); esValido = false; }
  if(validarTextoNoVacio(identificacionDispositivo) === false){ marcarError('historial-dispositivo', 'Campo obligatorio.'); esValido = false; }
  if(validarTextoNoVacio(identificacionTecnico) === false){ marcarError('historial-tecnico', 'Campo obligatorio.'); esValido = false; }
  if(validarTextoNoVacio(fecha) === false){ marcarError('historial-fecha', 'La fecha es obligatoria.'); esValido = false; }
  if(validarTextoNoVacio(descripcion) === false){ marcarError('historial-descripcion', 'La descripción no puede estar vacía.'); esValido = false; }
  if(validarTextoNoVacio(diagnostico) === false){ marcarError('historial-diagnostico', 'El diagnóstico no puede estar vacío.'); esValido = false; }
  if(validarTextoNoVacio(solucion) === false){ marcarError('historial-solucion', 'La solución no puede estar vacía.'); esValido = false; }
  if(validarCosto(costo) === false){ marcarError('historial-costo', 'El costo debe ser mayor a 0.'); esValido = false; }

  if(esValido === false){
    enfocarPrimerError(campos);
    mostrarNotificacion('error', 'Revisa los campos marcados en el formulario.');
    return;
  }

  datosApp.historial.push({
    identificacionServicio: identificacionServicio, identificacionDispositivo: identificacionDispositivo,
    identificacionTecnico: identificacionTecnico, fecha: fecha, descripcion: descripcion,
    diagnostico: diagnostico, solucion: solucion, costo: costo
  });
  guardarHistorial();
  registrarActividad('Se registró un historial de servicio para el dispositivo ' + identificacionDispositivo + '.');
  cerrarModal();
  actualizarSelectoresHistorial();
  actualizarTablaHistorial();
  actualizarDashboard();
  mostrarNotificacion('exito', 'Historial registrado correctamente.');
}

function abrirModalDetalleHistorial(indice){
  const registro = datosApp.historial[Number(indice)];
  if(!registro){ mostrarNotificacion('error', 'No se encontró el registro.'); return; }
  const contenido =
    '<div class="bloque-detalle">' +
      '<div class="rejilla-detalle">' +
        itemDetalle('Servicio', registro.identificacionServicio) +
        itemDetalle('Dispositivo', registro.identificacionDispositivo) +
        itemDetalle('Técnico', registro.identificacionTecnico) +
        itemDetalle('Fecha', registro.fecha) +
        itemDetalle('Costo', formatearMoneda(registro.costo)) +
      '</div>' +
      '<p class="subtitulo-detalle">Descripción</p><p>' + escaparTexto(registro.descripcion) + '</p>' +
      '<p class="subtitulo-detalle">Diagnóstico</p><p>' + escaparTexto(registro.diagnostico) + '</p>' +
      '<p class="subtitulo-detalle">Solución aplicada</p><p>' + escaparTexto(registro.solucion) + '</p>' +
    '</div>';
  abrirModal('Detalle del historial', contenido);
}

/* ============================================================
   15. MODALES (motor genérico de ventanas modales y confirmación,
       más los constructores de campos usados por los formularios)
   ============================================================ */

function campoTexto(id, etiqueta, tipo, requerido, ayuda){
  const atributoRequerido = requerido ? ' required' : '';
  const textoAyuda = ayuda ? '<span class="texto-ayuda">' + escaparTexto(ayuda) + '</span>' : '';
  return (
    '<div class="grupo-campo" id="grupo-' + id + '">' +
      '<label for="campo-' + id + '">' + escaparTexto(etiqueta) + (requerido ? ' *' : '') + '</label>' +
      '<input type="' + tipo + '" id="campo-' + id + '"' + atributoRequerido + '>' +
      textoAyuda +
      '<p class="error-campo" id="error-' + id + '" role="alert"></p>' +
    '</div>'
  );
}

function campoTextoConLista(id, etiqueta, idLista, sugerencias){
  const opciones = sugerencias.map(function(valor){ return '<option value="' + escaparTexto(valor) + '"></option>'; }).join('');
  return (
    '<div class="grupo-campo" id="grupo-' + id + '">' +
      '<label for="campo-' + id + '">' + escaparTexto(etiqueta) + ' *</label>' +
      '<input type="text" id="campo-' + id + '" list="' + idLista + '" required>' +
      '<datalist id="' + idLista + '">' + opciones + '</datalist>' +
      '<p class="error-campo" id="error-' + id + '" role="alert"></p>' +
    '</div>'
  );
}

function campoTextarea(id, etiqueta, requerido){
  return (
    '<div class="grupo-campo ancho-completo" id="grupo-' + id + '">' +
      '<label for="campo-' + id + '">' + escaparTexto(etiqueta) + (requerido ? ' *' : '') + '</label>' +
      '<textarea id="campo-' + id + '"' + (requerido ? ' required' : '') + '></textarea>' +
      '<p class="error-campo" id="error-' + id + '" role="alert"></p>' +
    '</div>'
  );
}

function campoSelect(id, etiqueta, opciones, requerido){
  const listaOpciones = opciones.map(function(opcion){ return '<option value="' + escaparTexto(opcion[0]) + '">' + escaparTexto(opcion[1]) + '</option>'; }).join('');
  return (
    '<div class="grupo-campo" id="grupo-' + id + '">' +
      '<label for="campo-' + id + '">' + escaparTexto(etiqueta) + (requerido ? ' *' : '') + '</label>' +
      '<select id="campo-' + id + '">' + listaOpciones + '</select>' +
      '<p class="error-campo" id="error-' + id + '" role="alert"></p>' +
    '</div>'
  );
}

function campoNumero(id, etiqueta, requerido, minimo, paso, ayuda){
  const textoAyuda = ayuda ? '<span class="texto-ayuda">' + escaparTexto(ayuda) + '</span>' : '';
  return (
    '<div class="grupo-campo" id="grupo-' + id + '">' +
      '<label for="campo-' + id + '">' + escaparTexto(etiqueta) + (requerido ? ' *' : '') + '</label>' +
      '<input type="number" id="campo-' + id + '" min="' + minimo + '" step="' + paso + '"' + (requerido ? ' required' : '') + '>' +
      textoAyuda +
      '<p class="error-campo" id="error-' + id + '" role="alert"></p>' +
    '</div>'
  );
}

function botonesFormulario(textoBotonPrincipal){
  return (
    '<div class="acciones-formulario">' +
      '<button type="button" class="boton boton-fantasma" data-accion-modal="cancelar">Cancelar</button>' +
      '<button type="submit" class="boton boton-primario">' + escaparTexto(textoBotonPrincipal) + '</button>' +
    '</div>'
  );
}

function itemDetalle(etiqueta, valor){
  return '<div class="item-detalle"><span>' + escaparTexto(etiqueta) + '</span><span>' + escaparTexto(valor) + '</span></div>';
}

let elementoConFocoPrevio = null;
let callbackCierreModal = null;
let callbackConfirmacionAceptar = null;

function abrirModal(titulo, contenidoHTML, alCerrar){
  const capa = document.getElementById('capa-modal');
  document.getElementById('titulo-modal').textContent = titulo;
  document.getElementById('modal-cuerpo').innerHTML = contenidoHTML;
  elementoConFocoPrevio = document.activeElement;
  callbackCierreModal = alCerrar || null;
  capa.hidden = false;
  document.body.style.overflow = 'hidden';

  const botonCancelar = document.querySelector('#modal-cuerpo [data-accion-modal="cancelar"]');
  if(botonCancelar) botonCancelar.addEventListener('click', cerrarModal);

  const primerCampo = document.querySelector('#modal-cuerpo input, #modal-cuerpo select, #modal-cuerpo textarea');
  if(primerCampo) primerCampo.focus();
}

function cerrarModal(){
  const capa = document.getElementById('capa-modal');
  if(capa.hidden) return;
  capa.hidden = true;
  document.getElementById('modal-cuerpo').innerHTML = '';
  document.body.style.overflow = '';
  const callback = callbackCierreModal;
  callbackCierreModal = null;
  if(typeof callback === 'function') callback();
  if(elementoConFocoPrevio && typeof elementoConFocoPrevio.focus === 'function'){
    elementoConFocoPrevio.focus();
  }
}

function abrirConfirmacion(titulo, texto, alAceptar){
  document.getElementById('titulo-confirmacion').textContent = titulo;
  document.getElementById('texto-confirmacion').textContent = texto;
  callbackConfirmacionAceptar = alAceptar;
  document.getElementById('capa-confirmacion').hidden = false;
  document.body.style.overflow = 'hidden';
  document.getElementById('boton-cancelar-confirmacion').focus();
}

function cerrarConfirmacion(){
  document.getElementById('capa-confirmacion').hidden = true;
  document.body.style.overflow = '';
  callbackConfirmacionAceptar = null;
}

function atraparFoco(evento, contenedor){
  const focables = contenedor.querySelectorAll('a[href], button:not([disabled]), input:not([disabled]), select:not([disabled]), textarea:not([disabled]), [tabindex]:not([tabindex="-1"])');
  if(focables.length === 0) return;
  const primero = focables[0];
  const ultimo = focables[focables.length - 1];
  if(evento.shiftKey && document.activeElement === primero){
    evento.preventDefault();
    ultimo.focus();
  } else if(evento.shiftKey === false && document.activeElement === ultimo){
    evento.preventDefault();
    primero.focus();
  }
}

function manejarTeclaGlobal(evento){
  if(evento.key === 'Escape'){
    if(document.getElementById('capa-confirmacion').hidden === false){ cerrarConfirmacion(); return; }
    if(document.getElementById('capa-modal').hidden === false){ cerrarModal(); return; }
    if(document.getElementById('app').classList.contains('lateral-movil-abierta')){ cerrarMenuMovil(); return; }
  }
  if(evento.key === 'Tab' && document.getElementById('capa-modal').hidden === false){
    atraparFoco(evento, document.getElementById('modal'));
  }
}

/* ============================================================
   16. NOTIFICACIONES (toasts)
   ============================================================ */

function mostrarNotificacion(tipo, mensaje){
  const contenedor = document.getElementById('contenedor-toasts');
  const iconos = { exito: 'icono-exito', error: 'icono-error', info: 'icono-info', advertencia: 'icono-alerta' };
  const toast = document.createElement('div');
  toast.className = 'toast toast-' + tipo;
  toast.setAttribute('role', 'status');
  toast.innerHTML = '<svg aria-hidden="true"><use href="#' + (iconos[tipo] || 'icono-info') + '"></use></svg><p></p>';
  toast.querySelector('p').textContent = mensaje;
  contenedor.appendChild(toast);
  setTimeout(function(){
    toast.classList.add('saliendo');
    setTimeout(function(){ toast.remove(); }, 250);
  }, CONFIGURACION_APP.duracionToast);
}

/* ============================================================
   17. EVENTOS
   ============================================================ */

function manejarClicEnContenido(evento){
  const boton = evento.target.closest('[data-accion]');
  if(!boton) return;
  const accion = boton.dataset.accion;
  const identificacion = boton.dataset.identificacion;
  if(accion === 'ver-cliente'){ abrirModalDetalleCliente(identificacion); }
  else if(accion === 'ver-tecnico'){ abrirModalDetalleTecnico(identificacion); }
  else if(accion === 'ver-dispositivo'){ abrirModalDetalleDispositivo(identificacion); }
  else if(accion === 'ver-orden'){ abrirModalDetalleOrden(identificacion); }
  else if(accion === 'actualizar-estado-orden'){ abrirModalActualizarEstado(identificacion); }
  else if(accion === 'ver-historial'){ abrirModalDetalleHistorial(boton.dataset.indice); }
}

function conectarFiltro(id, manejador){
  const elemento = document.getElementById(id);
  elemento.addEventListener('input', manejador);
  elemento.addEventListener('change', manejador);
}

function inicializarEventos(){
  document.querySelectorAll('.enlace-navegacion[data-seccion]').forEach(function(enlace){
    enlace.addEventListener('click', function(){ navegarASeccion(enlace.dataset.seccion); });
  });
  document.querySelectorAll('[data-seccion].boton').forEach(function(boton){
    boton.addEventListener('click', function(){ navegarASeccion(boton.dataset.seccion); });
  });

  document.getElementById('boton-colapsar').addEventListener('click', alternarColapsoLateral);
  document.getElementById('boton-menu-movil').addEventListener('click', abrirMenuMovil);
  document.getElementById('fondo-superpuesto').addEventListener('click', cerrarMenuMovil);

  document.getElementById('boton-cerrar-modal').addEventListener('click', cerrarModal);
  document.getElementById('capa-modal').addEventListener('click', function(evento){ if(evento.target === this) cerrarModal(); });
  document.getElementById('capa-confirmacion').addEventListener('click', function(evento){ if(evento.target === this) cerrarConfirmacion(); });
  document.getElementById('boton-aceptar-confirmacion').addEventListener('click', function(){
    const callback = callbackConfirmacionAceptar;
    cerrarConfirmacion();
    if(typeof callback === 'function') callback();
  });
  document.getElementById('boton-cancelar-confirmacion').addEventListener('click', cerrarConfirmacion);
  document.addEventListener('keydown', manejarTeclaGlobal);

  document.getElementById('boton-nuevo-cliente').addEventListener('click', abrirModalNuevoCliente);
  document.getElementById('boton-nuevo-tecnico').addEventListener('click', abrirModalNuevoTecnico);
  document.getElementById('boton-nuevo-dispositivo').addEventListener('click', abrirModalNuevoDispositivo);
  document.getElementById('boton-nuevo-servicio').addEventListener('click', abrirModalNuevoServicio);
  document.getElementById('boton-nueva-orden').addEventListener('click', abrirModalNuevaOrden);
  document.getElementById('boton-nuevo-historial').addEventListener('click', abrirModalNuevoHistorial);

  document.getElementById('boton-restablecer-datos').addEventListener('click', function(){
    abrirConfirmacion(
      'Restablecer datos de demostración',
      'Esta acción eliminará todos los clientes, técnicos, dispositivos, servicios, órdenes e historial guardados en este navegador, y los reemplazará por los datos de demostración originales. Esta acción no se puede deshacer.',
      restablecerDatosDemostracion
    );
  });

  document.getElementById('contenido-principal').addEventListener('click', manejarClicEnContenido);

  ['buscar-cliente-codigo', 'buscar-cliente-nombre', 'filtro-cliente-estado'].forEach(function(id){ conectarFiltro(id, actualizarTablaClientes); });
  ['buscar-tecnico-codigo', 'buscar-tecnico-texto', 'filtro-tecnico-disponibilidad'].forEach(function(id){ conectarFiltro(id, actualizarTablaTecnicos); });
  ['buscar-dispositivo-identificacion', 'buscar-dispositivo-marca', 'buscar-dispositivo-modelo', 'filtro-dispositivo-cliente', 'filtro-dispositivo-tipo', 'filtro-dispositivo-estado'].forEach(function(id){ conectarFiltro(id, actualizarTablaDispositivos); });
  ['buscar-servicio-identificacion', 'filtro-servicio-tipo'].forEach(function(id){ conectarFiltro(id, actualizarListaServicios); });
  ['buscar-orden-identificacion', 'filtro-orden-estado', 'filtro-orden-tecnico', 'filtro-orden-cliente', 'filtro-orden-solo-pendientes'].forEach(function(id){ conectarFiltro(id, actualizarTablaOrdenes); });
  ['buscar-historial-dispositivo', 'buscar-historial-tecnico', 'filtro-historial-fecha'].forEach(function(id){ conectarFiltro(id, actualizarTablaHistorial); });

  document.getElementById('boton-limpiar-filtros-historial').addEventListener('click', function(){
    document.getElementById('buscar-historial-dispositivo').value = '';
    document.getElementById('buscar-historial-tecnico').value = '';
    document.getElementById('filtro-historial-fecha').value = '';
    actualizarTablaHistorial();
  });
}

/* ============================================================
   18. INICIALIZACIÓN
   ============================================================ */

function inicializarAplicacion(){
  const almacenamientoDisponible = verificarDisponibilidadAlmacenamiento();
  actualizarIndicadorEstadoSistema(almacenamientoDisponible);

  cargarDatosApp();

  const configuracion = leerAlmacenamiento(CLAVES_ALMACENAMIENTO.configuracion, { version: 1, inicializado: true, lateralColapsado: false });
  if(configuracion.lateralColapsado){
    document.getElementById('app').classList.add('lateral-colapsado');
    document.getElementById('boton-colapsar').setAttribute('aria-pressed', 'true');
  }

  inicializarEventos();
  renderizarAccesosRapidos();

  actualizarRelojSistema();
  setInterval(actualizarRelojSistema, 1000);

  refrescarTodaLaInterfaz();

  const seccionInicial = location.hash ? location.hash.replace('#', '') : 'dashboard';
  navegarASeccion(seccionInicial);

  if(clavesCorruptasDetectadas.length > 0){
    mostrarNotificacion('advertencia', 'Se detectaron datos dañados en el almacenamiento local y se restauraron listas vacías para continuar de forma segura.');
  }
  if(almacenamientoDisponible === false){
    mostrarNotificacion('error', 'El navegador no permite usar almacenamiento local. Los datos no se guardarán entre sesiones.');
  }
}

document.addEventListener('DOMContentLoaded', inicializarAplicacion);
