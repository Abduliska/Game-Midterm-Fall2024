#ifndef SPRITEANIM_H
#define SPRITEANIM_H

#include "Resource.h"

class SpriteAnim : Resource
{
public:
    // Constructors/Destructors
    SpriteAnim();
    virtual ~SpriteAnim();

    // Accessors
    short GetClipCurrent() { return (short)m_clipCurrent; }

    // Methods
    virtual void Serialize(std::ostream& _stream);
    virtual void Deserialize(std::istream& _stream);
    virtual void ToString();

    void ClearMemory();
    void Create(short _clipStart, short _clipCount, float _clipSpeed);
    void Update(float _deltaTime);

    // Members
    static ObjectPool<SpriteAnim>* Pool;//manage instances of SpriteAnim objects. reuse and reduce memory allocation overhead

private:
    // Members
    short m_clipStart;   // Starting clip index
    short m_clipCount;   // Number of clips
    float m_clipCurrent; // Current clip index
    float m_clipSpeed;   // Speed of animation
    short m_clipEnd;     // Ending clip index
};

#endif // SPRITEANIM_H
