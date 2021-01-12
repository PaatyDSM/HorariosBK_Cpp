#include "pch.h"
#include "WorkDays.h"

using namespace BK_HORARIOS;

using namespace Platform;
using namespace Windows::Data::Json;

String^ WorkDays::fechaKey = "fecha";
String^ WorkDays::horaEntradaKey = "horaEntrada";
String^ WorkDays::horaSalidaKey = "horaSalida";
String^ WorkDays::tiendaKey = "tienda";
String^ WorkDays::asignacionesKey = "asignaciones";

WorkDays::WorkDays(void) : fecha(""), horaEntrada(""), horaSalida(""), tienda("")
{
}

WorkDays::WorkDays(JsonObject^ jsonObject)
{
	JsonObject^ WorkDaysObject = jsonObject->GetNamedObject(asignacionesKey, nullptr);
	fecha = jsonObject->GetNamedString(fechaKey);
	HoraEntrada = jsonObject->GetNamedString(horaEntradaKey);
	HoraSalida = jsonObject->GetNamedString(horaSalidaKey);
	Tienda = jsonObject->GetNamedString(tiendaKey);
}


String^ WorkDays::Fecha::get()
{
	return fecha;
}

void WorkDays::Fecha::set(String^ value)
{
	fecha = value;
}

String^ WorkDays::HoraEntrada::get()
{
	return horaEntrada;
}

void WorkDays::HoraEntrada::set(String^ value)
{
	horaEntrada = value;
}

String^ WorkDays::HoraSalida::get()
{
	return horaSalida;
}

void WorkDays::HoraSalida::set(String^ value)
{
	horaSalida = value;
}

String^ WorkDays::Tienda::get()
{
	return tienda;
}

void WorkDays::Tienda::set(String^ value)
{
	tienda = value;
}
