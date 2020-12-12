#pragma once

#include"Common.h"
#include"IDisposable.h"

namespace ue
{
    template <class ServiceType>
    struct EmptyDelete {
        constexpr EmptyDelete() noexcept = default;

        void operator()(ServiceType* _Ptr) const noexcept
        {
        }
    };

    template<class ServiceType>
    using ServicePtr = std::unique_ptr<ServiceType, EmptyDelete<ServiceType>>;

    template<class ServiceType>
    ServicePtr<ServiceType> MakeService(ServiceType* ptr)
    {
        return ServicePtr<ServiceType>(ptr);
    }

	class ServiceConsumer
	{
	protected:
        template<typename ServiceType>
        ServicePtr<ServiceType> GetService()
        {
            return ServicePtr<ServiceType>(dynamic_cast<ServiceType*>(this->GetService(typeid(ServiceType).name())));
        }

        template<typename ServiceType, typename CastType>
        ServicePtr<CastType> GetService()
        {
            return ServicePtr<CastType>(dynamic_cast<CastType*>(this->GetService(typeid(ServiceType).name())));
        }
    private:
        IDisposable* GetService(const std::string& serviceName);
	};
}