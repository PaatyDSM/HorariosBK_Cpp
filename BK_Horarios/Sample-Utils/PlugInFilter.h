#pragma once

#include "pch.h"

using namespace Windows::Foundation;
using namespace Windows::Web::Http;
using namespace Windows::Web::Http::Filters;

namespace BK_HORARIOS
{
	public ref class PlugInFilter sealed : public IHttpFilter
	{
	public:
		PlugInFilter(IHttpFilter^ innerFilter);

	virtual ~PlugInFilter(void);

	virtual IAsyncOperationWithProgress<
		HttpResponseMessage^,
		HttpProgress>^ SendRequestAsync(HttpRequestMessage^ request);

	private:
		IHttpFilter^ innerFilter;
	};
}
