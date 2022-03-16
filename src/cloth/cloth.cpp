#include "cloth.h"

Cloth::Cloth() :
	paused(true),
	pointToLinkIdx(-1)
{ }

Cloth::~Cloth()
{
	for (auto point : points)
		delete point;
}

Point* Cloth::AddPoint(olc::vf2d pos)
{
	Point* point = new Point{
		false,
		pos,
		pos
	};
	points.push_back(point);
	return point;
}

void Cloth::RemovePoint(olc::vf2d pos)
{
	for (int i = points.size() - 1; i >= 0; i--)
		if ((pos - points[i]->pos).mag() <= FIBER_SIZE)
		{
			Point* point = points[i];

			// Delete links
			for (int i = links.size() - 1; i >= 0; i--)
			{
				Link link = links[i];
				if (link.pointA == point || link.pointB == point)
					links.erase(links.begin() + i);
			}

			// Delete point
			points.erase(points.begin() + i);
			delete point;
			break;
		}
}

void Cloth::RemovePoint(Point* point)
{
	RemovePoint(point->pos);
}

void Cloth::LinkPoint(Point* a, Point* b)
{
	links.push_back(Link{
		a,
		b,
		(b->pos - a->pos).mag()
		});
}

void Cloth::ToggleLockPoint(Point* point)
{
	point->prevPos = point->pos;
	point->locked = !point->locked;
}

void Cloth::ToggleLockPoint(olc::vf2d pos)
{
	for (auto& point : points)
		if ((pos - point->pos).mag() <= FIBER_SIZE)
		{
			ToggleLockPoint(point);
			return;
		}

}

void Cloth::HandleClick(int button, olc::vf2d pos)
{
	// Add/Link point
	if (button == 0)
	{
		// Link fibers
		bool isLink = false;
		for (int i = 0; i < points.size(); i++)
		{
			Point* point = points[i];
			if ((pos - point->pos).mag() > FIBER_SIZE)
				continue;
			isLink = true;

			if (i == pointToLinkIdx)
			{
				pointToLinkIdx = -1;
				break;
			}
			else if (pointToLinkIdx < 0)
			{
				pointToLinkIdx = i;
				break;
			}

			LinkPoint(point, points[pointToLinkIdx]);
			pointToLinkIdx = -1;
			break;
		}


		// Link handled
		if (isLink) return;

		// Wasn't link but we have selected a fiber, so deselect it
		if (!isLink && pointToLinkIdx >= 0)
		{
			pointToLinkIdx = -1;
			return;
		}

		// Nothing else can happen so add point
		AddPoint(pos);

	}
	// Lock point
	else if (button == 1)
		ToggleLockPoint(pos);
	// Remove point
	else if (button == 2)
		RemovePoint(pos);
}

void Cloth::TogglePause()
{
	paused = !paused;
}

void Cloth::Simulate(float deltaTime)
{
	if (paused) return;
	for (auto& p : points)
	{
		// Locked points aren't simulated
		if (p->locked)
			continue;

		// Apply motion and gravity
		olc::vf2d savePos = p->pos;									// Used to set previous later
		p->pos += p->pos - p->prevPos;								// We use prev position as a way to measure speed
		p->pos += olc::vf2d(0, 1) * 250 * deltaTime * deltaTime;	// first part is down unit vector, 250 is gravity, double delta time moment etc
		p->prevPos = savePos;										// Update prev position as the saved position at start
	}

	// Fiber constraints (links)
	for (int i = 0; i < CONSTRAINT_LIMIT; i++) {
		for (auto& l : links) {
			// Direction unit vector and center position
			olc::vf2d center = (l.pointA->pos + l.pointB->pos) / 2;
			olc::vf2d dir = (l.pointA->pos - l.pointB->pos).norm();

			// Update link origin
			if (!l.pointA->locked)
				l.pointA->pos = center + dir * l.length / 2;

			// Update link attached
			if (!l.pointB->locked)
				l.pointB->pos = center - dir * l.length / 2;
		}
	}
}

void Cloth::GenerateClothPoints()
{
	// This was made really fast just so I can prototype a cloth(esk) structure of points and links
	// Is it elegant? not really but it works and that's all that really matters

	const int w = 1280 * 0.75;
	const int h = 720 * 0.6;

	const int iw = 27;
	const int ih = 15;

	const float disX = (float)w / iw;
	const float disY = (float)h / ih;

	const float offsetX = ((float)1280 - w) / 2;
	const float offsetY = ((float)720 - h) / 2;

	for (int x = 0; x < iw; x++)
	{
		for (int y = 0; y < ih; y++)
		{
			Point* point = AddPoint(olc::vf2d(offsetX + (disX * x), offsetY + (disY * y)));

			// Lock every 4 points along the top
			if (y == 0 && ((x % 4) == 0 || x == (iw - 1)))
				point->locked = true;

			// Link points
			if (y > 0) LinkPoint(point, points[points.size() - 2]);
			if (x > 0) LinkPoint(point, points[((ih * (x - 1)) + y)]);
		}
	}
}