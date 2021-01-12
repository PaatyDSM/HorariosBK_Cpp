#pragma once

#include "pch.h"

using namespace concurrency;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::Web::Http;

namespace BK_HORARIOS
{
	class Helpers
	{
	
	public:
		static task<HttpResponseMessage^> DisplayTextResultAsync(
			HttpResponseMessage^ response,
			TextBox^ output);

		static HttpClient^ CreateHttpClient();
	};
}
