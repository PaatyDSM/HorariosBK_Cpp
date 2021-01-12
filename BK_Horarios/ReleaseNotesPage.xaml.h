#pragma once

#include "ReleaseNotesPage.g.h"
#include "WelcomePage.xaml.h"

namespace BK_HORARIOS
{
	/// <summary>
	/// Una página vacía que se puede usar de forma independiente o a la que se puede navegar dentro de un objeto Frame.
	/// </summary>
	[Windows::Foundation::Metadata::WebHostHidden]
	public ref class ReleaseNotesPage sealed
	{
	public:
		ReleaseNotesPage();

	protected:
		virtual void OnNavigatedTo(NavigationEventArgs^ e) override;

	private:
		MainPage^ rootPage;

		void start_FadeInAnimation(void);
		void App_BackRequested(Object^ sender, BackRequestedEventArgs^ e);
		void SetBackButton(void);
		void LoadReleaseNotes(void);
		void start_FadeOutAnimation(void);
		void Footer_Click(Object^ sender, RoutedEventArgs^ e);
		void Backbutton1(Object^ sender, RoutedEventArgs^ e);
	};
}
