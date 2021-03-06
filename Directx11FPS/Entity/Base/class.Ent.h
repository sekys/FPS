#ifndef H_Entity
#define H_Entity
#include <string>
#include "class.EntPhysics.h"
//#include "../../Help/Base/class.DynArray.h"
using namespace std;


class Entity : public EntPhysics
{
	virtual void Destroyed() { }

public :
	virtual const char* getName() {  return "Base"; }
	virtual void Draw() { }
	virtual void DebugDraw();
	virtual void Debug() { }
	
	~Entity() { 
		Destroyed(); 
		//EntPhysics::~EntPhysics();
	};
};

inline void Entity::DebugDraw()
{
	// Pri debugu ..
	Shape::Base *a = this->getShape();
	a->Draw();
	a->DrawSustavu();

	// Vykreslujeme aj zltou farbou vector, smer pohybu ...
	/*if(gEntity[ent].velocity != 0.0f) {
		vec w = gEntity[ent].velocity / 10.0f;
		Draw::Vector(&gEntity[ent].construct.origin, &w);
	}*/
}

/*
// Pomocne vlastnosti
string classname;
short class_type;
float hp;
bool take_dmg;

// Animacia 
string model;
float anim_speed;
int anim_type;

// Funkcie
virtual COLL TestCollision(Entity *ent, COLL predtym);
virtual void DMG(Entity *ent, float dmg, DMGT typ);

virtual void Kill();
virtual void Spawn();
virtual void RoundStart();
virtual void RoundEnd();
virtual void Connect(); // ripoji sa alebo uplne vznikne alebo spusta server
virtual void Disconnect();
virtual void GoOutside();
*/

#endif


