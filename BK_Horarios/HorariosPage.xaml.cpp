#include "pch.h"
#include "HorariosPage.xaml.h"
#include "MainPage.xaml.h"
#include "WelcomePage.xaml.h"
#include "Sample-Utils\Helpers.h"
#include <fstream>
#include <iostream>

using namespace BK_HORARIOS;
using namespace std;
using namespace concurrency;
using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::Storage;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Interop;
using namespace Windows::Web::Http;
using namespace Windows::Web::Http::Filters;
using namespace Windows::Web::Http::Headers;
using namespace Windows::System::Profile;

// Path for local saving
static wstring w_localfolder(ApplicationData::Current->LocalFolder->Path->Begin());
static string localfolder(w_localfolder.begin(), w_localfolder.end());

// Function start_fadein_animation
void HorariosPage::HorariosPage::start_FadeInAnimation(void)
{
	HorariosPage_FadeInAnimation->Begin();
}

// OnNavigatedTo function
void HorariosPage::OnNavigatedTo(NavigationEventArgs^ e)
{
	// A pointer back to the main page.  This is needed if you want to call methods in MainPage such as NotifyUser()
	rootPage = MainPage::Current;

	// Set Back Button on Desktop devices
	SetBackButton();

	// Se invoca cuando se presionan los botones de retroceso de hardware o software.
	SystemNavigationManager::GetForCurrentView()->BackRequested += ref new EventHandler<BackRequestedEventArgs^>(this, &HorariosPage::App_BackRequested);

	// Convert String^ to int
	wstring w_legajo(((String^)e->Parameter)->Begin());
	string legajo(w_legajo.begin(), w_legajo.end());

	// CacheControl
	filter = ref new HttpBaseProtocolFilter();
	filter->CacheControl->ReadBehavior = HttpCacheReadBehavior::MostRecent;
	filter->CacheControl->WriteBehavior = HttpCacheWriteBehavior::NoCache;

	// Initialize httpclient
	client = ref new HttpClient(filter);

	// Create url with 'legajo' string
	string url = "http://proveedores.alsea.com.ar:48080/asignaciones-server/mobile/main/asignaciones/legajos/" + legajo;

	// Save last used legajo
	save_last_legajo(legajo);

	// Start Connection Async
	StartConnectionAsync(url, legajo, 0);

}

// Se invoca cuando se presionan los botones de retroceso de hardware o software.
void HorariosPage::App_BackRequested(Object^ sender, BackRequestedEventArgs^ e)
{
	e->Handled = true;
	Backbutton1(sender, nullptr);
}

// Set Back Button on Desktop devices
void HorariosPage::SetBackButton()
{
	String^ platformFamily = AnalyticsInfo::VersionInfo->DeviceFamily;

	if (platformFamily->Equals("Windows.Mobile"))
	{
		BackButtonPC->Opacity = 0;
	}
}

// Save last used legajo
void HorariosPage::save_last_legajo(string legajo)
{
	// Write file
	ofstream out(localfolder + "\\lastlegajo.tmp");
	if (out)
	{
		out << legajo;
		out.close();
	}
}

// Main
HorariosPage::HorariosPage()
{
	InitializeComponent();
}

// Function start_fadeout_animation
void HorariosPage::HorariosPage::start_FadeOutAnimation(void)
{
	HorariosPage_FadeOutAnimation->Begin();
}

// Function start_fadeout_animation2
void HorariosPage::HorariosPage::start_FadeOutAnimation2(void)
{
	HorariosPage_FadeOutAnimation2->Begin();
}

// Hyperlink buttons
void HorariosPage::Footer_Click(Object^ sender, RoutedEventArgs^ e)
{
	auto uri = ref new Uri((String^)((HyperlinkButton^)sender)->Tag);
	Windows::System::Launcher::LaunchUriAsync(uri);
}

// Go back to MainPage with uncleared errors
void HorariosPage::GoPageBack()
{
	///Specific Fix (#bug013)
	HiddenOutputField->Text = "{\"asignaciones\":[],\"fechaConsulta\":\"\",\"legajo\":\"\"}";
	DataContext = ref new User(HiddenOutputField->Text);

	// Go to page
	Frame->Navigate(TypeName(BK_HORARIOS::WelcomePage::typeid));
}

// Navigation: Back Button
void HorariosPage::Backbutton1(Object^ sender, RoutedEventArgs^ e)
{
	// Clear List of Horarios
	HiddenOutputField->Text = "{\"asignaciones\":[],\"fechaConsulta\":\"\",\"legajo\":\"\"}";

	DataContext = ref new User(HiddenOutputField->Text);

	// Clear StatusBlock
	rootPage->NotifyUser("", NotifyType::StatusMessage);

	// Go to page
	Frame->Navigate(TypeName(BK_HORARIOS::WelcomePage::typeid));
}

