#include "CppUnitTest.h"
#include"Helpers/MemoryLeakHelper.h"
#include"System/SystemController.h"
#include"MockObjects/MockService.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ue
{
	class ServiceProvider : public ue::ServiceConsumer
	{
	public:
		template<typename ServiceType>
		ServicePtr<ServiceType> GetService()
		{
			return ServiceConsumer::GetService<ServiceType>();
		}

		template<typename ServiceType, typename CastType>
		ServicePtr<CastType> GetService()
		{
			return ServiceConsumer::GetService<ServiceType, CastType>();
		}
	};


	TEST_CLASS(ServiceProviderUnitTests)
	{
	public:
		
		TEST_METHOD(DisposeAllServicesAfterUsed_Test)
		{
			MemoryLeakHelper::AssertMemoryLeak([] {
				SystemController controller;
				controller.GetServiceBuilder()->AddService<MockService>(new MockService());
			});
		}

		TEST_METHOD(ResolveService_Test)
		{
			ue::SystemController controller;

			auto mockService = new MockService();
			controller.GetServiceBuilder()->AddService<MockService>(mockService);
			controller.Init(INITIALIZE_UNITTESTS_STATE);

			ServiceProvider serviceProvider{};

			Assert::AreEqual(reinterpret_cast<size_t>(mockService), reinterpret_cast<size_t>(serviceProvider.GetService<MockService>().get()));
		}
	};
}
