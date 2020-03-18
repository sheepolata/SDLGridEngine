#pragma once
class Entity {
public:
	Entity() {};
	~Entity() {};

	void setPosition(float x, float y) { this->fPosition[0] = x; this->fPosition[1] = y; }
	float getXPos() { return this->fPosition[0]; }
	float getYPos() { return this->fPosition[1]; }

	void update(float fElapsedTime) {};

private:
	float fPosition[2] = { 0.0f, 0.0f };
};

