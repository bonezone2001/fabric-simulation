#pragma once
#include "../engine.h"
#include <iostream>
#include <vector>

#define CONSTRAINT_LIMIT 20
#define FIBER_SIZE 5

// A 2d point that represents a part of the overall fabric
struct Point
{
	bool locked;		// Is the point locked and unable to move?
	olc::vf2d pos;		// Position of the point currently
	olc::vf2d prevPos;	// Position of the point last update (used to calculate where we go next update)
};

// Link between cloth pieces (physics constraints)
struct Link
{
	Point* pointA;		// Link origin
	Point* pointB;		// Link target
	float length;		// Length of the link -- magnitude of (b - a)
};

class Cloth
{
private:
	bool paused;					// Simulation is paused?
	int pointToLinkIdx;				// Point we have selected and want to link to another
	std::vector<Point*> points;		// List of all points in simulation
	std::vector<Link> links;		// Links between each point and their lengths

public:
	Cloth();
	virtual ~Cloth();

private:
	// Add point to list
	Point* AddPoint(olc::vf2d pos);

	// Remove point from list (and all links referencing point)
	void RemovePoint(olc::vf2d pos);
	void RemovePoint(Point* point);

	// Links two different points together to form a constraint
	void LinkPoint(Point* a, Point* b);

	// Togle if a point is locked or not
	void ToggleLockPoint(Point* point);
	void ToggleLockPoint(olc::vf2d pos);

public:
	void TogglePause();								// Pause/unpause simulation (sets paused)
	void HandleClick(int button, olc::vf2d pos);	// Handle left/middle/right click -> left add point, middle remove point, right lock point
	void Simulate(float deltaTime);					// Update all internal points/links (constraints)
	void GenerateClothPoints();						// Generate cloth(esk) structure of points and links

public:
	inline int GetPointToLinkIdx() const { return pointToLinkIdx; }
	inline std::vector<Point*> GetPoints() { return points; }
	inline std::vector<Link>& GetLinks() { return links; }
};