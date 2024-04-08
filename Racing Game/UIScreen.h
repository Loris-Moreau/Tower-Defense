#pragma once

#include <string>
#include <functional>
#include <vector>
#include "Vector2.h"
#include "Color.h"
#include "Font.h"

using std::string;
using std::vector;

enum class UIState
{
	Active, Closing
};

class UIScreen
{
public:
	UIScreen();
	virtual ~UIScreen();
	
	UIState getState() const { return state; }
	void setTitle(const string& titleP, const Vector3& color = Color::white, int pointSize = 40);

	virtual void update(float deltaTime);
	virtual void draw(class Shader& shader);
	virtual void processInput(const class InputState& inputState);
	void close();
	void addButton(const string& name, std::function<void()> onClick);
	
protected:
	void drawTexture(Shader& shader, Texture* texture, const Vector2& offset = Vector2::zero, float scale = 1.0f);
	class Font& font;
	Texture* title;
	Vector2 titlePosition;
	UIState state;

	vector<class Button*> buttons;
	Texture& buttonOn;
	Texture& buttonOff;
	Vector2 nextButtonPosition;

	Texture* background;
	Vector2 backgroundPosition;
};
