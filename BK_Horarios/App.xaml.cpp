#include "pch.h"
#include "MainPage.xaml.h"

using namespace BK_HORARIOS;
using namespace Platform;
using namespace Windows::ApplicationModel;
using namespace Windows::ApplicationModel::Activation;
using namespace Windows::Foundation;
using namespace Windows::UI::Core;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Interop;
using namespace Windows::UI::Xaml::Navigation;

/// <summary>
/// Inicializa el objeto de aplicación Singleton. Esta es la primera línea de código creado
/// ejecutado y, como tal, es el equivalente lógico de main() o WinMain().
/// </summary>
App::App()
{
	InitializeComponent();
	Suspending += ref new SuspendingEventHandler(this, &App::OnSuspending);
}

/// <summary>
/// Se invoca cuando la aplicación la inicia normalmente el usuario final. Se usarán otros puntos
/// de entrada cuando la aplicación se inicie para abrir un archivo específico, por ejemplo.
/// </summary>
/// <param name="e">Información detallada acerca de la solicitud y el proceso de inicio.</param>
void App::OnLaunched(LaunchActivatedEventArgs^ e)
{
	// El siguiente comando admite la navegación a páginas nuevas y mantiene
	// un historial de navegación para navegar hacia adelante y hacia atrás.
	auto rootFrame = dynamic_cast<Frame^>(Window::Current->Content);

	// No repetir la inicialización de la aplicación si la ventana aún tiene contenido,
	// solo asegurarse de que la ventana está activa.
	if (rootFrame == nullptr)
	{
		// Crear un Frame que actua como contexto de navegación.
		rootFrame = ref new Frame();

		rootFrame->NavigationFailed += ref new NavigationFailedEventHandler(this, &App::OnNavigationFailed);

		if (e->PreviousExecutionState == ApplicationExecutionState::Terminated)
		{
			// Restaurar el estado de sesión guardado solo cuando sea necesario, programando
			// los pasos de inicio finales una vez completada la restauración.

			/*	.DISABLED. ONLY FOR TESTING.	*/
			// prerequisite = SuspensionManager::RestoreAsync();
		}
		if (e->PrelaunchActivated == false)
		{
			if (rootFrame->Content == nullptr)
			{
				// Cuando no se restaura la pila de navegación, navegar a la primera página,
				// configurando la nueva página pasándole la información requerida como
				// parámetro de navegación.
				rootFrame->Navigate(TypeName(MainPage::typeid), e->Arguments);
			}
			// Poner el marco en la ventana actual.
			Window::Current->Content = rootFrame;

			// Asegurarse de que la ventana actual está activa.
			Window::Current->Activate();
		}
	}
	else
	{
		if (e->PrelaunchActivated == false)
		{
			if (rootFrame->Content == nullptr)
			{
				// Cuando no se restaura la pila de navegación, navegar a la primera página,
				// configurando la nueva página pasándole la información requerida como
				// parámetro de navegación.
				rootFrame->Navigate(TypeName(MainPage::typeid), e->Arguments);
			}
			// Asegurarse de que la ventana actual está activa.
			Window::Current->Activate();
		}
	}
}

/// <summary>
/// Se invoca al suspender la ejecución de la aplicación. El estado de la aplicación se guarda
/// sin saber si la aplicación finalizará o se reanudará con el contenido
/// de la memoria aún intacto.
/// </summary>
/// <param name="sender">Origen de la solicitud de suspensión.</param>
/// <param name="e">Detalles de la solicitud de suspensión.</param>
void App::OnSuspending(Object^ sender, SuspendingEventArgs^ e)
{
	(void)sender;	// Parámetro sin usar
	(void)e;		// Parámetro sin usar

	// Guardar el estado de la aplicación y detener toda actividad en segundo plano.
}

/// <summary>
/// Se invoca cuando la aplicación la inicia normalmente el usuario final. Se usarán otros puntos
/// </summary>
/// <param name="sender">Marco que produjo el error de navegación</param>
/// <param name="e">Detalles sobre el error de navegación</param>
void App::OnNavigationFailed(Platform::Object^ sender, NavigationFailedEventArgs^ e)
{
	/// <param name="sender">Marco que produjo el error de navegación</param>
	/// <param name="e">Detalles sobre el error de navegación</param>
	throw ref new FailureException("Error al cargar la siguiente página: \"" + e->SourcePageType.Name + "\"");
}
