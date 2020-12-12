#include"DX11GraphicsController.h"
#include "DX11ObjectBase.h"

namespace ue
{
	void DX11ObjectBase::Init(uintptr_t state)
	{
		auto graphics = this->GetService<IGraphicsController,DX11GraphicsController>();

		_device = MakeService<ID3D11Device>(graphics->GetDevice());
		_deviceContext = MakeService<ID3D11DeviceContext>(graphics->GetDeviceContext());
	}
}

