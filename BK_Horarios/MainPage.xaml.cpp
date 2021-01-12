#include "pch.h"
#include "MainPage.xaml.h"
#include "WelcomePage.xaml.h"

using namespace BK_HORARIOS;
using namespace std;
using namespace Windows::Foundation;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::UI::Xaml::Interop;
using namespace Platform;
using namespace Windows::UI::Xaml::Navigation;
using namespace Windows::UI::ViewManagement;
using namespace Windows::System::Profile;

// Referencia al Frame en el cual todas las páginas son cargadas.
MainPage^ MainPage::Current = nullptr;

// Main
MainPage::MainPage()
{
	InitializeComponent();

	// This is a static public property that allows downstream pages to get a handle
	// to the MainPage instance in order to call methods that are in this class.
	MainPage::Current = this;
}

// OnNavigatedTo function
void MainPage::OnNavigatedTo(NavigationEventArgs^ e)
{
	// Set fullscreen on mobile devices and tablets.
	SetFullScreenModeON(0);

	// Set windows size.
	ApplicationView^ view = ApplicationView::GetForCurrentView();
	view->TryResizeView(Size(500, 680));
	view->SetPreferredMinSize(Size(500, 840));

	// When the navigation stack isn't restored navigate to the WelcomePage
	if (Page_Frame->Content == nullptr)
	{
		if (!Page_Frame->Navigate(TypeName{ "BK_HORARIOS.WelcomePage", TypeKind::Custom }))
		{
			// Show navigation error
			Frame->Background = ref new SolidColorBrush(Windows::UI::Colors::Gray);
			NotifyUser("Hubo un problema al cargar la página principal.", NotifyType::ErrorMessage);
		}
	}
}

// StatusBlock function
void MainPage::NotifyUser(String^ strMessage, NotifyType type)
{
	switch (type)
	{
	case NotifyType::StatusMessage:
		StatusBorder->Background = ref new SolidColorBrush(Windows::UI::Colors::Green);
		break;
	case NotifyType::ErrorMessage:
		StatusBorder->Background = ref new SolidColorBrush(Windows::UI::Colors::Red);
		break;
	case NotifyType::DebugMessage:
		StatusBorder->Background = ref new SolidColorBrush(Windows::UI::Colors::Yellow);
		break;
	default:
		break;
	}
	StatusBlock->Text = strMessage;

	// Collapsed the StatusBlock if it has no text to conserve real estate.
	if (StatusBlock->Text != "")
	{
		StatusBorder->Visibility = Windows::UI::Xaml::Visibility::Visible;
	}
	else
	{
		StatusBorder->Visibility = Windows::UI::Xaml::Visibility::Collapsed;
	}
}

// Set fullscreen
/// <summary>
/// Launch UWP apps in full-screen mode on mobile devices and tablets, desktop or both.
/// </summary>
/// <param name="device">0 for Mobile and Tablets, 1 for PC and 2 for both platforms</param>
void MainPage::SetFullScreenModeON(int device)
{
	String^ platformFamily = AnalyticsInfo::VersionInfo->DeviceFamily;

	if (device == 0)
	{
		if (platformFamily->Equals("Windows.Mobile"))
		{
			ApplicationView^ view = ApplicationView::GetForCurrentView();
			view->TryEnterFullScreenMode();
		}
	}
	else if (device == 1)
	{
		if (platformFamily->Equals("Windows.Desktop"))
		{
			ApplicationView^ view = ApplicationView::GetForCurrentView();
			view->TryEnterFullScreenMode();
		}
	}
	else if (device == 2)
	{
		ApplicationView^ view = ApplicationView::GetForCurrentView();
		view->TryEnterFullScreenMode();
	}


}

