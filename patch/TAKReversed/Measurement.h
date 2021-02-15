#pragma once



namespace Measurement
{
	// 1 Unit = 16 Tileset Pixels
	struct Unit
	{
		uint16_t value;
	};

	struct RelativeToTileset
	{
		uint16_t something;
		uint8_t relativePosition;
		uint8_t tileset;
	};
}

struct PositionInRelativeTilesetValues
{
	Measurement::RelativeToTileset x;
	Measurement::RelativeToTileset z;
};

struct PositionInUnits
{
	Measurement::Unit x;
	Measurement::Unit z;
};

// 00 = 00 =>  relativePosition =   0, tileset = 0
// 02 = 02 =>  relativePosition =  32, tileset = 0
// 0A = 10 =>  relativePosition = 160, tileset = 0
// 0F = 15 =>  relativePosition = 240, tileset = 0
// 10 = 16 =>  relativePosition =   0, tileset = 1
// 12 = 18 =>  relativePosition =  32, tileset = 1
// 3A = 18 =>  relativePosition = 160, tileset = 3
// 14                              64,           1              
namespace Convert
{
	extern "C" __declspec(dllexport) Measurement::Unit __stdcall RelativeToTileset_to_Unit(Measurement::RelativeToTileset relativeToTileset)
	{
		return Measurement::Unit{ static_cast<uint16_t>(relativeToTileset.relativePosition / 16 + ((relativeToTileset.tileset * 256) / 16)) };
	}

	extern "C" __declspec(dllexport) Measurement::RelativeToTileset Units_to_RelativeToTileset(Measurement::Unit unit)
	{
		uint32_t result = unit.value * 8;
		return Measurement::RelativeToTileset{ 0, static_cast<uint8_t>(result % 256), static_cast<uint8_t>(result / 256) };
	}

	extern "C" __declspec(dllexport) PositionInUnits PositionInRelativeTilesetValues_to_PositionInUnits(PositionInRelativeTilesetValues p)
	{
		Measurement::Unit x = RelativeToTileset_to_Unit(p.x);
		Measurement::Unit z = RelativeToTileset_to_Unit(p.z);

		return PositionInUnits{ x, z };
	}
}



