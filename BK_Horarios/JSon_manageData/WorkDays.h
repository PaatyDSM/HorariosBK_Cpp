#pragma once

using namespace Windows::Data::Json;

namespace BK_HORARIOS
{
	// Mark as WebHostHidden since Windows.Data.Json API is not available in JavaScript.
	[Windows::Foundation::Metadata::WebHostHidden]
	[Windows::UI::Xaml::Data::Bindable]
	public ref class WorkDays sealed
	{
	public:
		WorkDays(void);
		WorkDays(JsonObject^ jsonObject);

	property String^ Fecha
	{
		String^ get();
		void set(String^ value);
	}

	property String^ HoraEntrada
	{
		String^ get();
		void set(String^ value);
	}

	property String^ HoraSalida
	{
		String^ get();
		void set(String^ value);
	}

	property String^ Tienda
	{
		String^ get();
		void set(String^ value);
	}

	private:
		static String^ fechaKey;
		static String^ horaEntradaKey;
		static String^ horaSalidaKey;
		static String^ tiendaKey;
		static String^ asignacionesKey;

		String^ fecha;
		String^ horaEntrada;
		String^ horaSalida;
		String^ tienda;
	};
}

