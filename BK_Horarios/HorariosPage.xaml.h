#pragma once

#include "HorariosPage.g.h"
#include "WelcomePage.xaml.h"

using namespace std;
using namespace Windows::Web::Http;
using namespace Windows::Web::Http::Filters;

namespace BK_HORARIOS
{
	/// <summary>
	/// Una página vacía que se puede usar de forma independiente o a la que se puede navegar dentro de un objeto Frame.
	/// </summary>
	[Windows::Foundation::Metadata::WebHostHidden]

	public ref class HorariosPage sealed
	{
	public:
		HorariosPage();

	protected:
		virtual void OnNavigatedTo(NavigationEventArgs^ e) override;

	private:
		MainPage^ rootPage;

		HttpClient^ client;
		HttpBaseProtocolFilter^ filter;

		void start_FadeInAnimation(void);
		void start_FadeOutAnimation(void);
		void start_FadeOutAnimation2(void);
		void SetBackButton(void);
		void StartConnectionAsync(string, string);
		void Backbutton1(Object^ sender, RoutedEventArgs^ e);
		void GoPageBack(void);
		void Footer_Click(Object^ sender, RoutedEventArgs^ e);
		void save_legajo(string);
		void save_cache(String^ e);
		void read_cache(string);
	};
}
