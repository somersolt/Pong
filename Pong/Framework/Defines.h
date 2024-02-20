#pragma once

enum class Origins
{
	// T M B
	// L C R
	TL, TC, TR, ML, MC, MR, BL, BC, BR, CUSTOM,
};

enum class Sides
{
	NONE = -1, LEFT, RIGHT, COUNT
};

enum class SceneIds
{
	NONE = -1, SCENEDEV1, SCENEDEV2, SCENEGAME, COUNT // 0 1 2 이니까 카운트는 씬의 개수
};