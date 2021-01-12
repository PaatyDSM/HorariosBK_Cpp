#include "pch.h"
#include "User.h"

using namespace BK_HORARIOS;

using namespace Platform;
using namespace Platform::Collections;
using namespace Windows::Data::Json;
using namespace Windows::Foundation::Collections;

String^ User::legajoKey = "legajo";
String^ User::fechaConsultaKey = "fechaConsulta";
String^ User::asignacionesKey = "asignaciones";

User::User(void) : legajo(""), fechaConsulta("")
{
	asignaciones = ref new Vector<WorkDays^>();
}

User::User(String^ jsonString)
{
    JsonObject^ jsonObject = JsonObject::Parse(jsonString);
	legajo = jsonObject->GetNamedString(legajoKey, L"");
	fechaConsulta = jsonObject->GetNamedString(fechaConsultaKey, "");

	asignaciones = ref new Vector<WorkDays^>();

    JsonArray^ jsonArray = jsonObject->GetNamedArray(asignacionesKey, ref new JsonArray());
    for (unsigned int i = 0; i < jsonArray->Size; i++)
    {
        IJsonValue^ jsonValue = jsonArray->GetAt(i);
        if (jsonValue->ValueType == JsonValueType::Object)
        {
			asignaciones->Append(ref new WorkDays(jsonValue->GetObject()));
        }
    }
}

String^ User::Legajo::get()
{
    return legajo;
}

void User::Legajo::set(String^ value)
{
	legajo = value;
}

String^ User::FechaConsulta::get()
{
    return fechaConsulta;
}

void User::FechaConsulta::set(String^ value)
{
	fechaConsulta = value;
}

IVector<WorkDays^>^ User::Asignaciones::get()
{
    return asignaciones;
}
