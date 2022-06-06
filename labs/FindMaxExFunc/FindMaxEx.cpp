#include "FindMaxEx.h"

bool CompairAthletes(const Athlete& a1, const Athlete& a2)
{
	return (a1 < a2);
}

bool CompareTall(const Athlete& a1, const Athlete& a2)
{
	return (a1.tall < a2.tall);
}

bool CompareWeight(const Athlete& a1, const Athlete& a2)
{
	return (a1.weight < a2.weight);
}