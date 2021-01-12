#pragma once

#include "App.g.h"

using namespace Platform;
using namespace Windows::ApplicationModel;
using namespace Windows::ApplicationModel::Activation;
using namespace Windows::UI::Core;
using namespace Windows::UI::Xaml::Navigation;

namespace BK_HORARIOS
{
	/// <summary>
	/// Proporciona un comportamiento específico de la aplicación para complementar la clase Application predeterminada.
	/// </summary>
	ref class App sealed
	{
	protected:
		virtual void OnLaunched(LaunchActivatedEventArgs^ e) override;
	
	internal:
		App();

	private:
		void OnSuspending(Object^ sender, SuspendingEventArgs^ e);
		void OnNavigationFailed(Object ^sender, NavigationFailedEventArgs ^e);
	};
}


