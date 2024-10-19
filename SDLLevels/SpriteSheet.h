#ifndef SPRITESHEET_H
#define SPRITESHEET_H

#include "Texture.h"
#include "SpriteAnim.h"
#include "BasicStructs.h"

enum AnimationNames
{
	EN_AN_IDLE = 0,
	EN_AN_RUN,
	EN_AN_RUN1,
	EN_AN_RUN2,
	EN_AN_RUN3,
	EN_AN_RUN4,
	EN_AN_RUN5,
	EN_AN_RUN6,
	EN_AN_RUN7,
	EN_AN_RUN8,
	EN_AN_RUN9,
	EN_AN_TWO_COMBO_ATTACK,
	EN_AN_DEATH,
	EN_AN_HURT,
	EN_AN_JUMP_UP_FALL,
	EN_AN_EDGE_GRAB,
	EN_AN_EDGE_IDLE,
	EN_AN_WALL_SIDE,
	EN_AN_CROUCH,
	EN_AN_DASH,
	EN_AN_DASH_ATTACH,
	EN_AN_SLIDE,
	EN_AN_LADDER_GRAB

};

class SpriteSheet : public Texture
{
public:
	SpriteSheet();
	~SpriteSheet();

	//Methods
	void Serialize(std::ostream& _stream) override;
	void Deserialize(std::istream& _stream) override;
	void ToString() override;

	void SetSize(byte _rows, byte _columns, byte _clipSizeX, byte clipSizeY);
	void AddAnimation(AnimationNames _name, short _clipStart, short _clipCount, float _clipSpeed);
	Rect Update(AnimationNames _name, float _deltaTime);
	int GetCurrentClip(AnimationNames _name);


	// New accessor and mutator for animation speed
	float GetAnimationSpeed(AnimationNames _name) const;
	void SetAnimationSpeed(AnimationNames _name, float newSpeed);

	// New method to get a specific SpriteAnim
	SpriteAnim* GetAnimation(AnimationNames name) {
		auto it = m_animations.find(name);
		if (it != m_animations.end()) {
			return it->second; // Return the pointer to the SpriteAnim
		}
		return nullptr; // Return nullptr if not found
	}


	//Members
	static ObjectPool<SpriteSheet>* Pool;

private:
	//Members
	byte m_rows;
	byte m_columns;
	byte m_clipSizeX;
	byte m_clipSizeY;
	map<AnimationNames, SpriteAnim*> m_animations;

};


#endif //SPRITESHEET_H

