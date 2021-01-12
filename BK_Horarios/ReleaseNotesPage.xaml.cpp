#include "pch.h"

#include "ReleaseNotesPage.xaml.h"
#include "MainPage.xaml.h"

using namespace BK_HORARIOS;

using namespace Windows::Foundation;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Interop;
using namespace Windows::System::Profile;

static String^ CurrentVersionNumber = "1.2";

ReleaseNotesPage::ReleaseNotesPage()
{
	InitializeComponent();

	// Set version number
	FP_VersionButton->Content = CurrentVersionNumber;
}

// Function start_fadein_animation
void ReleaseNotesPage::start_FadeInAnimation(void)
{
	ReleaseNotes_FadeInAnimation->Begin();
}

// Function start_fadeout_animation
void ReleaseNotesPage::start_FadeOutAnimation(void)
{
	ReleaseNotes_FadeOutAnimation->Begin();
}

void ReleaseNotesPage::OnNavigatedTo(NavigationEventArgs^ e)
{
	SetBackButton();
	// Se invoca cuando se presionan los botones de retroceso de hardware o software.
	SystemNavigationManager::GetForCurrentView()->BackRequested += ref new EventHandler<BackRequestedEventArgs^>(this, &ReleaseNotesPage::App_BackRequested);
}

// Se invoca cuando se presionan los botones de retroceso de hardware o software.
void ReleaseNotesPage::App_BackRequested(Object^ sender, BackRequestedEventArgs^ e)
{
	e->Handled = true;
	Backbutton1(sender, nullptr);
}

// Navigation: Back Button
void ReleaseNotesPage::Backbutton1(Object^ sender, RoutedEventArgs^ e)
{
	Frame->Navigate(TypeName(BK_HORARIOS::WelcomePage::typeid));
}

// Set Back Button on Desktop devices
void ReleaseNotesPage::SetBackButton()
{
	String^ platformFamily = AnalyticsInfo::VersionInfo->DeviceFamily;

	if (platformFamily->Equals("Windows.Mobile"))
	{
		BackButtonPC->Opacity = 0;
	}
}

// On Click 'Hyperlinks'
void ReleaseNotesPage::Footer_Click(Object^ sender, RoutedEventArgs^ e)
{
	auto uri = ref new Uri((String^)((HyperlinkButton^)sender)->Tag);
	Windows::System::Launcher::LaunchUriAsync(uri);
}

void ReleaseNotesPage::LoadReleaseNotes(void)
{
	Notes->Text =
		"V1.2\n"
		"*Fixed an adress error in the server that caused the lejajos not to be found.\n"
		"*Changed minimun required Windows version to 10.0.10586 and updated libraries.\n"
		"*Fix minor errors on links.\n"
		"*Fixed certificates.\n"
		"\n"
		"------------------\n"
		"V1.1\n"
		"*Fixed crash in MainPage.\n"
		"*Cache multiple legajos.\n"
		"*Improved code.\n"
		"*Removed unused code.\n"
		"*Fixed bug#090.\n"
		"*Updated language to Spanish-Argentina.\n"
		"*Minor translations fixes.\n"
		"*GUI fixes in WelcomePage.\n"
		"*GUI fixes in HorariosPage.\n"
		"*GUI fixes in StatusMessage.\n"
		"*Fixed BadgeLogo assets for certification.\n"
		"*Update Webpage url.\n"
		"*Updated certificates.\n"
		"*Updated project to VS2019.\n"
		"\n"
		"------------------\n"
		"V1.0 (First release)\n"
		"(May / 3 / 2018)\n"
		"*Deleted unused code.\n"
		"*Fixed images.\n"
		"\n";

	// Stop ProgressRing
	loading_ring->IsActive = false;

	//Notes->VerticalAlignment = ...;
}



