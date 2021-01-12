#include "pch.h"

#include "ReleaseNotesPage.xaml.h"
#include "MainPage.xaml.h"

using namespace BK_HORARIOS;

using namespace Windows::Foundation;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Interop;
using namespace Windows::System::Profile;

ReleaseNotesPage::ReleaseNotesPage()
{
	InitializeComponent();
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

// Navigation: Back Button
void ReleaseNotesPage::Backbutton1(Object^ sender, RoutedEventArgs^ e)
{
	Frame->Navigate(TypeName(BK_HORARIOS::WelcomePage::typeid));
}

void ReleaseNotesPage::LoadReleaseNotes(void)
{
	Notes->Text =

		"V1.0 (First release)\n"
		"(May / 3 / 2018)\n"
		"*Deleted unused code.\n"
		"*Fixed images.\n"
		"\n";

		// Stop ProgressRing
		loading_ring->IsActive = false;
}
