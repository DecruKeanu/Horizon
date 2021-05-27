#pragma once
#include "Component.h"
#include "Structs.h"

namespace dae
{
	class Font;
	class Texture2D;
	class TransformComponent;
	class TextComponent final : public Component
	{
	public:
		TextComponent(GameObject* parent, const std::string& text, const std::shared_ptr<Font>& font);
		TextComponent(GameObject* parent, const std::string& text, const std::shared_ptr<Font>& font,const Color& textColor);
		void Initialize() override;
		void Update() override;
		void Render() const override;
		void SetText(const std::string& text);
		const std::string& GetText() const;
	private:
		bool m_NeedsUpdate;
		std::string m_Text;
		const Color m_textColor;
		std::shared_ptr<Font> m_pFont;
		std::shared_ptr<Texture2D> m_pTexture = nullptr;
		TransformComponent* m_pTransformComponent = nullptr;
	};
}

