#pragma once
#include "CppUnitTest.h"
#include<crtdbg.h>
#include<string>
#include<functional>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;


class MemoryLeakHelper
{
public:
	static void AssertMemoryLeak(std::function<void(void)> body)
	{
		_CrtMemState before;
		_CrtMemCheckpoint(&before);

		//our block code to detect memory leak
		body();

		_CrtMemState after;
		_CrtMemCheckpoint(&after);

		_CrtMemState _;
		int difference = _CrtMemDifference(&_, &before, &after);
		auto message = std::wstring(L"Total memory leak: ");
		message.append(std::to_wstring(_.lTotalCount))
			.append(L" bytes");

		Assert::AreEqual(0, difference, message.c_str());
	}
};

