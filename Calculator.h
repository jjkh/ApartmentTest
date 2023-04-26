#pragma once

#include "ICalculator_h.h"

// simple COM class based on this tutorial: https://www.codeguru.com/soap/step-by-step-com-tutorial
class CCalculator : public ICalculator
{
public:
	// IUnknown interface
	STDMETHODIMP QueryInterface(REFIID riid, void** ppObj);
	ULONG STDMETHODCALLTYPE AddRef();
	ULONG STDMETHODCALLTYPE Release();
	
	// ICalculator interface
	STDMETHODIMP Add(int a, int b, int* result);
	STDMETHODIMP Sub(int a, int b, int* result);

private:
	long m_refCount;
};
