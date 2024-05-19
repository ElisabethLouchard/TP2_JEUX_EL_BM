#pragma once

struct TitleSceneResult
{
	int dummy;
};

struct GameSceneResult
{
	int score;
};


union SceneResult
{
	TitleSceneResult titleSceneResult;
	GameSceneResult gameSceneResult;
};