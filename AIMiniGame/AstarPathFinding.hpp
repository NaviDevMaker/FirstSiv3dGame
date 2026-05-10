#pragma once
#include <Siv3D.hpp>

class AstarPathFinding
{
public:
	Array<Vec2> FindPath(const Vec2& start, const Vec2& goal,bool isDiagonal);
private:
	struct Node
	{
		//元々のやつであるらしい
		/*struct Point
		{
			int32 x;
			int32 y;
		};*/
		Point gridPos;
		double gCost;//ゴールからそのNodeまでのコスト
		double hCost;//そこからゴールまでのコスト

		//コストの総量
		double fCost() { return gCost + hCost; }

		//最後に逆算していくときに誰から来たのかのやつ
		Node* parent = nullptr;
	};

	Array<Point> GetNeighbors(const Point& point,bool isDiagonal) const;
	double Heuristic(const Point& a, const Point& b) const;
	Point ToGrid(const Vec2& pos) const;
	Vec2 ToWorld(const Point& grid) const;
	bool IsInsideGrid(const Point& grid) const;
};
