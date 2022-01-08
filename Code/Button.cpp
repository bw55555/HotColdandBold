#include "Button.h"

Button::Button(std::string _text, UseFunc useFunc, glm::vec3 scaling, glm::vec3 offset, float rotation, TextAlignH _hAlign, TextAlignV _vAlign) : Text(_text, glm::vec4(0.0f), scaling, offset, rotation, _hAlign, _vAlign) {
	f = useFunc;
	color = colormap[state];
}

//there's nothing else here... yet