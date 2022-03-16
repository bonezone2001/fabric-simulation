#define OLC_PGE_APPLICATION
#include "cloth/cloth.h"

// Just a quick little project I programmed really fast one night
// Code was done really fast just to prototype the algorithm.

// Credit to OneLoneCoder for the PixelGameEngine. Comes in really handy for prototyping
// and just getting into CPP and just rendering stuff. No large boilerplate

class ClothToy : public olc::PixelGameEngine
{
public:
	Cloth cloth;

	ClothToy()
	{
		sAppName = "Cloth Toy";
	}

public:
	bool OnUserCreate() override
	{
		cloth.GenerateClothPoints();
		return true;
	}

	bool OnUserUpdate(float deltaTime) override
	{
		// Update
		if (GetKey(olc::SPACE).bPressed) cloth.TogglePause();
		if (GetMouse(0).bPressed) cloth.HandleClick(0, GetMousePos());
		if (GetMouse(1).bPressed) cloth.HandleClick(1, GetMousePos());
		if (GetMouse(2).bHeld) cloth.HandleClick(2, GetMousePos());
		cloth.Simulate(deltaTime);

		// Render
		std::vector<Point*> points = cloth.GetPoints();
		std::vector<Link>& links = cloth.GetLinks();

		// Links
		Clear(olc::BLACK);
		for (auto& link : links)
			DrawLine(link.pointA->pos, link.pointB->pos);

		// Points
		for (int i = 0; i < points.size(); i++)
		{
			Point* point = points[i];
			olc::Pixel col = olc::WHITE;
			if (point->locked)
				col = olc::MAGENTA;
			if (cloth.GetPointToLinkIdx() == i)
				col = olc::RED;
			FillCircle(point->pos, FIBER_SIZE, col);
		}

		return true;
	}
};


int main()
{
	ClothToy tool;
	if (tool.Construct(1280, 720, 1, 1))
		tool.Start();

	return 0;
}