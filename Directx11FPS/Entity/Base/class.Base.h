#pragma once
#include <typeinfo>

// Pridaj dalsie podcasti
#include "Entity.Physics.h"
#include "Entity.Features.h"

namespace Entity {

class Base : 
	public IPhysics, 
	public IDestroyable,
	public IAnimateable
{
protected:
	// Callbacky
	virtual void Destroyed() { }
	virtual void GoOutside() { } // Objekt sa dostane mimo sveta
	virtual void Spawn() { }

public:
	// Pomocky
	const char* getName() { return typeid(*this).name(); }
	virtual void Draw() {}
	virtual void Debug() { }
	virtual void DebugDraw() {
		// Pri debugu ..
		Shapes::Base *a = this->getShape();
		a->Draw();
		a->DrawSustavu(1.f);

		// Vykreslujeme aj zltou farbou vector, smer pohybu ...
		//if(gEntity[ent].velocity != 0.0f) {
		//	vec w = gEntity[ent].velocity / 10.0f;
		//	Draw::Vector(&gEntity[ent].construct.origin, &w);
		//}
	}


	~Base() { 
		Destroyed(); 
	};
};


}


