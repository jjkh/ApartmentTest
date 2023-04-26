#include <stdio.h>
#include <Windows.h>

#include "Log.h"
#include "ICalculator_h.h"
#include "CalculatorObjFactory.h"

// COM stuff
extern const IID IID_ICalculator;
// {E447614D-E5C9-4977-B5DA-1E1E445C34F0}
const CLSID CLSID_Calculator = { 0xe447614d, 0xe5c9, 0x4977, { 0xb5, 0xda, 0x1e, 0x1e, 0x44, 0x5c, 0x34, 0xf0 } };

int main()
{
    LogApartmentType("before coinit");

    // initialise COM (STA)
    auto hr = CoInitialize(NULL);
    if (hr != S_OK) throw hr;
    LogApartmentType("after coinit");

    // create calculator factory
    CCalculatorFactory* pCalculatorFactory = new CCalculatorFactory;

    // register COM object (with object factory)
    DWORD factoryRegistration;
    hr = CoRegisterClassObject(CLSID_Calculator, pCalculatorFactory, CLSCTX_SERVER, REGCLS_MULTIPLEUSE, &factoryRegistration);
    if (hr != S_OK) throw hr;

    // create instance of COM object
    ICalculator* pICalculator;
    hr = CoCreateInstance(CLSID_Calculator, NULL, CLSCTX_SERVER, IID_ICalculator, reinterpret_cast<void**>(&pICalculator));
    if (hr != S_OK) throw hr;

    // use the COM object
    int result;
    hr = pICalculator->Add(1, 2, &result);
    if (hr != S_OK) throw hr;
    Log("Calculated: 1 + 2 = %d\n", result);
    
    // uninitialise COM
    CoUninitialize();
    LogApartmentType("after couninit");
}