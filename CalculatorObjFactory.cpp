#include "CalculatorObjFactory.h"
#include "Calculator.h"

// IUnknown methods
STDMETHODIMP CCalculatorFactory::QueryInterface(REFIID riid, void** ppObj)
{
	// supported interfaces
	if (riid == IID_IUnknown || riid == IID_IClassFactory) {
		*ppObj = static_cast<IClassFactory*>(this);
		AddRef();
		return S_OK;
	}

	// all other interfaces are unsupported
	*ppObj = NULL;
	return E_NOINTERFACE;
}

ULONG STDMETHODCALLTYPE CCalculatorFactory::AddRef()
{
	return InterlockedIncrement(&m_refCount);
}

ULONG STDMETHODCALLTYPE CCalculatorFactory::Release()
{
	long refCount = InterlockedDecrement(&m_refCount);
	if (refCount == 0)
		delete this;
	return refCount;
}

// IClassFactory methods
STDMETHODIMP CCalculatorFactory::CreateInstance(IUnknown* pUnknownOuter, const IID& iid, void** ppv)
{
	if (pUnknownOuter != NULL)
	{
		// cannot aggregate
		return CLASS_E_NOAGGREGATION;
	}

	// create an instance of the component
	CCalculator* pCalculator = new CCalculator;
	if (pCalculator == NULL)
	{
		return E_OUTOFMEMORY;
	}

	// get the requested interface
	return pCalculator->QueryInterface(iid, ppv);
}

STDMETHODIMP CCalculatorFactory::LockServer(BOOL bLock)
{
	return E_NOTIMPL;
}