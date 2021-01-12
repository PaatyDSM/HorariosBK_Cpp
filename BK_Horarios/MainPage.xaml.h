#pragma once

#include "MainPage.g.h"

namespace BK_HORARIOS
{
	/// <summary>
	/// Enumera los tipos de notificación de estado.
	/// </summary>
	public enum class NotifyType
	{
		StatusMessage,
		ErrorMessage,
		DebugMessage
	};

	/// <summary>
	/// MainPage contiene el "Frame" en el cual todas las páginas son cargadas y el
	/// "StatusBlock" que notifica los distintos tipos de mensaje al usuario.
	/// </summary>
	public ref class MainPage sealed
	{
	public:
		MainPage();

	protected:
		virtual void OnNavigatedTo(NavigationEventArgs^ e) override;

	private:
		void SetFullScreenModeON();

	internal:
		static MainPage^ Current;
		void NotifyUser(String^ strMessage, NotifyType type);

	};
}
