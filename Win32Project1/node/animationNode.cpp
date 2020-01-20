#include "animationNode.h"
#include "../render/animationDrawcall.h"
#include "../util/util.h"
#include "../scene/scene.h"
#include <string.h>

AnimationNode::AnimationNode(const vec3& boundingSize):
		Node(vec3(0, 0, 0), boundingSize) {
	animation = NULL;
	type = TYPE_ANIMATE;
}

AnimationNode::~AnimationNode() {}

void AnimationNode::setAnimation(Scene* scene, Animation* anim) {
	animation = anim;
	addObject(scene, new AnimationObject(animation));
}

void AnimationNode::prepareDrawcall() {
	if(drawcall) delete drawcall;
	drawcall = new AnimationDrawcall(animation);
	needCreateDrawcall = false;
}

void AnimationNode::updateDrawcall() {
	needUpdateDrawcall = false;
}

void AnimationNode::updateRenderData() {
}

void AnimationNode::animate(int animIndex,long startTime,long currentTime) {
	animation->bonesTransform(animIndex, (float)(currentTime - startTime)*0.001f);
}

AnimationObject* AnimationNode::getObject() {
	if (objects.size() > 0)
		return (AnimationObject*)objects[0];
	return NULL;
}

void AnimationNode::translateNodeCenterAtWorld(float x, float y, float z) {
	vec3 beforeWorldCenter = boundingBox->position;
	vec3 offset = vec3(x, y, z) - beforeWorldCenter;
	vec3 dPosition = position + offset;
	translateNode(dPosition.x, dPosition.y, dPosition.z);
}

void AnimationNode::translateNode(float x, float y, float z) {
	position.x = x, position.y = y, position.z = z;

	recursiveTransform(nodeTransform);
	updateNodeObject(objects[0], true, false);

	boundingBox->update(GetTranslate(nodeTransform));
	Node* superior = parent;
	while (superior) {
		superior->updateBounding();
		superior = superior->parent;
	}
}

void AnimationNode::rotateNodeObject(float ax, float ay, float az) {
	AnimationObject* object = (AnimationObject*)objects[0];
	object->setRotation(ax, ay, az);
	updateNodeObject(objects[0], false, true);
}
