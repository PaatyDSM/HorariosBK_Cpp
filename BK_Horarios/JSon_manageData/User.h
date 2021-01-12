#pragma once

#include "WorkDays.h"
#include "MainPage.xaml.h"

using namespace Platform;
using namespace Platform::Collections;
using namespace Windows::Foundation::Collections;

namespace BK_HORARIOS
{
	// Mark as WebHostHidden since WorkDays is WebHostHidden.
	[Windows::Foundation::Metadata::WebHostHidden]
	[Windows::UI::Xaml::Data::Bindable]
	public ref class User sealed
	{
	public:
		User(void);
		User(String^ jsonString);

	property String^ Legajo
	{
		String^ get();
		void set(String^ value);
	}

	property String^ FechaConsulta
	{
		String^ get();
		void set(String^ value);
	}

	property IVector<WorkDays^>^ Asignaciones
	{
		IVector<WorkDays^>^ get();
	}

	private:
		static String^ legajoKey;
		static String^ fechaConsultaKey;
		static String^ asignacionesKey;

	String^ legajo;
	String^ fechaConsulta;
	Vector<WorkDays^>^ asignaciones;
	};

}
