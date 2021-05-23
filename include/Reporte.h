#ifndef REPORTE_H
#define REPORTE_H
#include "UI.h"
#include "VentaDetalle.h"
#include "VentaCabecera.h"

/// REPORTE #1
void FacturacionesPorImporte(int,int);
void OrdenarFacturacionPorImporte(VentaCabecera*,int ,bool );

/// REPORTE #2
void PromedioRecaudacionPorMes(int,int);
float CalcularPromedio(int,int,bool);

#endif // REPORTE_H
