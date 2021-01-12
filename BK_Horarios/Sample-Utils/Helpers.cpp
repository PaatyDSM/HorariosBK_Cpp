#include "pch.h"

#include "Sample-Utils\Helpers.h"
#include <MainPage.xaml.h>

#include <Sample-Utils\PlugInFilter.h>

using namespace BK_HORARIOS;

using namespace concurrency;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::Web::Http;
using namespace Windows::Web::Http::Filters;
using namespace Windows::Web::Http::Headers;

task<HttpResponseMessage^> Helpers::DisplayTextResultAsync(
    HttpResponseMessage^ response,
    TextBox^ output)
{
    // Read content as string. We need to use use_current() with the continuations since the tasks are completed on
    // background threads and we need to run on the UI thread to update the UI.
    task<String^> readAsStringTask(response->Content->ReadAsStringAsync());

    return readAsStringTask.then([=](String^ responseBodyAsText)
	{
        // Convert all instances of <br> to newline.
        std::wstring ws = responseBodyAsText->Data();

        output->Text += ref new String(ws.c_str());

        return response;
    },
		task_continuation_context::use_current());
}

HttpClient^ Helpers::CreateHttpClient()
{
    // HttpClient functionality can be extended by plugging multiple filters together and providing
    // HttpClient with the configured filter pipeline.
    IHttpFilter^ filter = ref new HttpBaseProtocolFilter();
    filter = ref new PlugInFilter(filter); // Adds a custom header to every request and response message.
    HttpClient^ httpClient = ref new HttpClient(filter);

    // Sets a "User-Agent" request header as a default header on the HttpClient instance.
	httpClient->DefaultRequestHeaders->UserAgent->Append(ref new HttpProductInfoHeaderValue("Mozilla/5.0; PaatyDSM Apps"));

    return httpClient;
}
