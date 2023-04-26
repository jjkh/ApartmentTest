#include "Calculator.h"

#include "Log.h"

// IUnknown methods
STDMETHODIMP CCalculator::QueryInterface(REFIID riid, void** ppObj)
{
	// supported interfaces
	if (riid == IID_IUnknown || riid == IID_ICalculator) {
		*ppObj = static_cast<ICalculator*>(this);
		AddRef();
		return S_OK;
	}

	// all other interfaces are unsupported
	*ppObj = NULL;
	return E_NOINTERFACE;
}

ULONG STDMETHODCALLTYPE CCalculator::AddRef()
{
	return InterlockedIncrement(&m_refCount);
}

ULONG STDMETHODCALLTYPE CCalculator::Release()
{
	long refCount = InterlockedDecrement(&m_refCount);
	if (refCount == 0)
		delete this;
	return refCount;
}

// ICalculator interfaces
STDMETHODIMP CCalculator::Add(int a, int b, int* result)
{
	if (result == NULL)
		return E_FAIL;

	LogApartmentType("CCalculator::Add");
	*result = a + b;
	return S_OK;
}

STDMETHODIMP CCalculator::Sub(int a, int b, int* result)
{
	if (result == NULL)
		return E_FAIL;

	*result = a - b;
	return S_OK;
}