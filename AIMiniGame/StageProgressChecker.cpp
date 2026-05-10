#include "StageProgressChecker.hpp"

bool StageProgressChecker::IsClearedStage(int32 score)
{
	return score >= targetScore;
}
