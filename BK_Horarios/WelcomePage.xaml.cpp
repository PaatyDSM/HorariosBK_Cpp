#include "pch.h"
#include "WelcomePage.xaml.h"
#include "HorariosPage.xaml.h"
#include "ReleaseNotesPage.xaml.h"
#include "Sample-Utils\Helpers.h"
#include <fstream>
#include <thread>
#include <pplawait.h>
#include <string.h>

using namespace BK_HORARIOS;
using namespace std;
using namespace Concurrency;
using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::Storage;
using namespace Windows::System;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Interop;
using namespace Windows::UI::Xaml::Media;

static String^ CurrentVersionNumber = "v1.1";
static int CurrentVersionNumberInt = 110;

// Function start_fadein_animation
void WelcomePage::WelcomePage::start_FadeInAnimation(void)
{
	WelcomepPage_FadeInAnimation->Begin();
}

// OnNavigatedTo function
void WelcomePage::OnNavigatedTo(NavigationEventArgs^ e)
{
	// A pointer back to the main page.  This is needed if you want to call methods in MainPage such as NotifyUser()
	rootPage = MainPage::Current;

	if (e->Content->ToString() == "BackButtonPressed")
	{
		// Clear errors
		rootPage->NotifyUser("", NotifyType::StatusMessage);
	}

	// Set version number
	FP_VersionButton->Content = CurrentVersionNumber;

	// Read last used legajo
	read_legajo();

	// Check for updates
	//CheckUpdates();

}

// Read last used legajo
void WelcomePage::read_legajo(void)
{
	// Path for local saving
	wstring w_localfolder(ApplicationData::Current->LocalFolder->Path->Begin());
	string localfolder(w_localfolder.begin(), w_localfolder.end());

	// Filename
	string filename = localfolder + "\\lastlegajo.tmp";

	// Read file
	char fileData[16] = "";
	ifstream in(filename);
	if (in)
	{
		in >> fileData;
		in.close();
	}

	// Convert char to String^
	string s_filedata = string(fileData);
	wstring w_filedata = wstring(s_filedata.begin(), s_filedata.end());
	String^ str_fileData = ref new String(w_filedata.c_str());

	// Put legajo into TextBox
	main_legajo_input->Text = str_fileData;
}

// Main
WelcomePage::WelcomePage()
{
	InitializeComponent();
}

// On click 'Consultar Horarios' validate Legajo and send it to the next page 'HorariosPage'
void WelcomePage::send_legajo_button(Object^ sender, RoutedEventArgs^ e)
{
	// Clear errors
	rootPage->NotifyUser("", NotifyType::StatusMessage);

	// Convert String^ to string
	wstring w_str(main_legajo_input->Text->Begin());
	string str(w_str.begin(), w_str.end());

	// Check if 'legajo' is valid
	size_t check = str.find_first_not_of("0123456789");

	// Error handler and error messages
	// If no input
	if (str.length() == 0)
	{
		rootPage->NotifyUser("Primero tenés que ingresar un legajo.", NotifyType::ErrorMessage);
	}
	// If illegal character
	else if (check != string::npos)
	{
		rootPage->NotifyUser("El legajo que ingresaste no es válido.", NotifyType::ErrorMessage);
	}
	// If valid
	else
	{
		// Start FadeOutAnimation
		start_FadeOutAnimation();
	}
}

// Function start FadeOutAnimation
void WelcomePage::start_FadeOutAnimation()
{
	WelcomepPage_FadeOutAnimation->Begin();
}

// Navigate to HorariosPage
void WelcomePage::NavigatetoHorariosPage(Object^ sender, RoutedEventArgs^ e)
{
	// Navigate to HorariosPage and send parameters
	this->Frame->Navigate(TypeName(HorariosPage::typeid), main_legajo_input->Text);
}

// Function start_ReleaseNotesFadeOutAnimation
void WelcomePage::start_ReleaseNotesFadeOutAnimation()
{
	//TransitionColorFix1->Background = ref new SolidColorBrush(Windows::UI::Colors::Black);
	WelcomepPage_ReleaseNotesFadeOutAnimation->Begin();
}

// On click 'Hyperlinks'
void WelcomePage::Footer_Click(Object^ sender, RoutedEventArgs^ e)
{
	auto uri = ref new Uri((String^)((HyperlinkButton^)sender)->Tag);
	Windows::System::Launcher::LaunchUriAsync(uri);
}

// On click 'Version number' navigate to 'Release Notes Page'
void WelcomePage::Release_Notes_Click(Object^ sender, RoutedEventArgs^ e)
{
	// Clean error messages from previous page
	rootPage->NotifyUser("", NotifyType::StatusMessage);

	this->Frame->Navigate(TypeName(ReleaseNotesPage::typeid));
}

void WelcomePage::CheckUpdates(void)
{
	HiddenOutputField->Text = "";
	try
	{
		filter = ref new HttpBaseProtocolFilter();
		filter->CacheControl->ReadBehavior = HttpCacheReadBehavior::Default;
		filter->CacheControl->WriteBehavior = HttpCacheWriteBehavior::Default;
		client = ref new HttpClient(filter);
		create_task(client->GetAsync(ref new Uri("https://paatydsm.000webhostapp.com/apps/uwp/bk_horarios/version/last.txt"))).then([=](HttpResponseMessage^ response)
			{
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
						string str(w_str.begin(), w_str.end());
						int LastVersionAvailable = stoi(str);

						if (CurrentVersionNumberInt < LastVersionAvailable)
						{
							UpdatePanel->Visibility = Windows::UI::Xaml::Visibility::Visible;
						}
					}
					catch (Exception ^ ex)
					{
						UpdatePanel->Visibility = Windows::UI::Xaml::Visibility::Collapsed;
					}
				}
			);
	}
	catch (Exception ^ ex)
	{
		UpdatePanel->Visibility = Windows::UI::Xaml::Visibility::Collapsed;
	}
}

void WelcomePage::OnKeyDownHandler(Object^ sender, KeyEventArgs^ e)
{
	if (e->VirtualKey == VirtualKey::Enter)
	{
		send_legajo_button(nullptr, nullptr);
	}
}
