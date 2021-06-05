#pragma once

namespace Horizon
{
	enum class PossibleEvent
	{
		PlayerDied,
		GameOver,
		ColorChange,
		RemainingDisc,
		CatchingSamOrSlick,
		DefeatCoily,
		PreviousLevelData
	};

	struct IEventData abstract
	{
		virtual ~IEventData() = default;
	};

	template <typename T>
	struct EventData final : public IEventData
	{
		EventData(const T& data) { templatedData = data; };
		T templatedData;
	};

	struct Event final
	{
		template <typename T>
		Event(PossibleEvent possibleEvent, T eventData) { event = possibleEvent; pData = new EventData<T>(eventData); }
		Event(PossibleEvent possibleEvent) { event = possibleEvent; pData = nullptr; }
		~Event() { delete pData; pData = nullptr; }
		PossibleEvent event;
		IEventData* pData = nullptr;

		//Credit to Rhidian De Wit
		template <typename T>
		T GetData() const
		{
			return static_cast<EventData <T>*>(pData)->templatedData;
		}
	};
}



