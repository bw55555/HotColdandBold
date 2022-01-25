#pragma once
#include "Text.h"

enum class ButtonState { Inactive, Active, Selected };

inline void doNothingFunc() {};

class Button : public Text {
public:
	typedef void (*UseFunc)();

	UseFunc f;

	

	//use menu's createButton function instead
	Button(std::string _text, UseFunc useFunc, glm::vec3 scaling = glm::vec3(1.0f), glm::vec3 offset = glm::vec3(0.0f), float rotation = 0.0f, TextAlignH _hAlign = HTA::Left, TextAlignV _vAlign = VTA::Bottom);
	ButtonState state = ButtonState::Active;
	typedef std::unordered_map<ButtonState, glm::vec4> ColorMap;
	ColorMap colormap{ {ButtonState::Inactive, glm::vec4(0.7f, 0.7f, 0.7f, 1.0f)}, 
		{ButtonState::Active, glm::vec4(0.6f, 1.0f, 1.0f, 1.0f)},
		{ButtonState::Selected, glm::vec4(1.0f, 0.0f, 0.0f, 1.0f)} };
	void setColorMap(glm::vec4 inactiveColor, glm::vec4 activeColor, glm::vec4 selectedColor) { colormap = ColorMap{ {ButtonState::Selected, selectedColor}, {ButtonState::Active, activeColor}, {ButtonState::Inactive, inactiveColor} }; }
	void setColorMap(ColorMap c) { colormap = c; }
	void setActiveColor(glm::vec4 _color) { colormap[ButtonState::Active] = _color; color = colormap[state]; }
	void setSelectedColor(glm::vec4 _color) { colormap[ButtonState::Selected] = _color; color = colormap[state]; }
	void setInactiveColor(glm::vec4 _color) { colormap[ButtonState::Inactive] = _color; color = colormap[state]; }
	bool isSelected() {
		return state == ButtonState::Selected;
	}
	bool select() { 
		if (state == ButtonState::Inactive) { return false; }
		state = ButtonState::Selected; 
		color = colormap[state];
		return true;
	};
	void deselect() { state = ButtonState::Active; color = colormap[state];};
	void deactivate() { state = ButtonState::Inactive; color = colormap[state];};
	void activate() { state = ButtonState::Active; color = colormap[state];};
	void use() { f(); };
	~Button() {};
};