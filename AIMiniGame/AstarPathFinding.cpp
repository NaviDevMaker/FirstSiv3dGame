#include "AstarPathFinding.hpp"


//std::unique_ptrの場合は自動で解放してくれる、Node* のようにすると自分で delete n のようにしないといけない





//startからgoalまでの最短距離をVec2の配列で返す
Array<Vec2> AstarPathFinding::FindPath(const Vec2& start, const Vec2& goal)
{
	//スタートとゴールの要素をintにキャストしてPointにする
	//A*としてグリッドっぽく扱いたいから
	Point startP = ToGrid(start);// { static_cast<int32>(start.x), static_cast<int32>(start.y) };
	Point goalP = ToGrid(goal); //{ static_cast<int32>(goal.x), static_cast<int32>(goal.y) };

	//生成した Node を全部ここで管理する
	Array<std::unique_ptr<Node>> allNodes;
	//Node* だけだと寿命管理が危ない
    //unique_ptr で「この配列がNodeの実体を持つ」ようにしてる
	

	Array<Node*> openSet;	//OpenされたNodeのアドレスを格納する
	Array<Node*> closedSet; //Closed（調査終了）のNodeのアドレスを格納する

	//Nodeを生成する、make_uniqueはunique_ptrを作る関数
	auto startNode = std::make_unique<Node>();	//始点をOpenに追加
	startNode->gridPos = startP;
	startNode->gCost = 0.0;
	startNode->hCost = Heuristic(startP, goalP);
	startNode->parent = nullptr;
	//.get()はunique_ptrの中の生ポインタを取り出す
	openSet << startNode.get();
	allNodes << std::move(startNode);

	//Openされたノードがなくなるまで（すべてのNodeを調査するまで）、候補が尽きる = それまでに経路探索が失敗したことを意味する
	while (!openSet.isEmpty())
	{
		//スタートとなるNode
		Node* current = openSet[0];
		for (auto* node : openSet)
		{
			if (node->fCost() < current->fCost()) current = node;
		}
		//上記for文が終わった時、最もfCostが低いものがcurrentに入っている状態
		//currentがgoalだった場合、goal地点からparentをたどる、parentのparentをたどる...を繰り返し、traceの親がnullptr = startになるまで続ける
		if (current->gridPos == goalP)
		{
			Array<Vec2> path;
			Node* trace = current;
			while (trace->parent != nullptr)
			{
				path << ToWorld(trace -> gridPos);			//現在のNodeのgridPosをpathに追加

				trace = trace->parent;
			}
			//goalの地点が先頭になっているので順番を逆にする
			path.reverse();
			return path;
		}
		
		 
		 //見終わったNode = 現在見ているNodeはopenから削除
		 //closed = 調査済みの配列に格納
		openSet.remove(current);
		closedSet << current;
		for (const auto& neighborPos : GetNeighbors(current->gridPos))
		{
			//既に調査済み = closedのなかのNode nのgridPos　がneighborPos(currentを起点に隣接するNode)だった場合そこはスキップ
			if (closedSet.contains_if([&](const Node* n) {return n->gridPos == neighborPos; }))
			{
				continue;
			}
			Node* existing = nullptr;
			//そのNodeに行った場合の仮定のgCost
			//隣接なのでcurrentのgCost + 1
			double tentativeG = current->gCost + 1;
			//隣接するNodeが既にopenに入っているかの確認
			//入っている場合は、existingにそのNodeのポインターを入れる
			for (auto* node : openSet)
			{
				if (node == nullptr) continue;
				if (node->gridPos == neighborPos)
				{
					existing = node;
					break;
				}
			}

			if (existing == nullptr)
			{
				auto newNode = std::make_unique<Node>();
				newNode->gridPos = neighborPos;
				newNode->gCost = tentativeG;
				newNode->hCost = Heuristic(neighborPos, goalP);
				newNode->parent = current;

				openSet << newNode.get();
				allNodes << std::move(newNode);
			}
			else if (tentativeG < existing->gCost)
			{
				existing->gCost = tentativeG;
				existing->parent = current;
			}
		}

			


			
			


			//OpenSetにない場合新しく追加する
			//
				//位置を追加
				//gCostの追加
				//hCostの追加
				//currentから来たNodeなので親にcurrent

				//候補の追加
				//すべてのNodeに追加
			//既にあるNodeでもgCostが低いものを採用、hCostは変わらないのでgCostだけ見て判別

				//親を変更
	}
		
	return {};

}

Array<Point> AstarPathFinding::GetNeighbors(const Point& point) const
{
	return
	{
	   {point.x + 1,point.y},
	  {point.x - 1,point.y},
		{point.x,point.y + 1},
		{point.x,point.y - 1}
	};
}

//その地点からゴールまでの推定コスト(hCost)
double  AstarPathFinding::Heuristic(const Point& a, const Point& b) const
{
	return Abs(a.x - b.x) + Abs(a.y - b.y);
}

Point AstarPathFinding::ToGrid(const Vec2& pos) const
{
	//切り捨て 1マス = 32pxだからグリッドで合わせるために32で割る
	//[0,32,64,96]これを32で割ることでマス目がわかる [0,1,2,3]
	return Point{ static_cast<int32>(Floor(pos.x / 32)),static_cast<int32>(Floor(pos.y / 32)) };
}

Vec2 AstarPathFinding::ToWorld(const Point& grid) const
{
	//中心座標に合わせる
	return Vec2{ grid.x * 32 + 16,grid.y * 32 + 16 };
}
