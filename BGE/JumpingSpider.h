#pragma once
#include "Game.h"
#include "PhysicsController.h"
#include "PhysicsFactory.h"
#include <btBulletDynamicsCommon.h>

namespace BGE
{
	class JumpingSpider :
		public Game
	{
	public:
		JumpingSpider(void);
		~JumpingSpider(void);
		bool Initialise();
		void Update(float timeDelta);
		void Cleanup();

		shared_ptr<PhysicsController> CreateSpider();
		shared_ptr<PhysicsController> spider;
		shared_ptr<PhysicsController> forebody;
		shared_ptr<PhysicsController> abdomen;
		shared_ptr<PhysicsController> leg_thigh;
		shared_ptr<PhysicsController> leg_calf;
	};
}


