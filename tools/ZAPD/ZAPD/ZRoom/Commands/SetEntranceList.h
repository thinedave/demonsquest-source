#pragma once

#include "ZRoom/ZRoomCommand.h"

class Spawn
{
public:
	uint8_t startPositionIndex;
	uint8_t roomToLoad;

	Spawn(const std::vector<uint8_t>& rawData, uint32_t rawDataIndex);

	std::string GetBodySourceCode() const;
};

class SetEntranceList : public ZRoomCommand
{
public:
	std::vector<Spawn> entrances;

	SetEntranceList(ZFile* nParent);

	void DeclareReferences(const std::string& prefix) override;
	void ParseRawDataLate() override;
	void DeclareReferencesLate(const std::string& prefix) override;

	std::string GetBodySourceCode() const override;

	RoomCommand GetRoomCommand() const override;
	std::string GetCommandCName() const override;
};
