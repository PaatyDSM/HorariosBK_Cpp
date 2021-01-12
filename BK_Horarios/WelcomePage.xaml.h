#pragma once

#include "WelcomePage.g.h"
#include "MainPage.xaml.h"

using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Navigation;

namespace BK_HORARIOS
{
	/// <summary>
	/// Página que muestra los horarios en formato de lista.
	/// </summary>
	[Windows::Foundation::Metadata::WebHostHidden]

	public ref class WelcomePage sealed
	{
	public:
		WelcomePage();

	protected:
		virtual void OnNavigatedTo(NavigationEventArgs^ e) override;
		void App_BackRequested(Object ^ sender, BackRequestedEventArgs ^ e);

	private:
		MainPage^ rootPage;

		void start_FadeInAnimation(void);
		void read_legajo(void);
		void send_legajo_button(Object^ sender, RoutedEventArgs^ e);
		void Footer_Click(Object^ sender, RoutedEventArgs^ e);
		void start_FadeOutAnimation(void);
		void NavigatetoHorariosPage(Object^ sender, RoutedEventArgs^ e);
		void start_ReleaseNotesFadeOutAnimation(void);
		void Release_Notes_Click(Platform::Object^ sender, RoutedEventArgs^ e);
		void main_legajo_input_KeyDown(Platform::Object^ sender, Windows::UI::Xaml::Input::KeyRoutedEventArgs^ e);
	};
}