// Save cache to a file
void HorariosPage::save_cache(String^ cache, string legajo)
{
	// Convert String^ to string
	wstring w_data(cache->Begin());
	string s_data(w_data.begin(), w_data.end());

	// Save last used legajo to a file
	ofstream out(localfolder + "\\lasthorarios.tmp");
	if (out)
	{
		out << s_data;
		out.close();
	}

	// cache legajo
	ofstream out_c(localfolder + "\\lasthorarios" + legajo + ".tmp");
	if (out_c)
	{
		out_c << s_data;
		out_c.close();
	}

}

// Start Connection Async
void HorariosPage::StartConnectionAsync(string url, string legajo, int retry)
{
	// Show Message
	///Specific Fix (#bug090)
	rootPage->NotifyUser("Consultando horarios...", NotifyType::StatusMessage);

	// Convert string to String^
	wstring w_url(url.begin(), url.end());
	String^ baseUri = ref new String(w_url.c_str());

	// Do an asynchronous GET. We need to use use_current() with the continuations since the tasks
	// are completed on background threads and we need to run on the UI thread to update the UI.
	create_task(client->GetAsync(ref new Uri(baseUri))).then([=](HttpResponseMessage^ response)
		{
			//if (response->EnsureSuccessStatusCode())
			return Helpers::DisplayTextResultAsync(response, HiddenOutputField);
		},
		task_continuation_context::use_current()).then([=](task<HttpResponseMessage^> previousTask)
			{
				try
				{
					// Check if any previous task threw an exception.
					HttpResponseMessage^ response = previousTask.get();

					// Convert String^ to string
					wstring w_str(HiddenOutputField->Text->Data());
					string str3(w_str.begin(), w_str.end());

					// Find ':[{' string to check if the data contains a valid legajo info
					size_t found = str3.find(":[{");

					// If true
					if (found != std::string::npos)
					{
						try
						{
							// Parse JSON
							DataContext = ref new User(HiddenOutputField->Text);

							// Show successfull!
							rootPage->NotifyUser("Horarios leídos!", NotifyType::StatusMessage);

							// Save cache
							save_cache(HiddenOutputField->Text, legajo);

							// Show ContentPanelInfo
							ContentPanelInfo->Visibility = Windows::UI::Xaml::Visibility::Visible;

							// Show list
							List->Visibility = Windows::UI::Xaml::Visibility::Visible;

							// Stop ProgressRing
							loading_ring->IsActive = false;
						}
						catch (Exception ^ ex)
						{
							// Database parsing error
							rootPage->NotifyUser("Hay problemas con la conexión a internet.\nReintentando...", NotifyType::ErrorMessage);
							if (retry == 0)
							{
								StartConnectionAsync(url, legajo, 1);
							}
							else
							{
								rootPage->NotifyUser("Hay problemas con la conexión a internet.", NotifyType::ErrorMessage);

								// Try to read from cache
								read_cache(legajo, 1);
							}
						}
					}
					else
					{
						// Legajo NOT FOUND error
						rootPage->NotifyUser("El legajo no existe o no tiene asignado los horarios.", NotifyType::ErrorMessage);
						GoPageBack();
					}
				}
				catch (Exception^)
				{
					// If no internet connection is available, check if the last legajo obtained is equal to
					// the actual legajo and read it from the cache and show a message.

					rootPage->NotifyUser("Error. No hay conexión a internet.", NotifyType::ErrorMessage);

					// Try to read from cache
					read_cache(legajo, 0);
				}
			}
		);
}

// Read from cache
void HorariosPage::read_cache(string legajo, int database_error)
{
	// Read file
	string data;
	ifstream in(localfolder + "\\lasthorarios" + legajo + ".tmp");
	if (in)
	{
		getline(in, data);
		in.close();
	}

	// Check legajo first and if valid, parse JSon

	// Search for legajo item
	string query = "\"legajo\":\"" + legajo + "\"}";
	size_t found = data.find(query);

	// If true
	if (found != std::string::npos)
	{
		// Convert string to String^
		wstring w_data = wstring(data.begin(), data.end());
		String^ Str_data = ref new String(w_data.c_str());

		// Parse JSon
		DataContext = ref new User(Str_data);

		// Show ContentPanelInfo
		ContentPanelInfo->Visibility = Windows::UI::Xaml::Visibility::Visible;

		// Stop ProgressRing
		loading_ring->IsActive = false;

		// Show ErrorMessage
		if (database_error == 1)
		{
			rootPage->NotifyUser("Hay problemas con la conexión a internet.\nÚltimos horarios leídos de la memoria", NotifyType::ErrorMessage);
		}
		else
		{
			rootPage->NotifyUser("Error. No hay conexión a internet.\nÚltimos horarios leídos de la memoria", NotifyType::ErrorMessage);
		}

		// Show list
		List->Visibility = Windows::UI::Xaml::Visibility::Visible;
	}
	// Else Go Back
	else
	{
		GoPageBack();
	}
}

