#include "UIScreen.h"
#include "Texture.h"
#include "Font.h"
#include "Assets.h"
#include "Game.h"
#include "Button.h"

UIScreen::UIScreen() :
	font(Assets::getFont("Carlito")),
	title(nullptr),
	titlePosition(0.0f, 300.0f),
	state(UIState::Active),
	buttonOn(Assets::getTexture("ButtonYellow")),
	buttonOff(Assets::getTexture("ButtonBlue"))
{
	Game::instance().pushUI(this);
}

UIScreen::~UIScreen()
{
	if (title)
	{
		title->unload();
		delete title;
	}
}

void UIScreen::setTitle(const string& titleP, const Vector3& color,
int pointSize)
{
	if (title)
	{
		title->unload();
		delete title;
		title = nullptr;
	}
	title = font.renderText(titleP, color, pointSize);
}

void UIScreen::update(float dt)
{}

void UIScreen::draw(Shader& shader)
{
	if (title)
	{
		drawTexture(shader, title, titlePosition);
	}
	for (const auto b : buttons)
	{
		// Draw background of button
		const Texture* tex = b->getHighlighted() ? &buttonOn : &buttonOff;
		drawTexture(shader, tex, b->getPosition());
		// Draw text of button
		drawTexture(shader, b->getNameTex(), b->getPosition());
	}
}

void UIScreen::processInput(const InputState& inputState)
{
	if (!buttons.empty())
	{
		for (const auto b : buttons)
		{
			if (b->containsPoint(inputState.mouse.getPosition()))
			{
				b->setHighlighted(true);
			}
			else
			{
				b->setHighlighted(false);
			}
			if (b->getHighlighted() && inputState.mouse.getButtonState(1) ==
			ButtonState::Released)
			{
				b->onClick();
			}
		}
	}
}

void UIScreen::close()
{
	state = UIState::Closing;
}

void UIScreen::drawTexture(Shader& shader, const Texture* texture, const Vector2& offset, float scale)
{
	const Matrix4 scaleMat = Matrix4::createScale(static_cast<float>(texture->getWidth()) * scale, static_cast<float>(texture->getHeight()) * scale, 1.0f);
	const Matrix4 transMat = Matrix4::createTranslation(Vector3(offset.x, offset.y, 0.0f));
	const Matrix4 world = scaleMat * transMat;
	shader.setMatrix4("uWorldTransform", world);
	texture->setActive();
	// Draw quad
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}

void UIScreen::addButton(const string& name, std::function<void()>onClick)
{
	const Vector2 dims(static_cast<float>(buttonOn.getWidth()), static_cast<float>(buttonOn.getHeight()));
	Button* b = new Button(name, font, onClick, nextButtonPosition, dims);
	buttons.emplace_back(b);
	
	// Update position of next button
	// Move down by height of button plus padding
	nextButtonPosition.y -= buttonOff.getHeight() + 20.0f;
}
