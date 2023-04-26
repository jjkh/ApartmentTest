#pragma once

#include <objbase.h>

class CCalculatorFactory : public IClassFactory 
{
public:
	// IUnknown interface
	STDMETHODIMP QueryInterface(REFIID riid, void** ppObj);
	ULONG STDMETHODCALLTYPE AddRef();
	ULONG STDMETHODCALLTYPE Release();

	// IClassFactory interface
	STDMETHODIMP CreateInstance(IUnknown* pUnknownOuter, const IID& iid, void** ppv);
	STDMETHODIMP LockServer(BOOL bLock);
private:
	long m_refCount;
};