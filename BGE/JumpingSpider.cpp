#include "JumpingSpider.h"


using namespace BGE;

JumpingSpider::JumpingSpider(void)
{

}


JumpingSpider::~JumpingSpider(void)
{

}

bool JumpingSpider::Initialise()
{
	physicsFactory->CreateGroundPhysics();
	physicsFactory->CreateCameraPhysics();
	setGravity(glm::vec3(0, -9, 0));

	CreateSpider();
	
	return Game::Initialise();
}

void JumpingSpider::Update(float timeDelta)
{

	Game::Update();
}

void JumpingSpider::Cleanup()
{
	Game::Cleanup();
}

shared_ptr<PhysicsController> JumpingSpider::CreateSpider()
{
	glm::vec3 position = glm::vec3(0, 10, 0);

	glm::vec3 offset;
	float width = 4;
	float height = 3;
	float length = 6;
	float turningAngle = glm::half_pi<float>() / 4;


	offset = glm::vec3(0, 0, length + 1);

	//body parts and legs
	shared_ptr<PhysicsController> forebody = physicsFactory->CreateBox(width, height, length, position, glm::quat());
	shared_ptr<PhysicsController> abdomen = physicsFactory->CreateBox(5, 4, 4, position + offset, glm::quat());

	btFixedConstraint* forebody_abdomen;

	//adding constraints to forebody
	btTransform transformA;
	btTransform transformB;

	transformA.setIdentity();
	transformB.setIdentity();
	transformA.setOrigin(btVector3(0, 0, length));
	transformB.setOrigin(btVector3(0, 0, 0));
	forebody_abdomen = new btFixedConstraint(*forebody->rigidBody, *abdomen->rigidBody, transformA, transformB);
	dynamicsWorld->addConstraint(forebody_abdomen);

	glm::quat qupper = glm::angleAxis(-45.0f, glm::vec3(0, 0, 1));
	glm::quat qlower = glm::angleAxis(45.0f, glm::vec3(0, 0, 1));

	position = glm::vec3(50,10,0);
	shared_ptr<PhysicsController> segment = physicsFactory->CreateBox(4, .5, .5, position, qupper);
	position = glm::vec3(55, 10, 0);
	//shared_ptr<PhysicsController> segment2 = physicsFactory->CreateBox(4, .5, .5, position, qlower);

	btVector3 bodyPivot = btVector3(1-width, 0, length / 4);
	btVector3 thighPivot = btVector3(2, 0, 0);

	btHingeConstraint*  hinge1 =
		new btHingeConstraint(*forebody->rigidBody, *segment->rigidBody, bodyPivot, thighPivot, btVector3(0, 1, 0), btVector3(-1, 1, 0), true);
	hinge1->setLimit(-turningAngle, turningAngle);
	dynamicsWorld->addConstraint(hinge1); 

	//btVector3 thighPivot2 = btVector3();
	//btVector3 calfPivot = btVector3();
	/*
	transformA.setIdentity();
	transformB.setIdentity();
	transformA.setOrigin(btVector3(2.5, 0,0));
	transformB.setOrigin(btVector3(-2.5, 0,0));

	btFixedConstraint* hinge2 =
		new btFixedConstraint(*segment->rigidBody,*segment2->rigidBody, transformA, transformB);
	dynamicsWorld->addConstraint(hinge2);
		/*


		transformA.setIdentity();
		transformB.setIdentity();

		transformA.setOrigin(btVector3(0, 0, 2));
		transformB.setOrigin(btVector3(3,0,2));
		ant_1_body_right_upper = new btPoint2PointConstraint(*forebody->rigidBody, *ant_right1_upper->rigidBody, btVector3(0,0,2), btVector3(3,0,2));
		dynamicsWorld->addConstraint(ant_1_body_right_upper);
	/*
	 * The Spider has a lower and upper leg on each leg
	 * 2 pairs of Anterior legs
	 * 2 pairs of posterior legs
	 *
	 
	//8 legs, 8 hinges between 16 segments
	btHingeConstraint* ant_1_left_upper_left_lower;
	btHingeConstraint* ant_1_right_upper_right_lower;
	btHingeConstraint* ant_2_left_upper_left_lower;
	btHingeConstraint* ant_2_right_upper_right_lower;
	btHingeConstraint* post_1_left_upper_left_lower;
	btHingeConstraint* post_1_right_upper_right_lower;
	btHingeConstraint* post_2_left_upper_left_lower;
	btHingeConstraint* post_2_right_upper_right_lower;

	// 8 ball and socket joints between the upper legs and the forebody
	btPoint2PointConstraint* ant_1_body_left_upper;
	btPoint2PointConstraint* ant_1_body_right_upper;
	btPoint2PointConstraint* ant_2_body_left_upper;
	btPoint2PointConstraint* ant_2_body_right_upper;
	btPoint2PointConstraint* post_1_body_left_upper;
	btPoint2PointConstraint* post_1_body_right_upper;
	btPoint2PointConstraint* post_2_body_left_upper;
	btPoint2PointConstraint* post_2_body_right_upper;
	
	

	//for abdomen
	offset = glm::vec3(0, 0 , length + 1);

	//body parts and legs
	shared_ptr<PhysicsController> forebody = physicsFactory->CreateBox(width, height, length, position, glm::quat());
	shared_ptr<PhysicsController> abdomen = physicsFactory->CreateBox(5, 4, 4, position+offset, glm::quat());

	*/
	
	// Upper and lower legs
	//shared_ptr<PhysicsController> segment = physicsFactory->CreateBox(.5,.5,4, position, glm::quat());
	/*
	shared_ptr<PhysicsController> ant_left1_upper;
	shared_ptr<PhysicsController> ant_left2_upper;
	shared_ptr<PhysicsController> ant_right1_upper;
	shared_ptr<PhysicsController> ant_right2_upper;
	shared_ptr<PhysicsController> post_left1_upper;
	shared_ptr<PhysicsController> post_left2_upper;
	shared_ptr<PhysicsController> post_right1_upper;
	shared_ptr<PhysicsController> post_right2_upper;

	shared_ptr<PhysicsController> ant_left1_lower;
	shared_ptr<PhysicsController> ant_left2_lower;
	shared_ptr<PhysicsController> ant_right1_lower;
	shared_ptr<PhysicsController> ant_right2_lower;
	shared_ptr<PhysicsController> post_left1_lower;
	shared_ptr<PhysicsController> post_left2_lower;
	shared_ptr<PhysicsController> post_right1_lower;
	shared_ptr<PhysicsController> post_right2_lower;
	*/
	//vector<shared_ptr<PhysicsController>> limbs;
	/*for (int i = 0; i < 16; i++) {*/
	
		//segment->transform->Roll(45.0f);
		//segment->transform->position.y = 2.0f;
		/*limbs.push_back(segment);
	}*/

	return forebody;
}
