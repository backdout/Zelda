#include "ButtonFunc.h"

HRESULT ButtonFunc::Init()
{
	tileframeX = 0;
	tileframeY = 0;
	sampletileframeX = 0;
	sampletileframeY = 0;
	isFieldSelect = true;
	isCastleSelect = false;
	isDungeonSelect = false;
	isTerraninSelect = false;
	

	return S_OK;
}

void ButtonFunc::SetMapBt()
{
}

void ButtonFunc::MapLeft()
{
	
		if (tileframeX <= 0) tileframeX = 0;
		else tileframeX--;

}

void ButtonFunc::MapRight()
{
	if (isFieldSelect)
	{
		if (tileframeY < 120)
		{
			if (tileframeX >= 49) tileframeX = 49;
			else tileframeX++;
		}
		else
		{
			if (tileframeX >= 141) tileframeX = 141;
			else tileframeX++;
		}
	}
	if (isCastleSelect)
	{
		if (tileframeX >= 25) tileframeX = 25;
		else tileframeX++;
	}
	if (isDungeonSelect)
	{
		if (tileframeX >= 8) tileframeX = 8;
		else tileframeX++;
	}

}

void ButtonFunc::MapUp()
{
	
		if (tileframeY <= 0) tileframeY = 0;
		else tileframeY--;
	
}

void ButtonFunc::MapDown()
{
	if (isFieldSelect)
	{
		if (tileframeY >= 170) tileframeY = 170;
		else tileframeY++;
	}
	if (isCastleSelect|| isDungeonSelect)
	{
		if (tileframeY >= 1) tileframeY = 1;
		else tileframeY++;
	}
	

}

void ButtonFunc::SampleMapLeft()
{
	
	if (sampletileframeX <= 0) sampletileframeX = 0;
	else sampletileframeX--;

}

void ButtonFunc::SampleMapRight()
{
	if (isFieldSelect)
	{
		if (sampletileframeY < 120)
		{
			if (sampletileframeX >= 49) sampletileframeX = 49;
			else sampletileframeX++;
		}
		else
		{
			if (sampletileframeX >= 141) sampletileframeX = 141;
			else sampletileframeX++;
		}
	}
	if (isCastleSelect)
	{
		if (sampletileframeX >= 25) sampletileframeX = 25;
		else sampletileframeX++;
	}
	if (isDungeonSelect)
	{
		if (sampletileframeX >= 8) sampletileframeX = 8;
		else sampletileframeX++;
	}
}

void ButtonFunc::SampleMapUp()
{
	
		if (sampletileframeY <= 0) sampletileframeY = 0;
		else sampletileframeY--;

}

void ButtonFunc::SampleMapDown()
{
	if (isFieldSelect)
	{
		if (sampletileframeY >= 170) sampletileframeY = 170;
		else sampletileframeY++;
	}
	if (isCastleSelect|| isDungeonSelect)
	{
		if (sampletileframeY >= 1) sampletileframeY = 1;
		else sampletileframeY++;
	}


}

void ButtonFunc::FieldBt()
{/*
	if(isFieldSelct) 	isFieldSelct =false;
	else*/ isFieldSelect = true;
	isCastleSelect = false;
	isDungeonSelect = false;


}

void ButtonFunc::CastleBt()
{
	/*if (isCastleSelct) 	isCastleSelct = false;
	else 
	{*/
		isCastleSelect = true;
		isFieldSelect = false;
		isDungeonSelect = false;
	//}
}

void ButtonFunc::DungeonBt()
{
	/*if (isDungeonSelct) 	isDungeonSelct = false;
	else*/ isDungeonSelect = true;
	isCastleSelect = false;
	isFieldSelect = false;

}

void ButtonFunc::TerrainBt()
{
	if(isTerraninSelect) isTerraninSelect = false;
	else isTerraninSelect = true;
}

void ButtonFunc::NoneBt()
{
	isNoneSelect = true;
	isBlockSelect = false;
	isWaterSelect = false;
	isCliffSelect = false;
	isObjSelect = false;

}

void ButtonFunc::BlockBt()
{
	isNoneSelect = false;
	isBlockSelect = true;
	isWaterSelect = false;
	isCliffSelect = false;
	isObjSelect = false;
}

void ButtonFunc::WaterBt()
{
	isNoneSelect = false;
	isBlockSelect = false;
	isWaterSelect = true;
	isCliffSelect = false;
	isObjSelect = false;
}

void ButtonFunc::CliffBt()
{
	isNoneSelect = false;
	isBlockSelect = false;
	isWaterSelect = false;
	isCliffSelect = true;
	isObjSelect = false;
}

void ButtonFunc::ObjBt()
{
	isNoneSelect = false;
	isBlockSelect = false;
	isWaterSelect = false;
	isCliffSelect = false;
	isObjSelect = true;
}
