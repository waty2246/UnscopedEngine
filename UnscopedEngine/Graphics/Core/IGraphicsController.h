#pragma once

#include"Common.h"
#include"Core/IInitializable.h"

namespace ue
{
	class VideoCardInfo
	{
	public:
		inline VideoCardInfo(const std::wstring& videoCardName,size_t dedicatedMeory):_videoCardName(videoCardName), _dedicatedMeory(dedicatedMeory)
		{
		}

		inline std::wstring GetVideoCardName()const
		{
			return _videoCardName;
		}

		/// <summary>
		/// 
		/// </summary>
		/// <returns>size in MB</returns>
		inline size_t GetDedicatedMemory()const
		{
			return _dedicatedMeory;
		}
	private:
		std::wstring _videoCardName;
		size_t _dedicatedMeory;
	};

	class IGraphicsController : public IInitializable
	{
	public:
		virtual void TurnOnDepth()=0;
		virtual void TurnOffDepth() = 0;
		virtual void TurnOnWireframe()=0;
		virtual void TurnOffWireframe() = 0;
		virtual void BeginRender()=0;
		virtual void EndRender()=0;
		virtual const VideoCardInfo& GetVideoCardInfo()const=0;
	};
}